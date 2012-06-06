
#include "pg.mel.h"

int main()
{
	t_class *c;

	c = class_new("pg.mel~", (method)mfcc_new, (method)mfcc_free, (short)sizeof(t_mfcc), 0L, A_GIMME, 0);
	class_addmethod(c, (method)mfcc_dsp,		"dsp",			A_CANT,	0);
	class_addmethod(c, (method)mfcc_assist,		"assist",		A_CANT,	0);
	
	class_dspinit(c);
	class_register(CLASS_BOX, c);
	mfcc_class = c;
	
	CLASS_ATTR_LONG				(c, "mfcc", 0, t_mfcc, f_mfccMode);
	CLASS_ATTR_LABEL			(c, "mfcc", 0, "Mode");
	CLASS_ATTR_ENUMINDEX		(c, "mfcc", 0, "Mel \"Mfcc");
	CLASS_ATTR_DEFAULT			(c, "mfcc", 0, "0");
	CLASS_ATTR_SAVE				(c, "mfcc", 1);
	CLASS_ATTR_ORDER			(c, "window", 0, "1");

	CLASS_ATTR_LONG				(c, "window", 0, t_mfcc, f_modEnv);
	CLASS_ATTR_LABEL			(c, "window", 0, "Window type");
	CLASS_ATTR_ENUMINDEX		(c, "window", 0, "Square \" \"Hanning \" \"Hamming \" \"Turkey \" \"Cosinus \" \"Lanczos \" \"Triangular \" \"Gaussian \" \"Bartlett-Hann \" \"Blackman \" \"Kaiser \" \"Nuttall \" \"Blackman-Harris \" \"Blackman-Nuttall \" \"Flat-Top \" \"Poisson");
	CLASS_ATTR_ACCESSORS		(c, "window", NULL, mode_set);
	CLASS_ATTR_DEFAULT			(c, "window", 0, "0");
	CLASS_ATTR_SAVE				(c, "window", 1);
	CLASS_ATTR_FILTER_CLIP		(c, "window", 0, 10);
	CLASS_ATTR_ORDER			(c, "window", 0, "2");

	CLASS_ATTR_LONG				(c, "interval", 0, t_mfcc, f_interval);
	CLASS_ATTR_LABEL			(c, "interval", 0, "Polling interval");
	CLASS_ATTR_FILTER_CLIP		(c, "interval", 3, 5000);
	CLASS_ATTR_DEFAULT			(c, "interval", 0, "10");
	CLASS_ATTR_SAVE				(c, "interval", 1);
	
	CLASS_ATTR_LONG				(c, "smooth", 0, t_mfcc, f_limit);;
	CLASS_ATTR_LABEL			(c, "smooth", 0, "Smooth");
	CLASS_ATTR_FILTER_MIN		(c, "smooth", 0);
	CLASS_ATTR_DEFAULT			(c, "smooth", 0, "5");
	CLASS_ATTR_SAVE				(c, "smooth", 1);

	CLASS_ATTR_FLOAT			(c, "highpass", 0, t_mfcc, f_hightpass);
	CLASS_ATTR_LABEL			(c, "highpass", 0, "Highpass filter");
	CLASS_ATTR_FILTER_CLIP		(c, "highpass", 0., 1.);
	CLASS_ATTR_DEFAULT			(c, "highpass", 0, "0.95");
	CLASS_ATTR_SAVE				(c, "highpass", 1);

	post("pg.mel~ by Pierre Guillot",0);
	post("Universite Paris 8, France",0);
	
	return 0;
}

