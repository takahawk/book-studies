#include <stdio.h>

main()
{
	int blanks = 0;
	int tabs = 0;
	int newlines = 0;

	int c;
	while ((c = getchar()) != EOF)
		if (c == ' ')
			++blanks;
		else if (c == '\t')
			++tabs;
		else if (c == '\n')
			++newlines;

	printf("blanks   = %d\n", blanks);
	printf("tabs     = %d\n", tabs);
	printf("newlines = %d\n", newlines);
}