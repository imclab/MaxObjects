
#ifndef DEF_IKEDA
#define DEF_IKEDA

#include "pg.chaos.h"

void ikeda_bang(t_chaosSig *x);
void ikeda_list(t_chaosSig *x, t_symbol *s, short ac, t_atom *av);
void ikeda_set(t_chaosSig *x, t_symbol *s, short ac, t_atom *av);
void ikeda_print(t_chaosSig *x);
void ikeda_record(t_chaosSig *x);
void *ikeda_new(t_symbol *s, int argc, t_atom *argv);
void ikeda_free(t_chaosSig *x);
void ikeda_reset(t_chaosSig *x);
void ikeda_init(t_chaosSig *x, t_symbol *s, short argc, t_atom *argv);
void ikeda_assist(t_chaosSig *x, void *b, long m, long a, char *s);

#endif