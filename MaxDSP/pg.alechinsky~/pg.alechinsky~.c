
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
	//class_addmethod(c, (method)alechinsky_dsp,		"dsp",			A_CANT,	0);
	class_addmethod(c, (method)alechinsky_assist,		"assist",		A_CANT,	0);

	CLASS_ATTR_DOUBLE			(c, "delay", 0, t_alechinsky, f_value);
	CLASS_ATTR_LABEL			(c, "delay", 0, "Delay Time");
	CLASS_ATTR_DEFAULT			(c, "delay", 0, "2000");
	CLASS_ATTR_ACCESSORS		(c, "delay", NULL, delay_set);
	CLASS_ATTR_SAVE				(c, "delay", 1);
	CLASS_ATTR_FILTER_MIN		(c, "delay", 1);
	CLASS_ATTR_ORDER			(c, "delay", 0, "1");

	CLASS_ATTR_DOUBLE			(c, "tukey", 0, t_alechinsky, f_factor);
	CLASS_ATTR_LABEL			(c, "tukey", 0, "Tukey factor");
	CLASS_ATTR_ACCESSORS		(c, "tukey", NULL, factor_set);
	CLASS_ATTR_DEFAULT			(c, "tukey", 0, "0.5");
	CLASS_ATTR_SAVE				(c, "tukey", 1);
	CLASS_ATTR_FILTER_CLIP		(c, "tukey", 0, 1);
	CLASS_ATTR_ORDER			(c, "tukey", 0, "2");

	class_dspinit(c);
	class_register(CLASS_BOX, c);
	alechinsky_class = c;

	post("pg.alechinsky~ by Pierre Guillot",0);
	post("Copyright (C) 2012, Universite Paris 8");
	
	return 0;
}

void *alechinsky_new(t_symbol *s, int argc, t_atom *argv)
{
	int i;
	t_alechinsky *x = (t_alechinsky *)object_alloc((t_class *)alechinsky_class);

	/* Sampling Rate initialization **************/
	x->f_sr = sys_getsr();

	/* Windows Size Initialization **************/
	x->f_value = 0; 
	if( argv[0].a_type == A_LONG ) x->f_value = (int)(argv[0].a_w.w_long);
	if (x->f_value < 1)
	{
		x->f_value = 2000.;
	}
	x->f_inc = 0.;

	x->f_windowOne = (double *)getbytes((WINSIZE + 1) * sizeof(double));
	x->f_delayOne = (double *)getbytes((WINSIZE + 1) * sizeof(double));
	x->f_windowTwo = (double *)getbytes((WINSIZE + 1) * sizeof(double));
	x->f_delayTwo = (double *)getbytes((WINSIZE + 1) * sizeof(double));
	alechinsky_tukey(x, 0.2);

	delay_setup(&x->f_delay, 10000.);

	dsp_setup((t_pxobject *)x, 1);
	outlet_new((t_pxobject *)x, "signal");
	
	return (x);
}			

void alechinsky_dsp64(t_alechinsky *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	int i;
	x->f_sr = samplerate;
	delay_resize(&x->f_delay, x->f_sr);
	object_method(dsp64, gensym("dsp_add64"), x, alechinsky_perform64, 0, NULL);
}

void alechinsky_perform64(t_alechinsky *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	int i;
	double *in = ins[0];
	double *out = outs[0];
	double sigDelayOne, sigDelayTwo;

	for(i = 0; i < sampleframes; i++)
	{
		delay_write(&x->f_delay, in[i]);

		sigDelayOne = delay_read_ms(&x->f_delay, x->f_delayOne[(int)x->f_inc] * x->f_value);
		sigDelayTwo = delay_read_ms(&x->f_delay, x->f_delayTwo[(int)x->f_inc] * x->f_value);
		sigDelayOne *= x->f_windowOne[(int)x->f_inc];
		sigDelayTwo *= x->f_windowTwo[(int)x->f_inc];
		out[i] = sigDelayOne;

		x->f_inc += x->f_grain;
		if(x->f_inc >= WINSIZE)
			x->f_inc = 0;
	}
}

void alechinsky_free(t_alechinsky *x)
{
	dsp_free((t_pxobject *)x);
	delay_free(&x->f_delay);

	freebytes(x->f_windowOne, (WINSIZE + 1) * sizeof(double));
	freebytes(x->f_delayOne, (WINSIZE + 1) * sizeof(double));
	freebytes(x->f_windowTwo, (WINSIZE + 1) * sizeof(double));
	freebytes(x->f_delayTwo, (WINSIZE + 1) * sizeof(double));
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

t_max_err factor_set(t_alechinsky *x, t_object *attr, long argc, t_atom *argv)
{
	if ( atom_gettype(argv) == A_FLOAT)
		alechinsky_tukey(x, atom_getfloat(argv));
	return 0;
}

t_max_err delay_set(t_alechinsky *x, t_object *attr, long argc, t_atom *argv)
{
	if ( atom_gettype(argv) == A_FLOAT)
		alechinsky_delay(x, atom_getfloat(argv));
	return 0;
}

void alechinsky_delay(t_alechinsky *x, double delay)
{
	x->f_value = delay;
	x->f_grain = x->f_value * 0.001 * x->f_sr;
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
		{
			x->f_windowOne[i] = 0.5 * ( 1. + cos(PI * ( ((2. *(double)i) / (factor * (double)sizeMinus)) - 1.)));
			x->f_delayOne[i] = (double)i / (double)sizeMinus;
		}
		else if(i > ((factor * (double)sizeMinus) / 2.) && i <= ((double)sizeMinus * (1. - (factor / 2.))))
		{
			x->f_windowOne[i] = 1.;
			x->f_delayOne[i] = (double)i / (double)sizeMinus;
		}
		else if(i  > ((double)sizeMinus * (1. - (factor / 2.))) && i <= sizeMinus)
		{
			x->f_windowOne[i] = 0.5 * ( 1. + cos(PI * ( ((2. *(double)i) / (factor * (double)sizeMinus)) + 1. - (2. / factor))));
			x->f_delayOne[i] = (double)i / (double)sizeMinus;
		}
		else 
		{
			x->f_windowOne[i] = 0.;
			x->f_delayOne[i] = 0.;
		}
		x->f_windowTwo[i] = 1. - x->f_windowOne[i];
		x->f_delayTwo[i] = 1. - x->f_delayOne[i];
    }

	x->f_windowOne[WINSIZE] = x->f_windowOne[0];
	x->f_delayOne[WINSIZE] = x->f_delayOne[0];
	x->f_windowTwo[WINSIZE] = x->f_windowTwo[0];
	x->f_delayTwo[WINSIZE] = x->f_delayOne[0];
}
/*
void alechinsky_int(t_alechinsky *x, long n)	
{
	t_atom argv[1];
	switch (proxy_getinlet((t_object *)x))
	{
		case 1: 
			object_method_double((t_object)x, gensym("delay"), n, argv);
			break;
		case 2: 
			object_method(x, gensym("factor"), 1, argv[1]);
			break;
	}
	
}

void alechinsky_float(t_alechinsky *x, double n)	
{
	t_atom argv[1];
	switch (proxy_getinlet((t_object *)x))
	{
		atom_setfloat(argv, n);
		case 1:
			object_method(x, gensym("delay"), 1, argv[1]);
			break;
		case 2: 
			object_method(x, gensym("factor"), 1, argv[1]);
			break;
	}
	
}
*/