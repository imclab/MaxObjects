#include "pg.analyser.h"

void power(t_class *c)
{
	CLASS_ATTR_LONG				(c, "power", 0, t_analyser, f_basic);
	CLASS_ATTR_ACCESSORS		(c, "power", NULL, power_set);
	CLASS_ATTR_INVISIBLE		(c, "power", 0);

	CLASS_ATTR_LONG				(c, "minpow", 0, t_analyser, f_mode[9]);
	CLASS_ATTR_CATEGORY			(c, "minpow", 0, "Power");
	CLASS_ATTR_STYLE			(c, "minpow", 0, "onoff");
	CLASS_ATTR_ORDER			(c, "minpow", 0, "1");
	CLASS_ATTR_ACCESSORS		(c, "minpow", NULL, minpow_set);
	CLASS_ATTR_LABEL			(c, "minpow", 0, "Minimum Power");
	CLASS_ATTR_DEFAULT			(c, "minpow", 0, "1");
	CLASS_ATTR_SAVE				(c, "minpow", 1);

	CLASS_ATTR_LONG				(c, "avepow", 0, t_analyser, f_mode[10]);
	CLASS_ATTR_CATEGORY			(c, "avepow", 0, "Power");
	CLASS_ATTR_STYLE			(c, "avepow", 0, "onoff");
	CLASS_ATTR_ORDER			(c, "avepow", 0, "2");
	CLASS_ATTR_ACCESSORS		(c, "avepow", NULL, avepow_set);
	CLASS_ATTR_LABEL			(c, "avepow", 0, "Mean Power");
	CLASS_ATTR_DEFAULT			(c, "avepow", 0, "1");
	CLASS_ATTR_SAVE				(c, "avepow", 1);

	CLASS_ATTR_LONG				(c, "maxpow", 0, t_analyser, f_mode[11]);
	CLASS_ATTR_CATEGORY			(c, "maxpow", 0, "Power");
	CLASS_ATTR_STYLE			(c, "maxpow", 0, "onoff");
	CLASS_ATTR_ORDER			(c, "maxpow", 0, "3");
	CLASS_ATTR_ACCESSORS		(c, "maxpow", NULL, maxpow_set);
	CLASS_ATTR_LABEL			(c, "maxpow", 0, "Maximum power");
	CLASS_ATTR_DEFAULT			(c, "maxpow", 0, "1");
	CLASS_ATTR_SAVE				(c, "maxpow", 1);

	CLASS_ATTR_LONG				(c, "sumpow", 0, t_analyser, f_mode[12]);
	CLASS_ATTR_CATEGORY			(c, "sumpow", 0, "Power");
	CLASS_ATTR_STYLE			(c, "sumpow", 0, "onoff");
	CLASS_ATTR_ORDER			(c, "sumpow", 0, "4");
	CLASS_ATTR_ACCESSORS		(c, "sumpow", NULL, sumpow_set);
	CLASS_ATTR_LABEL			(c, "sumpow", 0, "Sum Power");
	CLASS_ATTR_DEFAULT			(c, "sumpow", 0, "1");
	CLASS_ATTR_SAVE				(c, "sumpow", 1);
}


t_max_err power_set(t_analyser *x, t_object *attr, long argc, t_atom *argv)
{
	minpow_set(x, attr, argc, argv);
	avepow_set(x, attr, argc, argv);
	maxpow_set(x, attr, argc, argv);
	sumpow_set(x, attr, argc, argv);
	return 0;
}

t_max_err minpow_set(t_analyser *x, t_object *attr, long argc, t_atom *argv)
{
	int mode;
	if ( atom_gettype(argv) == A_LONG)
	{
		mode =  atom_getlong(argv);
		outlet_set(x, mode, 9);
	}
	return 0;
}

t_max_err avepow_set(t_analyser *x, t_object *attr, long argc, t_atom *argv)
{
	int mode;
	if ( atom_gettype(argv) == A_LONG)
	{
		mode =  atom_getlong(argv);
		outlet_set(x, mode, 10);
	}
	return 0;
}

t_max_err maxpow_set(t_analyser *x, t_object *attr, long argc, t_atom *argv)
{
	int mode;
	if ( atom_gettype(argv) == A_LONG)
	{
		mode =  atom_getlong(argv);
		outlet_set(x, mode, 11);
	}
	return 0;
}

t_max_err sumpow_set(t_analyser *x, t_object *attr, long argc, t_atom *argv)
{
	int mode;
	if ( atom_gettype(argv) == A_LONG)
	{
		mode =  atom_getlong(argv);
		outlet_set(x, mode, 12);
	}
	return 0;
}