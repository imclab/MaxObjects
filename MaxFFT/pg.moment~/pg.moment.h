
#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"
#include "pg.window.h"
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

typedef struct  _moment 
{
	t_pxobject	f_ob;
	t_sample	f_sr;

	long		f_windowSize;
	long		f_overlapping;
	long		f_arraySize;
	t_sample	f_rapportFreq;
	t_sample	f_rapportSize;

	t_fft		*f_fft;
	t_window	f_env;

	long		f_winMode;
	long		f_ampMode;

	t_sample	f_centroid;
	t_sample	f_spread;
	t_sample	f_deviation;
	t_sample	f_skewness;
	t_sample	f_kurtosis;
} t_moment;

void *moment_class;

void *moment_new(t_symbol *s, int argc, t_atom *argv);
void moment_free(t_moment *x);
void moment_assist(t_moment *x, void *b, long m, long a, char *s);

void moment_dsp64(t_moment *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void moment_perform64(t_moment *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

t_max_err mode_set(t_moment *x, t_object *attr, long argc, t_atom *argv);
void fft_setup(t_fft *x, int windowSize, int instance, int nbIntance);
void fft_free(t_fft *x);