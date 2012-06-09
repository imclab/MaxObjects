
#ifndef DEF_MEL
#define DEF_MEL


#include "ext.h"
#include "ext_obex.h"
#include "ext_common.h"
#include "z_dsp.h"
#include <math.h>
#include "pg.window.h"
#include "pg.fft.h"

typedef struct  _mfcc 
{
	t_pxobject	f_ob;

	t_sample		f_sr;
	void		*out1;

	long		f_windowSize;
	long		f_overlapping;
	long		f_arraySize;
	
	long		f_nBands;
	void 		*f_clock;
	t_fft		*f_fft;

	t_sample	*f_result;
	t_atom		*f_output;
	long		f_interval;
	long		f_count;
	long		f_limit;
	t_window	f_env;
	long		f_modEnv;

	t_sample	**f_filterParameters;
	
	long		*f_melBandRef;
	long		f_mfccMode;

	t_sample	f_filter;
	t_sample	f_hightpass;
	t_sample	f_rapportSize;

} t_mfcc;

void *mfcc_class;

void *mfcc_new(t_symbol *s, int argc, t_atom *argv);
void mfcc_free(t_mfcc *x);
void mfcc_assist(t_mfcc *x, void *b, long m, long a, char *s);
void mfcc_out(t_mfcc *x);
void mfcc_dsp(t_mfcc *x, t_signal **sp, short *count);
t_int *mfcc_perform(t_int *w);
void mfcc_filterParameter(t_mfcc *x);
void mfcc_envSelector(t_mfcc *x);
t_max_err mode_set(t_mfcc *x, t_object *attr, long argc, t_atom *argv);

#endif