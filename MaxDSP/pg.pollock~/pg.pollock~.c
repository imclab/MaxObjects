/**********************************************************************/
//                                                                    //
// /****************************************************************/ //
// /*                                                              */ //
// /*                         POLLOCK	                           */ //
// /*                                                              */ //
// /* Auteur: Pierre GUILLOT                                       */ //
// /*         Universite Paris 8									*/ //
// /*                                                              */ //
// /*                                                              */ //
// /*                                                              */ //
// /****************************************************************/ //
//                                                                    //
/**********************************************************************/


/********************************************************************/
/*                          EN TETE                                 */
/********************************************************************/

#include "pg.pollock.h"

/**********************************************************************/
/*							FONCTION MAIN	                          */
/**********************************************************************/

int main(void)
{
    t_class *c;

	c = class_new("pg.pollock~", (method)pollock_new, (method)pollock_free, (short)sizeof(t_pollock), 0L, A_GIMME, 0);
    
    class_addmethod(c, (method)pollock_dsp,			"dsp",			A_CANT,		0); 
    class_addmethod(c, (method)pollock_int,			"int",			A_LONG,		0);
	class_addmethod(c, (method)pollock_float,		"float",		A_FLOAT,	0);
    class_addmethod(c, (method)pollock_assist,		"assist",		A_CANT,		0);
	class_addmethod(c, (method)pollock_dblclick,	"dblclick",		A_CANT,		0);
	
	
    class_dspinit(c);
	class_register(CLASS_BOX, c);
	pollock_class = c;
	
	CLASS_ATTR_LONG				(c, "envelope", 0, t_pollock, f_modEnv);
	CLASS_ATTR_LABEL			(c, "envelope", 0, "Envelope type");
	CLASS_ATTR_ENUMINDEX		(c, "envelope", 0, "Hanning \" \"Flat_top \" \"Poison \" \"Turkey \"Decay \" \"Rise");
	CLASS_ATTR_ACCESSORS		(c, "envelope", NULL, mode_set);
	CLASS_ATTR_DEFAULT			(c, "envelope", 0, "0");
	CLASS_ATTR_SAVE				(c, "envelope", 1);
	CLASS_ATTR_FILTER_CLIP		(c, "envelope", 0, 5);
	CLASS_ATTR_ORDER			(c, "envelope", 0, "1");
	
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
	post("Universite Paris 8, France",0);
	

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
	if (x = (t_pollock *)object_alloc(pollock_class)) 
	{

		/* Initialization of the sampling rate and the vector size ********/
		x->f_sr = sys_getsr();
		x->f_sb	= sys_getmaxblksize();
		
		/* Initialization of the envelope  ********************************/
		window_setup(&x->f_envelope, WINDOW_SIZE);

		/* Initialization of the delays ***********************************/
		if( argv[0].a_type == A_LONG ) x->f_voices = argv[0].a_w.w_long;
		else x->f_voices = 2;

		x->f_delay = (t_delay *)getbytes(x->f_voices * sizeof(t_delay));
		for(i = 0; i < x->f_voices; i++) delay_init(&x->f_delay[i], SIZETAB);
		
		x->f_inputSig = (t_sample *)getbytes(x->f_sb * sizeof(t_sample));
		for(i = 0; i < x->f_sb; i++) x->f_inputSig[i] = 0.f;
		
		window_hanning(&x->f_envelope);
		if( argv[1].a_type == A_LONG ) x->f_modEnv = argv[1].a_w.w_long;
		else x->f_modEnv = 0;
		switch(x->f_modEnv)
		{
			case 0:
				window_hanning(&x->f_envelope);
				break;
			case 1:
				window_flat_top(&x->f_envelope);
				break;
			case 2:
				window_poison(&x->f_envelope);
				break;
			case 3:
				window_turkey(&x->f_envelope);
				break;
			case 4:
				window_decay(&x->f_envelope);
				break;
			case 5:
				window_rise(&x->f_envelope);
				break;
		}
		
		/* Initialization for the granulation *****************************/
		x->f_grainLenght	= 1000.f;
		x->f_delayTime		= 1000.f;
		x->f_feedback		= 0.f;
		x->f_rarefaction	= 0.f;
		
		/* Initialization of the inlets ***********************************/

		x->x_proxy = proxy_new((t_object *)x, 4, &x->f_inlet);
		x->x_proxy = proxy_new((t_object *)x, 3, &x->f_inlet);
		x->x_proxy = proxy_new((t_object *)x, 2, &x->f_inlet);
		x->x_proxy = proxy_new((t_object *)x, 1, &x->f_inlet);
		dsp_setup((t_pxobject *)x,1);
		

		/* Creation des sorties */
		outlet_new((t_object *)x, "signal");
	}
	
    return (x);
	
}

