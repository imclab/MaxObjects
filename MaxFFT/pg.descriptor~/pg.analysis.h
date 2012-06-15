
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