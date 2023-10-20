#include <stdio.h>

#define BYTE_SIZE 8

void radix_exchange_sort(int a[], int n, int bit);
void print_arr(int a[], int n);

unsigned bits(unsigned x, int k, int j);

int main()
{
	int arr[] = {8, 2, 1, 9, 5, 6, 7, 3, 4, 10};

	const int n = sizeof(arr) / sizeof(arr[0]);
	const int num_bit = sizeof(int) * BYTE_SIZE;

	printf("origin: ");
	print_arr(arr, n);

	radix_exchange_sort(arr, n, num_bit - 1);

	printf("sorted: ");
	print_arr(arr, n);

	return 0;
	
}

void radix_exchange_sort(int a[], int n, int bit)
{
	int i, j, temp;

	if(n > 1 && bit >= 0) {
		i = 0;
		j = n - 1;

		while(1) {
			//search
			while(bits(a[i], bit, 1) == 0 && i < j) {
				i++;
			}
			while(bits(a[j], bit, 1) != 0 && i < j) {
				j--;
			}

			if(i >= j) {
				break;
			}
		
			temp = a[i];
			a[i] = a[j];
			a[j] = temp;
		}

		//if all bits are 0
		if(bits(a[n - 1], bit, 1) == 0) {
			j++;
		}

		radix_exchange_sort(a, j, bit - 1);
		radix_exchange_sort(a + j, n - j, bit - 1);
	}
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
