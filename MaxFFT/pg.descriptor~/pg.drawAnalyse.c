
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

void draw_spectrogram(t_descriptor *x, t_object *view, t_rect *rect)
{
	int  channel;
	double width, height, x1, y1, x2, y2, red, green, ratioWidth, ratioHeight, i, j;
	
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("sonogram_layer"), rect->width, rect->height);

	if (g) 
	{
		if(x->f_buf.f_nFrames != 0 && x->f_buf.f_arraySize != 0) 
		{
			channel = x->f_buf.f_channel - 1;
			ratioWidth	= width		= rect->width / (double)(x->f_buf.f_nFrames - 1);
			ratioHeight = height	= (rect->height / (double)x->f_ratio) / (double)(x->f_buf.f_arraySize);
			if(width <= 1.)
				width	= 1. / (rect->width / (double)(x->f_buf.f_nFrames - 1));
			if(height <= 1.)			
				height	= 1. / ((rect->height / (double)x->f_ratio) / (double)(x->f_buf.f_arraySize));

			for(i = 0.; i < (double)(x->f_buf.f_nFrames - 1); i += width)
			{
				for(j = 0.; j < (double)x->f_buf.f_arraySize; j += height)
				{
					x1 = i * ratioWidth;
					y1 = (rect->height / (double)x->f_ratio) - (j - height) * ratioHeight;

					x2 = width * ratioWidth;
					y2 = height* ratioHeight;

					red = 1. - (x->f_buf.f_sonogram[channel][(int)i][(int)j] / -90.);
					green = x->f_buf.f_sonogram[channel][(int)i][(int)j] / -90.;
					jgraphics_set_source_rgba(g, red, green, 0., 1.);
					jgraphics_rectangle_fill_fast(g, x1, y1, x2, y2);

				}
			}
		}
		jbox_end_layer((t_object*)x, view, gensym("sonogram_layer"));
	}
	if(x->f_analyseMode[3] == 1)
		jbox_paint_layer((t_object *)x, view, gensym("sonogram_layer"), rect->x, rect->y -1.);
}

void draw_centroid(t_descriptor *x, t_object *view, t_rect *rect)
{	
	int channel;
	double width, height, x1, y1, x2, y2, value, ratioWidth, i;

	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("centroid_layer"), rect->width, rect->height);
	
	if (g) 
	{
		if(x->f_buf.f_nSamples != 0)
		{
			channel = x->f_buf.f_channel - 1;
			ratioWidth = width	= rect->width / (double)(x->f_buf.f_nFrames - 1);
			if(width <= 1.)
				width	= 1. / (rect->width / (double)(x->f_buf.f_nFrames - 1));
			height	= rect->height / (double)x->f_ratio;
			jgraphics_set_source_rgba(g, 0., 0., 0., 1.);
			for(i = 0.; i < (double)(x->f_buf.f_nFrames - 1); i += width)
			{
				x1 = i * ratioWidth;
				x2 = (i + width) * ratioWidth;

				y1 = height - (x->f_buf.f_centroid[channel][(int)i] / (double)x->f_buf.f_buffer->b_sr) * height;
				y2 = height - (x->f_buf.f_centroid[channel][(int)(i + width)] / (double)x->f_buf.f_buffer->b_sr) * height;
				jgraphics_line_draw_fast(g, x1, y1, x2, y2, 1.);
			}
		}
		jbox_end_layer((t_object*)x, view, gensym("centroid_layer"));
	}
	if(x->f_analyseMode[4] == 1)
		jbox_paint_layer((t_object *)x, view, gensym("centroid_layer"), rect->x, rect->y -1.);
}

