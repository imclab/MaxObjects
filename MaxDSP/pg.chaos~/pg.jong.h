
#ifndef DEF_JONG
#define DEF_JONG

#include "pg.chaos.h"

void jong_bang(t_chaosSig *x);
void jong_list(t_chaosSig *x, t_symbol *s, short ac, t_atom *av);
void jong_set(t_chaosSig *x, t_symbol *s, short ac, t_atom *av);
void jong_print(t_chaosSig *x);
void jong_record(t_chaosSig *x);
void *jong_new(t_symbol *s, int argc, t_atom *argv);
void jong_free(t_chaosSig *x);
void jong_reset(t_chaosSig *x);
void jong_init(t_chaosSig *x, t_symbol *s, short argc, t_atom *argv);
void jong_assist(t_chaosSig *x, void *b, long m, long a, char *s);

#endif