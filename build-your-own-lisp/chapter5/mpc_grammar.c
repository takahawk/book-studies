#include "mpc.h"

int main()
{
	mpc_parser_t* Adjective = mpc_or(4,
		mpc_sym("wow"), mpc_sym("many"),
		mpc_sym("such"), mpc_sym("such")
	);

	mpc_parser_t* Noun = mpc_or(5,
		mpc_sym("lisp"), mpc_sym("language"),
		mpc_sym("book"), mpc_sym("build"),
		mpc_sym("c")
	);

	mpc_parser_t* Phrase = mpc_and(2, mpcf_strfold, Adjective, Noun, free);
	mpc_parser_t* Doge = mpc_many(mpcf_strfold, Phrase);
}