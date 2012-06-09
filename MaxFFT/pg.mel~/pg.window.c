
#include "pg.window.h"

void window_square(t_window *x)
{
	int i, size;
	t_sample j;
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
	t_sample j;
	size = x->f_size;
	j = size - 1;
  
	for(i = 0; i < size; i++)
	{
		x->f_envelope[i] = 0.54 - (0.46 * cos(2.0 * PI *(t_sample)i / j));
	}
}

void window_hanning(t_window *x)
{
	int i, size;
	t_sample j;
	size = x->f_size;
	j = size - 1;
  
	for(i = 0; i < size; i++)
	{
		x->f_envelope[i] = 0.5 * (1.0 - cos(2.0 * PI * (t_sample)i /j));
	}
}

void window_blackman(t_window *x)
{
	int i, size;
	t_sample j;
	size = x->f_size;
	j = size - 1;

	for(i = 0; i < size; i++)
    {
		x->f_envelope[i] = 0.42 - (0.5 * cos(2.0 * PI * (t_sample)i / j)) + (0.08 * cos(4.0 * PI * (t_sample)i / j));
    }
}

void window_cosinus(t_window *x)
{
	int i, size;
	t_sample j;
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
	t_sample j, alpha;
	size = x->f_size;
	j = size - 1;

	for(i = 0; i < size; i++)
    {
		alpha = PI * (((2. * (t_sample)i) / j) - 1.);
		x->f_envelope[i] = sin(alpha)/alpha;
    }
}


void window_kaiser(t_window *x)
{
	// Not yet //
	int i, size;
	t_sample j, alpha, a, b, iota;
	size = x->f_size;
	j = size - 1;
	alpha = 3.;
	for(i = 0; i < size; i++)
    {
		//b = (((2. * (t_sample)i) / j) - 1.) * (((2. * (t_sample)i) / j) - 1.);
		//a = iota * (PI * alpha * (sqrt( 1. - b))) / iota * (PI * alpha)
		x->f_envelope[i] = 1.;
    }
}

void window_triangular(t_window *x)
{
	int i, size;
	t_sample j, k, alpha;
	size = x->f_size;
	j = size - 1;
	alpha = 0.5;
	for(i = 0; i < size; i++)
    {
		k = (t_sample)i -(j / 2.);
		x->f_envelope[i] = (2. / j) * ((j / 2.) - k);
    }
}

void window_gaussian(t_window *x)
{
	int i, size;
	t_sample j, k, alpha;
	size = x->f_size;
	j = size - 1;
	alpha = 0.5;
	for(i = 0; i < size; i++)
    {
		k = (i - j / 2.)/(alpha * j / 2.) * (i - j / 2.)/(alpha * j / 2.) * -0.5;
		x->f_envelope[i] = exp(k);
    }
}

void window_bartlett_hann(t_window *x)
{
	int i, size;
	t_sample j, a1, a2, a3, abso;
	size = x->f_size;
	j = size - 1;
	a1 = 0.62;
	a2 = 0.48;
	a3 = 0.38;
	for(i = 0; i < size; i++)
    {
		abso = ((t_sample)i / (t_sample)j) - 0.5;
		if(abso < 0.) abso = -abso;
		x->f_envelope[i] = a1 - a2 * abso - a3 * cos((2.0 * PI *(t_sample)i) / j);
    }
}

void window_nuttall(t_window *x)
{
	int i, size;
	t_sample j, a1, a2, a3, a4;
	size = x->f_size;
	j = size - 1;
	a1 = 0.255768;
	a2 = 0.487395;
	a3 = 0.144232;
	a4 = 0.012604;
	for(i = 0; i < size; i++)
    {
		x->f_envelope[i] = (a1 - a2 * (cos( (2.0 * PI * (t_sample)i) / j)) + a3 * (cos( (4.0 * PI * (t_sample)i) / j)) - a4 * (cos( (6.0 * PI * (t_sample)i) / j)) + 0.032 * (cos( (8.0 * PI * (t_sample)i) / j)));
    }
}

void window_blackman_harris(t_window *x)
{
	int i, size;
	t_sample j, a1, a2, a3, a4;
	size = x->f_size;
	j = size - 1;
	a1 = 0.35875;
	a2 = 0.48829;
	a3 = 0.14128;
	a4 = 0.01168;
	for(i = 0; i < size; i++)
    {
		x->f_envelope[i] = (a1 - a2 * (cos( (2.0 * PI * (t_sample)i) / j)) + a3 * (cos( (4.0 * PI * (t_sample)i) / j)) - a4 * (cos( (6.0 * PI * (t_sample)i) / j)) + 0.032 * (cos( (8.0 * PI * (t_sample)i) / j)));
    }
}

void window_blackman_nuttall(t_window *x)
{
	int i, size;
	t_sample j, a1, a2, a3, a4;
	size = x->f_size;
	j = size - 1;
	a1 = 0.3635819;
	a2 = 0.4891775;
	a3 = 0.1365995;
	a4 = 0.0106441;
	for(i = 0; i < size; i++)
    {
		x->f_envelope[i] = (a1 - a2 * (cos( (2.0 * PI * (t_sample)i) / j)) + a3 * (cos( (4.0 * PI * (t_sample)i) / j)) - a4 * (cos( (6.0 * PI * (t_sample)i) / j)) + 0.032 * (cos( (8.0 * PI * (t_sample)i) / j)));
    }
}
void window_flat_top(t_window *x)
{
	int i, size;
	t_sample j, a1, a2, a3, a4;
	size = x->f_size;
	j = size - 1;
	a1 = 1.;
	a2 = 1.93;
	a3 = 1.29;
	a4 = 0.388;
	for(i = 0; i < size; i++)
    {
		x->f_envelope[i] = (a1 - a2 * (cos( (2.0 * PI * (t_sample)i) / j)) + a3 * (cos( (4.0 * PI * (t_sample)i) / j)) - a4 * (cos( (6.0 * PI * (t_sample)i) / j)) + 0.032 * (cos( (8.0 * PI * (t_sample)i) / j))) * 0.2;
    }
}

