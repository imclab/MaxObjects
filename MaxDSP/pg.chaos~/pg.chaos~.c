/**********************************************************************/
//                                                                    //
// /****************************************************************/ //
// /*                                                              */ //
// /*                         CHAOS 							   */ //
// /*                                                              */ //
// /* Auteur: Pierre GUILLOT                                       */ //
// /*         Etudiant Universite Paris 8						   */ //
// /*                                                              */ //
// /*                                                              */ //
// /*                                                              */ //
// /****************************************************************/ //
//                                                                    //
/**********************************************************************/


/********************************************************************/
/*                          EN TETE                                 */
/********************************************************************/
#include "pg.chaos.h"
#include "pg.ikeda.h"
#include "pg.mira.h"
#include "pg.jong.h"
#include "pg.lorenz.h"
#include "pg.clifford.h"
#include "pg.duffing.h"

int main()
{
	t_class *c;
	
	c = class_new("pg.chaos~", (method)chaos_new, (method)chaos_free, (short)sizeof(t_chaosSig), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)chaos_float,		"float",	A_FLOAT,	0);
	class_addmethod(c, (method)chaos_int,		"int",		A_LONG,		0);
	class_addmethod(c, (method)chaos_list,		"list",		A_GIMME,	0);
	class_addmethod(c, (method)chaos_assist,	"assist",	A_CANT,		0);
	class_addmethod(c, (method)chaos_reset,		"reset",				0);
	class_addmethod(c, (method)chaos_set,		"set",		A_GIMME,	0);
	class_addmethod(c, (method)chaos_print,		"print",				0);
	class_addmethod(c, (method)chaos_record,	"record",				0);
	class_addmethod(c, (method)chaos_dsp,		"dsp",		A_CANT,		0);
	class_dspinit(c);
	class_register(CLASS_BOX, c);
	chaosTilde_class = c;
	
	CLASS_ATTR_LONG				(c, "mode", 0, t_chaosSig, f_mode);
	CLASS_ATTR_LABEL			(c, "mode", 0, "Mode");
	CLASS_ATTR_ENUMINDEX		(c, "mode", 0, "Ikeda \" \"Mira \" \"Jong \" \"Lorenz \"Clifford \"Duffing");
	CLASS_ATTR_ACCESSORS		(c, "mode", NULL, mode_set);
	CLASS_ATTR_DEFAULT			(c, "mode", 0, "1");
	CLASS_ATTR_SAVE				(c, "mode", 0);
	
	post("pg.chaos~ by Pierre Guillot",0);
	post("Universite Paris 8, France",0);
	
	
	return 0;
}

void *chaos_new(t_symbol *s, int argc, t_atom *argv)
{
	t_chaosSig *x = NULL;
	int i;
	t_atom *argu;
	
	if (x = (t_chaosSig *)object_alloc(chaosTilde_class)) 
	{
		x->f_sr = sys_getsr();
		x->f_count = 0;
		if(argc > 0)
		{
			argu = (t_atom *)getbytes((argc + 1) * sizeof(t_atom));
			SETSYM(argu, gensym("@mode"));
			SETSYM(argu+1, argv->a_w.w_sym);
			for(i = 1; i < argc; i++)
			{
				if ( atom_gettype(argv+i)== A_FLOAT)
				{
					SETFLOAT(argu+i+1, atom_getfloat(argv+i));
					//post("%f", atom_getfloat(argv+i));
				}
				else if ( atom_gettype(argv+i)== A_LONG)
				{
					SETFLOAT(argu+i+1, (float)atom_getlong(argv+i));
					//post("%ld", atom_getlong(argv+i));
				}
			}
			attr_args_process(x, argc+1, argu);
		}
		else
		{
			//post("Bouh");
			argu = (t_atom *)getbytes(2 * sizeof(t_atom));
			SETSYM(argu, gensym("@mode"));
			SETSYM(argu+1, gensym("Ikeda"));
			attr_args_process(x, 2, argu);
		}
		
		x->f_ramp = 0;
		
		freebytes(argu, ((argc + 1) * sizeof(t_atom)));

		trigo_createCos(&x->f_cos, 8192);
		trigo_createSin(&x->f_sin, 8192);

		dsp_setup((t_pxobject *)x, 1);
		x->out4 = listout((t_object *)x);
		outlet_new((t_pxobject *)x, "signal");
		outlet_new((t_pxobject *)x, "signal");
		outlet_new((t_pxobject *)x, "signal");
	}
	
	return x;
}

