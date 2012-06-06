
/**********************************************************************/
/*                       FONCTION DELAY						          */
/**********************************************************************/
#include "pg.delay.h"

void delay_init(t_delay *c, int msec)
{
	int nsamps;

    nsamps = msec * sys_getsr() * (t_float)(0.001f);
    if (nsamps < 1) nsamps = 1;

    nsamps += ((- nsamps) & (SAMPBLK - 1));
    nsamps += DEFDELVS;
	
    c->f_n = nsamps;
    c->f_vector = (t_sample *)sysmem_newptrclear((nsamps + XTRASAMPS) * sizeof(t_sample));
    c->f_phase = XTRASAMPS;
	
	c->f_sr = sys_getsr();
	c->f_sb = sys_getblksize();
	c->f_sizemax = msec;
	
	c->f_delaySig	 = (float *)sysmem_newptrclear(sys_getmaxblksize() * sizeof(float));
	c->f_envelopeSig = (float *)sysmem_newptrclear(sys_getmaxblksize() * sizeof(float));
	
	c->f_modAmp			= 0.f;
	c->f_delTime		= 1000.f;
	c->f_grainLenghtDev = 1.f / c->f_sr;
	c->f_count = 0.f;
}

void delay_dspInit(t_delay *c, int sr, int sb)
{
	if(c->f_sr != sr || c->f_sb != sb)
	{
		c->f_sr = sr;
		c->f_sb = sb;
	}
}

void delay_free(t_delay *c)
{
    freebytes((t_sample *)c->f_vector,		(c->f_n + XTRASAMPS) * sizeof(t_sample));

	freebytes((float *)c->f_delaySig,		sys_getmaxblksize() * sizeof(float));
	freebytes((float *)c->f_envelopeSig,	sys_getmaxblksize() * sizeof(float));

}



