#include "pg.gradient.h"

int main()
{
	t_class *c;

	c = class_new("pg.gradient~", (method)gradient_new, (method)gradient_free, (short)sizeof(t_gradient), 0L, A_GIMME, 0);
	class_addmethod(c, (method)gradient_dsp64,		"dsp64",		A_CANT,	0);
	class_addmethod(c, (method)gradient_assist,		"assist",		A_CANT,	0);

	CLASS_ATTR_LONG				(c, "window", 0, t_gradient, f_winMode);
	CLASS_ATTR_LABEL			(c, "window", 0, "Window function");
	CLASS_ATTR_ENUMINDEX		(c, "window", 0, "Square \" \"Hanning \" \"Hamming \" \"Turkey \" \"Cosinus \" \"Lanczos \" \"Triangular \" \"Gaussian \" \"Bartlett-Hann \" \"Blackman \" \"Kaiser \" \"Nuttall \" \"Blackman-Harris \" \"Blackman-Nuttall \" \"Flat-Top \" \"Poisson");
	CLASS_ATTR_ACCESSORS		(c, "window", NULL, mode_set);
	CLASS_ATTR_DEFAULT			(c, "window", 0, "0");
	CLASS_ATTR_SAVE				(c, "window", 1);
	CLASS_ATTR_FILTER_CLIP		(c, "window", 0, 10);
	CLASS_ATTR_ORDER			(c, "window", 0, "1");

	CLASS_ATTR_LONG				(c, "amplitude", 0, t_gradient, f_ampMode);
	CLASS_ATTR_LABEL			(c, "amplitude", 0, "Amplitude mode");
	CLASS_ATTR_ENUMINDEX		(c, "amplitude", 0, "RMS \" \"Power \" \"Energy");
	CLASS_ATTR_DEFAULT			(c, "amplitude", 0, "0");
	CLASS_ATTR_SAVE				(c, "amplitude", 1);
	CLASS_ATTR_FILTER_CLIP		(c, "amplitude", 0, 2);
	CLASS_ATTR_ORDER			(c, "amplitude", 0, "1");

	CLASS_ATTR_LONG				(c, "gradient", 0, t_gradient, f_mode);
	CLASS_ATTR_LABEL			(c, "gradient", 0, "Gradient mode");
	CLASS_ATTR_ENUMINDEX		(c, "gradient", 0, "Slope \" \"Decrease");
	CLASS_ATTR_DEFAULT			(c, "gradient", 0, "0");
	CLASS_ATTR_SAVE				(c, "gradient", 1);
	CLASS_ATTR_FILTER_CLIP		(c, "gradient", 0, 2);
	CLASS_ATTR_ORDER			(c, "gradient", 0, "1");

	class_dspinit(c);
	class_register(CLASS_BOX, c);
	gradient_class = c;

	post("pg.gradient~ by Pierre Guillot",0);
	post("Universite Paris 8, France",0);
	
	return 0;
}

void *gradient_new(t_symbol *s, int argc, t_atom *argv)
{
	t_gradient *x = (t_gradient *)object_alloc((t_class *)gradient_class);

	/* Sampling Rate initialization **************/
	x->f_sr = sys_getsr();

	/* Windows Size Initialization **************/
	x->f_windowSize = 0; 
	if( argv[0].a_type == A_LONG ) x->f_windowSize = (int)(argv[0].a_w.w_long);
	if (x->f_windowSize%2 != 0)
	{
		x->f_windowSize = 1024;
		object_post((t_object*)x, "Wrong window size initialization, set to default : 1024");
	}
	x->f_arraySize = x->f_windowSize/2;

	/* Overlapping Initialization ***************/
	x->f_overlapping = 0; 
	if( argv[1].a_type == A_LONG ) x->f_overlapping = (int)(argv[1].a_w.w_long);
	if (x->f_overlapping < 1)
	{
		x->f_overlapping = 2;
		object_post((t_object*)x, "Wrong overlapping initialization, set to default : 2");
	}
		
	/* Initialization of the window  ********************************/
	
	if( argv[2].a_type == A_LONG ) x->f_ampMode = argv[2].a_w.w_long;
	if (x->f_ampMode < 0 || x->f_ampMode > 15)
	{
		x->f_ampMode = 1;
		object_post((t_object*)x, "Wrong window initialization, set to default : 1");
	}
	window_setup(&x->f_env, x->f_windowSize, x->f_ampMode);

	x->f_gradient = 0.;
	dsp_setup((t_pxobject *)x, 1);
	outlet_new((t_pxobject *)x, "signal");

	x->f_ampMode = 0;
	attr_args_process(x, argc, argv);
	return (x);
}			

