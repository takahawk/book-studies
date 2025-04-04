#include <stdio.h>

void print_hello(int n) {
	for (int i = 0; i < n; ++i)
		puts("Hello, world!");
}

int main()
{
	print_hello(7);
	return 0;
}
