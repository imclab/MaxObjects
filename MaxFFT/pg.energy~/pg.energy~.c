/*
* Copyright (C) 2012 Pierre Guillot, Universite Paris 8
* 
* This library is free software; you can redistribute it and/or modify it 
* under the terms of the GNU Library General Public License as published 
* by the Free Software Foundation; either version 2 of the License.
* 
* This library is distributed in the hope that it will be useful, but WITHOUT 
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
* FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public 
* License for more details.
*
* You should have received a copy of the GNU Library General Public License 
* along with this library; if not, write to the Free Software Foundation, 
* Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*
* guillotpierre6@gmail.com
*/

#include "pg.energy.h"

int main()
{
	t_class *c = class_new("pg.energy~", (method)energy_new, (method)energy_free, (long)sizeof(t_energy), 0L, A_GIMME, 0);
	class_addmethod(c, (method)energy_dsp64,		"dsp64",		A_CANT,	0);
	class_addmethod(c, (method)energy_dsp,			"dsp",			A_CANT,	0);
	class_addmethod(c, (method)energy_assist,		"assist",		A_CANT,	0);
	
	CLASS_ATTR_LONG				(c, "window", 0, t_energy, f_winMode);
	CLASS_ATTR_LABEL			(c, "window", 0, "Window function");
	CLASS_ATTR_ENUMINDEX		(c, "window", 0, "Square \" \"Hanning \" \"Hamming \" \"Tukey \" \"Cosinus \" \"Lanczos \" \"Triangular \" \"Gaussian \" \"Bartlett-Hann \" \"Blackman \" \"Kaiser \" \"Nuttall \" \"Blackman-Harris \" \"Blackman-Nuttall \" \"Flat-Top \" \"Poisson");
	CLASS_ATTR_ACCESSORS		(c, "window", NULL, mode_set);
	CLASS_ATTR_DEFAULT			(c, "window", 0, "0");
	CLASS_ATTR_SAVE				(c, "window", 1);
	CLASS_ATTR_FILTER_CLIP		(c, "window", 0, 10);
	CLASS_ATTR_ORDER			(c, "window", 0, "1");
	
	CLASS_ATTR_LONG				(c, "amplitude", 0, t_energy, f_ampMode);
	CLASS_ATTR_LABEL			(c, "amplitude", 0, "Amplitude mode");
	CLASS_ATTR_ENUMINDEX		(c, "amplitude", 0, "RMS \" \"Power \" \"Energy");
	CLASS_ATTR_DEFAULT			(c, "amplitude", 0, "0");
	CLASS_ATTR_SAVE				(c, "amplitude", 1);
	CLASS_ATTR_FILTER_CLIP		(c, "amplitude", 0, 2);
	CLASS_ATTR_ORDER			(c, "amplitude", 0, "1");
	
	class_dspinit(c);
	class_register(CLASS_BOX, c);
	energy_class = c;

	post("pg.energy~ by Pierre Guillot",0);
	post("Copyright (C) 2012, Universite Paris 8");
	
	return 0;
}

void *energy_new(t_symbol *s, long argc, t_atom *argv)
{
	t_energy *x = NULL;
		
	if(x = (t_energy *)object_alloc(energy_class))
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
		x->f_winMode = 1;
		if( argv[2].a_type == A_LONG ) x->f_winMode = argv[2].a_w.w_long;
		if (x->f_winMode < 0 || x->f_winMode > 15)
		{
			x->f_winMode = 1;
			object_post((t_object*)x, "Wrong window initialization, set to default : 1");
		}
		window_setup(&x->f_env, x->f_windowSize, x->f_winMode);

		x->f_min	= 0.;
		x->f_max	= 0.;
		x->f_ave	= 0.;
		x->f_sum	= 0.;
		
		dsp_setup((t_pxobject *)x, 1);
		outlet_new((t_pxobject *)x, "signal");
		outlet_new((t_pxobject *)x, "signal");
		outlet_new((t_pxobject *)x, "signal");
		outlet_new((t_pxobject *)x, "signal");
		x->f_ampMode = 0;
		attr_args_process(x, argc, argv);
	}
	return (x);
}			

