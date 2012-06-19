
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

typedef struct  _arman 
{
	t_pxobject	f_ob;
	long		f_voiceNumber;
	long		f_voices;

	double		f_sr;
	t_delay		f_delay;

	double		*f_window;
	
	double		f_winSize;
	double		f_ratio;
	double		f_rapport;
	double		*f_cent;
	int			*f_connected;
	double		*f_inc;
	double		*f_grain;
	double		f_delayAdd;

} t_arman;

void *arman_class;

void *arman_new(t_symbol *s, int argc, t_atom *argv);
void arman_free(t_arman *x);
void arman_assist(t_arman *x, void *b, long m, long a, char *s);


void arman_dsp64(t_arman *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void arman_perform64(t_arman *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

void arman_int(t_arman *x, long n);
void arman_float(t_arman *x, double n);
void arman_cosinus(t_arman *x);
void arman_ratio(t_arman *x, double winSize);
void arman_transpo(t_arman *x, double cent, int instance);
t_max_err window_size_set(t_arman *x, t_object *attr, long argc, t_atom *argv);
t_max_err voices_set(t_arman *x, t_object *attr, long argc, t_atom *argv);

void arman_dsp(t_arman *x, t_signal **sp, short *count);
t_int *arman_perform(t_int *w);
