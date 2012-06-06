
#include "pg.spectrum.h"

int main()
{
	t_class *c;

	c = class_new("pg.spectrum~", (method)spectrum_new, (method)spectrum_free, (short)sizeof(t_spectrum), 0L, A_GIMME, 0);
	class_addmethod(c, (method)spectrum_dsp,		"dsp",			A_CANT,	0);
	class_addmethod(c, (method)spectrum_assist,		"assist",		A_CANT,	0);
	
	class_dspinit(c);
	class_register(CLASS_BOX, c);
	spectrum_class = c;

	CLASS_ATTR_LONG				(c, "window", 0, t_spectrum, f_modEnv);
	CLASS_ATTR_LABEL			(c, "window", 0, "Window type");
	CLASS_ATTR_ENUMINDEX		(c, "window", 0, "Square \" \"Hanning \" \"Hamming \" \"Turkey \" \"Cosinus \" \"Lanczos \" \"Triangular \" \"Gaussian \" \"Bartlett-Hann \" \"Blackman \" \"Kaiser \" \"Nuttall \" \"Blackman-Harris \" \"Blackman-Nuttall \" \"Flat-Top \" \"Poisson");
	CLASS_ATTR_ACCESSORS		(c, "window", NULL, mode_set);
	CLASS_ATTR_DEFAULT			(c, "window", 0, "0");
	CLASS_ATTR_SAVE				(c, "window", 1);
	CLASS_ATTR_FILTER_CLIP		(c, "window", 0, 10);
	CLASS_ATTR_ORDER			(c, "window", 0, "1");

	CLASS_ATTR_LONG				(c, "logamp", 0, t_spectrum, f_logamp);
	CLASS_ATTR_LABEL			(c, "logamp", 0, "Amplitude scale");
	CLASS_ATTR_ENUMINDEX		(c, "logamp", 0, "Linear \"Logarithmic");
	CLASS_ATTR_DEFAULT			(c, "logamp", 0, "1");
	CLASS_ATTR_SAVE				(c, "logamp", 1);
	
	CLASS_ATTR_LONG				(c, "logfreq", 0, t_spectrum, f_logfreq);
	CLASS_ATTR_LABEL			(c, "logfreq", 0, "Frequency scale");
	CLASS_ATTR_ENUMINDEX		(c, "logfreq", 0, "Linear \"Logarithmic");
	CLASS_ATTR_DEFAULT			(c, "logfreq", 0, "0");
	CLASS_ATTR_SAVE				(c, "logfreq", 1);
	
	CLASS_ATTR_FLOAT_ARRAY		(c, "domain", 0, t_spectrum, domain, 2);
	CLASS_ATTR_LABEL			(c, "domain", 0, "Low and high domain range values (X-Axis)");
	CLASS_ATTR_ACCESSORS		(c, "domain", NULL, domain_mode_set);
	CLASS_ATTR_SAVE				(c, "domain", 1);

	CLASS_ATTR_LONG				(c, "interval", 0, t_spectrum, f_interval);
	CLASS_ATTR_LABEL			(c, "interval", 0, "Polling interval");
	CLASS_ATTR_FILTER_CLIP		(c, "interval", 3, 5000);
	CLASS_ATTR_DEFAULT			(c, "interval", 0, "10");
	CLASS_ATTR_SAVE				(c, "interval", 1);

	CLASS_ATTR_LONG				(c, "resize", 0, t_spectrum, f_resize);
	CLASS_ATTR_STYLE_LABEL		(c, "resize", 0, "onoff", "Resize mode");
	CLASS_ATTR_DEFAULT			(c, "resize", 0, "0");
	CLASS_ATTR_SAVE				(c, "resize", 1);
	
	CLASS_ATTR_LONG				(c, "smooth", 0, t_spectrum, f_limit);
	CLASS_ATTR_LABEL			(c, "smooth", 0, "Smooth");
	CLASS_ATTR_FILTER_MIN		(c, "smooth", 1);
	CLASS_ATTR_DEFAULT			(c, "smooth", 0, "5");
	CLASS_ATTR_SAVE				(c, "smooth", 1);

	post("pg.spectrum~ by Pierre Guillot",0);
	post("Universite Paris 8, France",0);
	
	return 0;
}

