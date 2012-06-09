
#ifndef DEF_analyser
#define DEF_analyser

#include "ext.h"
#include "ext_obex.h"
#include "ext_globalsymbol.h"
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

	t_sample		f_centroid;
	t_sample		f_spread;
	t_sample		f_skewness;
	t_sample		f_kurtosis;

	t_sample		f_minAmp;
	t_sample		f_aveAmp;
	t_sample		f_maxAmp;
	t_sample		f_sumAmp;

} t_fft;

typedef struct  _analyser 
{
	t_pxobject	f_ob;
	t_sample	f_sr;
	t_sample	f_sb;

	long		f_windowSize;
	long		f_overlapping;
	long		f_arraySize;
	t_sample	f_rapportSize;

	t_fft		*f_fft;
	t_window	f_env;
	long		f_modEnv;

	t_sample	f_analysis[17];

	long		f_outlet;
	long		f_basic;
	long		f_amplitude;
	long		f_mode[17];
	long		f_modePos[17];
	long		f_posMode[17];
} t_analyser;

void *analyser_class;

void *analyser_new(t_symbol *s, int argc, t_atom *argv);
void analyser_free(t_analyser *x);
void analyser_assist(t_analyser *x, void *b, long m, long a, char *s);
void analyser_dsp64(t_analyser *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void analyser_perform64(t_analyser *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void analyser_envSelector(t_analyser *x);

t_max_err mode_set(t_analyser *x, t_object *attr, long argc, t_atom *argv);

/* Basic Analysis */
void basic(t_class *c);
t_max_err basic_set(t_analyser *x, t_object *attr, long argc, t_atom *argv);

t_max_err centroid_set(t_analyser *x, t_object *attr, long argc, t_atom *argv);
t_max_err spread_set(t_analyser *x, t_object *attr, long argc, t_atom *argv);
t_max_err deviation_set(t_analyser *x, t_object *attr, long argc, t_atom *argv);
t_max_err skewness_set(t_analyser *x, t_object *attr, long argc, t_atom *argv);
t_max_err kurtosis_set(t_analyser *x, t_object *attr, long argc, t_atom *argv);

/* Amplitude Analysis */
void amplitude(t_class *c);
t_max_err amplitude_set(t_analyser *x, t_object *attr, long argc, t_atom *argv);

t_max_err minamp_set(t_analyser *x, t_object *attr, long argc, t_atom *argv);
t_max_err aveamp_set(t_analyser *x, t_object *attr, long argc, t_atom *argv);
t_max_err maxamp_set(t_analyser *x, t_object *attr, long argc, t_atom *argv);
t_max_err sumamp_set(t_analyser *x, t_object *attr, long argc, t_atom *argv);

/* Power Analysis */
void power(t_class *c);
t_max_err power_set(t_analyser *x, t_object *attr, long argc, t_atom *argv);

t_max_err minpow_set(t_analyser *x, t_object *attr, long argc, t_atom *argv);
t_max_err avepow_set(t_analyser *x, t_object *attr, long argc, t_atom *argv);
t_max_err maxpow_set(t_analyser *x, t_object *attr, long argc, t_atom *argv);
t_max_err sumpow_set(t_analyser *x, t_object *attr, long argc, t_atom *argv);

/* Energy Analysis */
void energy(t_class *c);
t_max_err energy_set(t_analyser *x, t_object *attr, long argc, t_atom *argv);

t_max_err mindec_set(t_analyser *x, t_object *attr, long argc, t_atom *argv);
t_max_err avedec_set(t_analyser *x, t_object *attr, long argc, t_atom *argv);
t_max_err macdec_set(t_analyser *x, t_object *attr, long argc, t_atom *argv);
t_max_err sumdec_set(t_analyser *x, t_object *attr, long argc, t_atom *argv);

void analyser_redefine_outlets(t_analyser *x, int mode, int pos);
void outlet_set(t_analyser *x, int mode, int instance);

/* FFT */
void fft(t_class *c);
t_max_err window_size_set(t_analyser *x, t_object *attr, long argc, t_atom *argv);
t_max_err overlapping_set(t_analyser *x, t_object *attr, long argc, t_atom *argv);
void fft_setup(t_fft *x, int windowSize, int instance, int nbIntance);
void fft_free(t_fft *x);

#endif