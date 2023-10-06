#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUM 5

void counting_sort(int a[], int n, int max_num);
void print_arr(int a[], int n);

int main()
{
	int arr[] = {1, 3, 2, 2, 3, 1, 3, 2, 4, 2, 4, 3, 1, 2, 1, 2, 5, 1, 5, 3};

	const int n = sizeof(arr) / sizeof(arr[0]);

	printf("origin: ");
	print_arr(arr, n);

	counting_sort(arr, n, MAX_NUM);

	printf("sorted: ");
	print_arr(arr, n);

	return 0;
	
}

void counting_sort(int a[], int n, int max_num)
{
	// max + 1 means use number 1 to 5, not 0 to 4
	int *count = (int*) malloc(sizeof(int) * (max_num + 1));
	int *temp = (int*) malloc(sizeof(int) * n);

	//init
	memset(count, 0, sizeof(int) * (max_num + 1));
	memset(temp, 0, sizeof(int) * n);

	//calc freqeuncy count
	for(int i = 0; i < n; i++) {
		count[a[i]]++;
	}

	//calc distribution count
	for(int i = 2; i < max_num + 1; i++) {
		count[i] += count[i - 1];
	}

	//read a[] from rear and save temp[]
	for(int i = n - 1; i >= 0; i--) {
		temp[--count[a[i]]] = a[i];
	}

	//copy temp[] to a[]
	for(int i = 0; i < n; i++) {
		a[i] = temp[i];
	}
	
	//destroy
	free(count);
	free(temp);
}
void print_arr(int a[], int n)
{
	for(int i = 0; i < n; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
}
