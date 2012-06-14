#include "pg.mel.h"

void fft_setup(t_fft *x, int windowSize, int instance, int nbIntance, int nBands)
{
	x->f_windowSize = windowSize;
	x->f_arraySize = x->f_windowSize / 2;
	x->f_instance = instance;
	x->f_nBands = nBands;

	x->f_ramp = (x->f_windowSize * x->f_instance) / nbIntance;

	x->f_real		= (double *)fftw_malloc(x->f_windowSize * sizeof(double));
	x->f_complex	= (fftw_complex *)fftw_malloc((x->f_arraySize + 1) * sizeof(fftw_complex));
	x->f_plan		= fftw_plan_dft_r2c_1d(x->f_windowSize, x->f_real, x->f_complex, FFTW_ESTIMATE);
	
	x->f_melBand	= (double *)fftw_malloc((x->f_nBands * 2) * sizeof(double));
	x->f_mffcoeff	= (double *)fftw_malloc((x->f_nBands * 2) * sizeof(double));
	x->f_planCos	= fftw_plan_r2r_1d(x->f_nBands , x->f_melBand, x->f_mffcoeff , FFTW_REDFT10, FFTW_ESTIMATE);
}

void fft_free(t_fft *x)
{
	fftw_destroy_plan(x->f_plan);
	fftw_free(x->f_real);
	fftw_free(x->f_complex);
	fftw_destroy_plan(x->f_planCos);
	fftw_free(x->f_melBand);
	fftw_free(x->f_mffcoeff);
}