void pollock_dsp(t_pollock *x, t_signal **sp, short *count)
{
	int i;

	x->f_sr = sp[0]->s_sr;
	
	for(i = 0; i < x->f_voices; i++)
	{
		delay_dspInit( &x->f_delay[i], x->f_sr, sp[0]->s_n);
	}
	dsp_add(pollock_perform, 4, x, sp[0]->s_vec, sp[1]->s_vec, sp[0]->s_n);

}


t_int *pollock_perform(t_int *w)
{
	t_pollock *x = (t_pollock *)(w[1]);
    t_sample *in = (t_sample *)(w[2]);
	t_sample *out = (t_sample *)(w[3]);
	int n = (int)w[4];
	int i, j;
	
	t_delay *ctl;
	t_sample *env;
	t_sample *del;
	
	float index;
	float diff;
	
	int nsamps;
	int phase;
    t_sample limit;
    t_sample fn;
    t_sample *vp, *bp, *wp, *ep;
	float rec;
	t_sample delsamps;
	
	for(j = 0; j < n; j++)
	{
		x->f_inputSig[j] = *in++;
		*out++ = 0.f;
	}
	out -= n;
	in -= n;
	
	for(i = 0; i < x->f_voices; i++)
	{
		ctl = &x->f_delay[i];
		env = ctl->f_envelopeSig;
		del = ctl->f_delaySig;
	
		nsamps = ctl->f_n;
		limit = nsamps - n - 1;
		
		for(j = 0; j < n; j++)
		{
			index = ctl->f_count * (float)(WINDOW_SIZE-1);
			diff = index - (int)index;
			*env++ = (x->f_envelope.f_envelope[(int)index] * (1.f - diff) + x->f_envelope.f_envelope[(int)index+1] * diff) * ctl->f_modAmp;
			*del++ = ctl->f_delTime;
			
			ctl->f_count += ctl->f_grainLenghtDev;
			if(ctl->f_count >= 1.f)
			{
				ctl->f_count = 0.f;
				ctl->f_grainLenghtDev	= (1000.f/ ((float)x->f_grainLenght * (((((float)rand()/(float)RAND_MAX) * (x->f_modLen / 100.f))) + (1.f - (x->f_modLen / 100.f)))  )) / x->f_sr;
				ctl->f_delTime			= ((((float)rand() / (float)RAND_MAX) * (x->f_modDel / 100.f) + ((100.f - x->f_modDel) / 100.)) * ((float)i / (float)x->f_voices) * x->f_delayTime) * x->f_sr * 0.001f - n;
				
				if (ctl->f_delTime < 1.00001f)	ctl->f_delTime = 1.00001f;
				if (ctl->f_delTime > limit)		ctl->f_delTime = limit;
	
				if( (rand() % 101 ) >= x->f_rarefaction)
				{
					ctl->f_modAmp = ((((float)rand() / (float)RAND_MAX) * (x->f_modAmp / 100.f)) + (1.f - (x->f_modAmp / 100.)));
				}
				else ctl->f_modAmp = 0.f;
			}
		}
	
		env -= n;
		del -= n;
		
		fn = n-1;
		vp = ctl->f_vector;
		wp = vp + ctl->f_phase;

		for(j = 0; j < n; j++)
		{
			delsamps = *del++;
			
			delsamps += fn;
			fn -= 1.f;
			
			bp = wp - (int)delsamps;
			if (bp < vp) bp += nsamps;

			rec = *bp * *env;
	
			*out++ += rec / (float)x->f_voices;
			*env++ = rec * x->f_feedback;
		}

		out -= n;
		env -= n;
		del -= n;
		
		phase = ctl->f_phase;
		bp = vp + phase;
		ep = vp + ctl->f_n;
		phase += n;
			
		for(j = 0; j < n; j++)
		{
			*bp++ = x->f_inputSig[j] + *env++;
			if (bp == ep)
			{
				bp = vp;
				phase -= nsamps;
			}
		}
		bp = vp + ctl->f_phase;
		env -= n;
		ctl->f_phase = phase;
	}
		
	
	return w + 5;
}

