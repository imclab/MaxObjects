
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

#include "pg.delayObj.h"

int main()
{
	t_class *c;

	c = class_new("pg.delay~", (method)delayObj_new, (method)delayObj_free, (short)sizeof(t_delayObj), 0L, A_GIMME, 0);
	class_addmethod(c, (method)delayObj_dsp64,			"dsp64",		A_CANT,	0);
	class_addmethod(c, (method)delayObj_dsp,			"dsp",			A_CANT,	0);
	class_addmethod(c, (method)delayObj_assist,			"assist",		A_CANT,	0);

	class_dspinit(c);
	class_register(CLASS_BOX, c);
	delayObj_class = c;

	post("pg.delay~ by Pierre Guillot",0);
	post("Copyright (C) 2012, Universite Paris 8");
	
	return 0;
}

void *delayObj_new(t_symbol *s, int argc, t_atom *argv)
{
	
	t_delayObj *x = NULL;
	if (x = (t_delayObj *)object_alloc((t_class *)delayObj_class)) 
	{
		x->f_sr = sys_getsr();
		delay_setup(&x->f_delay, 10000., x->f_sr);

		dsp_setup((t_pxobject *)x, 2);
		outlet_new((t_pxobject *)x, "signal");

		attr_args_process(x, argc, argv);
	}
	
	return (x);
}			

void delayObj_dsp64(t_delayObj *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	int i;
	x->f_sr = samplerate;
	delay_resize(&x->f_delay, x->f_sr);
	object_method(dsp64, gensym("dsp_add64"), x, delayObj_perform64, 0, NULL);
}

void delayObj_perform64(t_delayObj *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	int i;
	for(i = 0; i < sampleframes; i++)
	{ 
		delay_write(&x->f_delay, ins[0][i]);
		outs[0][i] = delay_read_ms_quadra(&x->f_delay, ins[1][i]);		
	}
}

void delayObj_free(t_delayObj *x)
{
	dsp_free((t_pxobject *)x);
	delay_free(&x->f_delay);
}

void delayObj_assist(t_delayObj *x, void *b, long m, long a, char *s)
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
		sprintf(s,"(Signal) Delayed signal %i", (int)a);
	}
}

void delayObj_dsp(t_delayObj *x, t_signal **sp, short *count)
{
	x->f_sr = (double)sp[0]->s_sr;
	delay_resize(&x->f_delay, x->f_sr);

	dsp_add(delayObj_perform, 4, x, sp[0]->s_vec, sp[1]->s_vec, sp[0]->s_n);
}

t_int *delayObj_perform(t_int *w)
{/*
	int i, index, indexTwo;

	t_delay *x		= (t_delay *)(w[1]);
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

