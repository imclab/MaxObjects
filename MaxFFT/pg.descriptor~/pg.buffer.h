
#include "ext.h"
#include "ext_obex.h"
#include "buffer.h"
#include "ext_atomic.h"
#include "ext_obex.h"
#include "z_dsp.h"

typedef struct _buf
{
	t_symbol	*f_name;
	t_buffer	*f_buffer;

	long		f_waveformSize;
	double		*f_waveform[4];
	long		f_spectrogramSize;
	double		*f_spectrogram[4];
} t_buf;

void buffer_init(t_buf *x);
void buffer_set(t_buf *x, t_symbol *name, long arraySize);
void waveform_compute(t_buf *x);
void buffer_free(t_buf *x);