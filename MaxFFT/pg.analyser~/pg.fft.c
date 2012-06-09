#include "pg.analyser.h"

void fft(t_class *c)
{
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
	
	CLASS_ATTR_LONG				(c, "window", 0, t_analyser, f_modEnv);
	CLASS_ATTR_LABEL			(c, "window", 0, "Window function");
	CLASS_ATTR_ENUMINDEX		(c, "window", 0, "Square \" \"Hanning \" \"Hamming \" \"Turkey \" \"Cosinus \" \"Lanczos \" \"Triangular \" \"Gaussian \" \"Bartlett-Hann \" \"Blackman \" \"Kaiser \" \"Nuttall \" \"Blackman-Harris \" \"Blackman-Nuttall \" \"Flat-Top \" \"Poisson");
	CLASS_ATTR_ACCESSORS		(c, "window", NULL, mode_set);
	CLASS_ATTR_DEFAULT			(c, "window", 0, "0");
	CLASS_ATTR_SAVE				(c, "window", 1);
	CLASS_ATTR_FILTER_CLIP		(c, "window", 0, 10);
	CLASS_ATTR_ORDER			(c, "window", 0, "1");
}
void fft_setup(t_fft *x, int windowSize, int instance, int nbIntance)
{
	x->f_windowSize = windowSize;
	x->f_arraySize = x->f_windowSize / 2;
	x->f_instance = instance;

	x->f_ramp = (x->f_windowSize * x->f_instance) / nbIntance;

	x->f_real		= (double *)fftw_malloc(x->f_windowSize * sizeof(double));
	x->f_complex	= (fftw_complex *)fftw_malloc(x->f_windowSize * sizeof(fftw_complex));
	x->f_plan		= fftw_plan_dft_r2c_1d(x->f_windowSize, x->f_real, x->f_complex, FFTW_ESTIMATE);

	x->f_centroid	= 0.;
	x->f_spread		= 0.;
	x->f_skewness	= 0.;
	x->f_kurtosis	= 0.;

	x->f_minAmp		= 300.;
	x->f_aveAmp		= 0.;
	x->f_maxAmp		= -300.;
	x->f_sumAmp		= 0.;
}

void fft_free(t_fft *x)
{
	fftw_destroy_plan(x->f_plan);
	fftw_free(x->f_real);
	fftw_free(x->f_complex);
}

t_max_err overlapping_set(t_analyser *x, t_object *attr, long argc, t_atom *argv)
{
	int i;
	if ( atom_gettype(argv) == A_LONG)
	{
		if(atom_getlong(argv) != x->f_overlapping)
		{
			if(!sys_getdspstate())
				x->f_overlapping = atom_getlong(argv);
		}
	}
	return 0;
}

t_max_err window_size_set(t_analyser *x, t_object *attr, long argc, t_atom *argv)
{
	int i;
	if ( atom_gettype(argv) == A_LONG)
	{
		if(atom_getlong(argv) != x->f_windowSize)
		{
			if(!sys_getdspstate())
				x->f_windowSize = atom_getlong(argv);
		}

	}
	return 0;
}

t_max_err mode_set(t_analyser *x, t_object *attr, long argc, t_atom *argv)
{
	window_mode_set(&x->f_env, attr, argc, argv);
	x->f_modEnv = x->f_env.f_mode;
	return 0;
}