#include "pg.analyser.h"

int main()
{
	t_class *c;

	c = class_new("pg.analyser~", (method)analyser_new, (method)analyser_free, (short)sizeof(t_analyser), 0L, A_GIMME, 0);
	class_addmethod(c, (method)analyser_dsp,		"dsp",			A_CANT,	0);
	class_addmethod(c, (method)analyser_assist,		"assist",		A_CANT,	0);
	
	class_dspinit(c);
	class_register(CLASS_BOX, c);
	analyser_class = c;

	CLASS_ATTR_LONG				(c, "window", 0, t_analyser, f_modEnv);
	CLASS_ATTR_LABEL			(c, "window", 0, "Window function");
	CLASS_ATTR_ENUMINDEX		(c, "window", 0, "Square \" \"Hanning \" \"Hamming \" \"Turkey \" \"Cosinus \" \"Lanczos \" \"Triangular \" \"Gaussian \" \"Bartlett-Hann \" \"Blackman \" \"Kaiser \" \"Nuttall \" \"Blackman-Harris \" \"Blackman-Nuttall \" \"Flat-Top \" \"Poisson");
	CLASS_ATTR_ACCESSORS		(c, "window", NULL, mode_set);
	CLASS_ATTR_DEFAULT			(c, "window", 0, "0");
	CLASS_ATTR_SAVE				(c, "window", 1);
	CLASS_ATTR_FILTER_CLIP		(c, "window", 0, 10);
	CLASS_ATTR_ORDER			(c, "window", 0, "1");

	post("pg.analyser~ by Pierre Guillot",0);
	post("Universite Paris 8, France",0);
	
	return 0;
}

void *analyser_new(t_symbol *s, int argc, t_atom *argv)
{
	t_analyser *x = (t_analyser *)object_alloc(analyser_class);
	int i;

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
	window_setup(&x->f_env, x->f_windowSize);
	if( argv[2].a_type == A_LONG ) x->f_modEnv = argv[2].a_w.w_long;
	if (x->f_modEnv < 0 || x->f_modEnv > 15)
	{
		x->f_modEnv = 1;
		object_post((t_object*)x, "Wrong enveloppe, set to default : 1 (Hanning)");
	}
	analyser_envSelector(x);

	x->f_rapportSize = (float)x->f_sr / (float)x->f_windowSize;

	/* FFt initialization ***********************/
	x->f_fft = (t_fft *)getbytes(x->f_overlapping  * sizeof(t_fft));
	for(i = 0; i < x->f_overlapping; i++)
	{
		fft_setup(&x->f_fft[i], x->f_windowSize, i, x->f_overlapping);
	}

	x->f_centroid	= 0.f;
	x->f_spread		= 0.f;
	x->f_deviation	= 0.f;
	x->f_skewness	= 0.f;
	x->f_kurtosis	= 0.f;

	dsp_setup((t_pxobject *)x, 1);
	outlet_new((t_pxobject *)x, "signal");
	outlet_new((t_pxobject *)x, "signal");
	outlet_new((t_pxobject *)x, "signal");
	outlet_new((t_pxobject *)x, "signal");
	
	return (x);
}			

void analyser_dsp(t_analyser *x, t_signal **sp, short *count)
{
	x->f_sr = (float)sp[0]->s_sr;
	x->f_rapportSize = x->f_sr / (float)x->f_windowSize;
	dsp_add(analyser_perform, 7, x, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, 
		sp[3]->s_vec, sp[4]->s_vec, sp[0]->s_n);
}

t_int *analyser_perform(t_int *w)
{	
	t_analyser	*x		= (t_analyser *)(w[1]);
	t_sample	*in		= (t_sample *)	(w[2]);
	t_sample	*out1	= (t_sample *)	(w[3]);
	t_sample	*out2	= (t_sample *)	(w[4]);
	t_sample	*out3	= (t_sample *)	(w[5]);
	t_sample	*out4	= (t_sample *)	(w[6]);
	int n				= (int)			(w[7]);
	
	int i, j;
	t_sample amplitude, frequency, rapport;

	if (x->f_ob.z_disabled) return w + 8;
	
	for(i = 0; i < x->f_overlapping; i++)
	{
		for(j = 0; j < n; j++)
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
				fftwf_execute(x->f_fft[i].f_plan);
				x->f_fft[i].f_ramp = 0;
			}
			
		}
		
	}

	for(j = 0; j < n; j++)
	{
		out1[j] = x->f_centroid;
		out2[j] = x->f_deviation;
		out3[j] = x->f_skewness;
		out4[j] = x->f_kurtosis;
	}

	return (w + 8);	
}

