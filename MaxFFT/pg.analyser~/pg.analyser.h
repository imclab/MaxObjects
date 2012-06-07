
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
#endif