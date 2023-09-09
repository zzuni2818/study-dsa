#include <stdio.h>

int get_gcd_subtraction(int u, int v);
int get_gcd_modulo(int u, int v);
int get_gcd_recursion(int u, int v);

int main()
{
	int u, v;

	printf("Euclid's algorithm: get greatest common divisor of two positive integer\n");

	while(1) {
		printf("Enter two positive integer: ");
		scanf("%d %d", &u, &v);

		if(u < 0 || v < 0) {
			printf("Invalid integer, u: %d, v: %d\n", u, v);
			continue;
		}
		if(u == 0 && v == 0) {
			break;
		}

		printf("greatest common divisor of %d and %d: %d (by subtraction)\n", u, v, get_gcd_subtraction(u, v));
		printf("greatest common divisor of %d and %d: %d (by modulo)\n", u, v, get_gcd_modulo(u, v));
		printf("greatest common divisor of %d and %d: %d (by recursion)\n", u, v, get_gcd_recursion(u, v));
	}
	
	return 0;
}

int get_gcd_subtraction(int u, int v)
{
	int t;

	while(u > 0) {
		if(u < v) {
			t = u;
			u = v;
			v = t;
		}
		u -= v;
	}
	
	return v;
}
int get_gcd_modulo(int u, int v)
{
	int t;

	while(v > 0) {
		t = u % v;
		u = v;
		v = t;
	}
	
	return u;
}

int get_gcd_recursion(int u, int v)
{
	if(v == 0) {
		return u;
	}

	return get_gcd_recursion(v, u % v);
}
