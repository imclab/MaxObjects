
/**** Les bibliotheques ****/
#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"	

/**** La structure de l'objet ****/
typedef struct _adaptor 
{
	t_pxobject	f_ob;
	int			f_intletCount;
	int			f_vectorSize;
	t_sample	*f_out;
} t_adaptor;

/**** Prototypes des fonctions ****/
void *adaptor_new(t_symbol *s, long argc, t_atom *argv);
void adaptor_free(t_adaptor *x);
void adaptor_assist(t_adaptor *x, void *b, long m, long a, char *s);

void adaptor_dsp(t_adaptor *x, t_signal **sp, short *count);//
t_int *adaptor_perform(t_int *w);

void *adaptor_class;

/*** Fonction principales ****/
int main(void)
{	
	t_class *c;
	
	c = class_new("pg.adaptor~", (method)adaptor_new, (method)adaptor_free, (long)sizeof(t_adaptor), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)adaptor_dsp, "dsp",  A_CANT, 0);
	class_addmethod(c, (method)adaptor_assist,		"assist",		A_CANT,	0);

	class_dspinit(c);
	class_register(CLASS_BOX, c);
	adaptor_class = c;
	
	post("pg.adaptor~ by Pierre Guillot",0);

	return 0;
}

void *adaptor_new(t_symbol *s, long argc, t_atom *argv)
{
	t_adaptor *x = NULL;

	if (x = (t_adaptor *)object_alloc(adaptor_class)) 
	{
		x->f_intletCount = 2;
		if( argv[0].a_type == A_LONG ) x->f_intletCount = (int)(argv[0].a_w.w_long);
		if (x->f_intletCount < 2)
		{
			x->f_intletCount = 2;
			object_post((t_object*)x, "Wrong inlets initialization, set to default : 2");
		}
		
		x->f_out = (t_sample *)getbytes(sys_getmaxblksize() * x->f_intletCount * sizeof(t_sample));

		dsp_setup((t_pxobject *)x, 1);
		outlet_new((t_pxobject *)x, "signal");

		x->f_ob.z_misc |= Z_NO_INPLACE;

	}

	return (x);
}

void adaptor_dsp(t_adaptor *x, t_signal **sp, short *count)
{
	x->f_vectorSize = x->f_intletCount * sp[0]->s_n;
	sp[1]->s_vec = x->f_out;
	sp[1]->s_n = x->f_vectorSize;
	dsp_add(adaptor_perform, 4, x, sp[0]->s_vec, sp[1]->s_vec, sp[0]->s_n);

}

t_int *adaptor_perform(t_int *w)
{
	t_adaptor *x = (t_adaptor *)(w[1]);
	t_sample *in = (t_sample *)(w[2]);
	t_sample *out = (t_sample *)(w[3]);
    int n = (int)(w[4]);
	int i, j;

	for(j = 0; j < x->f_intletCount; j++)
	{
		for(i = 0; i < n; i++)
		{
			out[i + j * n] = in[i];
		}
	}
	
	return (w + 5);
}

void adaptor_assist(t_adaptor *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) 
	{
		sprintf(s,"Unadapted signal");
	}
	else 
	{
		sprintf(s, "Adapted signal"); 
	}
}


void adaptor_free(t_adaptor *x) 
{
	dsp_free((t_pxobject *)x);
	freebytes(x->f_out, sys_getmaxblksize() * x->f_intletCount * sizeof(t_sample));
}