void *spectrum_new(t_symbol *s, int argc, t_atom *argv)
{
	t_spectrum *x = NULL;
	int i;

	if (x = (t_spectrum *)object_alloc(spectrum_class)) 
	{
		/* Sampling Rate initialization **************/
		x->f_sr = sys_getsr();

		/* Windows Size Initialization **************/
		x->f_windowsSize = 0; 
		if( argv[0].a_type == A_LONG ) x->f_windowsSize = (int)(argv[0].a_w.w_long);
		if (x->f_windowsSize%2 != 0)
		{
			x->f_windowsSize = 1024;
			object_post((t_object*)x, "Wrong window size initialization, set to default : 1024");
		}
		x->f_arraySize = x->f_windowsSize/2;

		/* Overlapping Initialization ***************/
		x->f_overlapping = 0; 
		if( argv[1].a_type == A_LONG ) x->f_overlapping = (int)(argv[1].a_w.w_long);
		if (x->f_overlapping < 1)
		{
			x->f_overlapping = 2;
			object_post((t_object*)x, "Wrong overlapping initialization, set to default : 2");
		}
		
		/* Initialization of the window  ********************************/
		window_setup(&x->f_env, x->f_windowsSize);
		if( argv[2].a_type == A_LONG ) x->f_modEnv = argv[2].a_w.w_long;
		if (x->f_modEnv < 0 || x->f_modEnv > 15)
		{
			x->f_modEnv = 1;
			object_post((t_object*)x, "Wrong enveloppe, set to default : 1 (Hanning)");
		}
		spectrum_envSelector(x);

		/* Amplitude weight initialization **********/
		x->f_rapportSize	= (float)(PI * (1.0 / (float)x->f_arraySize));

		x->f_floatSpec		= (float *)getbytes(x->f_arraySize * sizeof(float));
		x->f_result			= (float *)getbytes(x->f_arraySize * sizeof(float));
		x->f_spectrum		= (t_atom *)getbytes(x->f_arraySize * sizeof(t_atom));

		/* FFt initialization ***********************/
		x->f_fft = (t_fft *)getbytes(x->f_overlapping  * sizeof(t_fft));
		for(i = 0; i < x->f_overlapping; i++)
		{
			fft_setup(&x->f_fft[i], x->f_windowsSize, i, x->f_overlapping);
		}

		/* Attributes initialization ****************/
		x->f_limit		= 5;
		x->f_logamp		= 1;
		x->f_logfreq	= 0;
		x->f_interval	= 10;
		x->f_count		= 0;	
	
		/* Define the output range values ***********/
		x->domain.f_low = 0;
		x->f_arrayMin = x->domain.f_low / (int)x->f_sr * x->f_windowsSize;
		x->domain.f_high = x->f_sr/2;
		x->f_arrayMax = x->domain.f_high / (int)x->f_sr * x->f_windowsSize;
		x->domain.f_size = (int)x->f_arrayMax - x->f_arrayMin;

		/* Send the attributes to the object ********/
		attr_args_process (x, argc, argv);

		/* Inlet and outlet initialization **********/
		dsp_setup((t_pxobject *)x, 1);
		x->out1 = listout(x);

		/* Defer output clock initialization ********/
		x->f_clock = clock_new(x, (method)spectrum_sortie);
		clock_delay(x->f_clock, 0L); 
	}
	
	return x;
}			

void spectrum_dsp(t_spectrum *x, t_signal **sp, short *count)
{
	x->f_sr = sp[0]->s_sr;
	dsp_add(spectrum_perform, 3, x, sp[0]->s_vec, sp[0]->s_n);
}

t_int *spectrum_perform(t_int *w)
{	
	t_spectrum	*x	= (t_spectrum *)	(w[1]);
	t_float	*in1	= (t_sample *)		(w[2]);
	int n			= (int)				(w[3]);
	
	int i, j;
	float scaledAmp;
	
	if (x->f_ob.z_disabled) return w + 4; 
	
	for(i = 0; i < x->f_overlapping; i++)
	{
		for(j = 0; j < n; j++)
		{
			x->f_fft[i].f_real[x->f_fft[i].f_ramp] = in1[j] * x->f_env.f_envelope[x->f_fft[i].f_ramp];

			if (x->f_fft[i].f_ramp >= x->f_arrayMin && x->f_fft[i].f_ramp <= x->f_arrayMax)
			{
				scaledAmp = (x->f_rapportSize*(sqrt((x->f_fft[i].f_complex[x->f_fft[i].f_ramp][0]*x->f_fft[i].f_complex[x->f_fft[i].f_ramp][0])+(x->f_fft[i].f_complex[x->f_fft[i].f_ramp][1]*x->f_fft[i].f_complex[x->f_fft[i].f_ramp][1]))));
				if(x->f_logamp == 1)
				{
					scaledAmp = 20.f * (log10(scaledAmp));
					if (scaledAmp < -90.f) scaledAmp = -90.f;
				}
				
				x->f_fft[i].f_spectrum[x->f_fft[i].f_ramp-x->f_arrayMin] = scaledAmp;
			}
			x->f_fft[i].f_ramp++;
			if (x->f_fft[i].f_ramp == x->f_windowsSize)
			{
				fftwf_execute(x->f_fft[i].f_plan);
				x->f_fft[i].f_ramp = 0;
				if(x->f_fft[i].f_spew < 2) x->f_fft[i].f_spew++;
			}	
		}
	}
	return w + 4;	
}

