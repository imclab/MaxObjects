
#ifndef DEF_duffing
#define DEF_duffing

#include "pg.chaos.h"

void duffing_bang(t_chaosSig *x);
void duffing_list(t_chaosSig *x, t_symbol *s, short ac, t_atom *av);
void duffing_set(t_chaosSig *x, t_symbol *s, short ac, t_atom *av);
void duffing_print(t_chaosSig *x);
void duffing_record(t_chaosSig *x);
void *duffing_new(t_symbol *s, int argc, t_atom *argv);
void duffing_free(t_chaosSig *x);
void duffing_reset(t_chaosSig *x);
void duffing_init(t_chaosSig *x, t_symbol *s, short argc, t_atom *argv);
void duffing_assist(t_chaosSig *x, void *b, long m, long a, char *s);

#endif

