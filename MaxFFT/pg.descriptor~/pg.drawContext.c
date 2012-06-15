
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

void draw_timeline(t_descriptor *x, t_object *view, t_rect *rect)
{
	double textSize;
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("time_line_layer"), rect->width, rect->height);
	textSize = jbox_get_fontsize((t_object *)x);

	if (g) 
	{
		// Time Line background //
		jgraphics_set_source_jrgba(g, &x->f_colorsTimeBg);
		jgraphics_rectangle_fill_fast(g, 0., 0., rect->width, textSize + 2.);
		
		// Time Line Border //
		jgraphics_set_source_jrgba(g, &x->f_colorsTimeBd);
		jgraphics_rectangle_fill_fast(g, 0., textSize + 2., rect->width, 1.);
		
		jbox_end_layer((t_object*)x, view, gensym("time_line_layer"));
	}
	if(x->f_contextMode[0] == 1)
	{
		jbox_paint_layer((t_object *)x, view, gensym("time_line_layer"), 0., 0.);
		rect->height		-= textSize + 3.;
		rect->y				+= textSize + 3.;
		//x->f_middleY = rect->y + (rect->height / 2.) -1.5;
	}
}
void draw_background(t_descriptor *x,  t_object *view, t_rect *rect)
{
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("background_layer"), rect->width, rect->height);

	if (g) 
	{
		jgraphics_set_source_jrgba(g, &x->f_colorBackground);
		jgraphics_rectangle_fill_fast(g, 0., 0., rect->width, rect->height);
		
		jbox_end_layer((t_object*)x, view, gensym("background_layer"));
	}

	jbox_paint_layer((t_object *)x, view, gensym("background_layer"), rect->x, rect->y);
}

void draw_bar(t_descriptor *x, t_object *view, t_rect *rect)
{
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("bar_layer"), rect->width, rect->height);
	
	if (g)
	{
		jgraphics_set_source_rgba(g, 0., 0., 0., x->f_alpha);
		jgraphics_rectangle_fill_fast(g, x->f_mouseX1, 0., x->f_mouseX2, rect->height);
		jbox_end_layer((t_object*)x, view, gensym("bar_layer"));
	}
	jbox_paint_layer((t_object *)x, view, gensym("bar_layer"), 0., 0.);
}


/*
void draw_indicator_text(t_descriptor *x, t_object *view, t_rect *rect)
{
	int i, j, value;
	char text[16];
	double range, offset = 0.;
	double textSize = jbox_get_fontsize((t_object *)x);
	t_jfont *jf = jfont_create(jbox_get_fontname((t_object *)x)->s_name, (t_jgraphics_font_slant)jbox_get_font_slant((t_object *)x), (t_jgraphics_font_weight)jbox_get_font_weight((t_object *)x), jbox_get_fontsize((t_object *)x));
	t_jtextlayout *jtl = jtextlayout_create();
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("indicator_text_layer"), rect->width, rect->height);

	if (g)
	{
		if(x->f_mode[0] == 1) offset = textSize + 2.;
		
		jgraphics_set_source_jrgba(g, &x->f_colorsTimeBd);
		range = (x->f_buf.f_samplingRate / 2.) / ((rect->height - offset) / 15);
		for(i = rect->height - 15, j = 1; i > offset + 15; i -= 15, j++)
		{
			value = j * range;
			sprintf(text, "%i", value);

			jtextlayout_set(jtl, text, jf, rect->width - 45., (double)i - (textSize / 2.), 40, textSize, JGRAPHICS_TEXT_JUSTIFICATION_RIGHT, JGRAPHICS_TEXTLAYOUT_NOWRAP);
			jtextlayout_settextcolor(jtl,  &x->f_colorText); 
			jtextlayout_draw(jtl, g);
		}
	}

	jtextlayout_destroy(jtl);
	jfont_destroy(jf);
	jbox_end_layer((t_object*)x, view, gensym("indicator_text_layer"));
	jbox_paint_layer((t_object *)x, view, gensym("indicator_text_layer"), 0., 0.);
}

void draw_indicator_tick(t_descriptor *x,  t_object *view, t_rect *rect)
{
	int i;
	double  offset = 0.;
	double	textSize = jbox_get_fontsize((t_object *)x);
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("indicator_tick_layer"), rect->width, rect->height);

	if (g) 
	{
		jgraphics_set_source_jrgba(g, &x->f_colorsTimeBd);

		if(x->f_mode[0] == 1) offset = textSize + 2.;
		for(i = rect->height; i > offset + 15; i -= 15)
		{
			jgraphics_rectangle_fill_fast(g, rect->width - 3, (double)i, 3., 1.);
		}
		jbox_end_layer((t_object*)x, view, gensym("indicator_tick_layer"));
	}
	jbox_paint_layer((t_object *)x, view, gensym("indicator_tick_layer"), 0., 0.);
}
*/