/* symtab.c */
#include "symtab.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_VARS 100

static struct {
    char *name;
    int   value;
} table[MAX_VARS];
static int count = 0;

int sym_get(const char *name) {
    for (int i = 0; i < count; i++) {
        if (strcmp(table[i].name, name) == 0)
            return table[i].value;
    }
    return 0;
}

void sym_set(const char *name, int value) {
    for (int i = 0; i < count; i++) {
        if (strcmp(table[i].name, name) == 0) {
            table[i].value = value;
            return;
        }
    }
    if (count < MAX_VARS) {
        table[count].name  = strdup(name);
        table[count].value = value;
        count++;
    } else {
        fprintf(stderr, "Erro: tabela de símbolos cheia\n");
        exit(1);
    }
}

void sym_print_all(void) {
    for (int i = 0; i < count; i++) {
        printf(">> %s = %d\n", table[i].name, table[i].value);
    }
}