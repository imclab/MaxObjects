#include "pg.analyser.h"

void amplitude(t_class *c)
{
	CLASS_ATTR_LONG				(c, "amplitude", 0, t_analyser, f_basic);
	CLASS_ATTR_ACCESSORS		(c, "amplitude", NULL, amplitude_set);
	CLASS_ATTR_INVISIBLE		(c, "amplitude", 0);

	CLASS_ATTR_LONG				(c, "minamp", 0, t_analyser, f_mode[5]);
	CLASS_ATTR_CATEGORY			(c, "minamp", 0, "Amplitude");
	CLASS_ATTR_STYLE			(c, "minamp", 0, "onoff");
	CLASS_ATTR_ORDER			(c, "minamp", 0, "1");
	CLASS_ATTR_ACCESSORS		(c, "minamp", NULL, minamp_set);
	CLASS_ATTR_LABEL			(c, "minamp", 0, "Minimum Amplitude");
	CLASS_ATTR_DEFAULT			(c, "minamp", 0, "1");
	CLASS_ATTR_SAVE				(c, "minamp", 1);

	CLASS_ATTR_LONG				(c, "aveamp", 0, t_analyser, f_mode[6]);
	CLASS_ATTR_CATEGORY			(c, "aveamp", 0, "Amplitude");
	CLASS_ATTR_STYLE			(c, "aveamp", 0, "onoff");
	CLASS_ATTR_ORDER			(c, "aveamp", 0, "2");
	CLASS_ATTR_ACCESSORS		(c, "aveamp", NULL, aveamp_set);
	CLASS_ATTR_LABEL			(c, "aveamp", 0, "Mean Amplitude");
	CLASS_ATTR_DEFAULT			(c, "aveamp", 0, "1");
	CLASS_ATTR_SAVE				(c, "aveamp", 1);

	CLASS_ATTR_LONG				(c, "maxamp", 0, t_analyser, f_mode[7]);
	CLASS_ATTR_CATEGORY			(c, "maxamp", 0, "Amplitude");
	CLASS_ATTR_STYLE			(c, "maxamp", 0, "onoff");
	CLASS_ATTR_ORDER			(c, "maxamp", 0, "3");
	CLASS_ATTR_ACCESSORS		(c, "maxamp", NULL, maxamp_set);
	CLASS_ATTR_LABEL			(c, "maxamp", 0, "Maximum Amplitude");
	CLASS_ATTR_DEFAULT			(c, "maxamp", 0, "1");
	CLASS_ATTR_SAVE				(c, "maxamp", 1);

	CLASS_ATTR_LONG				(c, "sumamp", 0, t_analyser, f_mode[8]);
	CLASS_ATTR_CATEGORY			(c, "sumamp", 0, "Amplitude");
	CLASS_ATTR_STYLE			(c, "sumamp", 0, "onoff");
	CLASS_ATTR_ORDER			(c, "sumamp", 0, "4");
	CLASS_ATTR_ACCESSORS		(c, "sumamp", NULL, sumamp_set);
	CLASS_ATTR_LABEL			(c, "sumamp", 0, "Sum Amplitude");
	CLASS_ATTR_DEFAULT			(c, "sumamp", 0, "1");
	CLASS_ATTR_SAVE				(c, "sumamp", 1);
}

t_max_err amplitude_set(t_analyser *x, t_object *attr, long argc, t_atom *argv)
{
	minamp_set(x, attr, argc, argv);
	aveamp_set(x, attr, argc, argv);
	maxamp_set(x, attr, argc, argv);
	sumamp_set(x, attr, argc, argv);
	return 0;
}

t_max_err minamp_set(t_analyser *x, t_object *attr, long argc, t_atom *argv)
{
	int mode;
	if ( atom_gettype(argv) == A_LONG)
	{
		mode =  atom_getlong(argv);
		outlet_set(x, mode, 5);
	}
	return 0;
}

t_max_err aveamp_set(t_analyser *x, t_object *attr, long argc, t_atom *argv)
{
	int mode;
	if ( atom_gettype(argv) == A_LONG)
	{
		mode =  atom_getlong(argv);
		outlet_set(x, mode, 6);
	}
	return 0;
}

t_max_err maxamp_set(t_analyser *x, t_object *attr, long argc, t_atom *argv)
{
	int mode;
	if ( atom_gettype(argv) == A_LONG)
	{
		mode =  atom_getlong(argv);
		outlet_set(x, mode, 7);
	}
	return 0;
}

t_max_err sumamp_set(t_analyser *x, t_object *attr, long argc, t_atom *argv)
{
	int mode;
	if ( atom_gettype(argv) == A_LONG)
	{
		mode =  atom_getlong(argv);
		outlet_set(x, mode, 8);
	}
	return 0;
}
