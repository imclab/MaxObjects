
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

void descriptor_mousedown(t_descriptor *x, t_object *patcherview, t_pt pt, long modifiers)
{
	if(pt.y < x->f_middleY)
	{
		x->f_alpha = 1.;
		x->f_mouseX1 = pt.x;
		x->f_mouseX2 = 1.;
		descriptor_post(x, pt.x, patcherview);
		x->f_mouseSelect = false;
	}
	else
	{
		x->f_alpha = 0.5;
		x->f_mouseOrigin = x->f_mouseX1 = pt.x;
		x->f_mouseX2 = 1.;
		descriptor_post(x, pt.x, patcherview);
		x->f_mouseSelect = true;
	}
	
	jbox_invalidate_layer((t_object *)x, NULL, gensym("bar_layer"));
	jbox_redraw((t_jbox *)x);
	x->f_mouseDown = true;
}

void descriptor_mousedrag(t_descriptor *x, t_object *patcherview, t_pt pt, long modifiers)
{
	if(x->f_mouseDown == true)
	{
		x->f_alpha = 1.;
		if(x->f_mouseSelect == false)
		{
			x->f_mouseX1 = pt.x;
			x->f_mouseX2 = 1.;
			descriptor_post(x, pt.x, patcherview);
			jbox_invalidate_layer((t_object *)x, NULL, gensym("bar_layer"));
			jbox_redraw((t_jbox *)x);
		}
		else if(x->f_mouseSelect == true)
		{
			x->f_alpha = 0.5;
			if(pt.x > x->f_mouseOrigin)
			{
				x->f_mouseX1 = x->f_mouseOrigin;
				x->f_mouseX2 = pt.x - x->f_mouseOrigin;
				descriptor_postAve(x, x->f_mouseOrigin, pt.x, patcherview);
			}
			else
			{
				x->f_mouseX1 = pt.x;
				x->f_mouseX2 = x->f_mouseOrigin -  pt.x;
				descriptor_postAve(x, x->f_mouseX1, x->f_mouseOrigin, patcherview);
			}
			jbox_invalidate_layer((t_object *)x, NULL, gensym("bar_layer"));
			jbox_redraw((t_jbox *)x);
		}
	}
}

void descriptor_mouseup(t_descriptor *x, t_object *patcherview, t_pt pt, long modifiers)
{
	x->f_mouseDown = false;
}

void descriptor_mousewheel(t_descriptor *x, t_object *patcherview, t_pt pt, long modifiers, double x_inc, double y_inc)
{
	long control, shift, altGr;
	t_rect rect;
	control = eControlKey;
	shift = eShiftKey;
	altGr = 13;
	jbox_get_rect_for_view((t_object *)x, patcherview, &rect);

#ifdef WIN_VERSION
	control = 5;
	shift = 2;
#endif
	if(modifiers == control)
	{
		x->f_vZoom += y_inc;
		if(x->f_vZoom < 1.) x->f_vZoom = 1.;
		if(x->f_vOffset > 0.) x->f_vOffset = 0.;
		
		else if(x->f_vOffset < (rect.height * x->f_vZoom - rect.height) * -1.)
			x->f_vOffset = (rect.height * x->f_vZoom - rect.height) * -1.;
		
	}
	else if(modifiers == shift)
	{
		x->f_hZoom += y_inc;
		if(x->f_hZoom < 1.) x->f_hZoom = 1.;
		if(x->f_hOffset > 0.) x->f_hOffset = 0.;
		else if(x->f_hOffset < (rect.width * x->f_hZoom - rect.width) * -1.)
			x->f_hOffset = (rect.width * x->f_hZoom - rect.width) * -1.;
	}
	else if(modifiers == altGr)
	{
		x->f_vOffset += y_inc * 10. * x->f_vZoom;
		if(x->f_vOffset > 0.) x->f_vOffset = 0.;
		
		else if(x->f_vOffset < (rect.height * x->f_vZoom - rect.height) * -1.)
			x->f_vOffset = (rect.height * x->f_vZoom - rect.height) * -1.;
			
	}
	else
	{
		x->f_hOffset += y_inc * 10. * x->f_hZoom;
		if(x->f_hOffset > 0.) x->f_hOffset = 0.;
		else if(x->f_hOffset < (rect.width * x->f_hZoom - rect.width) * -1.)
			x->f_hOffset = (rect.width * x->f_hZoom - rect.width) * -1.;
	}

	jbox_invalidate_layer((t_object *)x, NULL, gensym("amplitude_layer"));
	jbox_invalidate_layer((t_object *)x, NULL, gensym("kurtosis_layer"));
	jbox_invalidate_layer((t_object *)x, NULL, gensym("skewness_layer"));
	jbox_invalidate_layer((t_object *)x, NULL, gensym("sonogram_layer"));
	jbox_invalidate_layer((t_object *)x, NULL, gensym("spread_layer"));
	jbox_invalidate_layer((t_object *)x, NULL, gensym("centroid_layer"));
	jbox_redraw((t_jbox *)x);
}

