#include "pg.descriptor.h"

int main()
{
	t_class *c;

	c = class_new("pg.descriptor~", (method)descriptor_new, (method)descriptor_free, (short)sizeof(t_descriptor), 0L, A_GIMME, 0);

	c->c_flags |= CLASS_FLAG_NEWDICTIONARY;
	jbox_initclass(c, JBOX_COLOR | JBOX_FIXWIDTH | JBOX_FONTATTR);

	class_addmethod(c, (method)descriptor_assist,		"assist",		A_CANT,	0);
	class_addmethod(c, (method)descriptor_paint,		"paint",		A_CANT,	0);
	class_addmethod(c, (method)descriptor_notify,		"notify",		A_CANT, 0);
	class_addmethod(c, (method)descriptor_mousedown,	"mousedown",	A_CANT, 0);
	class_addmethod(c, (method)descriptor_mousedrag,	"mousedrag",	A_CANT, 0);
	class_addmethod(c, (method)descriptor_mouseup,		"mouseup",		A_CANT, 0);
	class_addmethod(c, (method)descriptor_mousewheel,	"mousewheel",	A_CANT, 0);

	CLASS_ATTR_DEFAULT			(c, "patching_rect", 0, "0 0 300 120");

	/* Descriptor */
	CLASS_ATTR_LONG				(c, "windowsize", 0, t_descriptor, f_buf.f_windowSize);
	CLASS_ATTR_CATEGORY			(c, "windowsize", 0, "Descriptor~");
	CLASS_ATTR_LABEL			(c, "windowsize", 0, "Window Size");
	CLASS_ATTR_FILTER_MIN		(c, "windowsize", 2);
	CLASS_ATTR_DEFAULT			(c, "windowsize", 0, "2048");
	CLASS_ATTR_ACCESSORS		(c, "windowsize", NULL, window_size_set);
	CLASS_ATTR_SAVE				(c, "windowsize", 1);
	CLASS_ATTR_ORDER			(c, "windowsize", 0, "1");

	CLASS_ATTR_LONG				(c, "overlapping", 0, t_descriptor, f_buf.f_overlapping);
	CLASS_ATTR_CATEGORY			(c, "overlapping", 0, "Descriptor~");
	CLASS_ATTR_LABEL			(c, "overlapping", 0, "Overlapping");
	CLASS_ATTR_FILTER_MIN		(c, "overlapping", 1);
	CLASS_ATTR_DEFAULT			(c, "overlapping", 0, "4");
	CLASS_ATTR_SAVE				(c, "overlapping", 1);
	CLASS_ATTR_ORDER			(c, "overlapping", 0, "3");

	CLASS_ATTR_LONG				(c, "window", 0, t_descriptor, f_window.f_mode);
	CLASS_ATTR_CATEGORY			(c, "window", 0, "Descriptor~");
	CLASS_ATTR_LABEL			(c, "window", 0, "Window function");
	CLASS_ATTR_ENUMINDEX		(c, "window", 0, "Square \" \"Hanning \" \"Hamming \" \"Turkey \" \"Cosinus \" \"Lanczos \" \"Triangular \" \"Gaussian \" \"Bartlett-Hann \" \"Blackman \" \"Kaiser \" \"Nuttall \" \"Blackman-Harris \" \"Blackman-Nuttall \" \"Flat-Top \" \"Poisson");
	CLASS_ATTR_ACCESSORS		(c, "window", NULL, window_set);
	CLASS_ATTR_DEFAULT			(c, "window", 0, "1");
	CLASS_ATTR_SAVE				(c, "window", 1);
	CLASS_ATTR_FILTER_CLIP		(c, "window", 0, 10);
	CLASS_ATTR_ORDER			(c, "window", 0, "2");

	CLASS_ATTR_LONG				(c, "sonogram", 0, t_descriptor, f_analyseMode[3]);
	CLASS_ATTR_CATEGORY			(c, "sonogram", 0, "Descriptor~");
	CLASS_ATTR_STYLE			(c, "sonogram", 0, "onoff");
	CLASS_ATTR_ORDER			(c, "sonogram", 0, "1");
	CLASS_ATTR_LABEL			(c, "sonogram", 0, "Sonogram");
	CLASS_ATTR_DEFAULT			(c, "sonogram", 0, "1");
	CLASS_ATTR_SAVE				(c, "sonogram", 1);
	
	CLASS_ATTR_LONG				(c, "centroid", 0, t_descriptor, f_analyseMode[4]);
	CLASS_ATTR_CATEGORY			(c, "centroid", 0, "Descriptor~");
	CLASS_ATTR_STYLE			(c, "centroid", 0, "onoff");
	CLASS_ATTR_ORDER			(c, "centroid", 0, "1");
	CLASS_ATTR_LABEL			(c, "centroid", 0, "Centroid");
	CLASS_ATTR_DEFAULT			(c, "centroid", 0, "1");
	CLASS_ATTR_SAVE				(c, "centroid", 1);

	CLASS_ATTR_LONG				(c, "deviation", 0, t_descriptor, f_analyseMode[5]);
	CLASS_ATTR_CATEGORY			(c, "deviation", 0, "Descriptor~");
	CLASS_ATTR_STYLE			(c, "deviation", 0, "onoff");
	CLASS_ATTR_ORDER			(c, "deviation", 0, "1");
	CLASS_ATTR_LABEL			(c, "deviation", 0, "Spread");
	CLASS_ATTR_DEFAULT			(c, "deviation", 0, "1");
	CLASS_ATTR_SAVE				(c, "deviation", 1);

	CLASS_ATTR_LONG				(c, "skewness", 0, t_descriptor, f_analyseMode[2]);
	CLASS_ATTR_CATEGORY			(c, "skewness", 0, "Descriptor~");
	CLASS_ATTR_STYLE			(c, "skewness", 0, "onoff");
	CLASS_ATTR_ORDER			(c, "skewness", 0, "1");
	CLASS_ATTR_LABEL			(c, "skewness", 0, "Skewness");
	CLASS_ATTR_DEFAULT			(c, "skewness", 0, "1");
	CLASS_ATTR_SAVE				(c, "skewness", 1);

	CLASS_ATTR_LONG				(c, "kurtosis", 0, t_descriptor, f_analyseMode[1]);
	CLASS_ATTR_CATEGORY			(c, "kurtosis", 0, "Descriptor~");
	CLASS_ATTR_STYLE			(c, "kurtosis", 0, "onoff");
	CLASS_ATTR_ORDER			(c, "kurtosis", 0, "1");
	CLASS_ATTR_LABEL			(c, "kurtosis", 0, "Kurtosis");
	CLASS_ATTR_DEFAULT			(c, "kurtosis", 0, "1");
	CLASS_ATTR_SAVE				(c, "kurtosis", 1);

	CLASS_ATTR_LONG				(c, "amplitude", 0, t_descriptor, f_analyseMode);
	CLASS_ATTR_CATEGORY			(c, "amplitude", 0, "Descriptor~");
	CLASS_ATTR_STYLE			(c, "amplitude", 0, "onoff");
	CLASS_ATTR_ORDER			(c, "amplitude", 0, "1");
	CLASS_ATTR_LABEL			(c, "amplitude", 0, "Amplitude");
	CLASS_ATTR_DEFAULT			(c, "amplitude", 0, "1");
	CLASS_ATTR_SAVE				(c, "amplitude", 1);

	/* Behavior */
	CLASS_ATTR_SYM				(c, "set", 0, t_descriptor, f_buf.f_name);
	CLASS_ATTR_CATEGORY			(c, "set", 0, "Behavior");
	CLASS_ATTR_LABEL			(c, "set", 0, "buffer~ Object Name");
	CLASS_ATTR_ORDER			(c, "set", 0, "1");
	CLASS_ATTR_ACCESSORS		(c, "set", NULL, buffer_set);
	CLASS_ATTR_DEFAULT			(c, "set", 0, "");
	CLASS_ATTR_SAVE				(c, "set", 1);

	CLASS_ATTR_LONG				(c, "channel", 0, t_descriptor, f_buf.f_channel);
	CLASS_ATTR_CATEGORY			(c, "channel", 0, "Behavior");
	CLASS_ATTR_LABEL			(c, "channel", 0, "Channels");
	CLASS_ATTR_ORDER			(c, "channel", 0, "2");
	CLASS_ATTR_ACCESSORS		(c, "channel", NULL, channel_set);
	CLASS_ATTR_DEFAULT			(c, "channel", 0, "0");
	CLASS_ATTR_FILTER_CLIP		(c, "channel", 1, 4);
	CLASS_ATTR_SAVE				(c, "channel", 1);


	/* Tools */
	CLASS_ATTR_LONG				(c, "timeline", 0, t_descriptor, f_contextMode);
	CLASS_ATTR_CATEGORY			(c, "timeline", 0, "Tools");
	CLASS_ATTR_STYLE			(c, "timeline", 0, "onoff");
	CLASS_ATTR_ORDER			(c, "timeline", 0, "1");
	CLASS_ATTR_LABEL			(c, "timeline", 0, "Show Time Line");
	CLASS_ATTR_DEFAULT			(c, "timeline", 0, "1");
	CLASS_ATTR_SAVE				(c, "timeline", 1);
	/*
	CLASS_ATTR_LONG_ARRAY		(c, "tlmode", 0, t_descriptor, f_mode[1], 1);
	CLASS_ATTR_CATEGORY			(c, "tlmode", 0, "Tools");
	CLASS_ATTR_ENUMINDEX		(c, "tlmode", 0, "Millisecond \" \"Samples \" \"Phase");
	CLASS_ATTR_ORDER			(c, "tlmode", 0, "2");
	CLASS_ATTR_LABEL			(c, "tlmode", 0, "Time Line Mode");
	CLASS_ATTR_DEFAULT			(c, "tlmode", 0, "0");
	CLASS_ATTR_SAVE				(c, "tlmode", 1);
	CLASS_ATTR_FILTER_CLIP		(c, "tlmode", 0, 2);
	*/
	CLASS_ATTR_LONG				(c, "text", 0, t_descriptor, f_contextMode[1]);
	CLASS_ATTR_CATEGORY			(c, "text", 0, "Tools");
	CLASS_ATTR_STYLE			(c, "text", 0, "onoff");
	CLASS_ATTR_ORDER			(c, "text", 0, "2");
	CLASS_ATTR_LABEL			(c, "text", 0, "Show Indicators Text");
	CLASS_ATTR_DEFAULT			(c, "text", 0, "1");
	CLASS_ATTR_SAVE				(c, "text", 1);

	CLASS_ATTR_LONG				(c, "ticks", 0, t_descriptor, f_contextMode[2]);
	CLASS_ATTR_CATEGORY			(c, "ticks", 0, "Tools");
	CLASS_ATTR_STYLE			(c, "ticks", 0, "onoff");
	CLASS_ATTR_ORDER			(c, "ticks", 0, "3");
	CLASS_ATTR_LABEL			(c, "ticks", 0, "Show Indicators Tick");
	CLASS_ATTR_DEFAULT			(c, "ticks", 0, "1");
	CLASS_ATTR_SAVE				(c, "ticks", 1);

	/* Color */
	CLASS_ATTR_INVISIBLE		(c, "color", 0);
	CLASS_ATTR_INVISIBLE		(c, "textcolor", 0);

	CLASS_ATTR_RGBA				(c, "txcolor", 0, t_descriptor, f_colorText);
	CLASS_ATTR_CATEGORY			(c, "txcolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "txcolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "txcolor", 0, "Text Color");
	CLASS_ATTR_ORDER			(c, "txcolor", 0, "4");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "txcolor", 0, "0. 0. 0. 1.");

	CLASS_ATTR_RGBA				(c, "bgcolor", 0, t_descriptor, f_colorBackground);
	CLASS_ATTR_CATEGORY			(c, "bgcolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "bgcolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "bgcolor", 0, "Background Color");
	CLASS_ATTR_ORDER			(c, "bgcolor", 0, "1");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "bgcolor", 0, "0.86 0.86 0.86 1.");

	CLASS_ATTR_RGBA				(c, "tlcolor", 0, t_descriptor, f_colorsTimeBg);
	CLASS_ATTR_CATEGORY			(c, "tlcolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "tlcolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "tlcolor", 0, "Time Line Color");
	CLASS_ATTR_ORDER			(c, "tlcolor", 0, "5");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "tlcolor", 0, "0.95 0.95 0.95 1.");
	
	CLASS_ATTR_RGBA				(c, "bdcolor", 0, t_descriptor, f_colorsTimeBd);
	CLASS_ATTR_CATEGORY			(c, "bdcolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "bdcolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "bdcolor", 0, "Border Color");
	CLASS_ATTR_ORDER			(c, "bdcolor", 0, "2");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "bdcolor", 0, "0. 0. 0. 1.");
	/*
	CLASS_ATTR_RGBA				(c, "wfcolor", 0, t_descriptor, f_colorWaveform);
	CLASS_ATTR_CATEGORY			(c, "wfcolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "wfcolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "wfcolor", 0, "Waveform Color");
	CLASS_ATTR_ORDER			(c, "wfcolor", 0, "2");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "wfcolor", 0, "0. 0. 0. 1.");
	
	CLASS_ATTR_DOUBLE_ARRAY		(c, "gdcolor", 0, t_descriptor, f_gdColor, 4);
	CLASS_ATTR_CATEGORY			(c, "gdcolor", 0, "Color");
	CLASS_ATTR_STYLE			(c, "gdcolor", 0, "rgba");
	CLASS_ATTR_LABEL			(c, "gdcolor", 0, "Grid Color");
	CLASS_ATTR_ORDER			(c, "gdcolor", 0, "3");
	CLASS_ATTR_DEFAULT			(c, "gdcolor", 0, "0. 0. 0. 0.5");
	CLASS_ATTR_SAVE				(c, "gdcolor", 1);
	*/
	class_register(CLASS_BOX, c);
	descriptor_class = c;

	post("pg.descriptor~ by Pierre Guillot",0);
	post("Universite Paris 8, France",0);
	
	return 0;
}

