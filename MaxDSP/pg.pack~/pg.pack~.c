

/**** Les bibliotheques ****/
#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"

/**** La structure de l'objet ****/
typedef struct _pack 
{
	t_pxobject	f_ob;
	int			f_intletCount;
	int			f_vectorSize;
	t_sample	**f_in;
	t_sample	*f_out;
} t_pack;

/**** Prototypes des fonctions ****/
void *pack_new(t_symbol *s, long argc, t_atom *argv);
void pack_free(t_pack *x);
void pack_assist(t_pack *x, void *b, long m, long a, char *s);

void pack_dsp(t_pack *x, t_signal **sp, short *count);//
t_int *pack_perform(t_int *w);

void *pack_class;

/*** Fonction principales ****/
int main(void)
{	
	t_class *c;
	
	c = class_new("pg.pack~", (method)pack_new, (method)pack_free, (long)sizeof(t_pack), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)pack_dsp, "dsp",  A_CANT, 0);
	class_addmethod(c, (method)pack_assist, "assist",  A_CANT, 0); 

	class_dspinit(c);
	class_register(CLASS_BOX, c);
	pack_class = c;
	
	post("pg.pack~ by Pierre Guillot",0);

	return 0;
}

void *pack_new(t_symbol *s, long argc, t_atom *argv)
{
	t_pack *x = NULL;

	if (x = (t_pack *)object_alloc(pack_class)) 
	{
		x->f_intletCount = 2;
		if( argv[0].a_type == A_LONG ) x->f_intletCount = (int)(argv[0].a_w.w_long);
		if (x->f_intletCount < 2)
		{
			x->f_intletCount = 2;
			object_post((t_object*)x, "Wrong inlets initialization, set to default : 2");
		}
		
		x->f_in = (t_sample **)getbytes(x->f_intletCount * sizeof(t_sample *));
		x->f_out = (t_sample *)getbytes(sys_getmaxblksize() * x->f_intletCount * sizeof(t_sample));

		dsp_setup((t_pxobject *)x, x->f_intletCount);
		outlet_new((t_pxobject *)x, "signal");

		x->f_ob.z_misc |= Z_NO_INPLACE;
	}

	return (x);
}

void pack_dsp(t_pack *x, t_signal **sp, short *count)
{
	int i;
	int pointer_count;
	t_int **sigvec;

	x->f_vectorSize = x->f_intletCount * sp[0]->s_n;

	sp[x->f_intletCount]->s_n = x->f_vectorSize;
	sp[x->f_intletCount]->s_vec = x->f_out;

	pointer_count = x->f_intletCount + 3;
	sigvec  = (t_int **)calloc(pointer_count, sizeof(t_int *));	
	for(i = 0; i < pointer_count; i++)
	{
		sigvec[i] = (t_int *) calloc(sizeof(t_int), 1);
	}
	sigvec[0] = (t_int *)x; 
	for(i = 0; i < x->f_intletCount; i++)
	{
		sigvec[i + 1] = (t_int *)sp[i]->s_vec;
	}
	sigvec[x->f_intletCount + 1] = (t_int *)sp[x->f_intletCount]->s_vec;
	sigvec[x->f_intletCount + 2] = (t_int *)sp[0]->s_n;

	dsp_addv(pack_perform, pointer_count, (void **) sigvec);

	free(sigvec);
}

t_int *pack_perform(t_int *w)
{
	t_pack *x = (t_pack *)(w[1]);
	t_sample **in = x->f_in;
	t_sample *out = (t_sample *)(w[x->f_intletCount + 2]);
    int n = (int)(w[x->f_intletCount + 3]);
	int i, j;

	for(i = 0; i < x->f_intletCount; i++)
	{
		in[i] = (t_float *)(w[i + 2]);
	}

	for(j = 0; j < x->f_intletCount; j++)
	{
		for(i = 0; i < n; i++)
		{
			out[i + j * n] = in[j][i];
		}
	}
	
	return (w + x->f_intletCount + 4);
}

void pack_assist(t_pack *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) 
	{
		sprintf(s, "Unpacked signal");
	} 
	else 
	{	
		sprintf(s, "Packed signal"); 			
	}
}


void pack_free(t_pack *x) 
{
	dsp_free((t_pxobject *)x);
	freebytes(x->f_in, x->f_intletCount * sizeof(t_sample *));
	freebytes(x->f_out, sys_getmaxblksize() * x->f_intletCount * sizeof(t_sample));
}