void *mfcc_new(t_symbol *s, int argc, t_atom *argv)
{
	t_mfcc *x = NULL;
	int i;
	
	if (x = (t_mfcc *)object_alloc(mfcc_class)) 
	{		
		/* Sampling Rate Initialization **************/
		x->f_sr = sys_getsr();

		x->f_nBands = 0;
		x->f_limit = 5;			
		x->f_count = 0;	
		x->f_interval = 5;		
		x->f_mfccMode = 0;
		x->f_filter = 0.f;
		x->f_hightpass = 0.95f;

		/* Windows Size Initialization **************/
		x->f_windowSize = 0; 
		if( argv[0].a_type == A_LONG ) x->f_windowSize = (int)(argv[0].a_w.w_long);
		if (x->f_windowSize%2 != 0)
		{
			x->f_windowSize = 1024;
			object_post((t_object*)x, "Wrong window size initialization, set to default : 1024");
		}
		x->f_arraySize = x->f_windowSize / 2;

		/* Overlapping Initialization ***************/
		x->f_overlapping = 0; 
		if( argv[1].a_type == A_LONG ) x->f_overlapping = (int)(argv[1].a_w.w_long);
		if (x->f_overlapping < 1)
		{
			x->f_overlapping = 2;
			object_post((t_object*)x, "Wrong overlapping initialization, set to default : 2");
		}
		
		/* Mel bands Initialization ***************/
		if( argv[2].a_type == A_LONG ) x->f_nBands = (int)(argv[2].a_w.w_long);
		if (x->f_nBands < 1)
		{
			x->f_nBands = 24;
			object_post((t_object*)x, "Wrong bands initialization, set to default : 24");
		}

		/* Enveloppe   Initialization **************/
		window_setup(&x->f_env, x->f_windowSize);
		if( argv[3].a_type == A_LONG ) x->f_modEnv = argv[3].a_w.w_long;
		if (x->f_modEnv < 0 || x->f_modEnv > 15)
		{
			x->f_modEnv = 2;
			object_post((t_object*)x, "Wrong enveloppe, set to default : 2 (Hamming)");
		}
		mfcc_envSelector(x);

		x->f_result				= (float *)getbytes(x->f_nBands * sizeof(float));
		x->f_output				= (t_atom *)getbytes(x->f_nBands * sizeof(t_atom));

		/* Mel Filter Initialization **************/
		x->f_melBandRef			= (int *)getbytes(x->f_arraySize * sizeof(int));
		x->f_filterParameters	= (float **)getbytes(x->f_nBands  * sizeof(float *));
		for(i = 0; i < x->f_nBands ; i++)
		{
			x->f_filterParameters[i] = (float *)getbytes(x->f_arraySize  * sizeof(float));
		}
		mfcc_filterParameter(x);

		/* FFT Initialization ******************************************/
		x->f_fft = (t_fft *)getbytes(x->f_overlapping  * sizeof(t_fft));
		for(i = 0; i < x->f_overlapping; i++)
		{
			fft_setup(&x->f_fft[i], x->f_windowSize, i, x->f_overlapping, x->f_nBands);
		}

		attr_args_process (x, argc, argv);

		/* Inlet and Outlet Initialization ******************************/
		dsp_setup((t_pxobject *)x, 1);
		x->out1 = listout(x);

		/* Clock Initialization *****************************************/
		x->f_clock = clock_new(x, (method)mfcc_out);
		clock_delay(x->f_clock, 0L);

	}
	
	return x;
}			

void mfcc_dsp(t_mfcc *x, t_signal **sp, short *count)
{
	x->f_sr = sp[0]->s_sr;
	dsp_add(mfcc_perform, 3, x, sp[0]->s_vec, sp[0]->s_n);
}