void energy_dsp64(t_energy *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	int i;
	x->f_sr = samplerate;
	x->f_rapportSize	= (double)(PI * (1. / (double)x->f_arraySize));

	/* FFt initialization ***********************/
	x->f_fft = (t_fft *)getbytes(x->f_overlapping  * sizeof(t_fft));
	for(i = 0; i < x->f_overlapping; i++)
	{
		fft_setup(&x->f_fft[i], x->f_windowSize, i, x->f_overlapping);
	}
	object_method(dsp64, gensym("dsp_add64"), x, energy_perform64, 0, NULL);
}

void energy_perform64(t_energy *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	int i, j;
	double amplitude;
    double	*in		= ins[0];
    double	*out1	= outs[0];
	double	*out2	= outs[1];
	double	*out3	= outs[2];
	double	*out4	= outs[3];
	
	for(i = 0; i < x->f_overlapping; i++)
	{
		for(j = 0; j < sampleframes; j++)
		{
			x->f_fft[i].f_real[x->f_fft[i].f_ramp] = in[j] * x->f_env.f_envelope[x->f_fft[i].f_ramp];

			if (x->f_fft[i].f_ramp < x->f_arraySize && x->f_fft[i].f_ramp > 0)
			{
				amplitude = x->f_rapportSize * sqrt((x->f_fft[i].f_complex[x->f_fft[i].f_ramp][0] * x->f_fft[i].f_complex[x->f_fft[i].f_ramp][0]) + (x->f_fft[i].f_complex[x->f_fft[i].f_ramp][1] * x->f_fft[i].f_complex[x->f_fft[i].f_ramp][1]));
				if(x->f_ampMode != 1)
				{
					x->f_fft[i].f_sum	+= amplitude;
				}
				else
				{
					amplitude *= amplitude;
					x->f_fft[i].f_sum	+= amplitude;
				}
				if(amplitude < x->f_fft[i].f_min) x->f_fft[i].f_min = amplitude;
				if(amplitude > x->f_fft[i].f_max) x->f_fft[i].f_max = amplitude;

			}
			else if (x->f_fft[i].f_ramp == x->f_arraySize)
			{
				x->f_min	= x->f_fft[i].f_min;
				x->f_max	= x->f_fft[i].f_max;
				x->f_sum	= x->f_fft[i].f_sum;
				x->f_ave	= x->f_sum / (double)x->f_arraySize;
				if(x->f_ampMode == 2)
				{
					x->f_min	= 20. * log10(x->f_min);
					if (x->f_min < -90.f) x->f_min = -90.;
					x->f_ave	= 20. * log10(x->f_ave);
					if (x->f_ave < -90.f) x->f_ave = -90.;
					x->f_max	= 20. * log10(x->f_max);
					if (x->f_max < -90.f) x->f_max = -90.;
					x->f_sum	= 20. * log10(x->f_sum);
					if (x->f_sum < -90.f) x->f_sum = -90.;
				}

				x->f_fft[i].f_min = 300.;
				x->f_fft[i].f_max = -300.;
				x->f_fft[i].f_sum = 0.;
				
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
		out1[j] = x->f_min;
		out2[j] = x->f_ave;
		out3[j] = x->f_max;
		out4[j] = x->f_sum;
	}
}

void energy_free(t_energy *x)
{
	dsp_free((t_pxobject *)x);
	window_free(&x->f_env);
}

void energy_assist(t_energy *x, void *b, long m, long a, char *s)
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
				sprintf(s,"(Signal) Minimum");
				break;
			case 1:
				sprintf(s,"(Signal) Average");
				break;
			case 2:
				sprintf(s,"(Signal) Maximum");
				break;
			case 3:
				sprintf(s,"(Signal) Sum");
				break;
		}
	}
}


