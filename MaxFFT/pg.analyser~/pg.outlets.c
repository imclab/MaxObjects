#include "pg.analyser.h"

void outlet_set(t_analyser *x, int mode, int instance)
{
	t_object *b = NULL;
	if(!sys_getdspstate())
	{
		if(x->f_mode[instance] != mode)
		{
			object_obex_lookup(x, _sym_pound_B, (t_object **)&b);
			object_method(b, gensym("dynlet_begin"));
			if(mode <= 0)
			{
				x->f_mode[instance] = 0;
				outlet_delete(outlet_nth((t_object*)x, x->f_modePos[instance]));
				analyser_redefine_outlets(x, instance, x->f_modePos[instance]);
				x->f_modePos[instance] = - 1;
				x->f_outlet--;
			}
			else
			{
				outlet_append((t_object*)x, NULL, gensym("signal"));
				x->f_mode[instance] = 1;
				x->f_modePos[instance] = x->f_outlet;
				x->f_posMode[x->f_outlet] = instance;
				x->f_outlet++;
			}
			object_method(b, gensym("dynlet_end"));
		}
	}
}

void analyser_redefine_outlets(t_analyser *x, int mode, int pos)
{
	int i;

	for(i = x->f_modePos[mode]; i < 16; i++)
	{
		x->f_posMode[i] = x->f_posMode[i+1];
	}
	for(i = 0; i < 17; i++)
	{
		if(x->f_modePos[i] >= pos) x->f_modePos[i]--;
			
	}
}


void analyser_assist(t_analyser *x, void *b, long m, long a, char *s)
{
	int i;
	if (m == ASSIST_INLET) 
	{
		switch (a) 
		{	
			case 0:
				sprintf(s,"(Signal) Input");
				break;
		}
	}
	else 
	{

		if(a == x->f_modePos[0])
			sprintf(s,"(Signal) Centroid");
		else if(a == x->f_modePos[1])
			sprintf(s,"(Signal) Spread");
		else if(a == x->f_modePos[2])
			sprintf(s,"(Signal) Standard Deviation");
		else if(a == x->f_modePos[3])
			sprintf(s,"(Signal) Skewness");
		else if(a == x->f_modePos[4])
			sprintf(s,"(Signal) Kurtosis");
		else if(a == x->f_modePos[5])
			sprintf(s,"(Signal) Minimum Amplitude");
		else if(a == x->f_modePos[6])
			sprintf(s,"(Signal) Mean Amplitude");
		else if(a == x->f_modePos[7])
			sprintf(s,"(Signal) Maximum Amplitude");
		else if(a == x->f_modePos[8])
			sprintf(s,"(Signal) Sum Amplitude");
	}
}
