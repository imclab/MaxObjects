
#ifndef DEF_FFT
#define DEF_FFT

#include "ext.h"
#include "ext_obex.h"
#include "ext_common.h"
#include "z_dsp.h"
#include <fftw3.h>

typedef struct _fft
{
	float			*f_real; 
	float			*f_melBand;
	float			*f_mffcoeff;
	fftwf_complex	*f_complex;
	fftwf_plan		f_plan;
	fftwf_plan		f_planCos;
	int				f_ramp;

	float 			*f_mfcc;

	int 			f_spew;
	int				f_spew2;

	int				f_windowSize;
	int				f_arraySize;
	int				f_instance;
	int				f_nBands;
} t_fft;

void fft_setup(t_fft *x, int windowSize, int instance, int nbIntance, int nBands);
void fft_free(t_fft *x);

#endif