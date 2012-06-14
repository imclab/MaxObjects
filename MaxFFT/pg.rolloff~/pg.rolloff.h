
#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"
#include "../pg.window/pg.window.h"
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

	double		f_sumAmp;
	double		*f_amp;
} t_fft;

typedef struct  _rolloff 
{
	t_pxobject	f_ob;
	double	f_sr;

	long		f_windowSize;
	long		f_overlapping;
	long		f_arraySize;
	double	f_rapportSize;
	double	f_rapportFreq;

	t_fft		*f_fft;
	t_window	f_env;

	long		f_winMode;
	long		f_ampMode;

	double	f_rolloff;
	double	f_value;
} t_rolloff;

void *rolloff_class;

void *rolloff_new(t_symbol *s, int argc, t_atom *argv);
void rolloff_free(t_rolloff *x);
void rolloff_assist(t_rolloff *x, void *b, long m, long a, char *s);

void rolloff_dsp64(t_rolloff *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void rolloff_perform64(t_rolloff *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

t_max_err mode_set(t_rolloff *x, t_object *attr, long argc, t_atom *argv);
void fft_setup(t_fft *x, int windowSize, int instance, int nbIntance);
void fft_free(t_fft *x);

void rolloff_dsp(t_rolloff *x, t_signal **sp, short *count);
t_int *rolloff_perform(t_int *w);