void chaos_dsp(t_chaosSig *x, t_signal **sp, short *count)
{
	x->f_sr = (int)sp[0]->s_sr;
	//post("sampling rate %ld", x->f_sr);

	if (!count[0])
		dsp_add(chaos_performOffset, 5, x, sp[1]->s_vec, sp[2]->s_vec, sp[3]->s_vec, sp[0]->s_n);
	else
		dsp_add(chaos_perform, 6, x, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, sp[3]->s_vec, sp[0]->s_n);
}

t_int *chaos_perform(t_int *w)
{
	t_chaosSig	*x		= (t_chaosSig *)	(w[1]);
	t_float	*in1	= (t_sample *)	(w[2]);
	t_float	*out1	= (t_sample *)	(w[3]);
	t_float	*out2	= (t_sample *)	(w[4]);
	t_float	*out3	= (t_sample *)	(w[5]);
	int n			= (int)	(w[6]);

	if (x->f_ob.z_disabled) return w + 7;
	
	while(n--)
	{
		x->f_frequency = x->f_sr / *in1++;
		if(x->f_frequency <= 0) x->f_frequency = -x->f_frequency;
		if(x->f_ramp >= x->f_frequency)
		{
			switch(x->f_mode)
			{
			case 0:
				ikeda_bang(x);
				break;
			case 1:
				mira_bang(x);
				break;
			case 2:
				jong_bang(x);
				break;
			case 3:
				lorenz_bang(x);
				break;
			case 4:
				clifford_bang(x);
				break;
			case 5:
				duffing_bang(x);
				break;
			}
			x->f_ramp = -1;
		}
		x->f_ramp++;
		*out1++ = x->f_out1;
		*out2++ = x->f_out2;
		*out3++ = x->f_out3;
	}
	return (w + 7);
}

t_int *chaos_performOffset(t_int *w)
{
	t_chaosSig	*x		= (t_chaosSig *)	(w[1]);
	t_float	*out1	= (t_sample *)	(w[2]);
	t_float	*out2	= (t_sample *)	(w[3]);
	t_float	*out3	= (t_sample *)	(w[4]);
	int n			= (int)	(w[5]);

	if (x->f_ob.z_disabled) return w + 6;
	
	while(n--)
	{
		if(x->f_ramp >= x->f_frequency)
		{
			switch(x->f_mode)
			{
			case 0:
				ikeda_bang(x);
				break;
			case 1:
				mira_bang(x);
				break;
			case 2:
				jong_bang(x);
				break;
			case 3:
				lorenz_bang(x);
				break;
			case 4:
				clifford_bang(x);
				break;
			case 5:
				duffing_bang(x);
				break;
			}
			x->f_ramp = -1;
		}
		x->f_ramp++;
		*out1++ = x->f_parameter[0];
		*out2++ = x->f_parameter[1];
		*out3++ = x->f_parameter[2];
	}
	return (w + 6);
}

void chaos_float(t_chaosSig *x, double f)
{
	//post("%f", (float)f);
	if(f == 0) x->f_frequency = 0.f;
	else
	{
		if(f < 0) f *= -1;
		x->f_frequency = (float)x->f_sr / f;
	}
	//post("frequency %f", x->f_frequency);
}

void chaos_int(t_chaosSig *x, long l)
{
	chaos_float(x, (float)l);
}

void chaos_reset(t_chaosSig *x)
{
	switch(x->f_mode)
	{
		case 0:
			ikeda_reset(x);
			break;
		case 1:
			mira_reset(x);
			break;
		case 2:
			jong_reset(x);
			break;
		case 3:
			lorenz_reset(x);
			break;
		case 4:
			clifford_reset(x);
			break;
		case 5:
			duffing_reset(x);
			break;
	}
}

void chaos_bang(t_chaosSig *x)
{
	switch(x->f_mode)
	{
		case 0:
			ikeda_bang(x);
			break;
		case 1:
			mira_bang(x);
			break;
		case 2:
			jong_bang(x);
			break;
		case 3:
			lorenz_bang(x);
			break;
		case 4:
			clifford_bang(x);
			break;
		case 5:
			duffing_bang(x);
			break;
	}
}

