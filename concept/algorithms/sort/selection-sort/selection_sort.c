#include <stdio.h>

void selection_sort(int a[], int n);
void print_arr(int a[], int n);

int main()
{
	int arr[] = {8, 2, 1, 9, 5, 6, 7, 3, 4, 10};

	const int n = sizeof(arr) / sizeof(arr[0]);

	printf("origin: ");
	print_arr(arr, n);

	selection_sort(arr, n);

	printf("sorted: ");
	print_arr(arr, n);

	return 0;
	
}

void selection_sort(int a[], int n)
{
	int min_index, min;

	for(int i = 0; i < n - 1; i++) {
		min_index = i;
		min = a[i];

		for(int j = i + 1; j < n; j++) {
			if(a[j] < min) {
				min_index = j;
				min = a[j];
			}
		}

		a[min_index] = a[i];
		a[i] = min;
	}
}
void print_arr(int a[], int n)
{
	for(int i = 0; i < n; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
}
