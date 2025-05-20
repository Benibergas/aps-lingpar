/* ast.c */
#include "ast.h"
#include "symtab.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cooklang.tab.h"  /* traz os símbolos EQ, NEQ, LT etc. */


/* ——— Construtores de Expr ——— */
Expr *make_int(int v) {
    Expr *e = malloc(sizeof(Expr));
    e->kind = EXPR_INT;
    e->u.int_val = v;
    return e;
}

Expr *make_var(char *name) {
    Expr *e = malloc(sizeof(Expr));
    e->kind = EXPR_VAR;
    e->u.var_name = name;  /* já veio alocada pelo strdup no scanner */
    return e;
}

Expr *make_bin(BinOp op, Expr *l, Expr *r) {
  Expr *e = malloc(sizeof(Expr));
  e->kind       = EXPR_BIN;
  e->u.bin.op   = op;
  e->u.bin.left  = l;
  e->u.bin.right = r;
  return e;
}

/* ——— Construtores de Stmt ——— */
Stmt *make_assign(char *var, Expr *e) {
    Stmt *s = malloc(sizeof(Stmt));
    s->kind = STMT_ASSIGN;
    s->u.assign.var = var;
    s->u.assign.e   = e;
    s->next = NULL;
    return s;
}

Stmt *make_if(Expr *l, int op, Expr *r, Stmt *body) {
  Stmt *s = malloc(sizeof(Stmt));
  s->kind       = STMT_IF;
  s->u.ifs.l    = l;
  s->u.ifs.op   = op;
  s->u.ifs.r    = r;
  s->u.ifs.body = body;
  s->next = NULL;
  return s;
}

Stmt *make_while(Expr *l, int op, Expr *r, Stmt *body) {
    Stmt *s = malloc(sizeof(Stmt));
    s->kind = STMT_WHILE;
    s->u.whiles.l    = l;
    s->u.whiles.op   = op;
    s->u.whiles.r    = r;
    s->u.whiles.body = body;
    s->next = NULL;
    return s;
}

Stmt *make_action(ActionKind act, char *id, int amt, PredefCond c) {
    Stmt *s = malloc(sizeof(Stmt));
    s->kind = STMT_ACTION;
    s->u.action.act  = act;
    s->u.action.id   = id;
    s->u.action.amt  = amt;
    s->u.action.cond = c;
    s->next = NULL;
    return s;
}

/* ——— Append de statements em lista encadeada ——— */
Stmt *append_stmt(Stmt *list, Stmt *s) {
    if (!list) return s;
    Stmt *p = list;
    while (p->next) p = p->next;
    p->next = s;
    return list;
}

/* ——— Funções de avaliação ——— */
static int eval_expr(Expr *e) {
    switch (e->kind) {
      case EXPR_INT:
        return e->u.int_val;

      case EXPR_VAR:
        return sym_get(e->u.var_name);

      case EXPR_BIN: {
        int l = eval_expr(e->u.bin.left);
        int r = eval_expr(e->u.bin.right);
        switch (e->u.bin.op) {
          case OP_ADD: return l + r;
          case OP_SUB: return l - r;
          case OP_MUL: return l * r;
          case OP_DIV: return l / r;
        }
      }
    }
    return 0;  /* nunca chega aqui */
}

static void eval_stmt(Stmt *s) {
    for (; s; s = s->next) {
        switch (s->kind) {

          case STMT_ASSIGN: {
            int v = eval_expr(s->u.assign.e);
            sym_set(s->u.assign.var, v);
            break;
          }

          case STMT_IF: {
            int l = eval_expr(s->u.ifs.l);
            int r = eval_expr(s->u.ifs.r);
            int cond = 0;
            switch (s->u.ifs.op) {
              case EQ:  cond = (l == r); break;
              case NEQ: cond = (l != r); break;
              case LT:  cond = (l < r);  break;
              case LE:  cond = (l <= r); break;
              case GT:  cond = (l > r);  break;
              case GE:  cond = (l >= r); break;
            }
            if (cond)
                eval_stmt(s->u.ifs.body);
            break;
          }

          case STMT_WHILE: {
            while (1) {
              int l = eval_expr(s->u.whiles.l);
              int r = eval_expr(s->u.whiles.r);
              int cond = 0;
              switch (s->u.whiles.op) {
                case EQ:  cond = (l == r); break;
                case NEQ: cond = (l != r); break;
                case LT:  cond = (l < r);  break;
                case LE:  cond = (l <= r); break;
                case GT:  cond = (l > r);  break;
                case GE:  cond = (l >= r); break;
              }
              if (!cond) break;
              eval_stmt(s->u.whiles.body);
            }
            break;
          }

          case STMT_ACTION: {
            switch (s->u.action.act) {
              case ACT_ADD:
                printf("Adicionando %d de %s\n",
                       s->u.action.amt,
                       s->u.action.id);
                break;
              case ACT_MIX:
                printf("Misturando até condição %d\n",
                       s->u.action.cond);
                break;
              case ACT_BAKE:
                printf("Assando %s\n",
                       s->u.action.id);
                break;
              case ACT_SERVE:
                printf("Servindo %s\n",
                       s->u.action.id);
                break;
            }
            break;
          }
        }
    }
}

void eval_program(Stmt *prog) {
    eval_stmt(prog);
    sym_print_all();
}
