/***************************************************
defStruct
Par Pierre Guillot


defStruct.h

Contient la structure de l'objet et les #defines
****************************************************/
#ifndef DEF_POLLOCK
#define DEF_POLLOCK

#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"
#include "math.h"
#include "ext_common.h"
#include "ext_atomic.h"
#include "buffer.h"

#include "pg.window.h"
#include "pg.delay.h"


#define SIZETAB		10000

#define Ndefaut		4
#define NMAX		16
#define I360		0.0027777777777777778F
#define OFFSET		.3
#define T_COS     4096
#define NPOLY		4

typedef struct _pollock
{
    t_pxobject f_obj;
	
	/**** Audio parameters ******************************************/
	t_float f_sr;				/* Sampling rate					*/
    t_float f_sb;				/* Vector size						*/
	
	/**** Inlets ****************************************************/
	void	*x_proxy;			/* Proxy ptr						*/
	long	f_inlet;			/* Inlets space						*/
	
	float	f_grainLenght;		/* Grain lenght						*/
	float	f_delayTime;		/* Delai time in ms					*/ 
	float	f_feedback;			/* Feedback							*/
	float	f_rarefaction;		/* Rarefaction						*/
	
	/**** Parameters ************************************************/
	int			f_voices;		/* Number of instances				*/
	int			f_modEnv;		/* Envelope Type					*/
	float		f_modDel;		/* Delay modulation					*/
	float		f_modAmp;		/* Amplitude modulation				*/
	float		f_modLen;		/* Grain lenght modulation			*/
	
	/**** Granulation ***********************************************/
	t_window	f_envelope;		/* Envellope du grain				*/
	t_delay		*f_delay;		/* Delais							*/
	t_sample	*f_inputSig;	/* Vector for input signal			*/
} t_pollock;

t_symbol *ps_buffer;
/********************************************************************/
/*							PROTOTYPES							    */
/********************************************************************/

void *pollock_class;

void *pollock_new(t_symbol *s, int argc, t_atom *argv);
void pollock_dsp(t_pollock *x, t_signal **sp, short *count);
void pollock_free(t_pollock *x);
void pollock_assist(t_pollock *x, void *b, long m, long a, char *s);
void pollock_int(t_pollock *x, long n);
void pollock_float(t_pollock *x, double n);
void pollock_dblclick(t_pollock *x);
t_int *pollock_perform(t_int *w);
t_int *result_perform(t_int *w);

t_max_err mode_set(t_pollock *x, t_object *attr, long argc, t_atom *argv);

#endif

