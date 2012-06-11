
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
	t_sample		f_sumFreq;
	t_sample		f_firstAmp;

} t_fft;

typedef struct  _gradient 
{
	t_pxobject	f_ob;
	t_sample	f_sr;

	long		f_windowSize;
	long		f_overlapping;
	long		f_arraySize;
	t_sample	f_rapportSize;
	t_sample	f_rapportFreq;

	t_fft		*f_fft;
	t_window	f_env;
	long		f_ampMode;
	long		f_winMode;
	long		f_mode;

	t_sample	f_gradient;
	t_sample	f_sumFreq;
	t_sample	f_sumFreqCar;

} t_gradient;

void *gradient_class;

void *gradient_new(t_symbol *s, int argc, t_atom *argv);
void gradient_free(t_gradient *x);
void gradient_assist(t_gradient *x, void *b, long m, long a, char *s);

void gradient_dsp64(t_gradient *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void gradient_perform64(t_gradient *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

t_max_err mode_set(t_gradient *x, t_object *attr, long argc, t_atom *argv);
void fft_setup(t_fft *x, int windowSize, int instance, int nbIntance);
void fft_free(t_fft *x);

void gradient_dsp(t_gradient *x, t_signal **sp, short *count);
t_int *gradient_perform(t_int *w);