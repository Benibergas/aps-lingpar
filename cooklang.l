%{
#include "cooklang.tab.h"
#include <stdlib.h>
#include <string.h>
extern YYSTYPE yylval;
%}

%option noyywrap

%%
[ \t\r\n]+              /* ignora espaços */
"=="                    { return EQ; }
"!="                    { return NEQ; }
"<="                    { return LE; }
">="                    { return GE; }
"<"                     { return LT; }
">"                     { return GT; }
"="                     { return ASSIGN; }
"+"                     { return PLUS; }
"-"                     { return MINUS; }
"*"                     { return TIMES; }
"/"                     { return DIVIDE; }
";"                     { return SEMI; }
"("                     { return LPAREN; }
")"                     { return RPAREN; }
"se"                    { return SE; }
"entao"                 { return ENTAO; }
"enquanto"              { return ENQUANTO; }
"faca"                  { return FACA; }
"adicione"              { return ADICIONE; }
"misture_ate"           { return MISTURE_ATE; }
"asse"                  { return ASSE; }
"sirva"                 { return SIRVA; }
"forno_quente"          { return FORNO_QUENTE; }
"massa_uniforme"        { return MASSA_UNIFORME; }
"massa_liquida"         { return MASSA_LIQUIDA; }
"forno_desligado"       { return FORNO_DESLIGADO; }
"prato_pronto"          { return PRATO_PRONTO; }
[0-9]+                  {
                           yylval.num = atoi(yytext);
                           return NUMBER;
                        }
[A-Za-z_][A-Za-z0-9_]*   {
                           yylval.str = strdup(yytext);
                           return IDENTIFIER;
                        }
.                       {
                           fprintf(stderr, "Caracter invalido: '%s'\n", yytext);
                        }
%%
