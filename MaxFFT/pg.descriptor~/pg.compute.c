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

							sumAmp = 0.;
							for(l = 0; l < x->f_arraySize; l++)
							{
								value = complex[l][0] * complex[l][0] + complex[l][1] * complex[l][1];

								sumAmp += value;
								x->f_centroid[j][m] += value * (double)l * frequecyBand;

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

void descriptor_sonogram(t_buf *x, double **complex, int channel, int frame)
{
	int i;
	double value;
	for(i = 0; i < x->f_arraySize; i++)
	{
		value = sqrt(complex[i][0] * complex[i][0] + complex[i][1] * complex[i][1]) * x->f_rapportSize;
		x->f_sono.f_sonogramRms[channel][frame][i] = value;
		x->f_sono.f_sonogramPow[channel][frame][i] = value * value;
		value =  20. * log10(value);
		if(value <  -90.) value = -90.;
		x->f_sono.f_sonogramEne[channel][frame][i] = value;
	}
}

void descriptor_energy(t_buf *x, double **complex, int channel, int frame)
{
	int i;
	double value;

	x->f_ener.f_minRms[channel][frame] = 300.;
	x->f_ener.f_aveRms[channel][frame] = 0.;
	x->f_ener.f_maxRms[channel][frame] = -300.;
	x->f_ener.f_sumRms[channel][frame] = 0.;

	x->f_ener.f_minPow[channel][frame] = 300.;
	x->f_ener.f_avePow[channel][frame] = 0.;
	x->f_ener.f_maxPow[channel][frame] = -300.;
	x->f_ener.f_sumPow[channel][frame] = 0.;

	for(i = 0; i < x->f_arraySize; i++)
	{
		value = x->f_sono.f_sonogramRms[channel][frame][i];
		x->f_ener.f_sumRms[channel][frame] += value;
		if(value < x->f_ener.f_minRms[channel][frame]) x->f_ener.f_minRms[channel][frame] = value;
		if(value > x->f_ener.f_maxRms[channel][frame]) x->f_ener.f_maxRms[channel][frame] = value;

		value = x->f_sono.f_sonogramPow[channel][frame][i];
		x->f_ener.f_sumPow[channel][frame] += x->f_sono.f_sonogramPow[channel][frame][i];
		if(value < x->f_ener.f_minPow[channel][frame]) x->f_ener.f_minPow[channel][frame] = value;
		if(value > x->f_ener.f_maxPow[channel][frame]) x->f_ener.f_maxPow[channel][frame] = value;
	}
	x->f_ener.f_aveRms[channel][frame] = x->f_ener.f_sumRms[channel][frame] / (double)x->f_arraySize;
	x->f_ener.f_avePow[channel][frame] = x->f_ener.f_sumPow[channel][frame] / (double)x->f_arraySize;

	x->f_ener.f_minEne[channel][frame] = 20. * log10(x->f_ener.f_minRms[channel][frame]);
	x->f_ener.f_aveEne[channel][frame] = 20. * log10(x->f_ener.f_aveRms[channel][frame]);
	x->f_ener.f_maxEne[channel][frame] = 20. * log10(x->f_ener.f_maxRms[channel][frame]);
	x->f_ener.f_sumEne[channel][frame] = 20. * log10(x->f_ener.f_sumRms[channel][frame]);
		
}

void descriptor_moment(t_buf *x, double **complex, int channel, int frame, double frequencyBand)
{
	int i;
	double frequency, value, ratio;

	x->f_mome.f_centroidRms[channel][frame] = 0.;
	x->f_mome.f_deviatioRms[channel][frame]	= 0.;
	x->f_mome.f_skewnessRms[channel][frame] = 0.;
	x->f_mome.f_kurtosisRms[channel][frame] = 0.;
						
	x->f_mome.f_centroidPow[channel][frame] = 0.;
	x->f_mome.f_deviatioPow[channel][frame]	= 0.;
	x->f_mome.f_skewnessPow[channel][frame] = 0.;
	x->f_mome.f_kurtosisPow[channel][frame] = 0.;

	for(i = 0; i < x->f_arraySize; i++)
	{
		frequency = (double)i * frequencyBand;

		value = x->f_sono.f_sonogramRms[channel][frame][i];
		x->f_mome.f_centroidRms[channel][frame]	+= value * frequency;

		value = x->f_sono.f_sonogramPow[channel][frame][i];
		x->f_mome.f_centroidPow[channel][frame]	+= value * frequency;
	}

	for(i = 0; i < x->f_arraySize; i++)
	{
		frequency = (double)i * frequencyBand;

		value = x->f_sono.f_sonogramRms[channel][frame][i];
		ratio = frequency - x->f_mome.f_centroidRms[channel][frame];
		x->f_mome.f_deviatioRms[channel][frame]	+= value * (ratio * ratio);
		x->f_mome.f_skewnessRms[channel][frame]	+= value * (ratio * ratio * ratio);
		x->f_mome.f_kurtosisRms[channel][frame]	+= value * (ratio * ratio * ratio * ratio);

		ratio = frequency - x->f_mome.f_centroidPow[channel][frame];
		value = x->f_sono.f_sonogramPow[channel][frame][i];
		x->f_mome.f_deviatioPow[channel][frame]	+= value * (ratio * ratio);
		x->f_mome.f_skewnessPow[channel][frame]	+= value * (ratio * ratio * ratio);
		x->f_mome.f_kurtosisPow[channel][frame]	+= value * (ratio * ratio * ratio * ratio);
	}
}

void descriptor_gradient(t_buf *x, double **complex, int channel, int frame, double frequencyBand, double sr)
{
	int i;
	double sumFreqSim, sumFreqCar;
	double sumAmp, sumFreqRms, sumFreqPow, value ;

	sumFreqRms = sumFreqPow = sumFreqSim = sumFreqCar = 0.;
	for(i = 0; i < x->f_arraySize; i++)
	{
		sumFreqSim += (double)i * frequencyBand;
		sumFreqCar += ((double)i * frequencyBand) * ((double)i * frequencyBand);
	}
	sumFreqCar *= (double)x->f_arraySize;
	sumFreqCar -= (sumFreqSim * sumFreqSim);

	for(i = 0; i < x->f_arraySize; i++)
	{
		value = x->f_sono.f_sonogramRms[channel][frame][i];
		sumFreqRms += value * (double)i * frequencyBand;

		value = x->f_sono.f_sonogramPow[channel][frame][i];
		sumFreqPow  += value * (double)i * frequencyBand;
	}
	sumAmp = x->f_ener.f_sumRms[channel][frame];
	x->f_grad.f_slopeRms[channel][frame] = sumFreqRms * (t_double)x->f_arraySize;
	x->f_grad.f_slopeRms[channel][frame]  -= (sumFreqSim * sumAmp);
	x->f_grad.f_slopeRms[channel][frame]  /= sumFreqCar;
	x->f_grad.f_slopeRms[channel][frame] /= sumAmp;
	x->f_grad.f_slopeRms[channel][frame] *= sr / 4.;

	sumAmp = x->f_ener.f_sumPow[channel][frame];
	x->f_grad.f_slopePow[channel][frame] = sumFreqPow * (t_double)x->f_arraySize;
	x->f_grad.f_slopePow[channel][frame]  -= (sumFreqSim * sumAmp);
	x->f_grad.f_slopePow[channel][frame]  /= sumFreqCar;
	x->f_grad.f_slopePow[channel][frame] /= sumAmp;
	x->f_grad.f_slopePow[channel][frame] *= sr / 4.;
}