void draw_spread(t_descriptor *x, t_object *view, t_rect *rect)
{	
	int channel;
	double width, height, x1, y1, x2, y2, value, ratioWidth, i;

	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("spread_layer"), rect->width, rect->height);

	if (g) 
	{
		if(x->f_buf.f_nSamples != 0)
		{
			channel = x->f_buf.f_channel - 1;
			ratioWidth = width	= rect->width / (double)(x->f_buf.f_nFrames - 1);
			if(width <= 1.)
				width	= 1. / (rect->width / (double)(x->f_buf.f_nFrames - 1));
			height	= rect->height / (double)x->f_ratio;
			jgraphics_set_source_rgba(g, 0.8, 0.8, 0.8, 1.);
			for(i = 0.; i < (double)(x->f_buf.f_nFrames - 1); i += width)
			{
				x1 = i * ratioWidth;
				x2 = (i + width) * ratioWidth;

				y1 = height - ((x->f_buf.f_centroid[channel][(int)i] + x->f_buf.f_spread[channel][(int)i]) / (double)x->f_buf.f_buffer->b_sr) * height;
				y2 = height - ((x->f_buf.f_centroid[channel][(int)(i + width)] + x->f_buf.f_spread[channel][(int)(i + width)]) / (double)x->f_buf.f_buffer->b_sr) * height;
				jgraphics_line_draw_fast(g, x1, y1, x2, y2, 1.);

				y1 = height - ((x->f_buf.f_centroid[channel][(int)i] - x->f_buf.f_spread[channel][(int)i]) / (double)x->f_buf.f_buffer->b_sr) * height;
				y2 = height - ((x->f_buf.f_centroid[channel][(int)(i + width)] - x->f_buf.f_spread[channel][(int)(i + width)]) / (double)x->f_buf.f_buffer->b_sr) * height;
				if(y1 <= height) y1 = height;
				if(y2 <= height) y2 = height;
				jgraphics_line_draw_fast(g, x1, y1, x2, y2, 1.);
			}
		}
		jbox_end_layer((t_object*)x, view, gensym("spread_layer"));
	}
	if(x->f_analyseMode[5] == 1)
		jbox_paint_layer((t_object *)x, view, gensym("spread_layer"), rect->x, rect->y -1.);
}

void draw_skewness(t_descriptor *x, t_object *view, t_rect *rect)
{	
	int channel;
	double width, height, x1, y1, x2, y2, value, ratioWidth, i;

	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("skewness_layer"), rect->width, rect->height);

	if (g) 
	{
		if(x->f_buf.f_nSamples != 0)
		{
			channel = x->f_buf.f_channel - 1;
			ratioWidth = width	= rect->width / (double)(x->f_buf.f_nFrames - 1);
			if(width <= 1.)
				width	= 1. / (rect->width / (double)(x->f_buf.f_nFrames - 1));
			height	= rect->height / (double)x->f_ratio;
			jgraphics_set_source_rgba(g, 0., 0., 0., 1.);
			for(i = 0.; i < (double)(x->f_buf.f_nFrames - 1); i += width)
			{
				x1 = i * ratioWidth;
				x2 = (i + width) * ratioWidth;

				value = x->f_buf.f_skewness[channel][(int)i];
				if(value > 10.) value = 10.;
				if(value < -10.) value = -10.;
				value += 10.;
				value /= 20.;
				y1 = rect->height - x->f_offset - (value * height);

				value = x->f_buf.f_skewness[channel][(int)(i + width)];
				if(value > 10.) value = 10.;
				if(value < -10.) value = -10.;
				value += 10.;
				value /= 20.;
				y2 = rect->height - x->f_offset - (value * height);
				jgraphics_line_draw_fast(g, x1, y1, x2, y2, 1.);
			}
			jgraphics_set_source_jrgba(g, &x->f_colorsTimeBd);
			jgraphics_line_draw_fast(g, 0., rect->height - height - 1 - x->f_offset, rect->width, rect->height - height - 1 - x->f_offset, 1.);
		}
		jbox_end_layer((t_object*)x, view, gensym("skewness_layer"));
	}
	if(x->f_analyseMode[2] == 1)
	{
		x->f_offset += (rect->height / x->f_ratio) + 1.;
		jbox_paint_layer((t_object *)x, view, gensym("skewness_layer"), rect->x, rect->y);
	}
}