t_int *mfcc_perform(t_int *w)
{	
	t_mfcc	*x	= (t_mfcc *)	(w[1]);
	t_float	*in1	= (t_sample *)	(w[2]);
	int n			= (int)			(w[3]);
	
	int i, j, alpha;
	double energy;

	if (x->f_ob.z_disabled) return w + 4;
	
	for(i = 0; i < x->f_overlapping; i++)
	{
		for(j = 0; j < n; j++)
		{
			/* Enveloppe and filter if mffcMode = 1 else just the enveloppe */
			if (x->f_mfccMode != 0)
			{
				x->f_fft[i].f_real[x->f_fft[i].f_ramp] = (in1[j] - (x->f_hightpass * x->f_filter)) * x->f_env.f_envelope[x->f_fft[i].f_ramp];
				x->f_filter = in1[j];
			}
			else
			{
				x->f_fft[i].f_real[x->f_fft[i].f_ramp] = in1[j] * x->f_env.f_envelope[x->f_fft[i].f_ramp];
			}

			if (x->f_fft[i].f_spew2 > 1)
			{
				/* MFCC's perform */
				if (x->f_mfccMode != 0)
				{
					/* First : Scale above the mel scale */
					if (x->f_fft[i].f_ramp >= 0 && x->f_fft[i].f_ramp <  x->f_arraySize )
					{
						alpha = x->f_melBandRef[x->f_fft[i].f_ramp];

						energy =  (sqrt((x->f_fft[i].f_complex[x->f_fft[i].f_ramp][0]*x->f_fft[i].f_complex[x->f_fft[i].f_ramp][0])+(x->f_fft[i].f_complex[x->f_fft[i].f_ramp][1]*x->f_fft[i].f_complex[x->f_fft[i].f_ramp][1])));
						// Si la bande frequentielle appartient au flitre de la bande mel alpha, il appartient aussi au filtre de la bande alpha+1
						// sauf lorque j-1 car la bande j-1 existe pas, donc elle appartient seulement a la bande j+1.
						if(alpha != -1)
						{
							x->f_fft[i].f_melBand[alpha] += energy * x->f_filterParameters[alpha][x->f_fft[i].f_ramp];
						}
						// Sauf pour la derni�re bande car la position +1 de la derniere n'existe pas, elle appartient seulement a la bande alpha.
						if(alpha != x->f_nBands-1)
						{
							x->f_fft[i].f_melBand[alpha+1] += energy * x->f_filterParameters[alpha+1][x->f_fft[i].f_ramp];
						}
					
					}
					/* Second : Take the logarithm */
					else if(x->f_fft[i].f_ramp >= x->f_arraySize && x->f_fft[i].f_ramp < x->f_arraySize+x->f_nBands)
					{
						alpha = x->f_fft[i].f_ramp - x->f_arraySize ;
						if(x->f_fft[i].f_melBand[alpha] != 0.)
						{
							x->f_fft[i].f_melBand[alpha] = log10(x->f_fft[i].f_melBand[alpha]);
						}
						else
						{
							x->f_fft[i].f_melBand[alpha] = -90.f;
						}
					}
					/* Third : Perfom the cosinus transform */
					else if(x->f_fft[i].f_ramp == x->f_arraySize + x->f_nBands)
					{
						fftwf_execute( x->f_fft[i].f_planCos );
					}
					/* Fourth : Record the result */
					else if(x->f_fft[i].f_ramp >= x->f_arraySize + 1 + x->f_nBands && x->f_fft[i].f_ramp < x->f_arraySize + (2 * x->f_nBands))
					{
						alpha = x->f_fft[i].f_ramp - (x->f_arraySize + x->f_nBands + 1);
						
						x->f_fft[i].f_mfcc[alpha] = x->f_fft[i].f_mffcoeff[alpha+1];
						x->f_fft[i].f_melBand[alpha+1] = 0.f;
						if(alpha == x->f_nBands - 2)
						{
							x->f_fft[i].f_spew = 1;
							x->f_fft[i].f_melBand[0] = 0.f;
						}
					}
				}
				/* Mel perform */
				else
				{
					if (x->f_fft[i].f_ramp >= 0 && x->f_fft[i].f_ramp <  x->f_arraySize )
					{

						alpha = x->f_melBandRef[x->f_fft[i].f_ramp];
						energy =  (sqrt((x->f_fft[i].f_complex[x->f_fft[i].f_ramp][0]*x->f_fft[i].f_complex[x->f_fft[i].f_ramp][0])+(x->f_fft[i].f_complex[x->f_fft[i].f_ramp][1]*x->f_fft[i].f_complex[x->f_fft[i].f_ramp][1])));
					
						if(alpha != -1)
						{
							x->f_fft[i].f_melBand[alpha] += energy * x->f_filterParameters[alpha][x->f_fft[i].f_ramp];
						}
						if(alpha != x->f_nBands-1)
						{
							x->f_fft[i].f_melBand[alpha+1] += energy * x->f_filterParameters[alpha+1][x->f_fft[i].f_ramp];
						}
					
					}
					else if(x->f_fft[i].f_ramp >= x->f_arraySize && x->f_fft[i].f_ramp < x->f_arraySize + x->f_nBands)
					{
						alpha = x->f_fft[i].f_ramp - x->f_arraySize;
	
						x->f_fft[i].f_mfcc[alpha] = x->f_fft[i].f_melBand[alpha];
						x->f_fft[i].f_melBand[alpha] = 0.f;
					}
					else if(x->f_fft[i].f_ramp == x->f_arraySize + x->f_nBands)
					{
						x->f_fft[i].f_spew = 1;
					}
				}
			}
			
			x->f_fft[i].f_ramp++;
			if (x->f_fft[i].f_ramp >= x->f_windowSize)
			{
				fftwf_execute( x->f_fft[i].f_plan );
				x->f_fft[i].f_ramp = 0;
				x->f_fft[i].f_spew2 += 1;
			}	
		}
	}
	return w + 4;	
}

