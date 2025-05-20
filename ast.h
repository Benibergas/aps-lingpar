#ifndef AST_H
#define AST_H

typedef enum { EXPR_INT, EXPR_VAR, EXPR_BIN } ExprKind;
typedef enum { OP_ADD, OP_SUB, OP_MUL, OP_DIV } BinOp;
typedef enum { STMT_ASSIGN, STMT_IF, STMT_WHILE, STMT_ACTION } StmtKind;
typedef enum { ACT_ADD, ACT_MIX, ACT_BAKE, ACT_SERVE } ActionKind;
typedef enum { C_FORNO_QUENTE, C_MASSA_UNIFORME, C_MASSA_LIQUIDA, C_FORNO_DESLIGADO, C_PRATO_PRONTO} PredefCond;

typedef struct Expr {
  ExprKind kind;
  union {
    int int_val;           // EXPR_INT
    char *var_name;        // EXPR_VAR
    struct {                // EXPR_BIN
      BinOp op;
      struct Expr *left, *right;
    } bin;
  } u;
} Expr;

typedef struct Stmt {
  StmtKind kind;
  union {
    struct { char *var; Expr *e; } assign;            // STMT_ASSIGN
    struct { Expr *l, *r; int op; struct Stmt *body; } ifs, whiles; // STMT_IF / STMT_WHILE
    struct { ActionKind act; char *id; int amt; PredefCond cond; } action; // STMT_ACTION
  } u;
  struct Stmt *next;  // para encadear vários comandos
} Stmt;

/* Funções construtoras (em ast.c): */
Expr *make_int(int v);
Expr *make_var(char *name);
Expr *make_bin(BinOp op, Expr *l, Expr *r);

Stmt *make_assign(char *var, Expr *e);
Stmt *make_if(Expr *l, int op, Expr *r, Stmt *body);
Stmt *make_while(Expr *l, int op, Expr *r, Stmt *body);
Stmt *make_action(ActionKind act, char *id, int amt, PredefCond c);
Stmt *append_stmt(Stmt *list, Stmt *s);

/* E função de avaliação: */
void eval_program(Stmt *prog);

#endif
