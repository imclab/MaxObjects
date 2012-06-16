#include "pg.descriptor.h"

#include "pg.descriptor.h"

void analysis_setup(t_buf *x)
{
	int i, j;
	for(i = 0; i < 4; i++)
	{
		/* Sonogram */
		x->f_sono.f_sonogramRms[i] = (double **)getbytes(x->f_nFrames * sizeof(double *));
		x->f_sono.f_sonogramPow[i] = (double **)getbytes(x->f_nFrames * sizeof(double *));
		x->f_sono.f_sonogramEne[i] = (double **)getbytes(x->f_nFrames * sizeof(double *));
		for(j = 0; j < x->f_nFrames; j++)
		{
			x->f_sono.f_sonogramRms[i][j] = (double *)getbytes(x->f_arraySize * sizeof(double));
			x->f_sono.f_sonogramPow[i][j] = (double *)getbytes(x->f_arraySize * sizeof(double));
			x->f_sono.f_sonogramEne[i][j] = (double *)getbytes(x->f_arraySize * sizeof(double));
		}
		/* Energy */
		x->f_ener.f_minRms[i] = (double *)getbytes(x->f_nFrames * sizeof(double));
		x->f_ener.f_aveRms[i] = (double *)getbytes(x->f_nFrames * sizeof(double));
		x->f_ener.f_maxRms[i] = (double *)getbytes(x->f_nFrames * sizeof(double));
		x->f_ener.f_sumRms[i] = (double *)getbytes(x->f_nFrames * sizeof(double));

		x->f_ener.f_minPow[i] = (double *)getbytes(x->f_nFrames * sizeof(double));
		x->f_ener.f_avePow[i] = (double *)getbytes(x->f_nFrames * sizeof(double));
		x->f_ener.f_maxPow[i] = (double *)getbytes(x->f_nFrames * sizeof(double));
		x->f_ener.f_sumPow[i] = (double *)getbytes(x->f_nFrames * sizeof(double));

		x->f_ener.f_minEne[i] = (double *)getbytes(x->f_nFrames * sizeof(double));
		x->f_ener.f_aveEne[i] = (double *)getbytes(x->f_nFrames * sizeof(double));
		x->f_ener.f_maxEne[i] = (double *)getbytes(x->f_nFrames * sizeof(double));
		x->f_ener.f_sumEne[i] = (double *)getbytes(x->f_nFrames * sizeof(double));

		/* Moment */
		x->f_mome.f_centroidRms[i] = (double *)getbytes(x->f_nFrames * sizeof(double));
		x->f_mome.f_centroidPow[i] = (double *)getbytes(x->f_nFrames * sizeof(double));

		x->f_mome.f_deviatioRms[i] = (double *)getbytes(x->f_nFrames * sizeof(double));
		x->f_mome.f_deviatioPow[i] = (double *)getbytes(x->f_nFrames * sizeof(double));

		x->f_mome.f_skewnessRms[i] = (double *)getbytes(x->f_nFrames * sizeof(double));
		x->f_mome.f_skewnessPow[i] = (double *)getbytes(x->f_nFrames * sizeof(double));

		x->f_mome.f_kurtosisRms[i] = (double *)getbytes(x->f_nFrames * sizeof(double));
		x->f_mome.f_kurtosisPow[i] = (double *)getbytes(x->f_nFrames * sizeof(double));

		x->f_mome.f_rollofffRms[i] = (double *)getbytes(x->f_nFrames * sizeof(double));
		x->f_mome.f_rollofffPow[i] = (double *)getbytes(x->f_nFrames * sizeof(double));

		/* Gradient */
		x->f_grad.f_slopeRms[i] = (double *)getbytes(x->f_nFrames * sizeof(double));
		x->f_grad.f_slopePow[i] = (double *)getbytes(x->f_nFrames * sizeof(double));

		x->f_grad.f_decreRms[i] = (double *)getbytes(x->f_nFrames * sizeof(double));
		x->f_grad.f_decrePow[i] = (double *)getbytes(x->f_nFrames * sizeof(double));
	}
}

