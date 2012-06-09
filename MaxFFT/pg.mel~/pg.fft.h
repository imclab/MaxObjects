
#ifndef DEF_FFT
#define DEF_FFT

#include "ext.h"
#include "ext_obex.h"
#include "ext_common.h"
#include "z_dsp.h"
#include <fftw3.h>

typedef struct _fft
{
	t_sample		*f_real; 
	t_sample		*f_melBand;
	t_sample		*f_mffcoeff;
	fftw_complex	*f_complex;
	fftw_plan		f_plan;
	fftw_plan		f_planCos;
	long			f_ramp;

	t_sample		*f_mfcc;

	long 			f_spew;
	long			f_spew2;

	long			f_windowSize;
	long			f_arraySize;
	long			f_instance;
	long			f_nBands;
} t_fft;

void fft_setup(t_fft *x, int windowSize, int instance, int nbIntance, int nBands);
void fft_free(t_fft *x);

#endif