void spectrum_sortie(t_spectrum *x)
{
	int rapport;
	float loga;
	int i, j;

	for(i = 0; i < x->f_overlapping; i++)
	{
		if (x->f_fft[i].f_spew >= 2)
		{
			if(x->f_logfreq == 1)
			{
				loga = log10((float)(x->f_sr/2)+1.f);
				for(j = 0; j < x->domain.f_size; j++)
				{
					x->f_floatSpec[j] = x->f_fft[i].f_spectrum[j];
					x->f_fft[i].f_spectrum[j] = (x->f_floatSpec[(int)(x->domain.f_size*exp((float)(j - x->domain.f_size)/50.f))]+x->f_floatSpec[(int)(x->domain.f_size*exp((float)(j - x->domain.f_size)/50.f))+1])/2.f ;
				}
			}
			if (x->f_count != 0)
			{
				for(j = 0; j < x->domain.f_size; j++)
				{
					x->f_result[j] = x->f_result[j] + (x->f_fft[i].f_spectrum[j] - x->f_result[j])*(2.f/(x->f_limit+1));
					atom_setfloat(x->f_spectrum+j, x->f_result[j]);
				}
			}
			else
			{
				for(j = 0; j < x->domain.f_size; j++)
				{
					atom_setfloat(x->f_spectrum+j, x->f_result[j]);
					x->f_count++;
				}
			}
			
			if(x->f_resize == 1)
			{
				rapport = x->domain.f_size/SIZELIST;
				for(j = 0; j < SIZELIST; j++)
				{
					x->f_spectrum[j].a_w.w_float = x->f_spectrum[j*rapport].a_w.w_float;
				}
			
			outlet_list(x->out1, 0L, SIZELIST, x->f_spectrum);
			}
			else outlet_list(x->out1, 0L, x->domain.f_size, x->f_spectrum); 
		}
		x->f_fft[i].f_spew = 1;
	}
	clock_delay(x->f_clock, x->f_interval);
}

void spectrum_free(t_spectrum *x)
{
	int i;
	clock_unset(x->f_clock);
	
	dsp_free((t_pxobject *)x);
	object_free(x->f_clock);
	for(i = 0; i < x->f_overlapping; i++)
	{
		//fft_free(&x->f_fft[i]);
	}
	
	freebytes(x->f_fft,	x->f_overlapping * sizeof(t_fft));
	
	freebytes(x->f_floatSpec,	x->f_arraySize * sizeof(float));
	freebytes(x->f_result,		x->f_arraySize * sizeof(float));
	freebytes(x->f_spectrum,	x->f_arraySize * sizeof(t_atom));

	window_free(&x->f_env);
	
	
}

void spectrum_assist(t_spectrum *x, void *b, long m, long a, char *s)
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
				sprintf(s,"(List) Spectrum");
				break;
		}
	}
}

t_max_err domain_mode_set(t_spectrum *x, t_object *attr, long argc, t_atom *argv)
{
	if ( atom_gettype(argv) == A_LONG) x->domain.f_low = (float)atom_getlong(argv);
	else if ( atom_gettype(argv) == A_FLOAT) x->domain.f_low = atom_getfloat(argv);
	if (x->domain.f_low < 0 || x->domain.f_low > x->f_sr/2 - 1)
	{
		x->domain.f_low = 0;
	}
	x->f_arrayMin = x->domain.f_low / (int)x->f_sr * x->f_windowsSize;

	if ( atom_gettype(argv+1) == A_LONG) x->domain.f_high = (float)atom_getlong(argv+1);
	else if ( atom_gettype(argv+1) == A_FLOAT) x->domain.f_high = atom_getfloat(argv+1);

	if (x->domain.f_high > x->f_sr/2 || x->domain.f_high < x->domain.f_low)
	{
		x->domain.f_high = x->f_sr/2;
	}
	x->f_arrayMax = x->domain.f_high / (int)x->f_sr * x->f_windowsSize;

	x->domain.f_size = (int)x->f_arrayMax - x->f_arrayMin;
	if (x->domain.f_size < 0) x->domain.f_size = 0;

	return 0;
}


t_max_err mode_set(t_spectrum *x, t_object *attr, long argc, t_atom *argv)
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
	spectrum_envSelector(x);
	
	return 0;
}


void spectrum_envSelector(t_spectrum *x)
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
