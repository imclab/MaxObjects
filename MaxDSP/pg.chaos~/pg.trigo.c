
#include "pg.trigo.h"

void trigo_createCos(t_trigo *x, int size)
{
	int i;
	x->f_size = size + 1;
	x->f_table =  (float *)malloc(x->f_size * sizeof(float));
	for(i = 0; i < x->f_size; i++)
	{
		x->f_table[i] = cos(((float)i/(float)x->f_size) * TWOPI);
	}
}

void trigo_createSin(t_trigo *x, int size)
{
	int i;
	x->f_size = size + 1;
	x->f_table =  (float *)malloc(x->f_size * sizeof(float));
	for(i = 0; i < x->f_size; i++)
	{
		x->f_table[i] = sin(((float)i/(float)x->f_size) * TWOPI);
	}
}

void trigo_free(t_trigo *x)
{
	free(x->f_table);
}

void trigo_resizeCos(t_trigo *x, int size)
{
	trigo_free(x);
	trigo_createCos(x, size);
}

void trigo_resizeSin(t_trigo *x, int size)
{
	trigo_free(x);
	trigo_createSin(x, size);
}

float trigo_read(t_trigo *x, float value)
{
	float size = (float)x->f_size - 1.f;
	float dist;
	float result;

	if(value < 0) value = -value;
	if(value != 0)
	{
		value *= size;
		value = fmod(value, size);
	}
	dist = value - (int)value;
	result = (1.f - dist) * x->f_table[(int)value] + dist * x->f_table[(int)value + 1];

	return result;
}