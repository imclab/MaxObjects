
#ifndef DEF_my_fft
#define DEF_my_fft

#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"
#include <fftw3.h>

typedef struct _fft
{
	float			*f_real;
	float			*f_realOut;
	fftwf_complex	*f_complex;
	fftwf_plan		f_plan;
	fftwf_plan		f_planReverse;		
	int				f_ramp;		

	int				f_windowSize;
	int				f_arraySize;
	int				f_instance;

	float			*f_phase;
	float			*f_amp;

} t_fft;

void fft_setup(t_fft *x, int windowSize, int instance, int nbIntance);
void fft_free(t_fft *x);

#endif