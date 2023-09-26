#include <stdio.h>

void shell_sort(int a[], int n);
void print_arr(int a[], int n);

int main()
{
	int arr[] = {8, 2, 1, 9, 5, 6, 7, 3, 4, 10};

	const int n = sizeof(arr) / sizeof(arr[0]);

	printf("origin: ");
	print_arr(arr, n);

	shell_sort(arr, n);

	printf("sorted: ");
	print_arr(arr, n);

	return 0;
	
}

void shell_sort(int a[], int n)
{
	int i, j, h, k, tmp;

	for(h = n / 2; h > 0; h /= 2) {
		for(i = 0; i < h; i++) {
			for(j = i + h; j < n; j += h) {
				k = j;
				tmp = a[j];
				while(k >= h && a[k - h] > tmp) {
					a[k] = a[k - h];
					k -= h;
				}
				a[k] = tmp;
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
