#include <stdio.h>

void bubble_sort(int a[], int n);
void print_arr(int a[], int n);

int main()
{
	int arr[] = {8, 2, 1, 9, 5, 6, 7, 3, 4, 10};

	const int n = sizeof(arr) / sizeof(arr[0]);

	printf("origin: ");
	print_arr(arr, n);

	bubble_sort(arr, n);

	printf("sorted: ");
	print_arr(arr, n);

	return 0;
	
}

void bubble_sort(int a[], int n)
{
	int i, j, tmp;

	for(i = 0; i < n - 1; i++) {
		for(j = 1; j < n - i; j++) {
			if(a[j - 1] > a[j]) {
				tmp = a[j - 1];
				a[j - 1] = a[j];
				a[j] = tmp;
			}
		}
	}

}
void print_arr(int a[], int n)
{
	for(int i = 0; i < n; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
}
