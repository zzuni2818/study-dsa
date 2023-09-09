#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX 9999

int main()
{
	int n;

	printf("Print that all of prime numbers which is less than input number.\n\n");

	while(1) {
		printf("Input number(max: %d): ", MAX);
		scanf("%d", &n);

		if(n < 0 || n > MAX) {
			printf("invalid number: %d.\n", n);
			continue;
		}
		if(n == 0) {
			break;
		}

		bool *arr = (bool *) calloc(n, sizeof(bool));
		if(arr == NULL) {
			printf("Fail to allocate memory.\n");
			exit(EXIT_FAILURE);
		}

		for(int i = 2; i < n; i++) {
			//already removed number which is not prime number
			if(arr[i]) {
				continue;
			}
			//remove number which is not prime number
			for(int j = i + i; j <= n; j += i) {
				arr[j] = true;
			}
		}

		printf("prime numbers:");
		for(int i = 2; i <= n; i++) {
			//false: prime number
			if(arr[i] == false) {
				printf(" %d", i);
			}
		}
		printf("\n");

		free(arr);

	}

	return 0;
}
