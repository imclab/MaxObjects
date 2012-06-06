#include "pg.descriptor.h"

void descriptor_compute(t_buf *x, t_window *w)
{
	int				i, j, k, l, m, hopeSize;
	double			value, sumAmp, frequecyBand, ratio;
	double			*real;
	fftw_complex	*complex;
	fftw_plan		plan;	

	if(x->f_buffer != NULL)
	{
		real		= (double *)fftw_malloc(x->f_windowSize * sizeof(double));
		complex		= (fftw_complex *)fftw_malloc(x->f_windowSize * sizeof(fftw_complex));
		plan		= fftw_plan_dft_r2c_1d(x->f_windowSize, real, complex, FFTW_ESTIMATE);
		if(real && complex && plan)
		{
			ATOMIC_INCREMENT(&x->f_buffer->b_inuse);
			if (!x->f_buffer->b_valid) 
			{
				ATOMIC_DECREMENT(&x->f_buffer->b_inuse);
			}
			else
			{
				hopeSize = (x->f_windowSize / x->f_overlapping) * (x->f_overlapping - 1);
				frequecyBand = (double)x->f_buffer->b_sr / (double)x->f_windowSize;
				window_setup(w, x->f_windowSize, w->f_mode);
				for(j = 0; j < x->f_nChannels; j++)
				{
					for(i = 0, k = 0, m = 0; m < x->f_nFrames; i++)
					{
						if(i < x->f_nSamples)
						{
							real[k] = x->f_buffer->b_samples[i * x->f_buffer->b_nchans + j] * w->f_envelope[k];
						}
						else
						{
							real[k] = 0.;
						}
						k++;
						if(k == x->f_windowSize)
						{
							fftw_execute(plan);
							x->f_centroid[j][m] = 0.;
							x->f_spread[j][m] = 0.;
							x->f_skewness[j][m] = 0.;
							x->f_kurtosis[j][m] = 0.;
							x->f_minAmp[j][m] = 1.;
							x->f_maxAmp[j][m] = -91.;
							x->f_aveAmp[j][m] = 0.;
							sumAmp = 0.;
							for(l = 0; l < x->f_arraySize; l++)
							{
								value = complex[l][0] * complex[l][0] + complex[l][1] * complex[l][1];

								sumAmp += value;
								x->f_centroid[j][m] += value * (double)l * frequecyBand;

								value = sqrt(value) * x->f_rapportSize;
								value = 20.f * (log10(value));
								if (value < -90.f) value = -90.f;
						
								x->f_sonogram[j][m][l] = value;
								if(value > x->f_maxAmp[j][m]) x->f_maxAmp[j][m] = value;
								if(value < x->f_minAmp[j][m]) x->f_minAmp[j][m] = value;
								x->f_aveAmp[j][m] += value;
							}
							x->f_centroid[j][m] /= sumAmp;
							x->f_aveAmp[j][m] /= x->f_arraySize;

							for(l = 0; l < x->f_arraySize; l++)
							{
								value = complex[l][0] * complex[l][0] + complex[l][1] * complex[l][1];
								ratio = x->f_centroid[j][m] - (double)l * frequecyBand;
							
								x->f_spread[j][m]	+= value * ratio * ratio;
								x->f_skewness[j][m] += value * ratio * ratio * ratio;
								x->f_kurtosis[j][m] += value * ratio * ratio * ratio * ratio;
							}
							x->f_spread[j][m]	/= sumAmp;
							x->f_skewness[j][m] /= sumAmp;
							x->f_kurtosis[j][m] /= sumAmp;
						
							x->f_skewness[j][m] /= x->f_spread[j][m] * sqrt(x->f_spread[j][m]);
							x->f_kurtosis[j][m] /= x->f_spread[j][m] * x->f_spread[j][m];
							x->f_spread[j][m] = sqrt(x->f_spread[j][m]);

							k = 0;
							m++;
							i -= hopeSize;
						}
					}
				}
				ATOMIC_DECREMENT(&x->f_buffer->b_inuse);
			}
			if(plan)
				fftw_destroy_plan(plan);
			if(real)
				fftw_free(real);
			if(complex)
				fftw_free(complex);
		}
	}
}
