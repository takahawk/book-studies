#include <stdio.h>
#include <strings.h>

int main()
{
	int freqs[255];
	bzero(freqs, sizeof(int) * 255);

	int c;
	while ((c = getchar()) != EOF)
		freqs[c]++;

	for (int i = 0; i < 255; ++i) {
		if (freqs[i] == 0)
			continue;

		printf("%c: ", i);
		for (int j = 0; j < freqs[i]; ++j)
			putchar('x');

		putchar('\n');
	}
}