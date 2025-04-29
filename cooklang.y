%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definindo o tipo YYSTYPE para usar o yylval
typedef union {
    int num;
    char* str;
} YYSTYPE;

#define YYSTYPE_IS_DECLARED 1

void yyerror(const char *s);
int yylex(void);
int yyparse(void);

// Função principal
int main(void) {
    return yyparse();
}
%}

// Definindo o tipo dos tokens
%union {
    int num;
    char* str;
}

// Declaração dos tokens e seus tipos
%token <num> NUMERO
%token <str> PALAVRA
%token ADICIONE MISTURE_ATE ASSE SIRVA SE ENTAO ENQUANTO FACA

%%

// Aqui começa a gramática

programa:
    comandos
;

comandos:
    comando
    | comandos comando
;

comando:
    ADICIONE NUMERO PALAVRA { printf("Adicione %d %s\n", $2, $3); free($3); }
    | MISTURE_ATE PALAVRA   { printf("Misture até %s\n", $2); free($2); }
    | ASSE NUMERO           { printf("Asse a %d graus\n", $2); }
    | SIRVA                 { printf("Sirva\n"); }
    | SE PALAVRA '=' '=' NUMERO ENTAO comando
                            { printf("Se %s == %d então...\n", $2, $5); free($2); }
    | ENQUANTO PALAVRA PALAVRA PALAVRA FACA comando
                            { printf("Enquanto %s %s %s faça...\n", $2, $3, $4); free($2); free($3); free($4); }
;

%%

// Função para lidar com erros de sintaxe
void yyerror(const char *s) {
    fprintf(stderr, "Erro de sintaxe: %s\n", s);
}
