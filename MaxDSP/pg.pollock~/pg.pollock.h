
/*
* Copyright (C) 2012 Pierre Guillot, Universite Paris 8
* 
* This library is free software; you can redistribute it and/or modify it 
* under the terms of the GNU Library General Public License as published 
* by the Free Software Foundation; either version 2 of the License.
* 
* This library is distributed in the hope that it will be useful, but WITHOUT 
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
* FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public 
* License for more details.
*
* You should have received a copy of the GNU Library General Public License 
* along with this library; if not, write to the Free Software Foundation, 
* Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*
* guillotpierre6@gmail.com
*/

#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"
#include "math.h"
#include "ext_common.h"
#include "ext_atomic.h"
#include "buffer.h"

#include "pg.window.h"
#include "../pg.delay/pg.delay.h"


#define SIZETAB		10000
#define WINSIZE		16384

typedef struct _pollock
{
    t_pxobject f_obj;
	
	/**** Audio parameters ******************************************/
	t_double f_sr;				/* Sampling rate					*/
    t_double f_sb;				/* Vector size						*/
	
	/**** Inlets ****************************************************/
	void	*x_proxy;			/* Proxy ptr						*/
	long	f_inlet;			/* Inlets space						*/
	
	double	f_grainLenght;		/* Grain lenght						*/
	double	f_delayTime;		/* Delai time in ms					*/ 
	double	f_feedback;			/* Feedback							*/
	double	f_rarefaction;		/* Rarefaction						*/
	
	/**** Parameters ************************************************/
	int			f_voices;		/* Number of instances				*/
	int			f_modEnv;		/* Envelope Type					*/
	double		f_modDel;		/* Delay modulation					*/
	double		f_modAmp;		/* Amplitude modulation				*/
	double		f_modLen;		/* Grain lenght modulation			*/
	
	/**** Granulation ***********************************************/
	double		*f_window;		/* Envellope du grain				*/
	t_delay		f_delay;		/* Delais							*/
	double		f_factor;
	double		f_offset;
} t_pollock;

void *pollock_class;

void *pollock_new(t_symbol *s, int argc, t_atom *argv);
void pollock_dsp(t_pollock *x, t_signal **sp, short *count);
void pollock_free(t_pollock *x);
void pollock_assist(t_pollock *x, void *b, long m, long a, char *s);
void pollock_int(t_pollock *x, long n);
void pollock_double(t_pollock *x, double n);
void pollock_dblclick(t_pollock *x);
t_int *pollock_perform(t_int *w);
t_int *result_perform(t_int *w);
void pollock_tukey(t_pollock *x, double factor, double offset);