void mfcc_out(t_mfcc *x)
{
	int i, j;
	
	for(i = 0; i < x->f_overlapping; i++)
	{
		if (x->f_fft[i].f_spew == 1)
		{	
			if (x->f_count != 0 && x->f_limit != 0)
			{
				for(j = 0; j < x->f_nBands; j++)
				{
					x->f_result[j] = x->f_result[j] + (x->f_fft[i].f_mfcc[j] - x->f_result[j])*(2.f/(x->f_limit+1));
					SETFLOAT(x->f_output+j, x->f_result[j]);
				}
			}
			else
			{
				for(j = 0; j < x->f_nBands; j++)
				{
					x->f_result[j] = x->f_fft[i].f_mfcc[j];
					SETFLOAT(x->f_output+j, x->f_result[j]);
					x->f_count++;
				}
			}
			if (x->f_mfccMode != 0)
			{
				outlet_list(x->out1, 0L, (x->f_nBands-1), x->f_output);
			}
			else 
			{
				outlet_list(x->out1, 0L, x->f_nBands, x->f_output);
			}

		}
		x->f_fft[i].f_spew = 0;
	}
	clock_delay(x->f_clock, x->f_interval);
	
}

void mfcc_free(t_mfcc *x)
{
	int i;
	
	dsp_free((t_pxobject *)x);
	for(i = 0; i < x->f_overlapping; i++)
	{
		fft_free(&x->f_fft[i]);
	}
	freebytes(x->f_fft, x->f_overlapping * sizeof(t_fft));
	
	freebytes(x->f_result, x->f_nBands * sizeof(float));
	freebytes(x->f_result, x->f_nBands * sizeof(t_atom));
	freebytes(x->f_melBandRef , x->f_arraySize * sizeof(int));
	for(i = 0; i < x->f_nBands; i++)
	{
		freebytes(x->f_filterParameters[i], x->f_arraySize * sizeof(float));
	}
	freebytes(x->f_filterParameters, x->f_nBands * sizeof(float));
	window_free(&x->f_env);
	object_free(x->f_clock);

}

void mfcc_assist(t_mfcc *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) 
	{
		switch (a) 
		{	
			case 0:
				sprintf(s,"(Signal) Input");
				break;
		}
	}
	else 
	{
		switch (a) 
		{	
			case 0:
				if (x->f_mfccMode != 0)
				{
					sprintf(s,"(List) MFCCs");
				}
				else 
				{
					sprintf(s,"(List) Mel Bands");
				}

				break;
		}
	}
}


