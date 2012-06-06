
#ifndef DEF_FFT
#define DEF_FFT

#include "ext.h"
#include "ext_obex.h"
#include "ext_common.h"
#include "z_dsp.h"
#include <fftw3.h>

typedef struct _fft
{
	float			*f_real;	// Vecteur reel (signal) //
	fftwf_complex	*f_complex; // Vecteur complexe (resultat de FFT)//
	fftwf_plan		f_plan;		// Plan de la FFT //
	int				f_ramp;		// Position d'enregistrement du signal dans le vecteur reel //

	float			*f_spectrum;// Liste contenant les informations de magnitude et de phase de la FFT //
	int				f_spew;		// Premiere condition a remplir pour sortir une liste //

	int				f_windowSize;
	int				f_arraySize;
	int				f_instance;
} t_fft;

void fft_setup(t_fft *x, int windowSize, int instance, int nbIntance);
void fft_free(t_fft *x);

#endif