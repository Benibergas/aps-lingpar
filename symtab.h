/* symtab.h */
#ifndef SYMTAB_H
#define SYMTAB_H

/* Retorna o valor da variável (0 se ainda não foi atribuída). */
int  sym_get(const char *name);
/* Define ou atualiza o valor da variável. */
void sym_set(const char *name, int value);

void sym_print_all(void);


#endif /* SYMTAB_H */
