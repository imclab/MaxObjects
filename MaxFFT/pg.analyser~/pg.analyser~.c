#include "pg.analyser.h"

int main()
{
	t_class *c;

	c = class_new("pg.analyser~", (method)analyser_new, (method)analyser_free, (short)sizeof(t_analyser), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)analyser_dsp64,		"dsp64",		A_CANT, 0);
	class_addmethod(c, (method)analyser_assist,		"assist",		A_CANT,	0);
	
	class_dspinit(c);
	class_register(CLASS_BOX, c);
	analyser_class = c;
	/*
	CLASS_ATTR_LONG				(c, "windowsize", 0, t_analyser, f_windowSize);
	CLASS_ATTR_LABEL			(c, "windowsize", 0, "Window Size");
	CLASS_ATTR_ACCESSORS		(c, "windowsize", NULL, window_size_set);
	CLASS_ATTR_FILTER_MIN		(c, "windowsize", 2);
	CLASS_ATTR_DEFAULT			(c, "windowsize", 0, "2048");
	CLASS_ATTR_SAVE				(c, "windowsize", 1);
	CLASS_ATTR_ORDER			(c, "windowsize", 0, "1");

	CLASS_ATTR_LONG				(c, "overlapping", 0, t_analyser, f_overlapping);
	CLASS_ATTR_LABEL			(c, "overlapping", 0, "Overlapping");
	CLASS_ATTR_ACCESSORS		(c, "overlapping", NULL, overlapping_set);
	CLASS_ATTR_FILTER_MIN		(c, "overlapping", 1);
	CLASS_ATTR_DEFAULT			(c, "overlapping", 0, "4");
	CLASS_ATTR_SAVE				(c, "overlapping", 1);
	CLASS_ATTR_ORDER			(c, "overlapping", 0, "3");
	*/
	
	CLASS_ATTR_LONG				(c, "window", 0, t_analyser, f_modEnv);
	CLASS_ATTR_LABEL			(c, "window", 0, "Window function");
	CLASS_ATTR_ENUMINDEX		(c, "window", 0, "Square \" \"Hanning \" \"Hamming \" \"Turkey \" \"Cosinus \" \"Lanczos \" \"Triangular \" \"Gaussian \" \"Bartlett-Hann \" \"Blackman \" \"Kaiser \" \"Nuttall \" \"Blackman-Harris \" \"Blackman-Nuttall \" \"Flat-Top \" \"Poisson");
	CLASS_ATTR_ACCESSORS		(c, "window", NULL, mode_set);
	CLASS_ATTR_DEFAULT			(c, "window", 0, "0");
	CLASS_ATTR_SAVE				(c, "window", 1);
	CLASS_ATTR_FILTER_CLIP		(c, "window", 0, 10);
	CLASS_ATTR_ORDER			(c, "window", 0, "1");

	basic(c);
	amplitude(c);
	power(c);
	energy(c);

	post("pg.analyser~ by Pierre Guillot v1.0",0);
	post("Universite Paris 8, France",0);
	
	return 0;
}

void *analyser_new(t_symbol *s, int argc, t_atom *argv)
{
	t_analyser *x = NULL;
	int i;
	t_atom mode[1];
	if(x = (t_analyser *)object_alloc((t_class *)analyser_class))
	{
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
		if( argv[2].a_type == A_LONG ) x->f_modEnv = argv[2].a_w.w_long;
		if (x->f_modEnv < 0 || x->f_modEnv > 15)
		{
			x->f_modEnv = 1;
			object_post((t_object*)x, "Wrong enveloppe, set to default : 1 (Hanning)");
		}
		window_setup(&x->f_env, x->f_windowSize, x->f_modEnv);
		x->f_rapportSize = x->f_sr / (t_sample)x->f_windowSize;

			/* FFt initialization ***********************/
		x->f_fft = (t_fft *)getbytes(x->f_overlapping  * sizeof(t_fft));
		for(i = 0; i < x->f_overlapping; i++)
			fft_setup(&x->f_fft[i], x->f_windowSize, i, x->f_overlapping);
		x->f_arraySize = x->f_windowSize/2;
		window_setup(&x->f_env, x->f_windowSize, x->f_modEnv);
		x->f_rapportSize = x->f_sr / (t_sample)x->f_windowSize;

		x->f_centroid	= 0.;
		x->f_spread		= 0.;
		x->f_deviation	= 0.;
		x->f_skewness	= 0.;
		x->f_kurtosis	= 0.;

		x->f_outlet = 0;
		for(i = 0; i < 6; i++)
		{
			x->f_mode[i] = 0;
			x->f_modePos[i] = -1;
		}

		dsp_setup((t_pxobject *)x, 1);
		attr_args_process(x, argc, argv);
	}
	return (x);
}			

void analyser_dsp64(t_analyser *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	int i;
	x->f_sr = samplerate;
	x->f_sb = maxvectorsize;
	x->f_rapportSize = x->f_sr / (t_sample)x->f_windowSize;

	object_method(dsp64, gensym("dsp_add64"), x, analyser_perform64, 0, NULL);
}

