
#ifndef DEF_CHAOS
#define DEF_CHAOS

#include "ext.h"
#include "ext_obex.h"
#include "ext_common.h"
#include "z_dsp.h"
#include "math.h"
#include "pg.trigo.h"

#define TWOPI	6.28318530717958647692

typedef struct  _chaosSig
{
	t_pxobject f_ob;

	void	*out4;

	float	f_parameter[7];
	float	f_parameterInit[7];

	int		f_mode;
	int		f_count;
	int		f_ramp;
	int		f_sr;
	float	f_frequency;

	float	f_out1;
	float	f_out2;
	float	f_out3;

	t_trigo	f_cos;
	t_trigo	f_sin;

} t_chaosSig;

void *chaosTilde_class;

void chaos_bang(t_chaosSig *x);
void chaos_list(t_chaosSig *x, t_symbol *s, short ac, t_atom *av);
void chaos_set(t_chaosSig *x, t_symbol *s, short ac, t_atom *av);
void chaos_print(t_chaosSig *x);
void chaos_record(t_chaosSig *x);
void *chaos_new(t_symbol *s, int argc, t_atom *argv);
void chaos_free(t_chaosSig *x);
void chaos_reset(t_chaosSig *x);
void chaos_assist(t_chaosSig *x, void *b, long m, long a, char *s);
void chaos_dsp(t_chaosSig *x, t_signal **sp, short *count);
void chaos_int(t_chaosSig *x, long l);
void chaos_float(t_chaosSig *x, double f);
t_max_err mode_set(t_chaosSig *x, t_object *attr, long argc, t_atom *argv);

t_int *chaos_perform(t_int *w);
t_int *chaos_performOffset(t_int *w);

#endif