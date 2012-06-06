
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

	int			f_sr;
	void		*out1;

	int			f_windowSize;
	int			f_overlapping;
	int			f_arraySize;
	
	int			f_nBands;
	void 		*f_clock;
	t_fft		*f_fft;

	float		*f_result;
	t_atom		*f_output;
	int			f_interval;
	int			f_count;
	int			f_limit;
	t_window	f_env;
	int			f_modEnv;

	float		**f_filterParameters;
	
	int			*f_melBandRef;
	int			f_mfccMode;

	float		f_filter;
	float		f_hightpass;
	float 		f_rapportSize;

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