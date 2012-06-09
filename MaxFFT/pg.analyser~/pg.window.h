
#ifndef DEF_MY_WINDOW
#define DEF_MY_WINDOW

#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"

typedef struct _window
{
	t_sample	*f_envelope;
	long		f_size;
	long		f_mode;
}t_window;

void window_setup(t_window *x, long size, long mode);
void window_free(t_window *x);
t_max_err window_mode_set(t_window *x, t_object *attr, long argc, t_atom *argv);
void window_Selector(t_window *x);

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