#include "pg.analyser.h"

void energy(t_class *c)
{
	CLASS_ATTR_LONG				(c, "decibel", 0, t_analyser, f_basic);
	CLASS_ATTR_ACCESSORS		(c, "decibel", NULL, energy_set);
	CLASS_ATTR_INVISIBLE		(c, "decibel", 0);

	CLASS_ATTR_LONG				(c, "mindec", 0, t_analyser, f_mode[13]);
	CLASS_ATTR_CATEGORY			(c, "mindec", 0, "Energy");
	CLASS_ATTR_STYLE			(c, "mindec", 0, "onoff");
	CLASS_ATTR_ORDER			(c, "mindec", 0, "1");
	CLASS_ATTR_ACCESSORS		(c, "mindec", NULL, mindec_set);
	CLASS_ATTR_LABEL			(c, "mindec", 0, "Minimum dB");
	CLASS_ATTR_DEFAULT			(c, "mindec", 0, "1");
	CLASS_ATTR_SAVE				(c, "mindec", 1);

	CLASS_ATTR_LONG				(c, "avedec", 0, t_analyser, f_mode[14]);
	CLASS_ATTR_CATEGORY			(c, "avedec", 0, "Energy");
	CLASS_ATTR_STYLE			(c, "avedec", 0, "onoff");
	CLASS_ATTR_ORDER			(c, "avedec", 0, "2");
	CLASS_ATTR_ACCESSORS		(c, "avedec", NULL, avedec_set);
	CLASS_ATTR_LABEL			(c, "avedec", 0, "Mean dB");
	CLASS_ATTR_DEFAULT			(c, "avedec", 0, "1");
	CLASS_ATTR_SAVE				(c, "avedec", 1);

	CLASS_ATTR_LONG				(c, "maxdec", 0, t_analyser, f_mode[15]);
	CLASS_ATTR_CATEGORY			(c, "maxdec", 0, "Energy");
	CLASS_ATTR_STYLE			(c, "maxdec", 0, "onoff");
	CLASS_ATTR_ORDER			(c, "maxdec", 0, "3");
	CLASS_ATTR_ACCESSORS		(c, "maxdec", NULL, macdec_set);
	CLASS_ATTR_LABEL			(c, "maxdec", 0, "Maximum dB");
	CLASS_ATTR_DEFAULT			(c, "maxdec", 0, "1");
	CLASS_ATTR_SAVE				(c, "maxdec", 1);

	CLASS_ATTR_LONG				(c, "sumdec", 0, t_analyser, f_mode[16]);
	CLASS_ATTR_CATEGORY			(c, "sumdec", 0, "Energy");
	CLASS_ATTR_STYLE			(c, "sumdec", 0, "onoff");
	CLASS_ATTR_ORDER			(c, "sumdec", 0, "4");
	CLASS_ATTR_ACCESSORS		(c, "sumdec", NULL, sumdec_set);
	CLASS_ATTR_LABEL			(c, "sumdec", 0, "Sum dB");
	CLASS_ATTR_DEFAULT			(c, "sumdec", 0, "1");
	CLASS_ATTR_SAVE				(c, "sumdec", 1);
}


t_max_err energy_set(t_analyser *x, t_object *attr, long argc, t_atom *argv)
{
	mindec_set(x, attr, argc, argv);
	avedec_set(x, attr, argc, argv);
	macdec_set(x, attr, argc, argv);
	sumdec_set(x, attr, argc, argv);
	return 0;
}

t_max_err mindec_set(t_analyser *x, t_object *attr, long argc, t_atom *argv)
{
	int mode;
	if ( atom_gettype(argv) == A_LONG)
	{
		mode =  atom_getlong(argv);
		outlet_set(x, mode, 13);
	}
	return 0;
}

t_max_err avedec_set(t_analyser *x, t_object *attr, long argc, t_atom *argv)
{
	int mode;
	if ( atom_gettype(argv) == A_LONG)
	{
		mode =  atom_getlong(argv);
		outlet_set(x, mode, 14);
	}
	return 0;
}

t_max_err macdec_set(t_analyser *x, t_object *attr, long argc, t_atom *argv)
{
	int mode;
	if ( atom_gettype(argv) == A_LONG)
	{
		mode =  atom_getlong(argv);
		outlet_set(x, mode, 15);
	}
	return 0;
}

t_max_err sumdec_set(t_analyser *x, t_object *attr, long argc, t_atom *argv)
{
	int mode;
	if ( atom_gettype(argv) == A_LONG)
	{
		mode =  atom_getlong(argv);
		outlet_set(x, mode, 16);
	}
	return 0;
}