void descriptor_post(t_descriptor *x, double posX,  t_object *view)
{
	int i, index, channel;
	double value;
	t_atom time[1];
	t_rect rect;
	t_atom *spectrum;
	t_atom analysis[5];
	t_atom amplitude[4];
	jbox_get_rect_for_view((t_object *)x, view, &rect);

	if(x->f_buf.f_buffer != NULL)
	{
		channel = x->f_buf.f_channel - 1;
		spectrum = (t_atom *)getbytes(x->f_buf.f_arraySize * sizeof(t_atom));
		index = (posX / rect.width) * x->f_buf.f_nFrames;
		if(index < 0) index = 0;
		else if(index >= x->f_buf.f_nFrames) index = x->f_buf.f_nFrames - 1;
		value = (posX / rect.width) * ((double)x->f_buf.f_nSamples / (double)x->f_buf.f_samplingRate) * 1000.;
		if(value < 0.)
			value = 0.;
		else if(value > ((double)x->f_buf.f_nSamples / (double)x->f_buf.f_samplingRate) * 1000.)
			value = ((double)x->f_buf.f_nSamples / (double)x->f_buf.f_samplingRate) * 1000.;
		atom_setfloat(time, value);
		for(i = 0; i < x->f_buf.f_arraySize; i++)
		{
			atom_setfloat(spectrum + i, (float)x->f_buf.f_sono.f_sonogramEne[channel][index][i]);
		}

		atom_setfloat(analysis, x->f_buf.f_mome.f_centroidRms[channel][index]);
		atom_setfloat(analysis + 1, x->f_buf.f_mome.f_deviatioRms[channel][index]);
		atom_setfloat(analysis + 2, x->f_buf.f_mome.f_skewnessRms[channel][index]);
		atom_setfloat(analysis + 3, x->f_buf.f_mome.f_kurtosisRms[channel][index]);
		atom_setfloat(analysis + 4, x->f_buf.f_mome.f_rollofffRms[channel][index]);

		atom_setfloat(amplitude, x->f_buf.f_ener.f_minEne[channel][index]);
		atom_setfloat(amplitude + 1, x->f_buf.f_ener.f_aveEne[channel][index]);
		atom_setfloat(amplitude + 2, x->f_buf.f_ener.f_maxEne[channel][index]);
		atom_setfloat(amplitude + 2, x->f_buf.f_ener.f_sumEne[channel][index]);

		outlet_list(x->j_out1, 0, 1, time);
		outlet_list(x->j_out2, 0, x->f_buf.f_arraySize, spectrum);
		outlet_list(x->j_out3, 0, 4, analysis);
		outlet_list(x->j_out4, 0, 3, amplitude);
		freebytes(spectrum, x->f_buf.f_arraySize * sizeof(t_atom));
	}
	
}