void analyser_free(t_analyser *x)
{
	dsp_free((t_pxobject *)x);
	/*
	for(i = 0; i < x->f_overlapping; i++)
	{
		fft_free(&x->f_fft[i]);
	}
	*/
	freebytes(x->f_fft, x->f_overlapping * sizeof(t_fft));
	window_free(&x->f_env);
	
}

void analyser_assist(t_analyser *x, void *b, long m, long a, char *s)
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
				sprintf(s,"(Signal) Centroid");
				break;
			case 1:
				sprintf(s,"(Signal) Spread");
				break;
			case 2:
				sprintf(s,"(Signal) Skewness");
				break;
			case 3:
				sprintf(s,"(Signal) Kurtosis");
				break;
			case 4:
				sprintf(s,"(Signal) Decrease");
				break;
			case 5:
				sprintf(s,"(Signal) Roll-Off");
				break;
		}
	}
}


t_max_err mode_set(t_analyser *x, t_object *attr, long argc, t_atom *argv)
{
	int mode;
	mode = 16;
	if ( atom_gettype(argv) == A_LONG) mode = atom_getlong(argv);
	else if ( atom_gettype(argv) == A_FLOAT) mode = (int)atom_getfloat(argv);
	else if ( atom_gettype(argv) == A_SYM)
	{
		if ( gensym(argv->a_w.w_sym->s_name)	  == gensym("Square"))			mode = 0;
		else if ( gensym(argv->a_w.w_sym->s_name) == gensym("Hanning"))			mode = 1;
		else if ( gensym(argv->a_w.w_sym->s_name) == gensym("Hamming"))			mode = 2;
		else if ( gensym(argv->a_w.w_sym->s_name) == gensym("Turkey"))			mode = 3;
		else if ( gensym(argv->a_w.w_sym->s_name) == gensym("Cosinus"))			mode = 4;
		else if ( gensym(argv->a_w.w_sym->s_name) == gensym("Lanczos"))			mode = 5;
		else if ( gensym(argv->a_w.w_sym->s_name) == gensym("Triangular"))		mode = 6;
		else if ( gensym(argv->a_w.w_sym->s_name) == gensym("Gaussian"))		mode = 7;
		else if ( gensym(argv->a_w.w_sym->s_name) == gensym("Bartlett-Hann"))	mode = 8;
		else if ( gensym(argv->a_w.w_sym->s_name) == gensym("Blackman"))		mode = 9;
		else if ( gensym(argv->a_w.w_sym->s_name) == gensym("Kaiser"))			mode = 10;
		else if ( gensym(argv->a_w.w_sym->s_name) == gensym("Nuttall"))			mode = 11;
		else if ( gensym(argv->a_w.w_sym->s_name) == gensym("Blackman-Harris"))	mode = 12;
		else if ( gensym(argv->a_w.w_sym->s_name) == gensym("Blackman-Nuttall"))mode = 13;
		else if ( gensym(argv->a_w.w_sym->s_name) == gensym("Flat-Top"))		mode = 14;
		else if ( gensym(argv->a_w.w_sym->s_name) == gensym("Poisson"))			mode = 15;
	}

	x->f_modEnv = mode;
	analyser_envSelector(x);
	
	return 0;
}

void analyser_envSelector(t_analyser *x)
{
	switch(x->f_modEnv)
	{
		case 0:
			window_square(&x->f_env);
			break;
		case 1:
			window_hanning(&x->f_env);
			break;
		case 2:
			window_hamming(&x->f_env);
			break;
		case 3:
			window_turkey(&x->f_env);
			break;
		case 4:
			window_cosinus(&x->f_env);
			break;
		case 5:
			window_lanczos(&x->f_env);
			break;
		case 6:
			window_triangular(&x->f_env);
			break;
		case 7:
			window_gaussian(&x->f_env);
			break;
		case 8:
			window_bartlett_hann(&x->f_env);
			break;
		case 9:
			window_blackman(&x->f_env);
			break;
		case 10:
			window_kaiser(&x->f_env);
			break;
		case 11:
			window_nuttall(&x->f_env);
			break;
		case 12:
			window_blackman_harris(&x->f_env);
			break;
		case 13:
			window_blackman_nuttall(&x->f_env);
			break;
		case 14:
			window_flat_top(&x->f_env);
			break;
		case 15:
			window_poisson(&x->f_env);
			break;
	}
}
