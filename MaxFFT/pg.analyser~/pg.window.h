
#ifndef DEF_MY_WINDOW
#define DEF_MY_WINDOW

#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"

#define WINDOW_SIZE	16384

typedef struct _window
{
	float		*f_envelope;
	int			f_size;
}t_window;

void window_setup(t_window *x, int size);
void window_free(t_window *x);

void window_square(t_window *x);
void window_hamming(t_window *x);
void window_hanning(t_window *x);
void window_blackman(t_window *x);
void window_turkey(t_window *x);
void window_cosinus(t_window *x);
void window_lanczos(t_window *x);
void window_triangular(t_window *x);
void window_gaussian(t_window *x);
void window_kaiser(t_window *x); // Not yet //
void window_bartlett_hann(t_window *x);
void window_nuttall(t_window *x);
void window_blackman_harris(t_window *x);
void window_blackman_nuttall(t_window *x);
void window_flat_top(t_window *x);
void window_poisson(t_window *x);

#endif