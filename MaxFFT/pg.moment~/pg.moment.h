
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

	double		f_centroid;
	double		f_spread;
	double		f_skewness;
	double		f_kurtosis;
} t_fft;

typedef struct  _moment 
{
	t_pxobject	f_ob;
	double	f_sr;

	long		f_windowSize;
	long		f_overlapping;
	long		f_arraySize;
	double	f_rapportFreq;
	double	f_rapportSize;

	t_fft		*f_fft;
	t_window	f_env;

	long		f_winMode;
	long		f_ampMode;

	double	f_centroid;
	double	f_spread;
	double	f_deviation;
	double	f_skewness;
	double	f_kurtosis;
} t_moment;

void *moment_class;

void *moment_new(t_symbol *s, int argc, t_atom *argv);
void moment_free(t_moment *x);
void moment_assist(t_moment *x, void *b, long m, long a, char *s);

void moment_dsp64(t_moment *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void moment_perform64(t_moment *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

t_max_err mode_set(t_moment *x, t_object *attr, long argc, t_atom *argv);
void fft_setup(t_fft *x, int windowSize, int instance, int nbIntance);
void fft_free(t_fft *x);

void moment_dsp(t_moment *x, t_signal **sp, short *count);
t_int *moment_perform(t_int *w);