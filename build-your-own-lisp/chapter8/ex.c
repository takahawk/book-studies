// 1. Run the previous chapter's code through gdb and crash it. See what happens.
// > Program received signal SIGFPE, Arithmetic exception.
// > 0x000055555555564a in eval_op ()

// 2. How do you give an enum a name?
// > typedef enum { Foo, Bar } Baz;

// 3. What are union data types and how do they work?
// > union is data type that allows to use same memory represented as multiple different types

// 4. What are the advantages over using a union instead of struct?
// > they are for different use cases - structs for combining data, union for some kind of polymorphic code
// > where we can have different types of data in same variable

// 5. Can you use a union in the definition of lval?
// > yes, we can, but only for int/error - we still should have type of answer in struct

#include <stdio.h>
#include "mpc.h"

#ifdef _WIN32
#include <string.h>

static char input[2048];

char* readline(char *prompt) {
	fputs(prompt, stdout);
	fgets(buffer, 2048, stdin);
	char *cpy = malloc(strlen(buffer) + 1);
	strcpy(cpy, buffer);
	cpy[strlen(cpy) - 1] = '\0';
	return cpy;
}

void add_history(char *unused) {}

#else
#include <editline/readline.h>
#include <editline/history.h>
#endif

enum { LVAL_NUM, LVAL_ERR };
enum { LERR_DIV_ZERO, LERR_BAD_OP, LERR_BAD_NUM };

typedef struct {
	int type;
	// 7. Extend parsing and evaluation to support decimal types using a double field.
	double num;
	int err;
} lval;

lval lval_num(double x) {
	lval v;
	v.type = LVAL_NUM;
	v.num = x;
	return v;
}

lval lval_err(int err) {
	lval v;
	v.type = LVAL_ERR;
	v.err = err;
	return v;
}

void lval_print(lval v) {
	switch (v.type) {
	case LVAL_NUM:
		printf("%f", v.num);
		break;
	case LVAL_ERR:
		if (v.err == LERR_DIV_ZERO) {
			printf("Error: Division by Zero!");
		} else if (v.err == LERR_BAD_OP) {
			printf("Error: Invalid operator!");
		} else if (v.err == LERR_BAD_NUM) {
			printf("Error: Invalid number!");
		}
		break;
	}
}

void lval_println(lval v) {
	lval_print(v);
	putchar('\n');
}


lval eval_op(lval x, char* op, lval y) {
	if (x.type == LVAL_ERR) return x;
	if (y.type == LVAL_ERR) return y;

	if (strcmp(op, "+") == 0) { return lval_num(x.num + y.num); }
	if (strcmp(op, "-") == 0) { return lval_num(x.num - y.num); }
	if (strcmp(op, "*") == 0) { return lval_num(x.num * y.num); }
	if (strcmp(op, "/") == 0) { 
		return y.num == 0
			? lval_err(LERR_DIV_ZERO)
			: lval_num(x.num / y.num); 
	}
	// 6. Extend parsing and evaluation to support the remainder operator %.
	if (strcmp(op, "%") == 0) { 
		return y.num == 0
			? lval_err(LERR_DIV_ZERO)
			: lval_num((long) x.num % (long) y.num); 
	}

	return lval_err(LERR_BAD_OP);
}

lval eval(mpc_ast_t *t) {
	if (strstr(t->tag, "number")) {
		errno = 0;
		char *end;
		double x = strtod(t->contents, &end);
		return errno != ERANGE
			? lval_num(x)
			: lval_err(LERR_BAD_NUM);
	}

	char *op = t->children[1]->contents;

	lval x = eval(t->children[2]);

	int i = 3;

	while (strstr(t->children[i]->tag, "expr")) {
		x = eval_op(x, op, eval(t->children[i]));
		++i;
	}

	return x;
}

int main()
{
	mpc_parser_t* Number   = mpc_new("number");
	mpc_parser_t* Operator = mpc_new("operator");
	mpc_parser_t* Expr     = mpc_new("expr");
	mpc_parser_t* Lispy    = mpc_new("lispy");

	mpca_lang(MPCA_LANG_DEFAULT,
		"\
		number    : /-?[0-9]+(\\.[0-9]+)?/ ; \
		operator  : '+' | '-' | '*' | '/' | '%'; \
		expr      : <number> | '(' <operator> <expr>+ ')' ; \
		lispy     : /^/ <operator> <expr>+ /$/ ; \
		",
		Number, Operator, Expr, Lispy);

	puts("Lispy version 0.0.0.0.1");
	puts("Press Ctrl+c to Exit\n");

	while (1) {
		char *input = readline("lispy> ");
		add_history(input);

		mpc_result_t r;
		if (mpc_parse("<stdin>", input, Lispy, &r)) {
			lval result = eval(r.output);
			lval_println(result);
			mpc_ast_delete(r.output);
		} else {
			mpc_err_print(r.error);
			mpc_err_delete(r.error);
		}

		free(input);
	}

	mpc_cleanup(4, Number, Operator, Expr, Lispy);
}