void analyser_perform64(t_analyser *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	int i, j;
	t_double amplitude, frequency, rapport;
    t_double	*in = ins[0];
	t_double	**out  = outs;
	
	for(i = 0; i < x->f_overlapping; i++)
	{
		for(j = 0; j < sampleframes; j++)
		{
			x->f_fft[i].f_real[x->f_fft[i].f_ramp] = in[j] * x->f_env.f_envelope[x->f_fft[i].f_ramp];

			if (x->f_fft[i].f_ramp < x->f_arraySize && x->f_fft[i].f_ramp > 0)
			{
				amplitude = ((x->f_fft[i].f_complex[x->f_fft[i].f_ramp][0] * x->f_fft[i].f_complex[x->f_fft[i].f_ramp][0]) + (x->f_fft[i].f_complex[x->f_fft[i].f_ramp][1] * x->f_fft[i].f_complex[x->f_fft[i].f_ramp][1]));
				frequency = x->f_fft[i].f_ramp * x->f_rapportSize;
				rapport = frequency - x->f_centroid;

				x->f_fft[i].f_sumAmp	+= amplitude;

				x->f_fft[i].f_centroid	+= amplitude * frequency;
				x->f_fft[i].f_spread	+= amplitude * (rapport * rapport);
				x->f_fft[i].f_skewness	+= amplitude * (rapport * rapport * rapport);
				x->f_fft[i].f_kurtosis	+= amplitude * (rapport * rapport * rapport * rapport);
			}
			else if (x->f_fft[i].f_ramp == x->f_arraySize)
			{
				if(x->f_fft[i].f_sumAmp != 0.f)
				{
					x->f_centroid	= x->f_fft[i].f_centroid	/ x->f_fft[i].f_sumAmp;
					x->f_spread		= x->f_fft[i].f_spread		/ x->f_fft[i].f_sumAmp;
					x->f_deviation	= sqrt(x->f_spread);
					x->f_skewness	= (x->f_fft[i].f_skewness	/ x->f_fft[i].f_sumAmp) / (x->f_spread * x->f_deviation);
					x->f_kurtosis	= (x->f_fft[i].f_kurtosis	/ x->f_fft[i].f_sumAmp) / (x->f_spread * x->f_spread);
				}
				else
				{
					x->f_centroid	= 0.f;
					x->f_spread		= 0.f;
					x->f_deviation	= 0.f;
					x->f_skewness	= 0.f;
					x->f_kurtosis	= 0.f;
				}
				x->f_fft[i].f_sumAmp	= 0.f;
				x->f_fft[i].f_centroid	= 0.f;
				x->f_fft[i].f_spread	= 0.f;
				x->f_fft[i].f_skewness	= 0.f;
				x->f_fft[i].f_kurtosis	= 0.f;
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
		if(x->f_mode[0])
			out[x->f_modePos[0]][j] = x->f_centroid;
		if(x->f_mode[1])
			out[x->f_modePos[1]][j] = x->f_spread;
		if(x->f_mode[2])
			out[x->f_modePos[2]][j] = x->f_deviation;
		if(x->f_mode[3])
			out[x->f_modePos[3]][j] = x->f_skewness;
		if(x->f_mode[4])
			out[x->f_modePos[4]][j] = x->f_kurtosis;
	}
}

void analyser_free(t_analyser *x)
{
	int i;
	dsp_free((t_pxobject *)x);
	/*
	for(i = 0; i < x->f_overlapping; i++)
		fft_free(&x->f_fft[i]);
		*/
	freebytes(x->f_fft, x->f_overlapping * sizeof(t_fft));
	window_free(&x->f_env);
	
}

void analyser_assist(t_analyser *x, void *b, long m, long a, char *s)
{
	int i;
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

		if(a == x->f_modePos[0])
			sprintf(s,"(Signal) Centroid");
		else if(a == x->f_modePos[1])
			sprintf(s,"(Signal) Spread");
		else if(a == x->f_modePos[2])
			sprintf(s,"(Signal) Standard Deviation");
		else if(a == x->f_modePos[3])
			sprintf(s,"(Signal) Skewness");
		else if(a == x->f_modePos[4])
			sprintf(s,"(Signal) Kurtosis");
	}
}


t_max_err mode_set(t_analyser *x, t_object *attr, long argc, t_atom *argv)
{
	window_mode_set(&x->f_env, attr, argc, argv);
	return 0;
}

t_max_err overlapping_set(t_analyser *x, t_object *attr, long argc, t_atom *argv)
{
	t_object *patcher;
	object_obex_lookup(x, gensym("#P"), &patcher);
	if ( atom_gettype(argv) == A_LONG)
	{
		if(atom_getlong(argv) != x->f_overlapping)
		{
			dspchain_setbroken(x->myDspChain);
			x->f_overlapping = atom_getlong(argv);
		}
	}
	return 0;
}

t_max_err window_size_set(t_analyser *x, t_object *attr, long argc, t_atom *argv)
{
	if ( atom_gettype(argv) == A_LONG)
	{
		if(atom_getlong(argv) != x->f_windowSize)
		{
			dspchain_setbroken(x->myDspChain);
			x->f_windowSize = atom_getlong(argv);
		}
	}
	return 0;
}

t_max_err analyser_notify(t_analyser *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
	t_symbol *name;
	if (msg == gensym("attr_modified"))
	{
		name = (t_symbol *)object_method((t_object *)data, gensym("getname"));
		
		if(name == gensym("overlapping") || gensym("windowsize"))
		{
			canvas_stop_dsp();
		}
	}
	return object_notify((t_pxobject *)x, s, data);
}


void analyser_redefine_outlets(t_analyser *x, int pos)
{
	int i;
	for(i = 0; i < 5; i++)
	{
		if(x->f_modePos[i] >= pos) x->f_modePos[i]--;
	}
}