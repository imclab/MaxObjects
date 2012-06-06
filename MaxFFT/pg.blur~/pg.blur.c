
#include "ext.h"
#include "ext_obex.h"
#include "ext_common.h"
#include "z_dsp.h"
#include "math.h"
#include "pg.window.h"
#include "pg.fft.h"
#include <fftw3.h>

typedef struct  _blur 
{
	t_pxobject	f_ob;
	float		f_sr;

	long		f_windowSize;
	long		f_overlapping;
	long		f_arraySize;
	float 		f_rapportSize;

	t_fft		*f_fft;
	t_window	f_env;

	float		f_period;
	int			f_preserve;
	int			f_blur;
} t_blur;

t_symbol *ps_bang;

void *blur_class;

void *blur_new(t_symbol *s, int argc, t_atom *argv);
void blur_free(t_blur *x);
void blur_assist(t_blur *x, void *b, long m, long a, char *s);

void blur_dsp(t_blur *x, t_signal **sp, short *count);
t_int *blur_perform(t_int *w);
t_max_err preserve_mode_set(t_blur *x, t_object *attr, long argc, t_atom *argv);

int main()
{
	t_class *c;

	c = class_new("pg.blur~", (method)blur_new, (method)blur_free, (short)sizeof(t_blur), 0L, A_GIMME, 0);
	class_addmethod(c, (method)blur_dsp,			"dsp",			A_CANT,	0);
	class_addmethod(c, (method)blur_assist,			"assist",		A_CANT,	0);
	
	CLASS_ATTR_LONG				(c, "period", 0, t_blur, f_blur);
	CLASS_ATTR_LABEL			(c, "period", 0, "Period (in ms)");
	CLASS_ATTR_SAVE				(c, "period", 1);
	CLASS_ATTR_DEFAULT			(c, "period", 0, "100");
	CLASS_ATTR_ORDER			(c, "period", 0, "1");
	CLASS_ATTR_ACCESSORS		(c, "period", NULL, preserve_mode_set);
	
	
	CLASS_ATTR_LONG				(c, "preserve", 0, t_blur, f_preserve);
	CLASS_ATTR_STYLE_LABEL		(c, "preserve", 0, "onoff", "Preserve Mode");
	CLASS_ATTR_SAVE				(c, "preserve", 1);
	CLASS_ATTR_DEFAULT			(c, "preserve", 0, "0");

	
	class_dspinit(c);
	class_register(CLASS_BOX, c);
	blur_class = c;
	
	post("pg.blur~ : Object performed by Pierre Guillot",0);
	post("Universite Paris 8, France",0);
	
	return 0;
}

void *blur_new(t_symbol *s, int argc, t_atom *argv)
{
	t_blur *x = NULL;
	int i, b;

	if (x = (t_blur *)object_alloc(blur_class)) 
	{
		
		x->f_sr = sys_getsr();

		/* Windows Size Initialization **************/
		x->f_windowSize = 0; 
		if( argv[0].a_type == A_LONG ) x->f_windowSize = (int)(argv[0].a_w.w_long);
		if (x->f_windowSize%2 != 0)
		{
			x->f_windowSize = 1024;
			object_post((t_object*)x, "Wrong window size initialization, set to default : 1024");
		}
		x->f_arraySize = x->f_windowSize / 2;

		/* f_fftlapping Initialization ***************/
		x->f_overlapping = 0; 
		if( argv[1].a_type == A_LONG ) x->f_overlapping = (int)(argv[1].a_w.w_long);
		if (x->f_overlapping < 2)
		{
			x->f_overlapping = 2;
			object_post((t_object*)x, "Wrong f_fftlapping initialization, set to default : 2");
		}

		x->f_rapportSize = (float)(PI * (1.f / (float)x->f_arraySize));

		/* Enveloppe   Initialization **************/
		window_setup(&x->f_env, x->f_windowSize);
		window_hanning(&x->f_env);

		/* FFt initialization ***********************/
		x->f_fft = (t_fft *)getbytes(x->f_overlapping  * sizeof(t_fft));
		for(i = 0; i < x->f_overlapping; i++)
		{
			fft_setup(&x->f_fft[i], x->f_windowSize, i, x->f_overlapping);
		}
		
		x->f_period = 1;
		attr_args_process (x, argc, argv);
		
		dsp_setup((t_pxobject *)x, 1);
		outlet_new((t_object *)x, "signal");

		x->f_ob.z_misc |= Z_NO_INPLACE;
	}
	
	return x;
}			


