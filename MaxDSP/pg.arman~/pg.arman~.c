
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

#include "pg.arman.h"

int main()
{
	t_class *c;

	c = class_new("pg.arman~", (method)arman_new, (method)arman_free, (short)sizeof(t_arman), 0L, A_GIMME, 0);
	class_addmethod(c, (method)arman_dsp64,			"dsp64",		A_CANT,	0);
	class_addmethod(c, (method)arman_dsp,			"dsp",			A_CANT,	0);
	class_addmethod(c, (method)arman_assist,		"assist",		A_CANT,	0);
	class_addmethod(c, (method)arman_int,			"int",			A_LONG,	0);
	class_addmethod(c, (method)arman_float,			"float",		A_FLOAT,0);

	CLASS_ATTR_DOUBLE			(c, "size", 0, t_arman, f_winSize);
	CLASS_ATTR_LABEL			(c, "size", 0, "Window Size");
	CLASS_ATTR_DEFAULT			(c, "size", 0, "100.");
	CLASS_ATTR_ACCESSORS		(c, "size", NULL, window_size_set);
	CLASS_ATTR_SAVE				(c, "size", 1);
	CLASS_ATTR_FILTER_MIN		(c, "size", 1.);

	CLASS_ATTR_LONG				(c, "voices", 0, t_arman, f_voices);
	CLASS_ATTR_LABEL			(c, "voices", 0, "Voices Used");
	CLASS_ATTR_DEFAULT			(c, "voices", 0, "1");
	CLASS_ATTR_ACCESSORS		(c, "voices", NULL, voices_set);
	CLASS_ATTR_SAVE				(c, "voices", 1);
	CLASS_ATTR_FILTER_MIN		(c, "voices", 0);

	CLASS_ATTR_LONG				(c, "delay", 0, t_arman, f_delayAdd);
	CLASS_ATTR_LABEL			(c, "delay", 0, "Delay");
	CLASS_ATTR_DEFAULT			(c, "delay", 0, "0");
	CLASS_ATTR_SAVE				(c, "delay", 1);
	CLASS_ATTR_FILTER_MIN		(c, "delay", 0);

	class_dspinit(c);
	class_register(CLASS_BOX, c);
	arman_class = c;

	post("pg.arman~ by Pierre Guillot",0);
	post("Copyright (C) 2012, Universite Paris 8");
	
	return 0;
}

void *arman_new(t_symbol *s, int argc, t_atom *argv)
{
	int i;
	
	t_arman *x = NULL;

	if (x = (t_arman *)object_alloc((t_class *)arman_class)) 
	{
		x->f_sr = sys_getsr();
		delay_setup(&x->f_delay, 10000., x->f_sr);

		x->f_voiceNumber = 1;
		if( argv[0].a_type == A_LONG ) x->f_voiceNumber = (argv[0].a_w.w_long);
		else if( argv[0].a_type == A_FLOAT ) x->f_voiceNumber = (long)(argv[0].a_w.w_float);
		if(x->f_voiceNumber < 1)
			x->f_voiceNumber = 1;
		x->f_voices = x->f_voiceNumber;

		x->f_cent		= (double *)getbytes(x->f_voiceNumber * sizeof(double));
		x->f_window		= (double *)getbytes((WINSIZE + 1) * sizeof(double));
		x->f_connected	= (int *)getbytes((x->f_voiceNumber + 1) * sizeof(int));
		x->f_inc		= (double *)getbytes(x->f_voiceNumber * sizeof(double));
		x->f_grain		= (double *)getbytes(x->f_voiceNumber * sizeof(double));

		for(i = 0; i < x->f_voiceNumber; i++)
		{
			if( argv[i + 1].a_type == A_LONG ) x->f_cent[i] = (double)(argv[i + 1].a_w.w_long);
			else if( argv[i + 1].a_type == A_FLOAT ) x->f_cent[i] = (double)(argv[i + 1].a_w.w_float);
			else x->f_cent[i] = 1.;
			x->f_inc[i] = 0.;
		}

		x->f_delayAdd = 0.;
		x->f_rapport = pow(2., (1./12.));
		arman_cosinus(x);
		arman_ratio(x, 100.);

		dsp_setup((t_pxobject *)x, x->f_voiceNumber + 1);
		for(i = 0; i < x->f_voiceNumber; i++)
			outlet_new((t_pxobject *)x, "signal");

		attr_args_process(x, argc, argv);
	}
	
	return (x);
}			

