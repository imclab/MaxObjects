
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
	CLASS_ATTR_LABEL			(c, "delay", 0, "Delay");
	CLASS_ATTR_DEFAULT			(c, "delay", 0, "2000");
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
	x->f_incOne = 0.;

	x->f_windowOne = (double *)getbytes(WINSIZE * sizeof(double));
	x->f_delayOne = (double *)getbytes(WINSIZE * sizeof(double));
	x->f_windowTwo = (double *)getbytes(WINSIZE * sizeof(double));
	x->f_delayTwo = (double *)getbytes(WINSIZE * sizeof(double));
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
	int delayTwo;

	for(i = 0; i < sampleframes; i++)
	{
		delay_write(&x->f_delay, in[i]);
		/*
		delayTwo = x->f_incOne + (int)((x->f_value * x->f_sr * 0.001));
		if(delayTwo >= (int)(x->f_value * x->f_sr * 0.001) * 2.)
			delayTwo -= (int)(x->f_value * x->f_sr * 0.001);

		sigDelayOne = delay_read_sample(&x->f_delay, x->f_incOne);
		sigDelayTwo = delay_read_sample(&x->f_delay, delayTwo);

		x->f_incOne += 2;
		if(x->f_incOne >= x->f_value * x->f_sr * 0.001 * 2.)
			x->f_incOne = XTRASAMPS;

		out[i] = sigDelayOne +  sigDelayTwo; */
		x->f_incOne++;
		if(x->f_incOne >= 16384)
			x->f_incOne = 0.;
		out[i] = x->f_windowOne[x->f_incOne] + x->f_windowTwo[x->f_incOne];
	}
}

void alechinsky_free(t_alechinsky *x)
{
	int i;
	dsp_free((t_pxobject *)x);
	delay_free(&x->f_delay);
	freebytes(x->f_windowOne, WINSIZE * sizeof(double));
	freebytes(x->f_delayOne, WINSIZE * sizeof(double));
	freebytes(x->f_windowTwo, WINSIZE * sizeof(double));
	freebytes(x->f_delayTwo, WINSIZE * sizeof(double));
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

void alechinsky_tukey(t_alechinsky *x, double factor)
{
	int i, j, size, sizeMinus, globalSize;
	
	if(factor <= 0.) 
		factor = 0.;
	else if(factor >= 1.) 
		factor = 1.;
	x->f_factor = factor;

	globalSize = WINSIZE;
	size = (factor + factor / 2.) * (double)globalSize;
	sizeMinus = size - 1;
	post("global %i, normal %i", globalSize, size);
	for(i = 0; i < globalSize; i++)
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
		else if(i  > ((double)sizeMinus * (1. - (factor / 2.))) && i < size)
		{
			x->f_windowOne[i] = 0.5 * ( 1. + cos(PI * ( ((2. *(double)i) / (factor * (double)sizeMinus)) + 1. - (2. / factor))));
			x->f_delayOne[i] = (double)i / (double)sizeMinus;
		}
		else 
		{
			x->f_windowOne[i] = 0.;
			x->f_delayOne[i] = 0.;
		}
    }
	
	for(i = 0; i < globalSize; i++)
    {
		j = i + globalSize / 2;
		if(j >= globalSize)
			j -= globalSize;
		x->f_windowTwo[i] = x->f_windowOne[j];
		x->f_delayTwo[i] = x->f_delayOne[j];
    }
}