void *descriptor_new(t_symbol *s, int argc, t_atom *argv)
{
	t_descriptor *x =  NULL; 

	t_dictionary *d;
	long flags;
	
	if (!(d=object_dictionaryarg(argc,argv)))
		return NULL;

	x = (t_descriptor *)object_alloc((t_class *)descriptor_class);
	flags = 0 
			| JBOX_DRAWFIRSTIN 
			| JBOX_DRAWINLAST
			| JBOX_TRANSPARENT	
			| JBOX_GROWBOTH
			;
	jbox_new(&x->j_box, flags, argc, argv); 

	x->f_changes = 0;
	x->f_buf.f_arraySize = 0;
	x->f_buf.f_windowSize = 0;
	x->f_buf.f_channel = 0;
	x->f_buf.f_nChannels = 1;
	x->f_buf.f_nFrames = 0;
	x->f_buf.f_nSamples = 0;
	x->f_buf.f_overlapping = 0;
	x->f_buf.f_samplingRate = 44100;
	x->f_buf.f_buffer = NULL;

	x->f_mouseX1 = 0.;
	x->f_mouseX2 = 0.;
	x->f_mouseSelect = false;
	x->f_mouseDown = false;
	x->f_middleY = 150.;
	x->f_alpha = 1.;
	x->f_vZoom = 1.;
	x->f_hZoom = 1.;
	x->f_vOffset = 0.;
	x->f_hOffset = 0.;
	x->j_box.b_firstin = (t_object*) x;
	x->j_out4 = listout((t_object *)x);
	x->j_out3 = listout((t_object *)x);
	x->j_out2 = listout((t_object *)x);
	x->j_out1 = listout((t_object *)x);

	
	attr_dictionary_process(x, d);
	jbox_ready(&x->j_box);
	
	return (x);
}			