void pollock_free(t_pollock *x)
{

	int i;
	dsp_free((t_pxobject *)x);
	freeobject((t_object *) x->x_proxy);
	window_free(&x->f_envelope);
	
	for(i = 0; i < x->f_voices; i++) delay_free(&x->f_delay[i]);
	freebytes((t_delay *)x->f_delay, x->f_voices * sizeof(t_delay));
	
	freebytes((t_sample *)x->f_inputSig, x->f_sb * sizeof(t_sample));
  return;
}

void pollock_assist(t_pollock *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) {
		switch (a) {
				
			case 0:
				sprintf(s,"Input signal (signal)");
				break;
			case 1:
				sprintf(s,"Grain lenght (int or float)");
				break;
			case 2:
				sprintf(s,"Delay time (int or float)");
				break;
			case 3:
				sprintf(s,"Feedback (int or float)");
				break;
			case 4:
				sprintf(s,"Rarefaction (int or float)");
				break;
		}
	} else
		sprintf(s,"Granulated signal (signal)");
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
			for(i = 0; i < x->f_voices; i++)
			{
				x->f_delay[i].f_amp = x->f_feedback;
			}
			break;
		case 4: 
			/* Defini la raréfaction du grain **************************/
			x->f_rarefaction = n;
			break;
	}
	
}

void pollock_float(t_pollock *x, double n)	
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
			for(i = 0; i < x->f_voices; i++)
			{
				x->f_delay[i].f_amp = x->f_feedback;
			}
			break;
		case 4: 
			/* Defini la raréfaction du grain **************************/
			x->f_rarefaction = n;
			break;
	}
	
}

void pollock_dblclick(t_pollock *x)
{
	;
}

t_max_err mode_set(t_pollock *x, t_object *attr, long argc, t_atom *argv)
{
	int mode;
	
	if ( atom_gettype(argv) == A_LONG) mode = atom_getlong(argv);
	else if ( atom_gettype(argv) == A_FLOAT) mode = (int)atom_getfloat(argv);
	else if ( atom_gettype(argv) == A_SYM)
	{
		if ( gensym(argv->a_w.w_sym->s_name)	  == gensym("Hanning")) mode = 0;
		else if ( gensym(argv->a_w.w_sym->s_name) == gensym("Flat"))	mode = 1;
		else if ( gensym(argv->a_w.w_sym->s_name) == gensym("Poison"))	mode = 2;
		else if ( gensym(argv->a_w.w_sym->s_name) == gensym("Turkey"))	mode = 3;
		else if ( gensym(argv->a_w.w_sym->s_name) == gensym("Decay"))	mode = 4;
		else if ( gensym(argv->a_w.w_sym->s_name) == gensym("Rise"))	mode = 5;
	}


	x->f_modEnv = mode;
	switch(x->f_modEnv)
	{
		case 0:
			window_hanning(&x->f_envelope);
			break;
		case 1:
			window_flat_top(&x->f_envelope);
			break;
		case 2:
			window_poison(&x->f_envelope);
			break;
		case 3:
			window_turkey(&x->f_envelope);
			break;
		case 4:
			window_decay(&x->f_envelope);
			break;
		case 5:
			window_rise(&x->f_envelope);
			break;
	}
	
	return 0;
}