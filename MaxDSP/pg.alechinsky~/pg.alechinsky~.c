
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

#include "pg.alechinsky.h"

int main()
{
	t_class *c;

	c = class_new("pg.alechinsky~", (method)alechinsky_new, (method)alechinsky_free, (short)sizeof(t_alechinsky), 0L, A_GIMME, 0);
	class_addmethod(c, (method)alechinsky_dsp64,		"dsp64",		A_CANT,	0);
	class_addmethod(c, (method)alechinsky_dsp,			"dsp",			A_CANT,	0);
	class_addmethod(c, (method)alechinsky_assist,		"assist",		A_CANT,	0);
	class_addmethod(c, (method)alechinsky_int,			"int",			A_LONG,	0);
	class_addmethod(c, (method)alechinsky_float,		"float",		A_FLOAT,0);

	class_dspinit(c);
	class_register(CLASS_BOX, c);
	alechinsky_class = c;

	post("pg.alechinsky~ by Pierre Guillot",0);
	post("Copyright (C) 2012, Universite Paris 8");
	
	return 0;
}

void *alechinsky_new(t_symbol *s, int argc, t_atom *argv)
{
	double	maxDelay, initDelay, factor;
	
	t_alechinsky *x = (t_alechinsky *)object_alloc((t_class *)alechinsky_class);

	x->f_sr = sys_getsr();

	maxDelay = 10000.;
	if( argv[0].a_type == A_LONG ) maxDelay = (double)(argv[0].a_w.w_long) * 2.;
	else if( argv[0].a_type == A_FLOAT ) maxDelay = (double)(argv[0].a_w.w_float) * 2.;
	if (maxDelay < 1.)
		maxDelay = 10000.;
	delay_setup(&x->f_delay, maxDelay, x->f_sr);

	initDelay = 2500.;
	if( argv[1].a_type == A_LONG ) initDelay = (double)(argv[1].a_w.w_long);
	else if( argv[1].a_type == A_FLOAT ) initDelay = (double)(argv[1].a_w.w_float);
	alechinsky_delay(x, initDelay);

	x->f_window = (double *)getbytes((WINSIZE + 1) * sizeof(double));
	x->f_delayVec = (double *)getbytes((WINSIZE + 1) * sizeof(double));

	factor = 0.2;
	if( argv[2].a_type == A_LONG ) factor = (double)(argv[2].a_w.w_long);
	else if( argv[2].a_type == A_FLOAT ) factor = (double)(argv[2].a_w.w_float);
	alechinsky_tukey(x, factor);

	x->f_inc = 0.;
	
	x->f_proxy = proxy_new((t_object *)x, 2, &x->f_inlet);
	x->f_proxy = proxy_new((t_object *)x, 1, &x->f_inlet);
	dsp_setup((t_pxobject *)x, 1);
	outlet_new((t_pxobject *)x, "signal");
	
	return (x);
}			

void alechinsky_dsp64(t_alechinsky *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	x->f_sr = samplerate;
	delay_resize(&x->f_delay, x->f_sr);

	object_method(dsp64, gensym("dsp_add64"), x, alechinsky_perform64, 0, NULL);
}

void alechinsky_perform64(t_alechinsky *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	int i, index, indexTwo;
	double *in = ins[0];
	double *out = outs[0];
	double sigDelayOne, sigDelayTwo, ratio;
	double delayOne, delayTwo;
	double windoOne, windoTwo;

	for(i = 0; i < sampleframes; i++)
	{
		delay_write(&x->f_delay, in[i]);

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
		out[i] = sigDelayOne + sigDelayTwo;

		x->f_inc += x->f_grain;
		if(x->f_inc >= WINSIZE)
			x->f_inc = 0;
	}
}

void alechinsky_free(t_alechinsky *x)
{
	dsp_free((t_pxobject *)x);
	delay_free(&x->f_delay);

	freebytes(x->f_window, (WINSIZE + 1) * sizeof(double));
	freebytes(x->f_delayVec, (WINSIZE + 1) * sizeof(double));
}

void alechinsky_assist(t_alechinsky *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) 
	{
		switch (a) 
		{	
			case 0:
				sprintf(s,"(Signal) Input");
				break;
			case 1:
				sprintf(s,"(Int or Float) Delay Time");
				break;
			case 2:
				sprintf(s,"(Int or Float) Tukey Factor");
				break;
		}
	}
	else 
	{
		switch (a) 
		{	
			case 0:
				sprintf(s,"(Signal) Alechinskyed signal");
				break;
		}
	}
}

void alechinsky_delay(t_alechinsky *x, double delay)
{
	if(delay < 1.)
		delay = 1.;
	else if(delay * 2 > x->f_delay.f_lenghtMs)
		delay = x->f_delay.f_lenghtMs / 2.;

	x->f_grain = delay * 2. * 0.001 * x->f_sr;
	x->f_grain = ((double)(WINSIZE) * 2.) / x->f_grain;
	x->f_value = delay;
}

void alechinsky_tukey(t_alechinsky *x, double factor)
{
	int i, size, sizeMinus;
	
	if(factor <= 0.) 
		factor = 0.;
	else if(factor >= 1.) 
		factor = 1.;
	x->f_factor = factor;

	size = (1. - (1. - factor) / 2.) * (double)(WINSIZE);
	sizeMinus = size - 1;

	for(i = 0; i < WINSIZE; i++)
    {
		if(i <= ((factor * (double)sizeMinus) / 2.))
			x->f_window[i] = 0.5 * ( 1. + cos(PI * ( ((2. *(double)i) / (factor * (double)sizeMinus)) - 1.)));
		else if(i > ((factor * (double)sizeMinus) / 2.) && i <= ((double)sizeMinus * (1. - (factor / 2.))))
			x->f_window[i] = 1.;
		else if(i  > ((double)sizeMinus * (1. - (factor / 2.))) && i <= sizeMinus)
			x->f_window[i] = 0.5 * ( 1. + cos(PI * ( ((2. *(double)i) / (factor * (double)sizeMinus)) + 1. - (2. / factor))));
		else 
			x->f_window[i] = 0.;
    }
	for(i = 0; i < WINSIZE; i++)
    {
		x->f_delayVec[i] = (double)i / (double)WINSIZE;
	}

	x->f_window[WINSIZE] = x->f_window[0];
	x->f_delayVec[WINSIZE] = x->f_delayVec[0];
	alechinsky_delay(x, x->f_value);
}

void alechinsky_int(t_alechinsky *x, long n)	
{
	switch (proxy_getinlet((t_object *)x))
	{
		case 1: 
			alechinsky_delay(x, n);
			break;
		case 2: 
			alechinsky_tukey(x, n);
			break;
	}
	
}

void alechinsky_float(t_alechinsky *x, double n)	
{
	switch (proxy_getinlet((t_object *)x))
	{
		case 1:
			alechinsky_delay(x, n);
			break;
		case 2: 
			alechinsky_tukey(x, n);
			break;
	}
	
}

void alechinsky_dsp(t_alechinsky *x, t_signal **sp, short *count)
{
	x->f_sr = (double)sp[0]->s_sr;
	delay_resize(&x->f_delay, x->f_sr);

	dsp_add(alechinsky_perform, 4, x, sp[0]->s_vec, sp[1]->s_vec, sp[0]->s_n);
}

t_int *alechinsky_perform(t_int *w)
{
	int i, index, indexTwo;

	t_alechinsky *x		= (t_alechinsky *)(w[1]);
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

	return w + 5;
}

