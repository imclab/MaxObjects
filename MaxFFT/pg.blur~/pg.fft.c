#include "pg.fft.h"

void fft_setup(t_fft *x, int windowSize, int instance, int nbIntance)
{
	x->f_windowSize = windowSize;
	x->f_arraySize = x->f_windowSize / 2;
	x->f_instance = instance;

	x->f_ramp = (x->f_windowSize * x->f_instance) / nbIntance;

	x->f_real		= (float *)fftwf_malloc(x->f_windowSize * sizeof(float));
	x->f_realOut	= (float *)fftwf_malloc(x->f_windowSize * sizeof(float));
	x->f_complex	= (fftwf_complex *)fftwf_malloc(x->f_arraySize * sizeof(fftwf_complex));
	x->f_plan		= fftwf_plan_dft_r2c_1d(x->f_windowSize, x->f_real, x->f_complex, FFTW_ESTIMATE);
	x->f_planReverse= fftwf_plan_dft_c2r_1d(x->f_windowSize, x->f_complex, x->f_realOut, FFTW_ESTIMATE);

	x->f_amp		= (float *)fftwf_malloc(x->f_arraySize * sizeof(float));
	x->f_phase		= (float *)fftwf_malloc(x->f_arraySize * sizeof(float));
}

void fft_free(t_fft *x)
{
	fftwf_destroy_plan(x->f_plan);
	fftwf_destroy_plan(x->f_planReverse);
	fftwf_free(x->f_real);
	fftwf_free(x->f_realOut);
	fftwf_free(x->f_complex);

	fftwf_free(x->f_amp);
	fftwf_free(x->f_phase);
}