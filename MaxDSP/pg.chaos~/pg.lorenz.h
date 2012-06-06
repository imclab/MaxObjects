
#ifndef DEF_lorenz
#define DEF_lorenz

#include "pg.chaos.h"

void lorenz_bang(t_chaosSig *x);
void lorenz_list(t_chaosSig *x, t_symbol *s, short ac, t_atom *av);
void lorenz_set(t_chaosSig *x, t_symbol *s, short ac, t_atom *av);
void lorenz_print(t_chaosSig *x);
void lorenz_record(t_chaosSig *x);
void *lorenz_new(t_symbol *s, int argc, t_atom *argv);
void lorenz_free(t_chaosSig *x);
void lorenz_reset(t_chaosSig *x);
void lorenz_init(t_chaosSig *x, t_symbol *s, short argc, t_atom *argv);
void lorenz_assist(t_chaosSig *x, void *b, long m, long a, char *s);

#endif