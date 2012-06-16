
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

#include "pg.descriptor.h"

void buffer_setup(t_descriptor *x, long windowSize, long overlapping)
{
	int i, j, nSamples;
	t_atom argv[1];

	if(x->f_buf.f_buffer)
	{
		nSamples =x->f_buf.f_buffer->b_frames;
		x->f_buf.f_nChannels = x->f_buf.f_buffer->b_nchans;
		x->f_buf.f_samplingRate =x->f_buf.f_buffer->b_sr;
		atom_setlong(argv, x->f_buf.f_channel);
		channel_set(x, NULL, 1, argv);
	}
	else
	{
		nSamples = 0;
	}
	if(x->f_buf.f_windowSize != windowSize || x->f_buf.f_overlapping != overlapping || x->f_buf.f_nSamples != nSamples || x->f_changes == 1)
	{
		analysis_free(&x->f_buf);
		x->f_buf.f_windowSize = windowSize;
		x->f_buf.f_arraySize = x->f_buf.f_windowSize / 2;
		x->f_buf.f_overlapping = overlapping;

		x->f_buf.f_nSamples = nSamples;
		x->f_buf.f_nFrames = (x->f_buf.f_nSamples / x->f_buf.f_windowSize) * x->f_buf.f_overlapping;

		analysis_setup(&x->f_buf);

		x->f_buf.f_rapportSize = (float)(PI * (1.0 / (float)x->f_buf.f_arraySize));
		descriptor_compute(&x->f_buf, &x->f_window);
		
		x->f_hOffset = 0.;
		x->f_hZoom	= 1.;
		x->f_vOffset = 0.;
		x->f_hZoom = 1.;
		jbox_invalidate_layer((t_object *)x, NULL, gensym("sonogram_layer"));
		jbox_invalidate_layer((t_object *)x, NULL, gensym("centroid_layer"));
		jbox_invalidate_layer((t_object *)x, NULL, gensym("spread_layer"));
		jbox_invalidate_layer((t_object *)x, NULL, gensym("skewness_layer"));
		jbox_invalidate_layer((t_object *)x, NULL, gensym("kurtosis_layer"));
		jbox_invalidate_layer((t_object *)x, NULL, gensym("amplitude_layer"));
		jbox_redraw((t_jbox *)x);
		x->f_changes = 0;
	}
}

t_max_err buffer_set(t_descriptor *x, t_object *attr, long argc, t_atom *argv)
{
	int i;
	t_buffer *b;
	t_symbol *name;

	if (atom_gettype(argv) == A_SYM)
	{
		name = atom_getsym(argv);
		if(x->f_buf.f_name != name)
		{
			if ((b = (t_buffer *)(name->s_thing)) && ob_sym(b) == gensym("buffer~")) 
			{
				if(x->f_buf.f_name && x->f_buf.f_buffer != NULL)
				{
					globalsymbol_dereference((t_object*)x, x->f_buf.f_name->s_name, "buffer~");
				}
				x->f_buf.f_name = name;
				x->f_buf.f_buffer = (t_buffer*)globalsymbol_reference((t_object*)x, x->f_buf.f_name->s_name, "buffer~");
				x->f_changes = 1;
				buffer_setup(x, x->f_buf.f_windowSize, x->f_buf.f_overlapping); 
			}
			else
			{
				x->f_buf.f_buffer = NULL;
				x->f_buf.f_name = gensym("");
			}
		}
	}

	return 0;
}

t_max_err channel_set(t_descriptor *x, t_object *attr, long argc, t_atom *argv)
{
	if(atom_gettype(argv) == A_LONG)
	{
		if(x->f_buf.f_buffer == NULL)
		{
			if(atom_getlong(argv) > 1)
			{
				x->f_buf.f_channel = 1;
			}
			else
			{
				x->f_buf.f_channel = atom_getlong(argv);
			}
		}
		else
		{
			if(atom_getlong(argv) > x->f_buf.f_nChannels)
			{
				x->f_buf.f_channel = x->f_buf.f_nChannels;
			}
			else
			{
				x->f_buf.f_channel = atom_getlong(argv);
			}
		}
		jbox_invalidate_layer((t_object *)x, NULL, gensym("sonogram_layer"));
		jbox_invalidate_layer((t_object *)x, NULL, gensym("centroid_layer"));
		jbox_invalidate_layer((t_object *)x, NULL, gensym("spread_layer"));
		jbox_invalidate_layer((t_object *)x, NULL, gensym("skewness_layer"));
		jbox_invalidate_layer((t_object *)x, NULL, gensym("kurtosis_layer"));
		jbox_invalidate_layer((t_object *)x, NULL, gensym("amplitude_layer"));
		jbox_redraw((t_jbox *)x);
	}
	return 0;
}

t_max_err window_set(t_descriptor *x, t_object *attr, long argc, t_atom *argv)
{
	if(atom_gettype(argv) == A_LONG)
	{
		if(atom_getlong(argv) != x->f_window.f_mode)
		{
			x->f_window.f_mode = atom_getlong(argv);
			buffer_setup(x, x->f_buf.f_windowSize, x->f_buf.f_overlapping);
		}
	}
	return 0;
}

t_max_err window_size_set(t_descriptor *x, t_object *attr, long argc, t_atom *argv)
{
	if(atom_gettype(argv) == A_LONG)
	{
		buffer_setup(x, atom_getlong(argv), x->f_buf.f_overlapping);
	}	
	return 0;
}

t_max_err overlapping_set(t_descriptor *x, t_object *attr, long argc, t_atom *argv)
{
	if(atom_gettype(argv) == A_LONG)
	{
		buffer_setup(x, x->f_buf.f_windowSize, atom_getlong(argv));
	}
	return 0;
}

void buffer_free(t_buf *x)
{
	analysis_free(x);
}