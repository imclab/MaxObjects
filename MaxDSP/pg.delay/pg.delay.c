
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

#include "pg.delay.h"

void delay_setup(t_delay *c, double msec, double sr)
{
	c->f_sr = sr;
	c->f_lenghtMs = msec;
    c->f_lenght =  c->f_lenghtMs * (double)sys_getsr() * 0.001;
	c->f_lenght += 64;
	if (c->f_lenght < 1)  c->f_lenght = 1;
    c->f_vector = (double *)getbytes(( c->f_lenght + XTRASAMPS) * sizeof(double));
    c->f_phase = XTRASAMPS;

	c->f_alpha = 5. / 3.;
}

void delay_resize(t_delay *c, double sr)
{
	if(c->f_sr != sr)
	{
		freebytes((double *)c->f_vector, (c->f_lenght + XTRASAMPS) * sizeof(double));
		c->f_sr = sr;
		c->f_lenght =  c->f_lenghtMs * sr * 0.001;
		c->f_lenght += 64;
		if (c->f_lenght < 1)
			c->f_lenght = 1;
		c->f_vector = (double *)getbytes((c->f_lenght + XTRASAMPS) * sizeof(double));
		c->f_phase = XTRASAMPS;
	}
}

void delay_write(t_delay *c, double sample)
{

	c->f_vector[c->f_phase] = sample;
	c->f_phase++;
	if (c->f_phase >= c->f_lenght)
	{
		c->f_vector[0] = c->f_vector[c->f_lenght -4];
		c->f_vector[1] = c->f_vector[c->f_lenght -3];
		c->f_vector[2] = c->f_vector[c->f_lenght -2];
		c->f_vector[3] = c->f_vector[c->f_lenght -1];
		c->f_phase = 4;
	}
}

double delay_read_ms(t_delay *c, double delay)
{
	int delaySample;
	double one, two, thr, fou, oneMthr, ratio, delayMs, out;
	if(delay > c->f_lenghtMs)
		delay = c->f_lenghtMs;
	delayMs = (double)c->f_phase - (delay * c->f_sr * 0.001);
	if(delayMs < 4)delayMs = c->f_lenght + (delayMs - 4);

	delaySample = delayMs;
	ratio = delayMs - (double)delaySample;
	one = c->f_vector[delaySample-3];
	two = c->f_vector[delaySample-2];
	thr = c->f_vector[delaySample-1];
	fou = c->f_vector[delaySample];
	oneMthr = thr - two;
	out = two + ratio * (oneMthr - c->f_alpha * (1. - ratio) * ((fou - one - 3. * oneMthr) * ratio + (fou + 2. * one - 3. * two)));

	return out;
}

double delay_read_sample(t_delay *c, int delay)
{
	double out;
	if(delay > c->f_lenght)
		delay = c->f_lenght;
	delay = (double)c->f_phase - delay;
	if(delay < 4)delay = c->f_lenght + (delay - 4);

	out = c->f_vector[delay];
	
	return out;
}

void delay_free(t_delay *c)
{
    freebytes(c->f_vector, (c->f_lenght + XTRASAMPS) * sizeof(double));
}



