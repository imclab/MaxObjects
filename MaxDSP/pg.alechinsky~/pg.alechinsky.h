
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
#define WINSIZE	16384

#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"
#include "../pg.delay/pg.delay.h"
//#include "../pg.window/pg.window.h"
#include <fftw3.h>

typedef struct  _alechinsky 
{
	t_pxobject	f_ob;
	
	void		*f_proxy;
	long		f_inlet;

	double		f_sr;
	t_delay		f_delay;

	double		*f_window;
	double		*f_delayVec;

	double		f_value;
	double		f_inc;
	double		f_grain;
	double		f_factor;
} t_alechinsky;

void *alechinsky_class;

void *alechinsky_new(t_symbol *s, int argc, t_atom *argv);
void alechinsky_free(t_alechinsky *x);
void alechinsky_assist(t_alechinsky *x, void *b, long m, long a, char *s);


void alechinsky_dsp64(t_alechinsky *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void alechinsky_perform64(t_alechinsky *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void alechinsky_int(t_alechinsky *x, long n);
void alechinsky_float(t_alechinsky *x, double n);
void alechinsky_tukey(t_alechinsky *x, double factor);
void alechinsky_delay(t_alechinsky *x, double delay);

void alechinsky_dsp(t_alechinsky *x, t_signal **sp, short *count);
t_int *alechinsky_perform(t_int *w);
