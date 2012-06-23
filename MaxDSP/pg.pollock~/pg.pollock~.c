
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

#include "pg.pollock.h"

int main(void)
{
    t_class *c;

	c = class_new("pg.pollock~", (method)pollock_new, (method)pollock_free, (short)sizeof(t_pollock), 0L, A_GIMME, 0);
    
    class_addmethod(c, (method)pollock_dsp,			"dsp",			A_CANT,		0); 
    class_addmethod(c, (method)pollock_int,			"int",			A_LONG,		0);
	class_addmethod(c, (method)pollock_double,		"float",		A_FLOAT,	0);
    class_addmethod(c, (method)pollock_assist,		"assist",		A_CANT,		0);
	
	CLASS_ATTR_FLOAT			(c, "ampmod", 0, t_pollock, f_modAmp);
	CLASS_ATTR_LABEL			(c, "ampmod", 0, "Amplitude modulation");
	CLASS_ATTR_DEFAULT			(c, "ampmod", 0, "0.");
	CLASS_ATTR_SAVE				(c, "ampmod", 1);
	CLASS_ATTR_FILTER_CLIP		(c, "ampmod", 0., 100.);
	
	CLASS_ATTR_FLOAT			(c, "lenmod", 0, t_pollock, f_modLen);
	CLASS_ATTR_LABEL			(c, "lenmod", 0, "Grain lenght modulation");
	CLASS_ATTR_DEFAULT			(c, "lenmod", 0, "0.");
	CLASS_ATTR_SAVE				(c, "lenmod", 1);
	CLASS_ATTR_FILTER_CLIP		(c, "lenmod", 0., 100.);
	
	CLASS_ATTR_FLOAT			(c, "delmod", 0, t_pollock, f_modDel);
	CLASS_ATTR_LABEL			(c, "delmod", 0, "Delay modulation");
	CLASS_ATTR_DEFAULT			(c, "delmod", 0, "100.");
	CLASS_ATTR_SAVE				(c, "delmod", 1);
	CLASS_ATTR_FILTER_CLIP		(c, "delmod", 0., 100.);
	
	post("pg.pollock~ by Pierre Guillot",0);
	post("Copyright (C) 2012, Universite Paris 8");
	
    class_dspinit(c);
	class_register(CLASS_BOX, c);
	pollock_class = c;

	return 0;
}

/**********************************************************************/
/*                       FONCTION CREATION                            */
/**********************************************************************/

void *pollock_new(t_symbol *s, int argc, t_atom *argv)
{
	int i;
	/* Allocation de la dataspace *************************************/
	t_pollock *x = NULL;
	if (x = (t_pollock *)object_alloc((t_class *)pollock_class)) 
	{

		/* Initialization of the sampling rate and the vector size ********/
		x->f_sr = sys_getsr();
		x->f_sb	= sys_getmaxblksize();
		
		/* Initialization of the envelope  ********************************/
		x->f_window = (double *)getbytes((WINSIZE + 1) * sizeof(double));
		pollock_tukey(x, 0., 0.);

		/* Initialization of the delays ***********************************/
		if( argv[0].a_type == A_LONG ) x->f_voices = argv[0].a_w.w_long;
		else x->f_voices = 2;

		delay_setup(&x->f_delay, SIZETAB, x->f_sr);
		
		/* Initialization for the granulation *****************************/
		x->f_grainLenght	= 1000.f;
		x->f_delayTime		= 1000.f;
		x->f_feedback		= 0.f;
		x->f_rarefaction	= 0.f;
		
		dsp_setup((t_pxobject *)x,5);
		outlet_new((t_object *)x, "signal");
		attr_args_process(x, argc, argv);
	}
	
    return (x);
	
}

void pollock_dsp(t_pollock *x, t_signal **sp, short *count)
{
	x->f_sr = sp[0]->s_sr;
	delay_resize(&x->f_delay, x->f_sr);
	dsp_add(pollock_perform, 4, x, sp[0]->s_vec, sp[1]->s_vec, sp[0]->s_n);
}


