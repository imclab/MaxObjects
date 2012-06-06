
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
	float		f_sr;

	int			f_windowSize;
	int			f_overlapping;
	int			f_arraySize;
	float 		f_rapportSize;

	t_fft		*f_fft;
	t_window	f_env;
	int			f_modEnv;

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
t_int *analyser_perform(t_int *w);
void analyser_envSelector(t_analyser *x);

t_max_err mode_set(t_analyser *x, t_object *attr, long argc, t_atom *argv);
#endif