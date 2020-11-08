#include <stdio.h>
#include <stdlib.h>

#define left( i )     2*(i) + 1
#define right( i )    2*(i) + 2

void swap( int *a, int *b ){ int temp = *a; *a = *b; *b = temp; }

void min_heapify( int *arr, int i, int n )
{
    int l = left(i);
	int r = right(i);
	int smallest;

	if (l < n && arr[l] < arr[i]) smallest = l;
	else                          smallest = i;

	if (r < n && arr[r] < arr[smallest]) smallest = r;

	if (smallest != i) {
		swap(&arr[i], &arr[smallest]);
		min_heapify(arr, smallest, n);
	}
}

int main()
{
}