t_int *pollock_perform(t_int *w)
{
	t_pollock *x = (t_pollock *)(w[1]);
    float *in = (float *)(w[2]);
	float *out = (float *)(w[3]);
	int n = (int)w[4];
	float voiceSig;
	int i, j;

	for(i = 0; i < n; i++)
	{
		delay_write(&x->f_delay, in[n]);
		out[n] = 0.f;
		for(j = 0; j < x->f_voices; j++)
		{
			voiceSig = delay_read_ms_linear(&x->f_delay, x->f_delayTime);
			out[n] += voiceSig;
		}
	}
	
	return w + 5;
}

void pollock_free(t_pollock *x)
{
	dsp_free((t_pxobject *)x);
	freeobject((t_object *) x->x_proxy);
	freebytes(x->f_window, (WINSIZE + 1) * sizeof(double));
	delay_free(&x->f_delay);
}

void pollock_assist(t_pollock *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) {
		switch (a) {
				
			case 0:
				sprintf(s,"(Signal) Input signal");
				break;
			case 1:
				sprintf(s,"(Signal, Int or Float) Grain lenght ");
				break;
			case 2:
				sprintf(s,"(Signal, Int or Float) Delay time");
				break;
			case 3:
				sprintf(s,"(Signal, Int or Float) Feedback");
				break;
			case 4:
				sprintf(s,"(Signal, Int or Float) Rarefaction");
				break;
		}
	} else
		sprintf(s,"(Signal) Pollocked signal");
}


/**********************************************************************/
/*                       FONCTION INLETS                              */
/**********************************************************************/

void pollock_int(t_pollock *x, long n)	
{
	int i;
	switch (proxy_getinlet((t_object *)x))
	{
		case 1: 
			/* Defini la taille du grain *******************************/
			if (n < 1) n = 1;
			x->f_grainLenght = n;
			break;
		case 2: 
			/* Defini le temps de delai ********************************/
			if (n < 0) n = 1;
			if (n < 10000) n = 10000;
			x->f_delayTime = n;
			break;
		case 3: 
			/* Defini la reinjection ***********************************/
			if (n > 99) n = 99;
			else if (n <= 0 ) n = 0;
			x->f_feedback = n/100.0;
			break;
		case 4: 
			/* Defini la raréfaction du grain **************************/
			x->f_rarefaction = n;
			break;
	}
	
}

void pollock_double(t_pollock *x, double n)	
{
	int i;
	switch (proxy_getinlet((t_object *)x))
	{
		case 1: 
			/* Defini la taille du grain *******************************/
			if (n < 0) n = 1;
			x->f_grainLenght = n;
			break;
		case 2: 
			/* Defini le temps de delai ********************************/
			if (n < 0) n = 1;
			if (n < 10000) n = 10000;
			x->f_delayTime = n;
			break;
		case 3: 
			/* Defini la reinjection ***********************************/
			if (n > 99.f) n = 99.f;
			else if (n <= 0.f ) n = 0.f;
			x->f_feedback = n/100.0;
			break;
		case 4: 
			/* Defini la raréfaction du grain **************************/
			x->f_rarefaction = n;
			break;
	}
	
}

void pollock_tukey(t_pollock *x, double factor, double offset)
{
	int i, size, sizeMinus, ratio;
	
	if(factor <= 0.) 
		factor = 0.;
	else if(factor >= 1.) 
		factor = 1.;
	x->f_factor = factor;
	x->f_offset = offset;

	sizeMinus = WINSIZE - 1;
	ratio = ((factor * (double)sizeMinus) / 2.);

	for(i = 0; i < WINSIZE; i++)
    {
		if(i <= ratio)
			x->f_window[i] = 0.5 * ( 1. + cos(PI * ( ((2. *(double)i) / (factor * (double)sizeMinus)) - 1.)));
		else if(i > ratio && i <= ((double)sizeMinus * (1. - (factor / 2.))))
			x->f_window[i] = 1.;
		else if(i  > ((double)sizeMinus * (1. - (factor / 2.))) && i <= sizeMinus)
			x->f_window[i] = 0.5 * ( 1. + cos(PI * ( ((2. *(double)i) / (factor * (double)sizeMinus)) + 1. - (2. / factor))));
		else 
			x->f_window[i] = 0.;
    }

	x->f_window[WINSIZE] = x->f_window[0];
}
