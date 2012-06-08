
#ifndef DEF_analyser
#define DEF_analyser

#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"
#include "pg.fft.h"
#include "pg.window.h"

typedef struct  _analyser 
{
	t_pxobject	f_ob;
	t_sample	f_sr;
	t_sample	f_sb;
	t_dspchain	*myDspChain;

	long		f_windowSize;
	long		f_overlapping;
	long		f_arraySize;
	t_sample	f_rapportSize;

	t_fft		*f_fft;
	t_window	f_env;
	long		f_modEnv;

	t_sample	f_centroid;
	t_sample	f_spread;
	t_sample	f_deviation;
	t_sample	f_skewness;
	t_sample	f_kurtosis;

	long		f_outlet;
	long		f_basic;
	long		f_mode[8];
	long		f_modePos[8];
} t_analyser;

void *analyser_class;

void *analyser_new(t_symbol *s, int argc, t_atom *argv);
void analyser_free(t_analyser *x);
void analyser_assist(t_analyser *x, void *b, long m, long a, char *s);
void analyser_dsp(t_analyser *x, t_signal **sp, short *count);
void analyser_dsp64(t_analyser *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
t_int *analyser_perform(t_int *w);
void analyser_perform64(t_analyser *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void analyser_envSelector(t_analyser *x);

t_max_err mode_set(t_analyser *x, t_object *attr, long argc, t_atom *argv);
t_max_err analyser_notify(t_analyser *x, t_symbol *s, t_symbol *msg, void *sender, void *data);
t_max_err window_size_set(t_analyser *x, t_object *attr, long argc, t_atom *argv);
t_max_err overlapping_set(t_analyser *x, t_object *attr, long argc, t_atom *argv);

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
t_max_err minamp_set(t_analyser *x, t_object *attr, long argc, t_atom *argv);
t_max_err aveamp_set(t_analyser *x, t_object *attr, long argc, t_atom *argv);
t_max_err maxamp_set(t_analyser *x, t_object *attr, long argc, t_atom *argv);

/* Power Analysis */
void power(t_class *c);

/* Energy Analysis */
void energy(t_class *c);

void analyser_redefine_outlets(t_analyser *x, int pos);
#endif