void descriptor_free(t_descriptor *x)
{
	jbox_free(&x->j_box);
	buffer_free(&x->f_buf);
	window_free(&x->f_window);
}

void descriptor_assist(t_descriptor *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) 
	{
		switch (a) 
		{	
			case 0:
				sprintf(s,"(Anything) Input");
				break;
		}
	}
	else 
	{
		switch (a) 
		{	
			case 0:
				sprintf(s,"(Anything) Output");
				break;
			case 1:
				sprintf(s,"(Anything) Output");
				break;
			case 2:
				sprintf(s,"(Anything) Output");
				break;
			case 3:
				sprintf(s,"(Anything) Output");
				break;
		}
	}
}


t_max_err descriptor_notify(t_descriptor *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
	t_symbol *name;
	long number;
	if (msg == gensym("attr_modified"))
	{
		name = (t_symbol *)object_method((t_object *)data, gensym("getname"));
		
		if(name == gensym("bgcolor"))
		{
			jbox_invalidate_layer((t_object *)x, NULL, gensym("background_layer"));
		}
		else if(name == gensym("tlcolor") || name == gensym("bdcolor"))
		{
			jbox_invalidate_layer((t_object *)x, NULL, gensym("time_line_layer"));
			jbox_invalidate_layer((t_object *)x, NULL, gensym("indicator_tick_layer"));
		}
		else if(name == gensym("timeline"))
		{
			jbox_invalidate_layer((t_object *)x, NULL, gensym("indicator_text_layer"));
			jbox_invalidate_layer((t_object *)x, NULL, gensym("indicator_tick_layer"));
			jbox_invalidate_layer((t_object *)x, NULL, gensym("time_line_layer"));
		}
		else if(name == gensym("ticks"))
		{
			jbox_invalidate_layer((t_object *)x, NULL, gensym("indicator_tick_layer"));
		}
		else if(name == gensym("text") || name == gensym("txcolor"))
		{
			jbox_invalidate_layer((t_object *)x, NULL, gensym("indicator_text_layer"));
		}
		
		else if(name == gensym("amplitude") || name == gensym("kurtosis") || name == gensym("skewness") || name == gensym("sonogram"))
		{
			jbox_invalidate_layer((t_object *)x, NULL, gensym("amplitude_layer"));
			jbox_invalidate_layer((t_object *)x, NULL, gensym("kurtosis_layer"));
			jbox_invalidate_layer((t_object *)x, NULL, gensym("skewness_layer"));
			jbox_invalidate_layer((t_object *)x, NULL, gensym("sonogram_layer"));
			jbox_invalidate_layer((t_object *)x, NULL, gensym("spread_layer"));
			jbox_invalidate_layer((t_object *)x, NULL, gensym("centroid_layer"));
		}
		else if(name == gensym("spread") || name == gensym("centroid"))
		{
			jbox_invalidate_layer((t_object *)x, NULL, gensym("spread_layer"));
			jbox_invalidate_layer((t_object *)x, NULL, gensym("centroid_layer"));
		}
		jbox_redraw((t_jbox *)x);
	}
	else if(msg == gensym("globalsymbol_binding"))
	{
		x->f_buf.f_buffer = (t_buffer*)x->f_buf.f_name->s_thing;
	}
	else if (msg == gensym("globalsymbol_unbinding"))
	{
		x->f_buf.f_buffer = NULL;
	}
	else if (msg == gensym("buffer_modified"))
	{
		x->f_changes = 1;
		buffer_setup(x, x->f_buf.f_windowSize,  x->f_buf.f_overlapping);	
	}

	return jbox_notify((t_jbox *)x, s, msg, sender, data);
}

