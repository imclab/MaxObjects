
#ifndef DEF_window
#define DEF_window

#include "ext.h"
#include "ext_obex.h"
#include "ext_common.h"
#include "z_dsp.h"

#define WINDOW_SIZE	16384

typedef struct _window
{
	float		*f_envelope;
	int			f_size;
}t_window;

void window_setup(t_window *x, int size);
void window_square(t_window *x);
void window_hamming(t_window *x);
void window_hanning(t_window *x);
void window_blackman(t_window *x);
void window_flat_top(t_window *x);
void window_poison(t_window *x);
void window_turkey(t_window *x);
void window_decay(t_window *x);
void window_rise(t_window *x);

void window_free(t_window *x);
#endif