void analysis_free(t_buf *x)
{
	int i, j;
	for(i = 0; i < 4; i++)
	{
		/* Sonogram */
		for(j = 0; j < x->f_nFrames; j++)
		{
			if(x->f_sono.f_sonogramRms[i])
				freebytes(x->f_sono.f_sonogramRms[i][j], x->f_arraySize * sizeof(double));
			if(x->f_sono.f_sonogramPow[i])
				freebytes(x->f_sono.f_sonogramPow[i][j], x->f_arraySize * sizeof(double));
			if(x->f_sono.f_sonogramEne[i])
				freebytes(x->f_sono.f_sonogramEne[i][j], x->f_arraySize * sizeof(double));
		}
		if(x->f_sono.f_sonogramRms)
			freebytes(x->f_sono.f_sonogramRms[i], x->f_nFrames * sizeof(double *));
		if(x->f_sono.f_sonogramPow)
			freebytes(x->f_sono.f_sonogramPow[i], x->f_nFrames * sizeof(double *));
		if(x->f_sono.f_sonogramEne)
			freebytes(x->f_sono.f_sonogramEne[i], x->f_nFrames * sizeof(double *));

		/* Energy */
		if(x->f_ener.f_minRms)
			freebytes(x->f_ener.f_minRms[i], x->f_nFrames * sizeof(double));
		if(x->f_ener.f_aveRms)
			freebytes(x->f_ener.f_aveRms[i], x->f_nFrames * sizeof(double));
		if(x->f_ener.f_maxRms)
			freebytes(x->f_ener.f_maxRms[i], x->f_nFrames * sizeof(double));
		if(x->f_ener.f_sumRms)
			freebytes(x->f_ener.f_sumRms[i], x->f_nFrames * sizeof(double));

		if(x->f_ener.f_minPow)
			freebytes(x->f_ener.f_minPow[i], x->f_nFrames * sizeof(double));
		if(x->f_ener.f_avePow)
			freebytes(x->f_ener.f_avePow[i], x->f_nFrames * sizeof(double));
		if(x->f_ener.f_maxPow)
			freebytes(x->f_ener.f_maxPow[i], x->f_nFrames * sizeof(double));
		if(x->f_ener.f_sumPow)
			freebytes(x->f_ener.f_sumPow[i], x->f_nFrames * sizeof(double));

		if(x->f_ener.f_minEne)
			freebytes(x->f_ener.f_minEne[i], x->f_nFrames * sizeof(double));
		if(x->f_ener.f_aveEne)
			freebytes(x->f_ener.f_aveEne[i], x->f_nFrames * sizeof(double));
		if(x->f_ener.f_maxEne)
			freebytes(x->f_ener.f_maxEne[i], x->f_nFrames * sizeof(double));
		if(x->f_ener.f_sumEne)
			freebytes(x->f_ener.f_sumEne[i], x->f_nFrames * sizeof(double));

		/* Moment */
		if(x->f_mome.f_centroidRms)
			freebytes(x->f_mome.f_centroidRms[i], x->f_nFrames * sizeof(double));
		if(x->f_mome.f_centroidPow)
			freebytes(x->f_mome.f_centroidPow[i], x->f_nFrames * sizeof(double));

		if(x->f_mome.f_deviatioRms)
			freebytes(x->f_mome.f_deviatioRms[i], x->f_nFrames * sizeof(double));
		if(x->f_mome.f_deviatioPow)
			freebytes(x->f_mome.f_deviatioPow[i], x->f_nFrames * sizeof(double));

		if(x->f_mome.f_skewnessRms)
			freebytes(x->f_mome.f_skewnessRms[i], x->f_nFrames * sizeof(double));
		if(x->f_mome.f_skewnessPow)
			freebytes(x->f_mome.f_skewnessPow[i], x->f_nFrames * sizeof(double));

		if(x->f_mome.f_kurtosisRms)
			freebytes(x->f_mome.f_kurtosisRms[i], x->f_nFrames * sizeof(double));
		if(x->f_mome.f_kurtosisPow)
			freebytes(x->f_mome.f_kurtosisPow[i], x->f_nFrames * sizeof(double));

		if(x->f_mome.f_rollofffRms)
			freebytes(x->f_mome.f_rollofffRms[i], x->f_nFrames * sizeof(double));
		if(x->f_mome.f_rollofffPow)
			freebytes(x->f_mome.f_rollofffPow[i], x->f_nFrames * sizeof(double));

		/* Gradient */
		if(x->f_grad.f_slopeRms)
			freebytes(x->f_grad.f_slopeRms[i], x->f_nFrames * sizeof(double));
		if(x->f_grad.f_slopePow)
			freebytes(x->f_grad.f_slopePow[i], x->f_nFrames * sizeof(double));

		if(x->f_grad.f_decreRms)
			freebytes(x->f_grad.f_decreRms[i], x->f_nFrames * sizeof(double));
		if(x->f_grad.f_decrePow)
			freebytes(x->f_grad.f_decrePow[i], x->f_nFrames * sizeof(double));
	}
}