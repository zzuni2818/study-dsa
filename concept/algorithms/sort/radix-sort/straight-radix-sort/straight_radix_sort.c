#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define W 32

//generally recommended: M = W / 4
#define M (W / 4)
#define MV (1 << M)

void straight_radix_sort(int a[], int n);
void print_arr(int a[], int n);

unsigned bits(unsigned x, int k, int j);

int main()
{
	int arr[] = {8, 2, 1, 9, 5, 6, 7, 3, 4, 10};

	const int n = sizeof(arr) / sizeof(arr[0]);

	printf("origin: ");
	print_arr(arr, n);

	straight_radix_sort(arr, n);

	printf("sorted: ");
	print_arr(arr, n);

	return 0;
	
}

void straight_radix_sort(int a[], int n)
{
	int i, j;
	int *b, *count;

	b = (int*) malloc(sizeof(int) * n);
	count = (int*) malloc(sizeof(int) * MV);
	
	for(i = 0; i < W/M; i++) {
		//init count[]
		memset(count, 0, sizeof(int) * MV);

		//calc freqeuncy count
		for(j = 0; j < n; j++) {
			count[bits(a[j], i*M, M)]++;
		}
		//calc distribution count
		for(j = 1; j < MV; j++) {
			count[j] += count[j-1];
		}
		//sort at b[]
		for(j = n-1; j >= 0; j--) {
			b[--count[bits(a[j], i*M, M)]] = a[j];
		}
		//copy b[] to a[]
		for(j = 0; j < n; j++) {
			a[j] = b[j];
		}
	}
	free(b);
	free(count);
	
}
void print_arr(int a[], int n)
{
	for(int i = 0; i < n; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
}

unsigned bits(unsigned x, int k, int j)
{
	return (x >> k) & ~(~0 << j);
}
