#include "pg.mel.h"

void fft_setup(t_fft *x, int windowSize, int instance, int nbIntance, int nBands)
{
	int i;
	x->f_windowSize = windowSize;
	x->f_arraySize = x->f_windowSize / 2;
	x->f_instance = instance;
	x->f_nBands = nBands;

	x->f_ramp = (x->f_windowSize * x->f_instance) / nbIntance;

	x->f_real		= (t_sample *)fftw_malloc(x->f_windowSize * sizeof(t_sample));
	x->f_complex	= (fftw_complex *)fftw_malloc(x->f_arraySize * sizeof(fftw_complex));
	x->f_plan		= fftw_plan_dft_r2c_1d(x->f_windowSize, x->f_real, x->f_complex, FFTW_ESTIMATE);
	
	x->f_melBand	= (t_sample *)fftw_malloc(x->f_nBands  * sizeof(t_sample));
	x->f_mffcoeff	= (t_sample *)fftw_malloc(x->f_nBands  * sizeof(t_sample));
	x->f_planCos	= fftw_plan_r2r_1d(x->f_nBands, x->f_melBand, x->f_mffcoeff , FFTW_REDFT10, FFTW_ESTIMATE);

	x->f_mfcc		= (t_sample *)getbytes(x->f_nBands * sizeof(t_sample));
	for(i = 0; i < x->f_nBands; i++)
	{
		x->f_mfcc[i] = 0.f;
		x->f_melBand[i] = 0.f;
	}
	x->f_spew = 0;
}

void fft_free(t_fft *x)
{
	fftw_destroy_plan(x->f_plan);
	fftw_free(x->f_real);
	fftw_free(x->f_complex);
	fftw_destroy_plan(x->f_planCos);
	fftw_free(x->f_melBand);
	fftw_free(x->f_mffcoeff);
	freebytes(x->f_mfcc, x->f_arraySize * sizeof(t_sample));
}