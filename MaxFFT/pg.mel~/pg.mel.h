
#include "ext.h"
#include "ext_obex.h"
#include "ext_common.h"
#include "z_dsp.h"
#include <math.h>
#include "pg.window.h"
#include <fftw3.h>

typedef struct _fft
{
	t_sample		*f_real; 
	t_sample		*f_melBand;
	t_sample		*f_mffcoeff;
	fftw_complex	*f_complex;
	fftw_plan		f_plan;
	fftw_plan		f_planCos;
	long			f_ramp;

	t_sample		*f_mfcc;

	long 			f_spew;

	long			f_windowSize;
	long			f_arraySize;
	long			f_instance;
	long			f_nBands;
} t_fft;

typedef struct  _mel
{
	t_pxobject	f_ob;

	t_sample	f_sr;
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
	long		f_winMode;

	t_sample	**f_filterParameters;
	
	long		*f_melBandRef;
	long		f_mode;

	t_sample	f_filter;
	t_sample	f_hightpass;
	t_sample	f_rapportSize;

} t_mel;

void *mel_class;

void *mel_new(t_symbol *s, int argc, t_atom *argv);
void mel_free(t_mel *x);
void mel_assist(t_mel *x, void *b, long m, long a, char *s);
void mel_out(t_mel *x);

void mel_dsp64(t_mel *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void mel_perform64(t_mel *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void mel_filterParameter(t_mel *x);
void mel_envSelector(t_mel *x);
t_max_err mode_set(t_mel *x, t_object *attr, long argc, t_atom *argv);


void fft_setup(t_fft *x, int windowSize, int instance, int nbIntance, int nBands);
void fft_free(t_fft *x);
