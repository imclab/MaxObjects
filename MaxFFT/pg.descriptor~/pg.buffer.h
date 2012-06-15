
/*
* Copyright (C) 2012 Pierre Guillot, Universite Paris 8
* 
* This library is free software; you can redistribute it and/or modify it 
* under the terms of the GNU Library General Public License as published 
* by the Free Software Foundation; either version 2 of the License.
* 
* This library is distributed in the hope that it will be useful, but WITHOUT 
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
* FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public 
* License for more details.
*
* You should have received a copy of the GNU Library General Public License 
* along with this library; if not, write to the Free Software Foundation, 
* Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*
* guillotpierre6@gmail.com
*/

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