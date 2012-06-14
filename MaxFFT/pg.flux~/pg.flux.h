
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

	double			f_sumAmpMul;
	double			f_sumAmpCar;
	double			f_sumAmpDel;
} t_fft;

typedef struct  _flux 
{
	t_pxobject	f_ob;
	double	f_sr;

	long		f_windowSize;
	long		f_overlapping;
	long		f_arraySize;
	double		f_rapportSize;
	double		f_rapportFreq;

	t_fft		*f_fft;
	t_window	f_env;

	long		f_winMode;
	long		f_ampMode;

	double		f_flux;

	int			f_value;
	double		*f_delsample[17];
	int			*f_count;
} t_flux;

void *flux_class;

void *flux_new(t_symbol *s, int argc, t_atom *argv);
void flux_free(t_flux *x);
void flux_assist(t_flux *x, void *b, long m, long a, char *s);

void flux_dsp64(t_flux *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void flux_perform64(t_flux *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

t_max_err mode_set(t_flux *x, t_object *attr, long argc, t_atom *argv);
void fft_setup(t_fft *x, int windowSize, int instance, int nbIntance);
void fft_free(t_fft *x);

void flux_dsp(t_flux *x, t_signal **sp, short *count);
t_int *flux_perform(t_int *w);
