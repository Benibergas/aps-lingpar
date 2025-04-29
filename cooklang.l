%{
#include "cooklang.tab.h"
#include <stdlib.h>
#include <string.h>

// Definindo a função yywrap
int yywrap(void) {
    return 1; // Indica que o arquivo foi lido completamente
}

%}

%%

adicione          { return ADICIONE; }
misture_ate       { return MISTURE_ATE; }
asse              { return ASSE; }
sirva             { return SIRVA; }
se                { return SE; }
entao             { return ENTAO; }
enquanto          { return ENQUANTO; }
faca              { return FACA; }

[0-9]+            { yylval.num = atoi(yytext); return NUMERO; }
[a-zA-Z]+         { yylval.str = strdup(yytext); return PALAVRA; }
[ \t\n]+          ; // Ignora espaços e quebras de linha

.                 { return yytext[0]; }

%%

