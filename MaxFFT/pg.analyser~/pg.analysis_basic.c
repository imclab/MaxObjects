#include "pg.analyser.h"

void basic(t_class *c)
{
	
	CLASS_ATTR_LONG				(c, "basic", 0, t_analyser, f_basic);
	CLASS_ATTR_ACCESSORS		(c, "basic", NULL, basic_set);
	CLASS_ATTR_INVISIBLE		(c, "basic", 0);

	CLASS_ATTR_LONG				(c, "centroid", 0, t_analyser, f_mode);
	CLASS_ATTR_CATEGORY			(c, "centroid", 0, "Analysis");
	CLASS_ATTR_STYLE			(c, "centroid", 0, "onoff");
	CLASS_ATTR_ORDER			(c, "centroid", 0, "1");
	CLASS_ATTR_ACCESSORS		(c, "centroid", NULL, centroid_set);
	CLASS_ATTR_LABEL			(c, "centroid", 0, "Centroid");
	CLASS_ATTR_DEFAULT			(c, "centroid", 0, "1");
	CLASS_ATTR_SAVE				(c, "centroid", 1);

	CLASS_ATTR_LONG				(c, "spread", 0, t_analyser, f_mode[1]);
	CLASS_ATTR_CATEGORY			(c, "spread", 0, "Analysis");
	CLASS_ATTR_STYLE			(c, "spread", 0, "onoff");
	CLASS_ATTR_ORDER			(c, "spread", 0, "2");
	CLASS_ATTR_ACCESSORS		(c, "spread", NULL, spread_set);
	CLASS_ATTR_LABEL			(c, "spread", 0, "Spread");
	CLASS_ATTR_DEFAULT			(c, "spread", 0, "1");
	CLASS_ATTR_SAVE				(c, "spread", 1);

	CLASS_ATTR_LONG				(c, "deviation", 0, t_analyser, f_mode[2]);
	CLASS_ATTR_CATEGORY			(c, "deviation", 0, "Analysis");
	CLASS_ATTR_STYLE			(c, "deviation", 0, "onoff");
	CLASS_ATTR_ORDER			(c, "deviation", 0, "3");
	CLASS_ATTR_ACCESSORS		(c, "deviation", NULL, deviation_set);
	CLASS_ATTR_LABEL			(c, "deviation", 0, "Standard deviation");
	CLASS_ATTR_DEFAULT			(c, "deviation", 0, "1");
	CLASS_ATTR_SAVE				(c, "deviation", 1);

	CLASS_ATTR_LONG				(c, "skewness", 0, t_analyser, f_mode[3]);
	CLASS_ATTR_CATEGORY			(c, "skewness", 0, "Analysis");
	CLASS_ATTR_STYLE			(c, "skewness", 0, "onoff");
	CLASS_ATTR_ORDER			(c, "skewness", 0, "4");
	CLASS_ATTR_ACCESSORS		(c, "skewness", NULL, skewness_set);
	CLASS_ATTR_LABEL			(c, "skewness", 0, "Skewness");
	CLASS_ATTR_DEFAULT			(c, "skewness", 0, "1");
	CLASS_ATTR_SAVE				(c, "skewness", 1);

	CLASS_ATTR_LONG				(c, "kurtosis", 0, t_analyser, f_mode[4]);
	CLASS_ATTR_CATEGORY			(c, "kurtosis", 0, "Analysis");
	CLASS_ATTR_STYLE			(c, "kurtosis", 0, "onoff");
	CLASS_ATTR_ORDER			(c, "kurtosis", 0, "5");
	CLASS_ATTR_ACCESSORS		(c, "kurtosis", NULL, kurtosis_set);
	CLASS_ATTR_LABEL			(c, "kurtosis", 0, "Kurtosis");
	CLASS_ATTR_DEFAULT			(c, "kurtosis", 0, "1");
	CLASS_ATTR_SAVE				(c, "kurtosis", 1);

}
/* Basic Analysis */
t_max_err basic_set(t_analyser *x, t_object *attr, long argc, t_atom *argv)
{
	centroid_set(x, attr, argc, argv);
	spread_set(x, attr, argc, argv);
	deviation_set(x, attr, argc, argv);
	skewness_set(x, attr, argc, argv);
	kurtosis_set(x, attr, argc, argv);
}

t_max_err centroid_set(t_analyser *x, t_object *attr, long argc, t_atom *argv)
{
	int i, mode;
	t_object *b = NULL;
	
	if ( atom_gettype(argv) == A_LONG)
	{
		object_obex_lookup(x, gensym("#B"), (t_object **)&b);
		object_method(b, gensym("dynlet_begin"));
		mode =  atom_getlong(argv);
		if(mode > 0) mode = 1;
		else mode = 0;
		if(x->f_mode[0] != mode)
		{
			x->f_mode[0] = mode;
			if(x->f_mode[0] == 0)
			{
				outlet_delete(outlet_nth((t_object*)x, x->f_modePos[0]));
				analyser_redefine_outlets(x, x->f_modePos[0]);
				x->f_outlet--;
				x->f_modePos[0] = - 1;
			}
			else
			{
				outlet_append((t_object*)x, NULL, gensym("signal"));
				x->f_outlet++;
				x->f_modePos[0] = x->f_outlet - 1;
			}
		}
		object_method(b, gensym("dynlet_end"));
	}
	return 0;
}

