
#ifndef DEF_SPECTRUM
#define DEF_SPECTRUM

#include "ext.h"
#include "ext_obex.h"
#include "ext_common.h"
#include "z_dsp.h"
#include <math.h>
#include "pg.window.h"
#include "pg.fft.h"

#define SIZELIST 256

typedef struct  _domain 
{
	float		f_low; 
	float		f_high;
	int			f_size;
	
} t_domain;

typedef struct  _spectrum 
{
	t_pxobject	f_ob;
	int			f_sr;

	void		*out1;

	long		f_windowsSize;	// Taille de la fenetre FFT (reel)//
	long		f_arraySize;	// Taille du vecteur comlexe (complexe) //
	int			f_arrayMin;		// Valeur minimum utilisee de vecteur complexe //
	int			f_arrayMax;		// Valeur maximum utilisee de vecteur complexe //
	long		f_overlapping;	// Nombre d'overlapping //

	float 		f_rapportSize;	// Valeur de ponderation de l'amplitude //
	void 		*f_clock;		// Permet de differer l execution d'une fonction //

	t_fft		*f_fft;			// Tableaux de structure FFT //
	t_domain	domain;			// Structure contenant les informations de bande frequentielle //

	int			f_resize;		// Mode resize liste sur 256 valeurs //
	int			f_logamp;		// Mode logarithmique pour les frequences //
	int			f_logfreq;		// Mode logarithmique pour les amplitudes //
	int			f_interval;		// Valeur en ms pour differer l'execution de la fonction sortie  //
	int			f_limit;		// Valeur en ms pour smoother la liste  //
	int			f_modEnv;

	float		*f_floatSpec;	// Vecteur permettant d' appliquer une echelle logarithmique au frequences //
	float		*f_result;		// Vecteur permettant de smoother la liste //
	t_atom		*f_spectrum;

	int			f_count;		// Valeur permettant d'eviter le smooth sur la première sortie de liste //
	t_window	f_env;
} t_spectrum;

void *spectrum_class;

void *spectrum_new(t_symbol *s, int argc, t_atom *argv);
void spectrum_free(t_spectrum *x);
void spectrum_assist(t_spectrum *x, void *b, long m, long a, char *s);
void spectrum_dsp(t_spectrum *x, t_signal **sp, short *count);
void spectrum_sortie(t_spectrum *x);
t_int *spectrum_perform(t_int *w);
void spectrum_envSelector(t_spectrum *x);
t_max_err domain_mode_set(t_spectrum *x, t_object *attr, long argc, t_atom *argv);
t_max_err mode_set(t_spectrum *x, t_object *attr, long argc, t_atom *argv);

#endif