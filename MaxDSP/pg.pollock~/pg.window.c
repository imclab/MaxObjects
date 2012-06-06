
#include "pg.window.h"

void window_square(t_window *x)
{
	int i, size;
	float j;
	size = x->f_size;
	j = size - 1;
	for(i = 0; i < size; i++)
	{
		x->f_envelope[i] = 1;
	}
}

void window_hamming(t_window *x)
{
	int i, size;
	float j;
	size = x->f_size;
	j = size - 1;
  
	for(i = 0; i < size; i++)
	{
		x->f_envelope[i] = 0.54 - (0.46 * cos(2.0 * PI *(float)i / j));
	}
}

void window_hanning(t_window *x)
{
	int i, size;
	float j;
	size = x->f_size;
	j = size - 1;
  
	for(i = 0; i < size; i++)
	{
		x->f_envelope[i] = 0.5 * (1.0 - cos(2.0 * PI * (float)i /j));
	}
}

void window_blackman(t_window *x)
{
	int i, size;
	float j;
	size = x->f_size;
	j = size - 1;

	for(i = 0; i < size; i++)
    {
		x->f_envelope[i] = 0.42 - (0.5 * cos(2.0 * PI * (float)i / j)) + (0.08 * cos(4.0 * PI * (float)i / j));
    }
}

void window_flat_top(t_window *x)
{
	int i, size;
	float j;
	size = x->f_size;
	j = size - 1;
	
	for(i = 0; i < size; i++)
    {
		x->f_envelope[i] = (1. - 1.93 * (cos( (2.0 * PI * (float)i) / j)) + 1.29 * (cos( (4.0 * PI * (float)i) / j)) - 0.388 * (cos( (6.0 * PI * (float)i) / j)) + 0.032 * (cos( (8.0 * PI * (float)i) / j))) * 0.2;
    }
}

void window_poison(t_window *x)
{
	int i, size;
	float j, alpha, beta;
	size = x->f_size;
	j = size - 1;
	alpha = 1./ (((float)size / 2.)/(60./8.69));
	for(i = 0; i < size; i++)
    {
		beta = -1. * ((float)i - (j / 2.));
		if (beta >= 0) beta = -beta;
		beta *= alpha;
		x->f_envelope[i] = exp(beta);
    }
}

void window_turkey(t_window *x)
{
	int i, size;
	float j, alpha;
	size = x->f_size;
	j = size - 1;
	alpha = 0.5;
	for(i = 0; i < size; i++)
    {
		if(i <= ((alpha * j) / 2.))
			x->f_envelope[i] = 0.5 * ( 1. + cos(PI * ( ((2 *(float)i) / (alpha * j)) - 1.)));
		else if(i > ((alpha * j) / 2.) && i <= (j * (1. - ( alpha / 2.))))
			x->f_envelope[i] = 1.f;
		else 
			x->f_envelope[i] = 0.5 * ( 1. + cos(PI * ( ((2 *(float)i) / (alpha * j)) + 1. - (2. / alpha))));
    }
}

void window_decay(t_window *x)
{
	int i, size;
	float j, alpha, beta;
	size = x->f_size;
	j = size - 1;
	alpha = 1./ (((float)size / (2. * 8.))/(60./8.69));
	for(i = 0; i < size; i++)
    {
		if (i <= (size / 16)) 
		{
			beta = -1. * ((float)i - (j / (2. * 8.)));
			if (beta >= 0) beta = -beta;
			beta *= alpha;
			x->f_envelope[i] = exp(beta);
		}
		else 
		{
			beta = j * (14. /8.);
			alpha = i - (j / 16.) + 0.5 * beta;
			x->f_envelope[i] = 0.5 * (1.0 - cos(2.0 * PI * (float)alpha /beta));
		}

    }
}

void window_rise(t_window *x)
{
	int i, k, size;
	float j, alpha, beta;
	size = x->f_size;
	j = size - 1;
	
	for(i = 0; i < size; i++)
    {
		k = j - i;
		if (i <= (size / 16.)) 
		{
			alpha = 1./ (((float)size / (2. * 8.))/(60./8.69));
			beta = -1. * ((float)i - (j / (2. * 8.)));
			if (beta >= 0) beta = -beta;
			beta *= alpha;
			x->f_envelope[k] = exp(beta);
		}
		else 
		{
			beta = j * (14. /8.);
			alpha = i - (j / 16.) + 0.5 * beta;
			x->f_envelope[k] = 0.5 * (1.0 - cos(2.0 * PI * (float)alpha /beta));
			
		}
		
    }
	
}

void window_setup(t_window *x, int size)
{
	if(x->f_envelope != NULL) freebytes(x->f_envelope, sizeof(float)* x->f_size);
	x->f_size = size;
	x->f_envelope = (float *)getbytes(x->f_size * sizeof(float));
}


void window_free(t_window *x)
{
	if(x->f_envelope != NULL) freebytes(x->f_envelope, sizeof(float)* x->f_size);
}