void gradient_dsp64(t_gradient *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	int i;
	x->f_sr = samplerate;
	x->f_rapportSize	= (double)(PI * (1. / (double)x->f_arraySize));
	x->f_rapportFreq	= (double)x->f_sr / (double)x->f_windowSize;
	/* FFt initialization ***********************/
	x->f_fft = (t_fft *)getbytes(x->f_overlapping  * sizeof(t_fft));
	for(i = 0; i < x->f_overlapping; i++)
	{
		fft_setup(&x->f_fft[i], x->f_windowSize, i, x->f_overlapping);
	}

	x->f_sumFreq = 0.;
	x->f_sumFreqCar = 0.;
	for(i = 0; i < x->f_arraySize; i++)
	{
		x->f_sumFreq += (double)i * x->f_rapportFreq;
		x->f_sumFreqCar += ((double)i * x->f_rapportFreq) * ((double)i * x->f_rapportFreq);
	}
	x->f_sumFreqCar *= (double)x->f_arraySize;
	x->f_sumFreqCar -= (x->f_sumFreq * x->f_sumFreq);

	object_method(dsp64, gensym("dsp_add64"), x, gradient_perform64, 0, NULL);
}

void gradient_perform64(t_gradient *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	int i, j;
	t_double amplitude, frequency, logAdd;
    t_double	*in		= ins[0];
    t_double	*out1	= outs[0];
	
	for(i = 0; i < x->f_overlapping; i++)
	{
		for(j = 0; j < sampleframes; j++)
		{
			x->f_fft[i].f_real[x->f_fft[i].f_ramp] = in[j] * x->f_env.f_envelope[x->f_fft[i].f_ramp];

			/* Slope */
			if(x->f_mode == 0)
			{
				if (x->f_fft[i].f_ramp < x->f_arraySize && x->f_fft[i].f_ramp > 0)
				{
					amplitude = x->f_rapportSize * sqrt((x->f_fft[i].f_complex[x->f_fft[i].f_ramp][0] * x->f_fft[i].f_complex[x->f_fft[i].f_ramp][0]) + (x->f_fft[i].f_complex[x->f_fft[i].f_ramp][1] * x->f_fft[i].f_complex[x->f_fft[i].f_ramp][1]));
					frequency = (t_double)x->f_fft[i].f_ramp * x->f_rapportFreq;
					
					if(x->f_ampMode == 0)
					{
						x->f_fft[i].f_sumAmp	+= amplitude;
						x->f_fft[i].f_sumFreq	+= amplitude * frequency;
					}
					else if(x->f_ampMode == 1)
					{
						amplitude *= amplitude;
						x->f_fft[i].f_sumAmp	+= amplitude;
						x->f_fft[i].f_sumFreq	+= amplitude * frequency;
					}
					else if(x->f_ampMode == 2)
					{
						amplitude = 20. * log10(amplitude);
						if (amplitude < -90.f) amplitude = -90.f;
						logAdd = pow(10., (amplitude / 10.));
						x->f_fft[i].f_sumAmp	+= logAdd;
						x->f_fft[i].f_sumFreq	+= logAdd * frequency;
					}
						
				}
				else if (x->f_fft[i].f_ramp == x->f_arraySize)
				{
					if(x->f_fft[i].f_sumAmp != 0.)
					{
						x->f_gradient = x->f_fft[i].f_sumFreq * (t_double)x->f_arraySize;
						x->f_gradient -= (x->f_sumFreq * x->f_fft[i].f_sumAmp);
						x->f_gradient /= x->f_sumFreqCar;
						x->f_gradient /= x->f_fft[i].f_sumAmp;
						x->f_gradient *= (t_sample)x->f_sr / 4.;
					}
					else 
					{
						x->f_gradient = 0.;
					}
					x->f_fft[i].f_sumAmp = 0.;
					x->f_fft[i].f_sumFreq = 0.;
				}
			}
			/* Decrease */
			else
			{
				if (x->f_fft[i].f_ramp < x->f_arraySize && x->f_fft[i].f_ramp > 0)
				{
					amplitude = x->f_rapportSize * sqrt((x->f_fft[i].f_complex[x->f_fft[i].f_ramp][0] * x->f_fft[i].f_complex[x->f_fft[i].f_ramp][0]) + (x->f_fft[i].f_complex[x->f_fft[i].f_ramp][1] * x->f_fft[i].f_complex[x->f_fft[i].f_ramp][1]));
					if(x->f_ampMode == 0)
					{
						if(x->f_fft[i].f_ramp == 1)
							x->f_fft[i].f_firstAmp = amplitude;
						else
						{
							x->f_fft[i].f_sumAmp	+= amplitude - x->f_fft[i].f_firstAmp;
							x->f_fft[i].f_sumFreq	+= amplitude * (t_sample)(x->f_fft[i].f_ramp - 1);
						}
					}
					else if(x->f_ampMode == 1)
					{
						amplitude *= amplitude;
						if(x->f_fft[i].f_ramp == 1)
							x->f_fft[i].f_firstAmp = amplitude;
						else
						{
							x->f_fft[i].f_sumAmp	+= amplitude - x->f_fft[i].f_firstAmp;
							x->f_fft[i].f_sumFreq	+= amplitude * (t_sample)(x->f_fft[i].f_ramp - 1);
						}
					}
					else if(x->f_ampMode == 2)
					{
						amplitude = 20. * log10(amplitude);
						if (amplitude < -90.f) amplitude = -90.f;
						logAdd = pow(10., (amplitude / 10.));
						
						if(x->f_fft[i].f_ramp == 1)
							x->f_fft[i].f_firstAmp = logAdd;
						else
						{
							x->f_fft[i].f_sumAmp	+= logAdd - x->f_fft[i].f_firstAmp;
							x->f_fft[i].f_sumFreq	+= logAdd * (t_sample)(x->f_fft[i].f_ramp - 1);
						}
					}
				}
				else if (x->f_fft[i].f_ramp == x->f_arraySize)
				{
					if(x->f_fft[i].f_sumFreq != 0.)
					{
						x->f_gradient = x->f_fft[i].f_sumAmp / x->f_fft[i].f_sumFreq;
					}
					else 
					{
						x->f_gradient = 0.;
					}
					x->f_fft[i].f_sumAmp = 0.;
					x->f_fft[i].f_sumFreq = 0.;
				}
			}

			x->f_fft[i].f_ramp++;
			if (x->f_fft[i].f_ramp == x->f_windowSize)
			{
				fftw_execute(x->f_fft[i].f_plan);
				x->f_fft[i].f_ramp = 0;
			}
	
		}

	}

	for(j = 0; j < sampleframes; j++)
	{
		out1[j] = x->f_gradient;
	}
}

void gradient_free(t_gradient *x)
{
	dsp_free((t_pxobject *)x);
	freebytes(x->f_fft, x->f_overlapping * sizeof(t_fft));
	window_free(&x->f_env);
}

void gradient_assist(t_gradient *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) 
	{
		switch (a) 
		{	
			case 0:
				sprintf(s,"(Signal) Input");
				break;
		}
	}
	else 
	{
		switch (a) 
		{	
			case 0:
				if(x->f_mode == 0)
					sprintf(s,"(Signal) Slope");
				else
					sprintf(s,"(Signal) Decrease");
				break;
		}
	}
}


t_max_err mode_set(t_gradient *x, t_object *attr, long argc, t_atom *argv)
{
	window_mode_set(&x->f_env, attr, argc, argv);
	x->f_ampMode = x->f_env.f_mode;
	return 0;
}
