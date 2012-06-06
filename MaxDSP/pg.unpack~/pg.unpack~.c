
/**** Les bibliotheques ****/
#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"	

/**** La structure de l'objet ****/
typedef struct _unpack 
{
	t_pxobject	f_ob;	
	int			f_outletCount;
	int			f_vectorSize;
	t_sample	**f_out;
} t_unpack;

/**** Prototypes des fonctions ****/
void *unpack_new(t_symbol *s, long argc, t_atom *argv);
void unpack_free(t_unpack *x);
void unpack_assist(t_unpack *x, void *b, long m, long a, char *s);

void unpack_dsp(t_unpack *x, t_signal **sp, short *count);//
t_int *unpack_perform(t_int *w);

void *unpack_class;

/*** Fonction principales ****/
int main(void)
{	
	t_class *c;
	
	c = class_new("pg.unpack~", (method)unpack_new, (method)unpack_free, (long)sizeof(t_unpack), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)unpack_dsp, "dsp",  A_CANT, 0); 
	class_addmethod(c, (method)unpack_assist, "assist",  A_CANT, 0); 

	class_dspinit(c);
	class_register(CLASS_BOX, c);
	unpack_class = c;
	
	post("pg.unpack~ by Pierre Guillot",0);

	return 0;
}

void *unpack_new(t_symbol *s, long argc, t_atom *argv)
{
	t_unpack *x = NULL;
	int i;

	if (x = (t_unpack *)object_alloc(unpack_class)) 
	{
		x->f_outletCount = 2;
		if( argv[0].a_type == A_LONG ) x->f_outletCount = (int)(argv[0].a_w.w_long);
		if (x->f_outletCount < 2)
		{
			x->f_outletCount = 2;
			object_post((t_object*)x, "Wrong inlets initialization, set to default : 2");
		}
		x->f_out = (t_float **)t_getbytes(x->f_outletCount * sizeof(t_sample *));

		dsp_setup((t_pxobject *)x, 1);
		for(i = 0; i < x->f_outletCount; i++)
		{
			outlet_new((t_pxobject *)x, "signal");
		}

	}
	return (x);
}

void unpack_dsp(t_unpack *x, t_signal **sp, short *count)
{
	int i;
	int pointer_count;
	t_int **sigvec;

	x->f_vectorSize =  sp[0]->s_n / x->f_outletCount;
	sp[0]->s_n = x->f_vectorSize;
	pointer_count = x->f_outletCount + 3;
	sigvec  = (t_int **)calloc(pointer_count, sizeof(t_int *));	
	for(i = 0; i < pointer_count; i++)
	{
		sigvec[i] = (t_int *) calloc(sizeof(t_int), 1);
	}
	sigvec[0] = (t_int *)x;
	sigvec[1] = (t_int *)sp[0]->s_vec;
	for(i = 2; i <= pointer_count - 2; i++)
	{
		sigvec[i] = (t_int *)sp[i - 1]->s_vec;
	}
	sigvec[pointer_count - 1] = (t_int *)sp[0]->s_n;

	dsp_addv(unpack_perform, pointer_count, (void **) sigvec);

	free(sigvec);
}


t_int *unpack_perform(t_int *w)
{
	t_unpack *x = (t_unpack *)(w[1]);
	t_sample *in = (t_sample *)(w[2]);
	t_sample **out = x->f_out;
    int n = (int)(w[x->f_outletCount + 3]);
	int i, j;

	for(i = 0; i < x->f_outletCount; i++)
	{
		out[i] = (t_float *)(w[i + 3]);
	}
	
    for(i = 0; i < n; i++)
	{
		for(j = 0; j < x->f_outletCount; j++)
		{
			out[j][i] = in[i + j * n];
		}
	}
	
	return (w + x->f_outletCount + 4);
}

void unpack_assist(t_unpack *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) 
	{
		sprintf(s, "Packed signal");
	} 
	else 
	{	
		sprintf(s, "Unpacked signal"); 			
	}
}


void unpack_free(t_unpack *x) 
{
	dsp_free((t_pxobject *)x);
	freebytes(x->f_out, x->f_outletCount * sizeof(t_sample *));
}

