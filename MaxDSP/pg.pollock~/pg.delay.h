/***************************************************
DELAY
Par Pierre Guillot


delay.h

Contient la structure de l'objet et les #defines
****************************************************/
#ifndef DEF_DELAY
#define DEF_DELAY

#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"

#define DEFDELVS	64         
#define XTRASAMPS	0
#define SAMPBLK		4
#define NMAXDELAY   64

typedef int t_delayTime;
typedef float t_delayAmp;
typedef float t_delaySample;

typedef struct delay
{
    int			f_n;
    t_sample	*f_vector;
    int			f_phase;
	int			f_npoly;
	int			f_sr;
	int			f_sb;
	int			f_sizemax;
	
	float		f_amp;
	float		f_modAmp;
	float		f_delTime;
	float		f_grainLenghtDev;
	float		*f_envelopeSig;
	float		*f_delaySig;
	float		f_count;
	
} t_delay;

void delay_init(t_delay *c, int msec);
void delay_dspInit(t_delay *c, int sr, int sb);
void delay_free(t_delay *c);
void delay_time(t_delay *c, float f, int i);
void delay_amp(t_delay *c, float f, int i);

t_int *delayClear_perform(t_int *w);
t_int *delayReadSig_perform(t_int *w);
t_int *delayWrite_perform(t_int *w);

#endif