void arman_dsp64(t_arman *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	int i;
	x->f_sr = samplerate;

	delay_resize(&x->f_delay, x->f_sr);
	for(i = 0; i < x->f_voiceNumber + 1; i++)
		x->f_connected[i] = count[i];
	arman_ratio(x, x->f_winSize);
	object_method(dsp64, gensym("dsp_add64"), x, arman_perform64, 0, NULL);
}

void arman_perform64(t_arman *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	int i, j, index;
	double sigDelayOne, sigDelayTwo, ratio, incOne, incTwo;
	double delayOne, delayTwo;
	double window;
	if(x->f_connected[0]);
	{
		for(i = 0; i < sampleframes; i++)
		{ 
			delay_write(&x->f_delay, ins[0][i]);
			for(j = 0; j < x->f_voices; j++)
			{
				if(x->f_connected[j+1] == 1 && ins[j+1][i] != x->f_cent[j])
				{
					arman_transpo(x, ins[j+1][i], j);
				}

				incOne = x->f_inc[j];
				incTwo = fmod(x->f_inc[j] + 0.5, 1.);

				index = incOne * (double)WINSIZE;
				ratio = (incOne * (double)WINSIZE) - index;
				window = x->f_window[index] * (1.- ratio) + x->f_window[index + 1] * ratio;
				
				delayOne = (incOne * x->f_winSize) + x->f_delayAdd;
				delayTwo = (incTwo * x->f_winSize) + x->f_delayAdd;

				sigDelayOne = delay_read_ms_linear(&x->f_delay, delayOne);
				sigDelayTwo = delay_read_ms_linear(&x->f_delay, delayTwo);

				outs[j][i] = sigDelayOne * window + sigDelayTwo * (1. - window);
				
				x->f_inc[j] += x->f_grain[j];
				
				if(x->f_inc[j] >= 1. && x->f_grain[j] >= 0.)
					x->f_inc[j] = 0.;
				else if(x->f_inc[j] <= 0. && x->f_grain[j] < 0.)
					x->f_inc[j] = 1.;
				

			}
			for(; j < x->f_voiceNumber; j++)
				outs[j][i] = 0.;
		}
	}
}

void arman_free(t_arman *x)
{
	dsp_free((t_pxobject *)x);
	delay_free(&x->f_delay);

	freebytes(x->f_window, (WINSIZE + 1) * sizeof(double));
	freebytes(x->f_cent, x->f_voiceNumber * sizeof(double));
	freebytes(x->f_connected, (x->f_voiceNumber + 1) * sizeof(int));
	freebytes(x->f_inc, x->f_voiceNumber * sizeof(double));
	freebytes(x->f_grain, x->f_voiceNumber * sizeof(double));
}

void arman_assist(t_arman *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) 
	{
		if(a == 0)
			sprintf(s,"(Signal) Input");
		else
			sprintf(s,"(Int, Float or Signal) Transposition %i", (int)a);
	}
	else 
	{
		sprintf(s,"(Signal) Armaned signal %i", (int)a);
	}
}

t_max_err voices_set(t_arman *x, t_object *attr, long argc, t_atom *argv)
{
	int voices;
	if (atom_gettype(argv) == A_LONG) voices = (double)atom_getlong(argv);
	else if (atom_gettype(argv) == A_FLOAT) voices = (double)atom_getfloat(argv);
	if(voices < 0)
		voices  = 0;
	else if(voices > x->f_voiceNumber)
		voices = x->f_voiceNumber;

	x->f_voices = voices;
	return 1;
}