void draw_kurtosis(t_descriptor *x, t_object *view, t_rect *rect)
{	
	int channel;
	double width, height, x1, y1, x2, y2, value, ratioWidth, i;
	
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("kurtosis_layer"), rect->width, rect->height);

	if (g) 
	{
		if(x->f_buf.f_nSamples != 0)
		{
			channel = x->f_buf.f_channel - 1;
			ratioWidth = width	= rect->width / (double)(x->f_buf.f_nFrames - 1);
			if(width <= 1.)
				width	= 1. / (rect->width / (double)(x->f_buf.f_nFrames - 1));
			height	= rect->height / (double)x->f_ratio;
			jgraphics_set_source_rgba(g, 0., 0., 0., 1.);
			for(i = 0.; i < (double)(x->f_buf.f_nFrames - 1); i += width)
			{
				x1 = i * ratioWidth;
				x2 = (i + width) * ratioWidth;

				value = x->f_buf.f_kurtosis[channel][(int)i];
				if(value > 100.) value = 100.;
				value /= 100.;
				y1 = rect->height - x->f_offset - (value * height);

				value = x->f_buf.f_kurtosis[channel][(int)(i + width)];
				if(value > 100.) value = 100.;
				value /= 100.;
				y2 = rect->height - x->f_offset - (value * height);

				jgraphics_line_draw_fast(g, x1, y1, x2, y2, 1.);
			}
			jgraphics_set_source_jrgba(g, &x->f_colorsTimeBd);
			jgraphics_line_draw_fast(g, 0., rect->height - height - 1 - x->f_offset, rect->width, rect->height - height - 1 - x->f_offset, 1.);
		}
		jbox_end_layer((t_object*)x, view, gensym("kurtosis_layer"));
	}
	if(x->f_analyseMode[1] == 1)
	{
		x->f_offset += (rect->height / x->f_ratio) + 1.;
		jbox_paint_layer((t_object *)x, view, gensym("kurtosis_layer"), rect->x, rect->y);
	}
}

void draw_amplitude(t_descriptor *x, t_object *view, t_rect *rect)
{	
	int channel;
	double width, height, x1, y1, x2, y2, value, ratioWidth, i;

	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("amplitude_layer"), rect->width, rect->height);

	if (g) 
	{
		if(x->f_buf.f_nSamples != 0)
		{
			channel = x->f_buf.f_channel - 1;
			ratioWidth = width	= rect->width / (double)(x->f_buf.f_nFrames - 1);
			if(width <= 1.)
				width	= 1. / (rect->width / (double)(x->f_buf.f_nFrames - 1));
			height	= rect->height / (double)x->f_ratio;
			jgraphics_set_source_rgba(g, 0., 0., 0., 1.);
			for(i = 0.; i < (double)(x->f_buf.f_nFrames - 1); i += width)
			{
				x1 = i * ratioWidth ;
				x2 = (i + width) * ratioWidth;
				value = x->f_buf.f_minAmp[channel][(int)i];
				value /= 90.;
				value += 1.;
				y1 = rect->height - (value * height);
				value = x->f_buf.f_minAmp[channel][(int)(i + width)];
				value /= 90.;
				value += 1.;
				y2 = rect->height - (value * height);
				jgraphics_line_draw_fast(g, x1, y1, x2, y2, 1.);

				value = x->f_buf.f_aveAmp[channel][(int)i];
				value /= 90.;
				value += 1.;
				y1 = rect->height - (value * height);
				value = x->f_buf.f_aveAmp[channel][(int)(i + width)];
				value /= 90.;
				value += 1.;
				y2 = rect->height - (value * height);
				jgraphics_line_draw_fast(g, x1, y1, x2, y2, 1.);

				value = x->f_buf.f_maxAmp[channel][(int)i];
				value /= 90.;
				value += 1.;
				y1 = rect->height - (value * height);
				value = x->f_buf.f_maxAmp[channel][(int)(i + width)];
				value /= 90.;
				value += 1.;
				y2 = rect->height - (value * height);
				jgraphics_line_draw_fast(g, x1, y1, x2, y2, 1.);
			}
			jgraphics_set_source_jrgba(g, &x->f_colorsTimeBd);
			jgraphics_line_draw_fast(g, 0., rect->height -  height - 1, rect->width, rect->height -  height - 1, 1.);
		}
		jbox_end_layer((t_object*)x, view, gensym("amplitude_layer"));
	}
	if(x->f_analyseMode[0] == 1)
	{
		x->f_offset += (rect->height / x->f_ratio) + 1.;
		jbox_paint_layer((t_object *)x, view, gensym("amplitude_layer"), rect->x, rect->y);
	}
		
}