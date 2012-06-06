
#include "pg.window.h"

void window_square(t_window *x)
{
	int i, size;
	float j;
	size = x->f_size;
	j = size - 1;
	for(i = 0; i < size; i++)
	{
		x->f_envelope[i] = 1.;
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

void window_cosinus(t_window *x)
{
	int i, size;
	float j;
	size = x->f_size;
	j = size - 1;

	for(i = 0; i < size; i++)
    {
		x->f_envelope[i] = sin((PI * i) / j);
    }
}

void window_lanczos(t_window *x)
{
	int i, size;
	float j, alpha;
	size = x->f_size;
	j = size - 1;

	for(i = 0; i < size; i++)
    {
		alpha = PI * (((2. * (float)i) / j) - 1.);
		x->f_envelope[i] = sin(alpha)/alpha;
    }
}


void window_kaiser(t_window *x)
{
	// Not yet //
	int i, size;
	float j, alpha, a, b, iota;
	size = x->f_size;
	j = size - 1;
	alpha = 3.;
	for(i = 0; i < size; i++)
    {
		//b = (((2. * (float)i) / j) - 1.) * (((2. * (float)i) / j) - 1.);
		//a = iota * (PI * alpha * (sqrt( 1. - b))) / iota * (PI * alpha)
		x->f_envelope[i] = 1.f;
    }
}

void window_triangular(t_window *x)
{
	int i, size;
	float j, k, alpha;
	size = x->f_size;
	j = size - 1;
	alpha = 0.5;
	for(i = 0; i < size; i++)
    {
		k = (float)i -(j / 2.);
		x->f_envelope[i] = (2. / j) * ((j / 2.) - k);
    }
}

void window_gaussian(t_window *x)
{
	int i, size;
	float j, k, alpha;
	size = x->f_size;
	j = size - 1;
	alpha = 0.5;
	for(i = 0; i < size; i++)
    {
		k = (i - j / 2.f)/(alpha * j / 2.f) * (i - j / 2.f)/(alpha * j / 2.f) * -0.5f;
		x->f_envelope[i] = exp(k);
    }
}

void window_bartlett_hann(t_window *x)
{
	int i, size;
	float j, a1, a2, a3, abso;
	size = x->f_size;
	j = size - 1;
	a1 = 0.62;
	a2 = 0.48;
	a3 = 0.38;
	for(i = 0; i < size; i++)
    {
		abso = ((float)i / (float)j) - 0.5;
		if(abso < 0.f) abso = -abso;
		x->f_envelope[i] = a1 - a2 * abso - a3 * cos((2.0 * PI *(float)i) / j);
    }
}

void window_nuttall(t_window *x)
{
	int i, size;
	float j, a1, a2, a3, a4;
	size = x->f_size;
	j = size - 1;
	a1 = 0.255768f;
	a2 = 0.487396f;
	a3 = 0.144232f;
	a4 = 0.012604f;
	for(i = 0; i < size; i++)
    {
		x->f_envelope[i] = (a1 - a2 * (cos( (2.0 * PI * (float)i) / j)) + a3 * (cos( (4.0 * PI * (float)i) / j)) - a4 * (cos( (6.0 * PI * (float)i) / j)) + 0.032 * (cos( (8.0 * PI * (float)i) / j)));
    }
}

void window_blackman_harris(t_window *x)
{
	int i, size;
	float j, a1, a2, a3, a4;
	size = x->f_size;
	j = size - 1;
	a1 = 0.35875f;
	a2 = 0.48829f;
	a3 = 0.14128f;
	a4 = 0.01168f;
	for(i = 0; i < size; i++)
    {
		x->f_envelope[i] = (a1 - a2 * (cos( (2.0 * PI * (float)i) / j)) + a3 * (cos( (4.0 * PI * (float)i) / j)) - a4 * (cos( (6.0 * PI * (float)i) / j)) + 0.032 * (cos( (8.0 * PI * (float)i) / j)));
    }
}

void window_blackman_nuttall(t_window *x)
{
	int i, size;
	float j, a1, a2, a3, a4;
	size = x->f_size;
	j = size - 1;
	a1 = 0.3635819f;
	a2 = 0.4891775f;
	a3 = 0.1365995f;
	a4 = 0.0106441f;
	for(i = 0; i < size; i++)
    {
		x->f_envelope[i] = (a1 - a2 * (cos( (2.0 * PI * (float)i) / j)) + a3 * (cos( (4.0 * PI * (float)i) / j)) - a4 * (cos( (6.0 * PI * (float)i) / j)) + 0.032 * (cos( (8.0 * PI * (float)i) / j)));
    }
}
void window_flat_top(t_window *x)
{
	int i, size;
	float j, a1, a2, a3, a4;
	size = x->f_size;
	j = size - 1;
	a1 = 1.f;
	a2 = 1.93f;
	a3 = 1.29f;
	a4 = 0.388;
	for(i = 0; i < size; i++)
    {
		x->f_envelope[i] = (a1 - a2 * (cos( (2.0 * PI * (float)i) / j)) + a3 * (cos( (4.0 * PI * (float)i) / j)) - a4 * (cos( (6.0 * PI * (float)i) / j)) + 0.032 * (cos( (8.0 * PI * (float)i) / j))) * 0.2;
    }
}

void window_poisson(t_window *x)
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