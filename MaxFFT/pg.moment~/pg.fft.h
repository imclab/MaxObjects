
#ifndef DEF_my_fft
#define DEF_my_fft

#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"
#include <fftw3.h>

typedef struct _fft
{
	double			*f_real;
	fftw_complex	*f_complex;
	fftw_plan		f_plan;		
	int				f_ramp;		

	int				f_windowSize;
	int				f_arraySize;
	int				f_instance;

	t_sample		f_sumAmp;

	t_sample		f_centroid;
	t_sample		f_spread;
	t_sample		f_skewness;
	t_sample		f_kurtosis;

} t_fft;

void fft_setup(t_fft *x, int windowSize, int instance, int nbIntance);
void fft_free(t_fft *x);

#endif