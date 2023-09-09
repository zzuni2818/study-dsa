#include <stdio.h>
#include <stdbool.h>
#include <math.h>

bool is_prime(int n);
bool is_prime_sqrt(int n);

int main()
{
	int n;

	printf("Test that input number is prime or not.\n\n");

	while(1) {
		printf("Input number to test: ");
		scanf("%d", &n);

		if(n < 0) {
			continue;
		}
		if(n == 0) {
			break;
		}

		printf("%d is %s\n", n, (is_prime(n) ? "prime number" : "not prime number"));
		printf("%d is %s (by square root)\n", n, (is_prime_sqrt(n) ? "prime number" : "not prime number"));
	}

	return 0;
}

bool is_prime(int n)
{
	if(n == 1) {
		return false;
	}
	for(int i = 2; i < n; i++) {
		if(n % i == 0) {
			return false;
		}
	}

	return true;
}
bool is_prime_sqrt(int n)
{
	if(n == 1) {
		return false;
	}

	const int sqrtn = (int) sqrt(n);
	for(int i = 2; i <= sqrtn; i++) {
		if(n % i == 0) {
			return false;
		}
	}

	return true;
}
