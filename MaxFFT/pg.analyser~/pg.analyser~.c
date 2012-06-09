#include "pg.analyser.h"

int main()
{
	t_class *c;

	common_symbols_init();

	c = class_new("pg.analyser~", (method)analyser_new, (method)analyser_free, (short)sizeof(t_analyser), 0L, A_GIMME, 0);

	class_addmethod(c, (method)analyser_dsp64,		"dsp64",		A_CANT, 0);
	class_addmethod(c, (method)analyser_assist,		"assist",		A_CANT,	0);
	
	fft(c);
	basic(c);
	amplitude(c);
	power(c);
	energy(c);

	class_dspinit(c);
	class_register(CLASS_BOX, c);
	analyser_class = c;

	post("pg.analyser~ by Pierre Guillot v1.0",0);
	post("Universite Paris 8, France",0);
	
	return 0;
}

void *analyser_new(t_symbol *s, int argc, t_atom *argv)
{
	int i;
	t_analyser *x = NULL;

	if(x = (t_analyser *)object_alloc((t_class *)analyser_class))
	{
		x->f_outlet = 0;
		for(i = 0; i < 17; i++)
		{
			x->f_analysis[i] = 0.;
			x->f_mode[i] = 0;
			x->f_modePos[i] = 0;
			x->f_posMode[i] = 0;
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

				/* FFt initialization ***********************/
	x->f_fft = (t_fft *)getbytes(x->f_overlapping  * sizeof(t_fft));
	for(i = 0; i < x->f_overlapping; i++)
		fft_setup(&x->f_fft[i], x->f_windowSize, i, x->f_overlapping);
	x->f_arraySize = x->f_windowSize/2;
	window_setup(&x->f_env, x->f_windowSize, x->f_env.f_mode);

	x->f_rapportSize = x->f_sr / (t_sample)x->f_windowSize;

	object_method(dsp64, gensym("dsp_add64"), x, analyser_perform64, 0, NULL);
}

void analyser_perform64(t_analyser *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	int i, j, k;
	t_double	amplitude, power, logAmp;
	t_double	frequency, rapport;
    t_double	*in = ins[0];
	t_double	**out  = outs;
	
	for(i = 0; i < x->f_overlapping; i++)
	{
		for(j = 0; j < sampleframes; j++)
		{
			x->f_fft[i].f_real[x->f_fft[i].f_ramp] = in[j] * x->f_env.f_envelope[x->f_fft[i].f_ramp];

			if (x->f_fft[i].f_ramp < x->f_arraySize && x->f_fft[i].f_ramp > 0)
			{
				/* Echelles d'amplitudes */
				power = ((x->f_fft[i].f_complex[x->f_fft[i].f_ramp][0] * x->f_fft[i].f_complex[x->f_fft[i].f_ramp][0]) + (x->f_fft[i].f_complex[x->f_fft[i].f_ramp][1] * x->f_fft[i].f_complex[x->f_fft[i].f_ramp][1]));
				amplitude = x->f_rapportSize * sqrt(power);
				logAmp = 20. * (log10(amplitude));
				if (logAmp < -90.) logAmp = -90.;

				frequency = x->f_fft[i].f_ramp * x->f_rapportSize;
				rapport = frequency - x->f_analysis[0];

				x->f_fft[i].f_sumAmp	+= power;
				if(power < x->f_fft[i].f_minAmp) x->f_fft[i].f_minAmp = power;
				if(power > x->f_fft[i].f_maxAmp) x->f_fft[i].f_maxAmp = power;

				x->f_fft[i].f_centroid	+= power * frequency;
				x->f_fft[i].f_spread	+= power * (rapport * rapport);
				x->f_fft[i].f_skewness	+= power * (rapport * rapport * rapport);
				x->f_fft[i].f_kurtosis	+= power * (rapport * rapport * rapport * rapport);
			}
			else if (x->f_fft[i].f_ramp == x->f_arraySize)
			{
				if(x->f_fft[i].f_sumAmp != 0.)
				{
					x->f_analysis[5]	= x->f_fft[i].f_minAmp;
					x->f_analysis[6]	= x->f_fft[i].f_maxAmp;
					x->f_analysis[7]	= x->f_fft[i].f_sumAmp / (t_sample)x->f_arraySize;
					x->f_analysis[8]	= x->f_fft[i].f_sumAmp;

					x->f_analysis[0]	= x->f_fft[i].f_centroid  / x->f_analysis[8];
					x->f_analysis[1]	= x->f_fft[i].f_spread	  / x->f_analysis[8];
					x->f_analysis[2]	= sqrt(x->f_analysis[1]);
					x->f_analysis[3]	= (x->f_fft[i].f_skewness / x->f_analysis[8]) / (x->f_analysis[1] * x->f_analysis[2]);
					x->f_analysis[4]	= (x->f_fft[i].f_kurtosis / x->f_analysis[8]) / (x->f_analysis[1] * x->f_analysis[1]);
				}
				else
				{
					for(k = 0; k < 17; k++)
						x->f_analysis[k] = 0.;
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
		for(k = 0; k < x->f_outlet; k++)
		{
			out[k][j] = x->f_analysis[x->f_posMode[k]];
		}
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

