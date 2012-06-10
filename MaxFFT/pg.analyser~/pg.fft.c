#include "pg.fft.h"

void fft_setup(t_fft *x, int windowSize, int instance, int nbIntance)
{
	x->f_windowSize = windowSize;
	x->f_arraySize = x->f_windowSize / 2;
	x->f_instance = instance;

	x->f_ramp = (x->f_windowSize * x->f_instance) / nbIntance;

	x->f_real		= (double *)fftw_malloc(x->f_windowSize * sizeof(double));
	x->f_complex	= (fftw_complex *)fftw_malloc(x->f_windowSize * sizeof(fftw_complex));
	x->f_plan		= fftw_plan_dft_r2c_1d(x->f_windowSize, x->f_real, x->f_complex, FFTW_ESTIMATE);

	x->f_sumAmp	= 0.;

	x->f_centroid	= 0.;
	x->f_spread		= 0.;
	x->f_skewness	= 0.;
	x->f_kurtosis	= 0.;
}

void fft_free(t_fft *x)
{
	fftw_destroy_plan(x->f_plan);
	fftw_free(x->f_real);
	fftw_free(x->f_complex);
}