void window_poisson(t_window *x)
{
	int i, size;
	t_sample j, alpha, beta;
	size = x->f_size;
	j = size - 1;
	alpha = 1./ (((t_sample)size / 2.)/(60./8.69));
	for(i = 0; i < size; i++)
    {
		beta = -1. * ((t_sample)i - (j / 2.));
		if (beta >= 0) beta = -beta;
		beta *= alpha;
		x->f_envelope[i] = exp(beta);
    }
}

void window_turkey(t_window *x)
{
	int i, size;
	t_sample j, alpha;
	size = x->f_size;
	j = size - 1;
	alpha = 0.5;
	for(i = 0; i < size; i++)
    {
		if(i <= ((alpha * j) / 2.))
			x->f_envelope[i] = 0.5 * ( 1. + cos(PI * ( ((2 *(t_sample)i) / (alpha * j)) - 1.)));
		else if(i > ((alpha * j) / 2.) && i <= (j * (1. - ( alpha / 2.))))
			x->f_envelope[i] = 1.;
		else 
			x->f_envelope[i] = 0.5 * ( 1. + cos(PI * ( ((2 *(t_sample)i) / (alpha * j)) + 1. - (2. / alpha))));
    }
}


void window_setup(t_window *x, long size, long mode)
{
	if(x->f_size != size || x->f_mode != mode)
	{
		if(x->f_size != size)
		{
			if(x->f_envelope) 
				freebytes(x->f_envelope, x->f_size * sizeof(double));

			x->f_size = size;
			x->f_envelope = (double *)getbytes(x->f_size * sizeof(double));
		}
		if(x->f_mode != mode)
		{
			x->f_mode = mode;
		}
		window_Selector(x);
	}
}


void window_free(t_window *x)
{
	if(x->f_envelope != NULL) freebytes(x->f_envelope, sizeof(t_sample)* x->f_size);
}

t_max_err window_mode_set(t_window *x, t_object *attr, long argc, t_atom *argv)
{
	int mode;
	mode = 16;
	if ( atom_gettype(argv) == A_LONG) mode = atom_getlong(argv);
	else if ( atom_gettype(argv) == A_FLOAT) mode = (int)atom_getfloat(argv);
	else if ( atom_gettype(argv) == A_SYM)
	{
		if ( gensym(argv->a_w.w_sym->s_name)	  == gensym("Square"))			mode = 0;
		else if ( gensym(argv->a_w.w_sym->s_name) == gensym("Hanning"))			mode = 1;
		else if ( gensym(argv->a_w.w_sym->s_name) == gensym("Hamming"))			mode = 2;
		else if ( gensym(argv->a_w.w_sym->s_name) == gensym("Turkey"))			mode = 3;
		else if ( gensym(argv->a_w.w_sym->s_name) == gensym("Cosinus"))			mode = 4;
		else if ( gensym(argv->a_w.w_sym->s_name) == gensym("Lanczos"))			mode = 5;
		else if ( gensym(argv->a_w.w_sym->s_name) == gensym("Triangular"))		mode = 6;
		else if ( gensym(argv->a_w.w_sym->s_name) == gensym("Gaussian"))		mode = 7;
		else if ( gensym(argv->a_w.w_sym->s_name) == gensym("Bartlett-Hann"))	mode = 8;
		else if ( gensym(argv->a_w.w_sym->s_name) == gensym("Blackman"))		mode = 9;
		else if ( gensym(argv->a_w.w_sym->s_name) == gensym("Kaiser"))			mode = 10;
		else if ( gensym(argv->a_w.w_sym->s_name) == gensym("Nuttall"))			mode = 11;
		else if ( gensym(argv->a_w.w_sym->s_name) == gensym("Blackman-Harris"))	mode = 12;
		else if ( gensym(argv->a_w.w_sym->s_name) == gensym("Blackman-Nuttall"))mode = 13;
		else if ( gensym(argv->a_w.w_sym->s_name) == gensym("Flat-Top"))		mode = 14;
		else if ( gensym(argv->a_w.w_sym->s_name) == gensym("Poisson"))			mode = 15;
	}
	if(mode != x->f_mode)
	{
		x->f_mode = mode;
		window_Selector(x);
	}
	
	return 0;
}

void window_Selector(t_window *x)
{
	if(x->f_envelope)
	{
		switch(x->f_mode)
		{
			case 0:
				window_square(x);
				break;
			case 1:
				window_hanning(x);
				break;
			case 2:
				window_hamming(x);
				break;
			case 3:
				window_turkey(x);
				break;
			case 4:
				window_cosinus(x);
				break;
			case 5:
				window_lanczos(x);
				break;
			case 6:
				window_triangular(x);
				break;
			case 7:
				window_gaussian(x);
				break;
			case 8:
				window_bartlett_hann(x);
				break;
			case 9:
				window_blackman(x);
				break;
			case 10:
				window_kaiser(x);
				break;
			case 11:
				window_nuttall(x);
				break;
			case 12:
				window_blackman_harris(x);
				break;
			case 13:
				window_blackman_nuttall(x);
				break;
			case 14:
				window_flat_top(x);
				break;
			case 15:
				window_poisson(x);
				break;
		}
	}
}