void blur_dsp(t_blur *x, t_signal **sp, short *count)
{
	x->f_sr = (float)sp[0]->s_sr;
	dsp_add(blur_perform, 4, x, sp[0]->s_vec, sp[1]->s_vec, sp[0]->s_n);
}

t_int *blur_perform(t_int *w)
{	
	t_blur	*x	= (t_blur *)	(w[1]);
	t_float	*in1	= (t_sample *)	(w[2]);
	t_float	*out	= (t_sample *)	(w[3]);
	int n			= (int)			(w[4]);
	
	int i, j;
	float amp, phase;
	
	if (x->f_ob.z_disabled) return w + 5;

	for(j = 0; j < n; j++)
	{
		out[j] = 0.f;
	}

	for(i = 0; i < x->f_overlapping; i++)
	{
		for(j = 0; j < n; j++)
		{
			x->f_fft[i].f_real[x->f_fft[i].f_ramp] = in1[j];
			
			if (x->f_fft[i].f_ramp < x->f_arraySize)
			{
				if( x->f_fft[i].f_complex[x->f_fft[i].f_ramp][0] != 0.f)
				{
					amp		= sqrt((x->f_fft[i].f_complex[x->f_fft[i].f_ramp][0]*x->f_fft[i].f_complex[x->f_fft[i].f_ramp][0])+(x->f_fft[i].f_complex[x->f_fft[i].f_ramp][1]*x->f_fft[i].f_complex[x->f_fft[i].f_ramp][1]));
					//phase	= atan( x->f_fft[i].f_complex[x->f_fft[i].f_ramp][1] / x->f_fft[i].f_complex[x->f_fft[i].f_ramp][0] );
				
					if (x->f_preserve == 1) 
					{
						if (x->f_fft[i].f_amp[x->f_fft[i].f_ramp] > amp) x->f_fft[i].f_amp[x->f_fft[i].f_ramp] = x->f_fft[i].f_amp[x->f_fft[i].f_ramp] + (( amp - x->f_fft[i].f_amp[x->f_fft[i].f_ramp]) * x->f_period);
						else x->f_fft[i].f_amp[x->f_fft[i].f_ramp] = amp;
					}
					else x->f_fft[i].f_amp[x->f_fft[i].f_ramp] = x->f_fft[i].f_amp[x->f_fft[i].f_ramp] + (( amp - x->f_fft[i].f_amp[x->f_fft[i].f_ramp]) * x->f_period);

					x->f_fft[i].f_phase[x->f_fft[i].f_ramp] = phase;
					x->f_fft[i].f_complex[x->f_fft[i].f_ramp][0] = x->f_fft[i].f_amp[x->f_fft[i].f_ramp] * cos(x->f_fft[i].f_phase[x->f_fft[i].f_ramp]);
					x->f_fft[i].f_complex[x->f_fft[i].f_ramp][1] = x->f_fft[i].f_amp[x->f_fft[i].f_ramp] * sin(x->f_fft[i].f_phase[x->f_fft[i].f_ramp]);
				}
			}
			
			out[j] += x->f_fft[i].f_realOut[x->f_fft[i].f_ramp] * (float)x->f_rapportSize * x->f_env.f_envelope[x->f_fft[i].f_ramp];
			
			x->f_fft[i].f_ramp++;
			if (x->f_fft[i].f_ramp >= x->f_windowSize)
			{
				fftwf_execute( x->f_fft[i].f_planReverse );
				fftwf_execute( x->f_fft[i].f_plan );
				
				x->f_fft[i].f_ramp = 0;
			}
		}
	}
	return w + 5;	
}


void blur_free(t_blur *x)
{
	int i;

	dsp_free((t_pxobject *)x);
	for(i = 0; i < x->f_overlapping; i++)
	{
		;
	}
	freebytes(x->f_fft, x->f_overlapping * sizeof(t_f_fftl));
	window_free(&x->f_env);
}

void blur_assist(t_blur *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) 
	{
		sprintf(s,"(Signal) Input");
	}
	else 
	{
		sprintf(s,"(Signal) Blur signal");
	}
}

t_max_err preserve_mode_set(t_blur *x, t_object *attr, long argc, t_atom *argv)
{
	long size = atom_getlong(argv);
	x->f_blur = size;
	if (x->f_blur < 1) x->f_blur = 1;
	x->f_period = 2.f / ((((float)x->f_blur * (x->f_sr / 1000.f)) / (float)x->f_windowSize) + 1.f);
	
	return 0;
}