void mfcc_filterParameter(t_mfcc *x)
{
	int i, j;

	float maxMel;
	float melBandSize;
	float freqBandSize;
	float *melBandCenterMel;
	float *melBandCenterHerz;
	float twoMelBandSize;
	float *freqBandCenter;
	float *normalizeFactor;
	// Defini le coefficient mel maximum //
	// A partir de la frequence d echantillonage - 20Hz //
	maxMel = 2595*log10( ( ((float)(x->f_sr/2) - 20.f) / 700.f) + 1.f );
	// Defini la taille d'une bande en mel //
	melBandSize = maxMel/x->f_nBands;
	// Defini le centre des bandes mel en  mel //
	melBandCenterMel = (float *)getbytes(x->f_nBands  * sizeof(float));
	for(i = 0; i < x->f_nBands; i++)
	{
		melBandCenterMel[i] = (float)i * melBandSize  +  melBandSize / 2.f ;
	}
	// Defini le centre des bandes mel en Hz //
	melBandCenterHerz	= (float *)getbytes((x->f_nBands+1)  * sizeof(float));
	for(i = 0; i < x->f_nBands; i++)
	{
		melBandCenterHerz[i]	= (700 * ( pow(10, melBandCenterMel[i]/2595.f) - 1.f)) + 20.f;
		
		//post("%ld", i);
		//post("cen %f", melBandCenterHerz[i]);
	}
	melBandCenterHerz[x->f_nBands] = x->f_sr;
	// Defini la taille d'une bande FFT //
	freqBandSize = (float)x->f_sr / (float)x->f_windowSize;
	// Defini le centre des bandes de FFT //
	freqBandCenter = (float *)getbytes(x->f_arraySize  * sizeof(float));
	for(i = 0; i < x->f_arraySize; i++)
	{
		freqBandCenter[i] = ( (float)i * freqBandSize ) + ( freqBandSize / 2.f );
	}
	
	// On applique un filtre a deux bandes frequentielles par defaut 
	// L'on defini un tableau permattant de savoir a quelles bandes
	// frequentielles le filtre est different de zero et nous evite ainsi
	// une application du filtre sur toutes les bandes
	for(i = 0; i < x->f_arraySize; i++)
	{
		int frequency = (float)(i*freqBandSize);
		for(j = 0; j < x->f_nBands; j++)
		{
			if( frequency < melBandCenterHerz[0])
			{
				x->f_melBandRef[i] = -1;
			}
			else if( frequency > melBandCenterHerz[j] && frequency < melBandCenterHerz[j+1])
			{
				x->f_melBandRef[i] = j;
			}
		}
	}
	
	// on defini un facteur de normalize par bande de mel
	// Si une bande de mel recouvre N bande de FFT
	// alors le facteur = 1/N
	normalizeFactor = (float *)getbytes(x->f_nBands  * sizeof(float));
	for(i = 0; i < x->f_nBands; i++)
	{
		normalizeFactor[i] = 0;
		for(j = 0; j < x->f_arraySize; j++)
		{
			if( x->f_melBandRef[j] == i || x->f_melBandRef[j] == i-1 )
			{
				normalizeFactor[i]++;
				//post("OK");
			}
		}
		if (normalizeFactor[i] <= 1) 
		{
			normalizeFactor[i] = 1;
		}
		//post("%ld facteur %ld", i, (int)normalizeFactor[i]);
	}
	
	//x->f_rapportSize = (float)(PI * (1.0 / (float)x->f_arraySize));
	//for(i = 0; i < x->f_arraySize; i++) post("%ld %ld", i, x->f_melBandRef[i]);
	// Defini les facteurs de filtres triangulaire en fonctions des bandes fft et mel //
	for(i = 0; i < x->f_nBands; i++)
	{
		for(j = 0; j < x->f_arraySize; j++)
		{
			// Filtre triangulaire (n) = 2/N * ( N/2 -| n - (N-1)/2|)

			// Definition de la period N : twoMelBandSize
			// Pour la bande 0 : N =  melBandCenterHerz[1] - 0
			if(i == 0) twoMelBandSize = melBandCenterHerz[1];
			// Pour la derniere bande N = SamplingRate/2 - - melBandCenterHerz[i-1];
			else if(i == x->f_nBands-1) twoMelBandSize = x->f_sr/2 - melBandCenterHerz[i-1];
			// Pour le reste N = melBandCenterHerz[i+1] - melBandCenterHerz[i-1]
			else twoMelBandSize = melBandCenterHerz[i+1] - melBandCenterHerz[i-1];
			// Calculs
			// n est egal freqBandCenter[j]-melBandCenterHerz[i-1])
			x->f_filterParameters[i][j] = ((2.f/twoMelBandSize)  * ((twoMelBandSize/2.f) - fabs((freqBandCenter[j]-melBandCenterHerz[i-1])  - ((twoMelBandSize - 1.f) / 2.f)))/normalizeFactor[i]) ;
			if (x->f_filterParameters[i][j] <= 0.f) x->f_filterParameters[i][j] = 0.f;
			//if(i == x->f_nBands - 1 ) post("x->f_filterParameters %ld %ld = %f", i, j, (float)x->f_filterParameters[i][j]);
		}
	}

	
	
	freebytes(melBandCenterMel, x->f_nBands * sizeof(float));
	freebytes(melBandCenterHerz, (x->f_nBands + 1) * sizeof(float));
	freebytes(freqBandCenter, x->f_arraySize * sizeof(float));
	freebytes(freqBandCenter, x->f_nBands * sizeof(float));
}