void descriptor_paint(t_descriptor *x, t_object *view)
{
	int i;
	t_rect rect;
	t_jgraphics *g;
	
	g = (t_jgraphics*)patcherview_get_jgraphics(view); 
	jbox_get_rect_for_view((t_object *)x, view, &rect);
	x->f_middleY = rect.height / 2.;
	x->f_offset = 0.;
	x->f_ratio = 0;
	for(i = 0; i < 3; i++)
		if(x->f_analyseMode[i] == 1) x->f_ratio++;
	if(x->f_analyseMode[3] == 1 || x->f_analyseMode[4] == 1 || x->f_analyseMode[5] == 1)
		x->f_ratio++;
	if(x->f_ratio == 0)  x->f_ratio = 1;
	
	rect.x = 0.;
	rect.y = 0.;
	rect.width	*= x->f_hZoom;
	rect.height *= x->f_vZoom;
	rect.x = x->f_hOffset;
	rect.y = x->f_vOffset;

	draw_timeline(x, view, &rect);

	draw_background(x, view, &rect);
	draw_amplitude(x, view, &rect);
	draw_kurtosis(x, view, &rect);
	draw_skewness(x, view, &rect);
	draw_spectrogram(x, view, &rect);
	draw_spread(x, view, &rect);
	draw_centroid(x, view, &rect);
	
	/*
	if(x->f_mode[1] == 1)
		draw_indicator_text(x, view, &rect);
	if(x->f_mode[2] == 1)
		draw_indicator_tick(x, view, &rect);
	*/
	jbox_get_rect_for_view((t_object *)x, view, &rect);
	draw_bar(x, view, &rect);
	
}