t_max_err mode_set(t_energy *x, t_object *attr, long argc, t_atom *argv)
{
	window_mode_set(&x->f_env, attr, argc, argv);
	x->f_winMode = x->f_env.f_mode;
	return 0;
}


void energy_dsp(t_energy *x, t_signal **sp, short *count)
{
	int i;
	x->f_sr = (double)sp[0]->s_sr;
	x->f_rapportSize	= (double)(PI * (1. / (double)x->f_arraySize));

	/* FFt initialization ***********************/
	x->f_fft = (t_fft *)getbytes(x->f_overlapping  * sizeof(t_fft));
	for(i = 0; i < x->f_overlapping; i++)
	{
		fft_setup(&x->f_fft[i], x->f_windowSize, i, x->f_overlapping);
	}

	dsp_add(energy_perform, 7, x, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, 
		sp[3]->s_vec, sp[4]->s_vec, sp[0]->s_n);
}


t_int *energy_perform(t_int *w)
{	
	t_energy	*x		= (t_energy *)(w[1]);
	float	*in		= (float *)	(w[2]);
	float	*out1	= (float *)	(w[3]);
	float	*out2	= (float *)	(w[4]);
	float	*out3	= (float *)	(w[5]);
	float	*out4	= (float *)	(w[6]);
	int n				= (int)			(w[7]);

	double amplitude;
	int i, j;
	if (x->f_ob.z_disabled) return w + 8;

	for(i = 0; i < x->f_overlapping; i++)
	{
		for(j = 0; j < n; j++)
		{
			x->f_fft[i].f_real[x->f_fft[i].f_ramp] = in[j] * x->f_env.f_envelope[x->f_fft[i].f_ramp];

			if (x->f_fft[i].f_ramp < x->f_arraySize && x->f_fft[i].f_ramp > 0)
			{
				amplitude = x->f_rapportSize * sqrt((x->f_fft[i].f_complex[x->f_fft[i].f_ramp][0] * x->f_fft[i].f_complex[x->f_fft[i].f_ramp][0]) + (x->f_fft[i].f_complex[x->f_fft[i].f_ramp][1] * x->f_fft[i].f_complex[x->f_fft[i].f_ramp][1]));
				if(x->f_ampMode == 0)
				{
					x->f_fft[i].f_sum	+= amplitude;
				}
				else if(x->f_ampMode == 1)
				{
					amplitude *= amplitude;
					x->f_fft[i].f_sum	+= amplitude;
				}
				else if(x->f_ampMode == 2)
				{
					amplitude = 20. * log10(amplitude);
					if (amplitude < -90.f) amplitude = -90.;
					x->f_fft[i].f_sum	+= pow(10., (amplitude / 10.));
				}
				if(amplitude < x->f_fft[i].f_min) x->f_fft[i].f_min = amplitude;
				if(amplitude > x->f_fft[i].f_max) x->f_fft[i].f_max = amplitude;
				

			}
			else if (x->f_fft[i].f_ramp == x->f_arraySize)
			{
				x->f_min	= x->f_fft[i].f_min;
				x->f_max	= x->f_fft[i].f_max;
				x->f_sum	= x->f_fft[i].f_sum;
				if(x->f_ampMode == 2)
					x->f_ave	= 10. * log10(x->f_sum / (double)x->f_arraySize);
				else
				x->f_ave	= x->f_sum / (double)x->f_arraySize;


				x->f_fft[i].f_min = 300.;
				x->f_fft[i].f_max = -300.;
				x->f_fft[i].f_sum = 0.;
				
			}

			x->f_fft[i].f_ramp++;
			if (x->f_fft[i].f_ramp == x->f_windowSize)
			{
				fftw_execute(x->f_fft[i].f_plan);
				x->f_fft[i].f_ramp = 0;
			}
	
		}

	}

	for(j = 0; j < n; j++)
	{
		out1[j] = x->f_min;
		out2[j] = x->f_ave;
		out3[j] = x->f_max;
		out4[j] = x->f_sum;
	}
	return (w + 8);	
}
