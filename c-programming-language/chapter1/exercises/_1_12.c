#include <stdio.h>

#define IN  1
#define OUT 0

main()
{
	int state = OUT;

	int c;
	while ((c = getchar()) != EOF) {
		if (c == '\n' || c == '\t' || c == ' ') {
			if (state == IN)
				putchar('\n');
			state = OUT;
		} else {
			state = IN;
			putchar(c);
		}
	}
}