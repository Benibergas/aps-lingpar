%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

extern FILE *yyin;
extern int  yylineno;
Stmt *prog = NULL;
int  yylex(void);

void yyerror(const char *s) {
    fprintf(stderr, "Erro na linha %d: %s\n", yylineno, s);
}
%}

/* **Este** bloco vai para cooklang.tab.h antes do union */
%code requires {
  #include "ast.h"
}

/* agora o Bison já conhece Expr e Stmt */
%union {
  int    num;
  char  *str;
  Expr  *expr;
  Stmt  *stmt;
}

/*------------------------------------------------------
  Tokens (batem com cooklang.l)
------------------------------------------------------*/
%token <str> IDENTIFIER
%token <num> NUMBER

%token ASSIGN PLUS MINUS TIMES DIVIDE
%token EQ NEQ LT LE GT GE

%token LPAREN RPAREN SEMI

%token SE ENTAO ENQUANTO FACA
%token ADICIONE MISTURE_ATE ASSE SIRVA

%token FORNO_QUENTE MASSA_UNIFORME MASSA_LIQUIDA FORNO_DESLIGADO PRATO_PRONTO

/*------------------------------------------------------
  Associação de tipos aos não-terminais
------------------------------------------------------*/
%type <expr> expressao termo fator
%type <stmt> comando atribuicao condicional loop acao
/* 'programa' atualiza o global 'prog', não usa $$ */
%type <num>  op_comp

/*------------------------------------------------------
  Precedência e associatividade
------------------------------------------------------*/
%left PLUS MINUS
%left TIMES DIVIDE

%start programa

%%

programa
  : /* vazio */               { prog = NULL; }
  | programa comando         { prog = append_stmt(prog, $2); }
  ;

comando
  : atribuicao               { $$ = $1; }
  | condicional              { $$ = $1; }
  | loop                     { $$ = $1; }
  | acao                     { $$ = $1; }
  ;

atribuicao
  : IDENTIFIER ASSIGN expressao SEMI
    { $$ = make_assign($1, $3); }
  ;

expressao
  : termo                     { $$ = $1; }
  | expressao PLUS  termo     { $$ = make_bin(OP_ADD, $1, $3); }
  | expressao MINUS termo     { $$ = make_bin(OP_SUB, $1, $3); }
  ;

termo
  : fator                     { $$ = $1; }
  | termo TIMES  fator        { $$ = make_bin(OP_MUL, $1, $3); }
  | termo DIVIDE fator        { $$ = make_bin(OP_DIV, $1, $3); }
  ;

fator
  : NUMBER                    { $$ = make_int($1); }
  | IDENTIFIER                { $$ = make_var($1); }
  | LPAREN expressao RPAREN   { $$ = $2; }
  ;

op_comp
  : EQ   { $$ = EQ; }
  | NEQ  { $$ = NEQ; }
  | LT   { $$ = LT; }
  | LE   { $$ = LE; }
  | GT   { $$ = GT; }
  | GE   { $$ = GE; }
  ;

condicional
  : SE LPAREN expressao op_comp expressao RPAREN ENTAO comando
    { $$ = make_if($3, $4, $5, $8); }
  ;

loop
  : ENQUANTO LPAREN expressao op_comp expressao RPAREN FACA comando
    { $$ = make_while($3, $4, $5, $8); }
  ;

acao
  : ADICIONE IDENTIFIER NUMBER SEMI
    { $$ = make_action(ACT_ADD,  $2,    $3,      0); }
  | MISTURE_ATE FORNO_QUENTE   SEMI
    { $$ = make_action(ACT_MIX,  NULL,  0, C_FORNO_QUENTE); }
  | MISTURE_ATE MASSA_UNIFORME SEMI
    { $$ = make_action(ACT_MIX,  NULL,  0, C_MASSA_UNIFORME); }
  | MISTURE_ATE MASSA_LIQUIDA  SEMI
    { $$ = make_action(ACT_MIX,  NULL,  0, C_MASSA_LIQUIDA); }
  | MISTURE_ATE FORNO_DESLIGADO SEMI
    { $$ = make_action(ACT_MIX,  NULL,  0, C_FORNO_DESLIGADO); }
  | MISTURE_ATE PRATO_PRONTO    SEMI
    { $$ = make_action(ACT_MIX,  NULL,  0, C_PRATO_PRONTO); }
  | ASSE IDENTIFIER            SEMI
    { $$ = make_action(ACT_BAKE, $2,    0,      0); }
  | SIRVA IDENTIFIER           SEMI
    { $$ = make_action(ACT_SERVE,$2,    0,      0); }
  ;

%%

int main(int argc, char **argv) {
    if (argc > 1) yyin = fopen(argv[1], "r");
    if (yyparse() == 0) {
        eval_program(prog);
    }
    return 0;
}
