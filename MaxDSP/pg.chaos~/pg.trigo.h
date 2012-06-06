
#ifndef DEF_TRIGO
#define DEF_TRIGO

#include "ext.h"
#include "ext_obex.h"
#include "ext_common.h"
#include "z_dsp.h"
#include "math.h"

typedef struct  _trigo
{
	int		f_size;
	float	*f_table;
} t_trigo;

void trigo_createCos(t_trigo *x, int size);
void trigo_createSin(t_trigo *x, int size);
void trigo_free(t_trigo *x);
void trigo_resizeCos(t_trigo *x, int size);
void trigo_resizeSin(t_trigo *x, int size);

#endif