void chaos_list(t_chaosSig *x, t_symbol *s, short ac, t_atom *av)
{
	switch(x->f_mode)
	{
		case 0:
			ikeda_list(x, s, ac, av);
			break;
		case 1:
			mira_list(x, s, ac, av);
			break;
		case 2:
			jong_list(x, s, ac, av);
			break;
		case 3:
			lorenz_list(x, s, ac, av);
			break;
		case 4:
			clifford_list(x, s, ac, av);
			break;
		case 5:
			duffing_list(x, s, ac, av);
			break;
	}
}

void chaos_set(t_chaosSig *x, t_symbol *s, short ac, t_atom *av)
{
	switch(x->f_mode)
	{
		case 0:
			ikeda_set(x, s, ac, av);
			break;
		case 1:
			mira_set(x, s, ac, av);
			break;
		case 2:
			jong_set(x, s, ac, av);
			break;
		case 3:
			lorenz_set(x, s, ac, av);
			break;
		case 4:
			clifford_set(x, s, ac, av);
			break;
		case 5:
			duffing_set(x, s, ac, av);
			break;
	}
}

void chaos_print(t_chaosSig *x)
{
	switch(x->f_mode)
	{
		case 0:
			ikeda_print(x);
			break;
		case 1:
			mira_print(x);
			break;
		case 2:
			jong_print(x);
			break;
		case 3:
			lorenz_print(x);
			break;
		case 4:
			clifford_print(x);
			break;
		case 5:
			duffing_print(x);
			break;
	}
}

void chaos_record(t_chaosSig *x)
{
	switch(x->f_mode)
	{
		case 0:
			ikeda_record(x);
			break;
		case 1:
			mira_record(x);
			break;
		case 2:
			jong_record(x);
			break;
		case 3:
			lorenz_record(x);
			break;
		case 4:
			clifford_record(x);
			break;
		case 5:
			duffing_record(x);
			break;
	}
}

void chaos_free(t_chaosSig *x)
{
	dsp_free((t_pxobject *)x);
	trigo_free(&x->f_cos);
	trigo_free(&x->f_sin);
}

void chaos_assist(t_chaosSig *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET)
	{
		sprintf(s,"Frequency (float or signal) and parameters x, y, z, a, b, c, d (list)");
	}
	else 
	{
		switch (a) 
		{	
			case 0:
				sprintf(s,"Coordinates x (signal)");
				break;
			case 1:
				sprintf(s,"Coordinates y (signal)");
				break;
			case 2:
				sprintf(s,"Coordinates z (signal)");
				break;
			case 3:
				sprintf(s,"Initial parameters (list)");
				break;
		}
		
	}
}

t_max_err mode_set(t_chaosSig *x, t_object *attr, long argc, t_atom *argv)
{
	int mode;
	/*
	int i;
	for(i = 1; i < argc; i++)
	{
		post("%f", atom_getfloat(argv+i));
	}
	*/
	if ( atom_gettype(argv) == A_LONG) mode = atom_getlong(argv);
	else if ( atom_gettype(argv) == A_FLOAT) mode = (int)atom_getfloat(argv);
	else if ( atom_gettype(argv) == A_SYM)
	{
		if ( gensym(argv->a_w.w_sym->s_name) == gensym("Ikeda")) mode = 0;
		else if ( gensym(argv->a_w.w_sym->s_name) == gensym("Mira")) mode = 1;
		else if ( gensym(argv->a_w.w_sym->s_name) == gensym("Jong")) mode = 2;
		else if ( gensym(argv->a_w.w_sym->s_name) == gensym("Lorenz")) mode = 3;
		else if ( gensym(argv->a_w.w_sym->s_name) == gensym("Clifford")) mode = 4;
		else if ( gensym(argv->a_w.w_sym->s_name) == gensym("Duffing")) mode = 5;
	}
	
	if (mode != x->f_mode || x->f_count == 0)
	{
		x->f_mode = mode;
		switch(x->f_mode)
		{
			case 0:
				ikeda_init(x, gensym("init"), argc-1, argv+1 );
				break;
			case 1:
				mira_init(x, gensym("init"), argc-1, argv+1 );
				break;
			case 2:
				jong_init(x, gensym("init"), argc-1, argv+1 );
				break;
			case 3:
				lorenz_init(x, gensym("init"), argc-1, argv+1 );
				break;
			case 4:
				clifford_init(x, gensym("init"), argc-1, argv+1 );
				break;
			case 5:
				duffing_init(x, gensym("init"), argc-1, argv+1 );
				break;
		}
	}
	return 0;
}