t_max_err window_size_set(t_arman *x, t_object *attr, long argc, t_atom *argv)
{
	double winSize;
	if (atom_gettype(argv) == A_LONG) winSize = (double)atom_getlong(argv);
	else if (atom_gettype(argv) == A_FLOAT) winSize = (double)atom_getfloat(argv);
	if(winSize >= x->f_delay.f_lenghtMs)
		winSize = x->f_delay.f_lenghtMs - 1.;
	arman_ratio(x, winSize);
	return 1;
}

void arman_ratio(t_arman *x, double winSize)
{
	int i;
	if(winSize != x->f_winSize)
	{
		x->f_winSize = winSize;
		x->f_ratio = (1000. / x->f_winSize * -1.) / x->f_sr;
		for(i = 0; i < x->f_voiceNumber; i++)
		{
			arman_transpo(x, x->f_cent[i], i);
		}
	}
}

void arman_transpo(t_arman *x, double cent, int instance)
{
	x->f_cent[instance] = cent;
	x->f_grain[instance] = x->f_ratio * (pow(x->f_rapport, cent) - 1.);
}

void arman_cosinus(t_arman *x)
{
	int i, size, sizeMinus;

	size = WINSIZE;
	sizeMinus = size - 1;

	for(i = 0; i < size; i++)
    {
		x->f_window[i] = (cos(((double)i/(double)(sizeMinus)) * TWOPI - PI) + 1.) * 0.5;
    }

	x->f_window[WINSIZE] = x->f_window[0];
}

void arman_int(t_arman *x, long n)	
{
	long i;
	i = proxy_getinlet((t_object *)x);
	if(i != 0)
	{
		arman_transpo(x, (double)n, i - 1);
	}
	
}

void arman_float(t_arman *x, double n)	
{
	long i;
	i = proxy_getinlet((t_object *)x);
	if(i != 0)
	{
		arman_transpo(x, (double)n, i - 1);
	}
}

void arman_dsp(t_arman *x, t_signal **sp, short *count)
{
	x->f_sr = (double)sp[0]->s_sr;
	delay_resize(&x->f_delay, x->f_sr);

	dsp_add(arman_perform, 4, x, sp[0]->s_vec, sp[1]->s_vec, sp[0]->s_n);
}

t_int *arman_perform(t_int *w)
{/*
	int i, index, indexTwo;

	t_arman *x		= (t_arman *)(w[1]);
    float		 *in	= (float *)(w[2]);
	float		*out	= (float *)(w[3]);
	int n				= (int)w[4];

	double sigDelayOne, sigDelayTwo, ratio;
	double delayOne, delayTwo;
	double windoOne, windoTwo;

	if(x->f_ob.z_disabled) return w + 5;

	for(i = 0; i < n; i++)
	{
		delay_write(&x->f_delay, (double)in[i]);

		index = x->f_inc;
		indexTwo = x->f_inc + WINSIZE / 2;
		if(indexTwo >= WINSIZE)
			indexTwo -= WINSIZE;
		ratio = x->f_inc - index;

		delayOne = (x->f_delayVec[index + 1] * ratio +  x->f_delayVec[index] * (1. - ratio)) * x->f_value * 2.;
		delayTwo = (x->f_delayVec[indexTwo + 1] * ratio +  x->f_delayVec[indexTwo] * (1. - ratio)) * x->f_value * 2.;

		sigDelayOne = delay_read_ms(&x->f_delay, delayOne);
		sigDelayTwo = delay_read_ms(&x->f_delay, delayTwo);

		windoOne = (x->f_window[index + 1] * ratio +  x->f_window[index] * (1. - ratio));
		windoTwo =	(x->f_window[indexTwo + 1] * ratio +  x->f_window[indexTwo] * (1. - ratio));
		sigDelayOne *= windoOne;
		sigDelayTwo *= windoTwo;
		out[i] = (float)(sigDelayOne + sigDelayTwo);

		x->f_inc += x->f_grain;
		if(x->f_inc >= WINSIZE)
			x->f_inc = 0;
	}
	*/
	return w + 5;
}