void descriptor_postAve(t_descriptor *x, double posX1, double posX2,  t_object *view)
{ /*
	int i, j, index1, index2, channel;
	double value, minAmp, aveAmp, maxAmp, centroid ,spread, skewness, kurtosis, ratio;
	t_atom	time[2];
	t_rect rect;
	t_atom *spectrum;
	t_atom analysis[4];
	t_atom amplitude[3];
	double *spectrumAve;
	jbox_get_rect_for_view((t_object *)x, view, &rect);

	if(x->f_buf.f_buffer != NULL)
	{
		spectrumAve = (double *)getbytes(x->f_buf.f_arraySize * sizeof(double));
		if(spectrumAve)
		{
			channel = x->f_buf.f_channel - 1;
			spectrum = (t_atom *)getbytes(x->f_buf.f_arraySize * sizeof(t_atom));

			index1 = (posX1 / rect.width) * x->f_buf.f_nFrames;
			if(index1 < 0) index1 = 0;
			else if(index1 >= x->f_buf.f_nFrames) index1 = x->f_buf.f_nFrames - 1;

			index2= (posX2 / rect.width) * x->f_buf.f_nFrames;
			if(index2 < 0) index2 = 0;
			else if(index2 >= x->f_buf.f_nFrames) index2 = x->f_buf.f_nFrames - 1;

			ratio = (double)(index2- index1);
			if(index2 == index1)
			{
				index2++;
				ratio = 1.;
			}
			value = (posX1 / rect.width) * ((double)x->f_buf.f_nSamples / (double)x->f_buf.f_samplingRate) * 1000.;
			if(value < 0.)
				value = 0.;
			atom_setfloat(time, value);

			value = (posX2 / rect.width) * ((double)x->f_buf.f_nSamples / (double)x->f_buf.f_samplingRate) * 1000.;
			if(value > ((double)x->f_buf.f_nSamples / (double)x->f_buf.f_samplingRate) * 1000.)
				value = ((double)x->f_buf.f_nSamples / (double)x->f_buf.f_samplingRate) * 1000.;
			atom_setfloat(time+1, value);
			
			for(j = 0; j < x->f_buf.f_arraySize; j++)
			{
				spectrumAve[j] = 0.;
				for(i = index1; i < index2; i++)
				{
					spectrumAve[j] += x->f_buf.f_sonogram[channel][i][j];
				}
				spectrumAve[j] /= ratio;
			}
			for(i = 0; i < x->f_buf.f_arraySize; i++)
			{
				atom_setfloat(spectrum + i, spectrumAve[i]);
			}
			minAmp = aveAmp =  maxAmp = centroid = spread = skewness = kurtosis =0.;
			for(i = index1; i < index2; i++)
			{
				minAmp += x->f_buf.f_minAmp[channel][i];
				maxAmp += x->f_buf.f_maxAmp[channel][i];
				aveAmp += x->f_buf.f_aveAmp[channel][i];
				centroid += x->f_buf.f_centroid[channel][i];
				spread += x->f_buf.f_spread[channel][i];
				skewness += x->f_buf.f_skewness[channel][i];
				kurtosis += x->f_buf.f_kurtosis[channel][i];
			}
			minAmp /= ratio;
			maxAmp /= ratio;
			aveAmp /= ratio;
			centroid /= ratio;
			spread /= ratio;
			skewness /= ratio;
			kurtosis /= ratio;

			atom_setfloat(analysis, centroid);
			atom_setfloat(analysis + 1, spread);
			atom_setfloat(analysis + 2, skewness);
			atom_setfloat(analysis + 3, kurtosis);

			atom_setfloat(amplitude, minAmp);
			atom_setfloat(amplitude + 1, aveAmp);
			atom_setfloat(amplitude + 2, maxAmp);

			outlet_list(x->j_out1, 0, 2, time);
			outlet_list(x->j_out2, 0, x->f_buf.f_arraySize, spectrum);
			outlet_list(x->j_out3, 0, 4, analysis);
			outlet_list(x->j_out4, 0, 3, amplitude);
			freebytes(spectrum, x->f_buf.f_arraySize * sizeof(t_atom));
			freebytes(spectrumAve, x->f_buf.f_arraySize * sizeof(double));
		}
	}
	*/
}