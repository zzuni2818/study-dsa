#include <stdio.h>

void insertion_sort(int a[], int n);
void print_arr(int a[], int n);

int main()
{
	int arr[] = {8, 2, 1, 9, 5, 6, 7, 3, 4, 10};

	const int n = sizeof(arr) / sizeof(arr[0]);

	printf("origin: ");
	print_arr(arr, n);

	insertion_sort(arr, n);

	printf("sorted: ");
	print_arr(arr, n);

	return 0;
}

void insertion_sort(int a[], int n)
{
	int i, j, target;

	for(i = 1; i < n; i++) {
		j = i;
		target = a[i];

		while(j > 0 && a[j - 1] > target) {
			a[j] = a[j - 1];
			j--;
		}
		a[j] = target;

	}
}

void print_arr(int a[], int n)
{
	for(int i = 0; i < n; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
}
