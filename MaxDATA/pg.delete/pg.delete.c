
#include "ext.h"
#include "ext_obex.h"
#include "ext_common.h"
#include "jpatcher_api.h"
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
	class_addmethod(c, (method)delete_assist,	"assist",		A_CANT,		0);
	class_addmethod(c, (method)delete_notify,	"notify",		A_CANT,		0);
	
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
		sprintf(s,"(Message or Bang)");
	else 
	{
		sprintf(s,"");
	}
}

void delete_bang(t_delete *x)
{
	int i, check;
	t_object *patcher, *box, *obj;

	object_obex_lookup(x, gensym("#P"), &patcher);

	for (box = jpatcher_get_firstobject(patcher), check = 0; box; box = jbox_get_nextobject(box)) 
	{
		if(check == 1)
			object_method(obj, gensym("free"));

		obj = jbox_get_object(box);
		check = 0;
		if (delete_patchline(x, patcher, obj))
		{
			for(i = 0; i < x->f_size; i++)
			{
				if(x->f_all == 1)
					check = 1;
				else if (obj && object_classname(obj) == x->f_name[i])
				{
					check = 1;
					post("bah??");
				}
			}
		}
	}
	if(check == 1)
		object_free(obj);
}

int delete_patchline(t_delete *x, t_object *patcher, t_object *cible)
{
	int i;
	t_object *line, *obj;

	for (line = jpatcher_get_firstline(patcher); line; line = jpatchline_get_nextline(line)) 
	{
		obj = jpatchline_get_box1(line);
	
		if (object_classname(obj) == gensym("pg.delete"))//(obj == &x->f_ob)// && jpatchline_get_outletnum(line) == 0 && cible == jpatchline_get_box2(line))
		{
			post("salut");
			return 0;
		}
	}
	return 1;

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

void delete_free(t_delete *x)
{
	freebytes(x->f_name, x->f_size * sizeof(t_symbol *));
}

t_max_err delete_notify(t_delete *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
	return object_notify(x, s, data);
}