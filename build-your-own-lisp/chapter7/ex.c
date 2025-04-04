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

long eval_op(long x, char* op, long y) {
	if (strcmp(op, "+") == 0) { return x + y; }
	if (strcmp(op, "-") == 0) { return x - y; }
	if (strcmp(op, "*") == 0) { return x * y; }
	if (strcmp(op, "/") == 0) { return x / y; }
	// 5. Add the operator %, which returns the remainder of division. For example % 10 6 is 4.
	if (strcmp(op, "%") == 0) { return x % y; }
	// 6. Add the operator ^, which raises one number to another. For example ^ 4 2 is 16.
	if (strcmp(op, "^") == 0) {
		int res = 1;
		for (int i = 0; i < y; ++i) {
			res *= x;
		}
		return res;
	}
	// 7. Add the function min, which returns the smallest number. For example min 1 5 3 is 1.
	if (strcmp(op, "max") == 0) { return x > y ? x : y; }
	// 8. Add the function max, which returns the biggest number. For example max 1 5 3 is 5.
	if (strcmp(op, "min") == 0) { return x < y ? x : y; }

	return 0;
}

long eval(mpc_ast_t *t) {
	if (strstr(t->tag, "number")) {
		return atoi(t->contents);
	}

	char *op = t->children[1]->contents;


	long x = eval(t->children[2]);

	// 9. Change the minus operator - so that when it receives one argument it negates it.
	if (t->children_num == 4 && strcmp(op, "-") == 0)
		return -x;

	int i = 3;

	while (strstr(t->children[i]->tag, "expr")) {
		x = eval_op(x, op, eval(t->children[i]));
		++i;
	}

	return x;
}

// 1. Write a recursive function to compute the number of leaves of a tree.
long leaves(mpc_ast_t *t) {
	if (t->children_num == 0)
		return 1;

	int res = 0;
	for (int i = 0; i < t->children_num; ++i) {
		res += leaves(t->children[i]);
	}

	return res;
}

// 2. Write a recursive function to compute the number of branches of a tree.
long branches(mpc_ast_t *t) {
	if (t->children_num == 0)
		return 0;

	int res = 1;
	for (int i = 0; i < t->children_num; ++i) {
		res += branches(t->children[i]);
	}

	return res;
}

// 3. Write a recursive function to compute the most number of children spanning from one branch of a tree.
long max_children(mpc_ast_t *t) {
	if (t->children_num == 0)
		return 0;

	int max = t->children_num;

	for (int i = 0; i < t->children_num; ++i) {
		int tmp = max_children(t->children[i]);
		if (max < tmp)
			max = tmp;
	}

	return max;
}

// 4. How would you use strstr to see if a node was tagged as an expr?
// > strstr(node->tag, "expr") != NULL

// 5. How would you use strcmp to see if a node had the contents '(' or ')'?
// > strcmp(node->contents, "(") == 0


int main()
{
	mpc_parser_t* Number   = mpc_new("number");
	mpc_parser_t* Operator = mpc_new("operator");
	mpc_parser_t* Expr     = mpc_new("expr");
	mpc_parser_t* Lispy    = mpc_new("lispy");

	mpca_lang(MPCA_LANG_DEFAULT,
		"\
		number    : /-?[0-9]+/ ; \
		operator  : '+' | '-' | '*' | '/' | '%' | '^' | \"max\" | \"min\" ; \
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
			long result = eval(r.output);
			printf("%li\n", result);
			printf("leaves: %li\n", leaves(r.output));
			printf("branches: %li\n", branches(r.output));
			printf("max number of children: %li\n", max_children(r.output));
			mpc_ast_print(r.output);
			mpc_ast_delete(r.output);
		} else {
			mpc_err_print(r.error);
			mpc_err_delete(r.error);
		}

		free(input);
	}

	mpc_cleanup(4, Number, Operator, Expr, Lispy);
}