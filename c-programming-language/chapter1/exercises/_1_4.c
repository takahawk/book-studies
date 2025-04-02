#include <stdio.h>

main()
{
	float fahr, celsius;
	float lower, upper, step;

	lower = 0;
	upper = 300;
	step = 20;

	celsius = lower;

	printf("CELSIUS TO FAHRENHEIT TABLE\n");
	printf("===========================\n");

	while (celsius <= upper) {
		fahr = (9./5.) * celsius + 32.;
		printf("%3.0f %6.1f\n", celsius, fahr);
		celsius += step;
	}
}