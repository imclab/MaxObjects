#include "ext.h"
#include "ext_obex.h"

typedef struct _sonogram
{
	double		**f_sonogramRms[4];
	double		**f_sonogramPow[4];
	double		**f_sonogramEne[4];
}t_sonogram;

typedef struct _energy
{
	double		*f_minRms[4];
	double		*f_aveRms[4];
	double		*f_maxRms[4];
	double		*f_sumRms[4];

	double		*f_minPow[4];
	double		*f_avePow[4];
	double		*f_maxPow[4];
	double		*f_sumPow[4];

	double		*f_minEne[4];
	double		*f_aveEne[4];
	double		*f_maxEne[4];
	double		*f_sumEne[4];
}t_energy;

typedef struct _moment
{
	double		*f_centroidRms[4];
	double		*f_deviatioRms[4];
	double		*f_skewnessRms[4];
	double		*f_kurtosisRms[4];

	double		*f_centroidPow[4];
	double		*f_deviatioPow[4];
	double		*f_skewnessPow[4];
	double		*f_kurtosisPow[4];
}t_moment;

typedef struct _gradient
{
	double		*f_slopeRms[4];
	double		*f_decreRms[4];

	double		*f_slopePow[4];
	double		*f_decrePow[4];
}t_gradient;