#include "mpc.h"

int number_of_nodes(mpc_ast_t* t) {
	if (t->children_num == 0) return 1;

	int total = 1;
	for (int i = 0; i < t->children_num; ++i)
		total += number_of_nodes(t->children[i]);
	return total;
}