void mfcc_envSelector(t_mfcc *x)
{
	switch(x->f_modEnv)
	{
		case 0:
			window_square(&x->f_env);
			break;
		case 1:
			window_hanning(&x->f_env);
			break;
		case 2:
			window_hamming(&x->f_env);
			break;
		case 3:
			window_turkey(&x->f_env);
			break;
		case 4:
			window_cosinus(&x->f_env);
			break;
		case 5:
			window_lanczos(&x->f_env);
			break;
		case 6:
			window_triangular(&x->f_env);
			break;
		case 7:
			window_gaussian(&x->f_env);
			break;
		case 8:
			window_bartlett_hann(&x->f_env);
			break;
		case 9:
			window_blackman(&x->f_env);
			break;
		case 10:
			window_kaiser(&x->f_env);
			break;
		case 11:
			window_nuttall(&x->f_env);
			break;
		case 12:
			window_blackman_harris(&x->f_env);
			break;
		case 13:
			window_blackman_nuttall(&x->f_env);
			break;
		case 14:
			window_flat_top(&x->f_env);
			break;
		case 15:
			window_poisson(&x->f_env);
			break;
	}
}

t_max_err mode_set(t_mfcc *x, t_object *attr, long argc, t_atom *argv)
{
	int mode;
	mode = 16;
	if ( atom_gettype(argv) == A_LONG) mode = atom_getlong(argv);
	else if ( atom_gettype(argv) == A_FLOAT) mode = (int)atom_getfloat(argv);
	else if ( atom_gettype(argv) == A_SYM)
	{
		if ( gensym(argv->a_w.w_sym->s_name)	  == gensym("Square"))			mode = 0;
		else if ( gensym(argv->a_w.w_sym->s_name) == gensym("Hanning"))			mode = 1;
		else if ( gensym(argv->a_w.w_sym->s_name) == gensym("Hamming"))			mode = 2;
		else if ( gensym(argv->a_w.w_sym->s_name) == gensym("Turkey"))			mode = 3;
		else if ( gensym(argv->a_w.w_sym->s_name) == gensym("Cosinus"))			mode = 4;
		else if ( gensym(argv->a_w.w_sym->s_name) == gensym("Lanczos"))			mode = 5;
		else if ( gensym(argv->a_w.w_sym->s_name) == gensym("Triangular"))		mode = 6;
		else if ( gensym(argv->a_w.w_sym->s_name) == gensym("Gaussian"))		mode = 7;
		else if ( gensym(argv->a_w.w_sym->s_name) == gensym("Bartlett-Hann"))	mode = 8;
		else if ( gensym(argv->a_w.w_sym->s_name) == gensym("Blackman"))		mode = 9;
		else if ( gensym(argv->a_w.w_sym->s_name) == gensym("Kaiser"))			mode = 10;
		else if ( gensym(argv->a_w.w_sym->s_name) == gensym("Nuttall"))			mode = 11;
		else if ( gensym(argv->a_w.w_sym->s_name) == gensym("Blackman-Harris"))	mode = 12;
		else if ( gensym(argv->a_w.w_sym->s_name) == gensym("Blackman-Nuttall"))mode = 13;
		else if ( gensym(argv->a_w.w_sym->s_name) == gensym("Flat-Top"))		mode = 14;
		else if ( gensym(argv->a_w.w_sym->s_name) == gensym("Poison"))			mode = 15;
	}
	
	x->f_modEnv = mode;
	mfcc_envSelector(x);
	
	return 0;
}