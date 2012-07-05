
#include "ext.h"
#include "ext_obex.h"
#include "ext_common.h"
#include "jpatcher_api.h"
#include "jgraphics.h"
#include "ext_strings.h"

typedef struct  _delete
{
	t_object f_ob;
	void	*f_outlet1;
	void	*f_outlet2;

	t_symbol **f_name;
	int		f_size;
	int		f_all;

} t_delete;

void *delete_class;

void delete_assist(t_delete *x, void *b, long m, long a, char *s);
void delete_bang(t_delete *x);
void delete_set(t_delete *x, t_symbol *s, long argc, t_atom *argv);
void delete_delete(t_delete *x, t_symbol *s, long argc, t_atom *argv);
int delete_patchline(t_delete *x, t_object *patcher, t_object *cible);
t_max_err delete_notify(t_delete *x, t_symbol *s, t_symbol *msg, void *sender, void *data);
void *delete_new(t_symbol *s, int argc, t_atom *argv);
void delete_free(t_delete *x);

int main()
{
	t_class *c;

	c = class_new("pg.delete", (method)delete_new, (method)delete_free, (short)sizeof(t_delete), 0L, A_GIMME, 0);
	class_addmethod(c, (method)delete_bang,		"bang",						0);
	class_addmethod(c, (method)delete_set,		"set",			A_GIMME,	0);
	class_addmethod(c, (method)delete_delete,	"delete",		A_GIMME,	0);
	class_addmethod(c, (method)delete_assist,	"assist",		A_CANT,		0);
	
	class_register(CLASS_BOX, c);
	delete_class = c;

	post("pg.delete by Pierre Guillot",0);
	post("Universite Paris 8, France",0);

	return 0;
}

void *delete_new(t_symbol *s, int argc, t_atom *argv)
{
	int i;
	t_delete *x = NULL;
	
	if (x = (t_delete *)object_alloc((t_class *)delete_class)) 
	{
		x->f_all = 0;
		x->f_size = argc;
		x->f_name = (t_symbol **)getbytes(x->f_size * sizeof(t_symbol *));
		for(i = 0; i < argc; i++)
		{
			if(atom_gettype(argv+i) == A_SYM)
				x->f_name[i] = atom_getsym(argv+i);
		}
		
		for(i = 0; i < x->f_size; i++)
		{
			if(x->f_name[i] == gensym("all"))
				x->f_all = 1;
		}
		x->f_outlet1 = outlet_new((t_object *)x, NULL);
		x->f_outlet2 = outlet_new((t_object *)x, NULL);
	}
	return x;
}			

void delete_assist(t_delete *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET)
		sprintf(s,"(Message or Bang) Set and/or delete an object type");
	else 
	{
		switch (a) 
		{	
			case 0:
				sprintf(s,"(Nothing) Exclude an object", a);
			break;
			case 1:
				sprintf(s,"(Nothing) Include an object", a);
			break;
		}
	}
}

void delete_bang(t_delete *x)
{
	int i, check, nBox;
	t_object *patcher, *box, *obj, *delBox;

	object_obex_lookup(x, gensym("#P"), &patcher);

	for (box = jpatcher_get_firstobject(patcher), check = 0; box; box = jbox_get_nextobject(box)) 
	{
		if(check == 1)
			jpatcher_deleteobj(patcher, (t_jbox *)delBox);

		obj = jbox_get_object(box);
		delBox = box;
		check = 0;
		if(x->f_all == 1 && delete_patchline(x, patcher, obj) != 0)
			check = 1;
		else if(delete_patchline(x, patcher, obj) == 2)
			check = 1;
		else if(delete_patchline(x, patcher, obj) == 1)
		{
			for(i = 0; i < x->f_size; i++)
			{
				if (object_classname(obj) == x->f_name[i])
					check = 1;
			}
		}
		
	}
	if(check == 1)
		jpatcher_deleteobj(patcher, (t_jbox *)delBox);
}

int delete_patchline(t_delete *x, t_object *patcher, t_object *cible)
{
	int i, value;
	t_object *line, *obj;

	value = 1;
	for (line = jpatcher_get_firstline(patcher); line; line = jpatchline_get_nextline(line)) 
	{
		obj = jbox_get_object(jpatchline_get_box1(line));
		
		if (obj == &x->f_ob && jpatchline_get_outletnum(line) == 0 && cible == jbox_get_object(jpatchline_get_box2(line)))
		{
			value = 0;
		}
		else if (obj == &x->f_ob && jpatchline_get_outletnum(line) == 1 && cible == jbox_get_object(jpatchline_get_box2(line)))
		{
			value = 2;
		}
	}
	return value;
}

void delete_set(t_delete *x, t_symbol *s, long argc, t_atom *argv)
{
	int i;
	x->f_all = 0;
	freebytes(x->f_name, x->f_size * sizeof(t_symbol *));
	x->f_size = argc;
	x->f_name = (t_symbol **)getbytes(x->f_size * sizeof(t_symbol *));
	for (i = 0; i < argc; i++) 
	{
		if (atom_gettype(argv+i) == A_SYM) 
			x->f_name[i] = atom_getsym(argv+i);
	}

	for(i = 0; i < x->f_size; i++)
	{
		if(x->f_name[i] == gensym("all"))
			x->f_all = 1;
	}
}

void delete_delete(t_delete *x, t_symbol *s, long argc, t_atom *argv)
{
	delete_set(x, s, argc, argv);
	delete_bang(x);
}

void delete_free(t_delete *x)
{
	freebytes(x->f_name, x->f_size * sizeof(t_symbol *));
}
