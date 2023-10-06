#include <stdio.h>

void quick_sort(int a[], int n);
void print_arr(int a[], int n);

int main()
{
	int arr[] = {8, 2, 1, 9, 5, 6, 7, 3, 4, 10};

	const int n = sizeof(arr) / sizeof(arr[0]);

	printf("origin: ");
	print_arr(arr, n);

	quick_sort(arr, n);

	printf("sorted: ");
	print_arr(arr, n);

	return 0;
	
}

void quick_sort(int a[], int n)
{
	const int pivot = a[n - 1];
	int i = 0, j = n - 2;
	int temp;

	if(n <= 1) {
		return;
	}

	while(1) {
		while(a[i] < pivot) {
			i++;
		}
		while(a[j] > pivot) {
			j--;
		}
		if(i >= j) {
			break;
		}

		temp = a[i];
		a[i] = a[j];
		a[j] = temp;
	}
	temp = a[i];
	a[i] = a[n - 1];
	a[n - 1] = temp;

	quick_sort(a, i);
	quick_sort(a + i + 1, n - i - 1);
	
}
void print_arr(int a[], int n)
{
	for(int i = 0; i < n; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
}
