
#ifndef DEF_descriptor
#define DEF_descriptor

#include "ext.h"
#include "ext_obex.h"
#include "jpatcher_api.h"
#include "jgraphics.h"
#include "jpatcher_syms.h"
#include "ext_dictionary.h"
#include "ext_globalsymbol.h"
#include "z_dsp.h"
#include "buffer.h"
#include "pg.window.h"
#include <fftw3.h>

typedef struct _buf
{
	t_symbol	*f_name;
	t_buffer	*f_buffer;
	long		f_channel;
	long		f_nChannels;
	
	double	f_rapportSize;
	long		f_windowSize;
	long		f_overlapping;
	long		f_arraySize;
	long		f_samplingRate;

	long		f_nSamples;
	long		f_nFrames;

	double		**f_sonogram[4];
	double		*f_centroid[4];
	double		*f_spread[4];
	double		*f_skewness[4];
	double		*f_kurtosis[4];
	double		*f_maxAmp[4];
	double		*f_minAmp[4];
	double		*f_aveAmp[4];
} t_buf;

typedef struct  _descriptor 
{
	
	t_jbox		j_box;
	void		*j_out1;
	void		*j_out2;
	void		*j_out3;
	void		*j_out4;

	t_buf		f_buf;
	t_window	f_window;

	t_jrgba		f_colorBackground;
	t_jrgba		f_colorText;
	t_jrgba		f_colorsTimeBg;
	t_jrgba		f_colorsTimeBd;
	t_jrgba		f_colorWaveform;
	long		f_contextMode[4];
	long		f_analyseMode[6];
	double		f_alpha;

	int			f_changes;
	char		f_mouseDown;
	double		f_mouseOrigin;
	double		f_mouseX1;
	double		f_mouseX2;
	
	char		f_mouseSelect;

	double		f_middleY;
	int			f_ratio;
	double		f_offset;
	double		f_vZoom;
	double		f_hZoom;
	double		f_vOffset;
	double		f_hOffset;
} t_descriptor;

void *descriptor_class;

void *descriptor_new(t_symbol *s, int argc, t_atom *argv);
void descriptor_free(t_descriptor *x);
void descriptor_assist(t_descriptor *x, void *b, long m, long a, char *s);

t_max_err descriptor_notify(t_descriptor *x, t_symbol *s, t_symbol *msg, void *sender, void *data);

/* FFT **********************************************/
t_max_err window_set(t_descriptor *x, t_object *attr, long argc, t_atom *argv);
t_max_err window_size_set(t_descriptor *x, t_object *attr, long argc, t_atom *argv);

/* Buffer *******************************************/
t_max_err buffer_set(t_descriptor *x, t_object *attr, long argc, t_atom *argv);
t_max_err channel_set(t_descriptor *x, t_object *attr, long argc, t_atom *argv);

void buffer_setup(t_descriptor *x, long windowSize, long overlapping);
void descriptor_compute(t_buf *x, t_window *w);
void buffer_free(t_buf *x);

/* Paint *********************************************/
void descriptor_paint(t_descriptor *x, t_object *view);

			/* Context */
void draw_background(t_descriptor *x, t_object *view, t_rect *rect);
void draw_timeline(t_descriptor *x, t_object *view, t_rect *rect);
void draw_indicator_text(t_descriptor *x,  t_object *view, t_rect *rect);
void draw_indicator_tick(t_descriptor *x,  t_object *view, t_rect *rect);

			/* Analyse */
void draw_spectrogram(t_descriptor *x, t_object *view, t_rect *rect);
void draw_spread(t_descriptor *x, t_object *view, t_rect *rect);
void draw_centroid(t_descriptor *x, t_object *view, t_rect *rect);
void draw_skewness(t_descriptor *x, t_object *view, t_rect *rect);
void draw_kurtosis(t_descriptor *x, t_object *view, t_rect *rect);
void draw_amplitude(t_descriptor *x, t_object *view, t_rect *rect);
			/* Interaction */
void draw_bar(t_descriptor *x, t_object *view, t_rect *rect);

/* Post **********************************************/
void descriptor_mousedown(t_descriptor *x, t_object *patcherview, t_pt pt, long modifiers);
void descriptor_mousedrag(t_descriptor *x, t_object *patcherview, t_pt pt, long modifiers);
void descriptor_mouseup(t_descriptor *x, t_object *patcherview, t_pt pt, long modifiers);
void descriptor_mousewheel(t_descriptor *x, t_object *patcherview, t_pt pt, long modifiers, double x_inc, double y_inc);

void descriptor_post(t_descriptor *x, double posX,  t_object *view);
void descriptor_postAve(t_descriptor *x, double posX1, double posX2,  t_object *view);

#endif