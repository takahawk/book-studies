#include <stdio.h>

main()
{
	int prev_blank = 0;

	int c;

	while ((c = getchar()) != EOF) {
		if (c == ' ' && prev_blank)
			continue;
		prev_blank = c == ' ';
		putchar(c);
	}
}