t_max_err spread_set(t_analyser *x, t_object *attr, long argc, t_atom *argv)
{
	int i, mode;
	t_object *b = NULL;
	
	if ( atom_gettype(argv) == A_LONG)
	{
		object_obex_lookup(x, gensym("#B"), (t_object **)&b);
		object_method(b, gensym("dynlet_begin"));
		mode =  atom_getlong(argv);
		if(mode > 0) mode = 1;
		else mode = 0;
		if(x->f_mode[1] != mode)
		{
			x->f_mode[1] = mode;
			if(x->f_mode[1] == 0)
			{
				outlet_delete(outlet_nth((t_object*)x, x->f_modePos[1]));
				analyser_redefine_outlets(x, x->f_modePos[1]);
				x->f_outlet--;
				x->f_modePos[1] = - 1;
			}
			else
			{
				outlet_append((t_object*)x, NULL, gensym("signal"));
				x->f_outlet++;
				x->f_modePos[1] = x->f_outlet - 1;
			}
		}
		object_method(b, gensym("dynlet_end"));
	}
	return 0;
}

t_max_err deviation_set(t_analyser *x, t_object *attr, long argc, t_atom *argv)
{
	int i, mode;
	t_object *b = NULL;
	
	if ( atom_gettype(argv) == A_LONG)
	{
		object_obex_lookup(x, gensym("#B"), (t_object **)&b);
		object_method(b, gensym("dynlet_begin"));
		mode =  atom_getlong(argv);
		if(mode > 0) mode = 1;
		else mode = 0;
		if(x->f_mode[2] != mode)
		{
			x->f_mode[2] = mode;
			if(x->f_mode[2] == 0)
			{
				outlet_delete(outlet_nth((t_object*)x, x->f_modePos[2]));
				analyser_redefine_outlets(x, x->f_modePos[2]);
				x->f_outlet--;
				x->f_modePos[2] = - 1;
			}
			else
			{
				outlet_append((t_object*)x, NULL, gensym("signal"));
				x->f_outlet++;
				x->f_modePos[2] = x->f_outlet - 1;
			}
		}
		object_method(b, gensym("dynlet_end"));
	}
	return 0;
}

t_max_err skewness_set(t_analyser *x, t_object *attr, long argc, t_atom *argv)
{
	int i, mode;
	t_object *b = NULL;
	
	if ( atom_gettype(argv) == A_LONG)
	{
		object_obex_lookup(x, gensym("#B"), (t_object **)&b);
		object_method(b, gensym("dynlet_begin"));
		mode =  atom_getlong(argv);
		if(mode > 0) mode = 1;
		else mode = 0;
		if(x->f_mode[3] != mode)
		{
			x->f_mode[3] = mode;
			if(x->f_mode[3] == 0)
			{
				outlet_delete(outlet_nth((t_object*)x, x->f_modePos[3]));
				analyser_redefine_outlets(x, x->f_modePos[3]);
				x->f_outlet--;
				x->f_modePos[3] = - 1;
			}
			else
			{
				outlet_append((t_object*)x, NULL, gensym("signal"));
				x->f_outlet++;
				x->f_modePos[3] = x->f_outlet - 1;
			}
		}
		object_method(b, gensym("dynlet_end"));
	}
	return 0;
}

t_max_err kurtosis_set(t_analyser *x, t_object *attr, long argc, t_atom *argv)
{
	int i, mode;
	t_object *b = NULL;
	
	if ( atom_gettype(argv) == A_LONG)
	{
		object_obex_lookup(x, gensym("#B"), (t_object **)&b);
		object_method(b, gensym("dynlet_begin"));
		mode =  atom_getlong(argv);
		if(mode > 0) mode = 1;
		else mode = 0;
		if(x->f_mode[4] != mode)
		{
			x->f_mode[4] = mode;
			if(x->f_mode[4] == 0)
			{
				outlet_delete(outlet_nth((t_object*)x, x->f_modePos[4]));
				analyser_redefine_outlets(x, x->f_modePos[4]);
				x->f_outlet--;
				x->f_modePos[4] = - 1;
			}
			else
			{
				outlet_append((t_object*)x, NULL, gensym("signal"));
				x->f_outlet++;
				x->f_modePos[4] = x->f_outlet - 1;
			}
		}
		object_method(b, gensym("dynlet_end"));
	}
	return 0;
}

