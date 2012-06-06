#include "pg.fft.h"

void fft_setup(t_fft *x, int windowSize, int instance, int nbIntance, int nBands)
{
	int i;
	x->f_windowSize = windowSize;
	x->f_arraySize = x->f_windowSize / 2;
	x->f_instance = instance;
	x->f_nBands = nBands;

	x->f_ramp = (x->f_windowSize * x->f_instance) / nbIntance;

	x->f_real		= (float *)fftwf_malloc(x->f_windowSize * sizeof(float));
	x->f_complex	= (fftwf_complex *)fftwf_malloc(x->f_arraySize * sizeof(fftwf_complex));
	x->f_plan		= fftwf_plan_dft_r2c_1d(x->f_windowSize, x->f_real, x->f_complex, FFTW_ESTIMATE);
	x->f_melBand	= (float *)fftwf_malloc(x->f_nBands  * sizeof(float));
	x->f_mffcoeff	= (float *)fftwf_malloc(x->f_nBands  * sizeof(float));
	x->f_planCos	= fftwf_plan_r2r_1d(x->f_nBands, x->f_melBand, x->f_mffcoeff , FFTW_REDFT10, FFTW_ESTIMATE);

	x->f_mfcc		= (float *)getbytes(x->f_nBands * sizeof(float));
	for(i = 0; i < x->f_nBands; i++)
	{
		x->f_mfcc[i] = 0.f;
		x->f_melBand[i] = 0.f;
	}
	x->f_spew = 0;
	x->f_spew2 = 0;
}

void fft_free(t_fft *x)
{
	fftwf_destroy_plan(x->f_plan);
	fftwf_free(x->f_real);
	fftwf_free(x->f_complex);
	fftwf_destroy_plan(x->f_planCos);
	fftwf_free(x->f_melBand);
	fftwf_free(x->f_mffcoeff);
	freebytes(x->f_mfcc, x->f_arraySize * sizeof(float));
}