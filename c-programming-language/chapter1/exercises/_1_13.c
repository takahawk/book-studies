#include <stdio.h>
#include <strings.h>

#define IN  1
#define OUT 0

#define MAXLEN 200

int main()
{
	int freqs[MAXLEN];
	bzero(freqs, sizeof(int) * MAXLEN);

	int state = OUT;
	int c;
	int len = 0;

	while ((c = getchar()) != EOF) {
		if (c == ' ' || c == '\t' || c == '\n') {
			if (state == IN) {
				freqs[len]++;
				len = 0;
			}
			state = OUT;
		} else {
			state = IN;
			len++;
		}

	}

	for (int i = 1; i < MAXLEN; ++i) {
		int freq = freqs[i];
		if (freq == 0)
			continue;
		printf("%d: ", i);
		for (int j = 0; j < freq; ++j) {
			putchar('x');
		}
		putchar('\n');
	}
}