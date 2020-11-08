#include <iostream>
#include <algorithm>
#include <exception>

using std::sort;
using std::cout;
using std::endl;
using std::domain_error;

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int get_median(int *arr, int n)
{
    sort(arr, arr+n);
    return arr[n/2];
}

int partition(int *arr, int l, int r, int x)
{
    int i;
    for (i=l; i<r; i++)
        if (arr[i] == x)
           break;

    swap(&arr[i], &arr[r]);

    i = l;
    for (int j = l; j <= r-1; j++) {
        if (arr[j] <= x) {
            swap(&arr[i], &arr[j]);
            i++;
        }
    }

    swap(&arr[i], &arr[r]);

    return i;
}

int median_of_medians(int *arr, int l, int r, int k)
{
    if( k>=1 && k<=r-l+1 ) {
        int n = r-l+1;

        int i;
        int *median = new int[(n+4)/5];

        for(i=0 ; i<n/5 ; i++) {
            median[i] = get_median(arr+l+i*5, 5);
        }
        if(i*5 < n) {
            median[i] = get_median(arr+l+i*5, n%5);
            i++;
        }

        int mom = (i==1) ? median[i-1] : median_of_medians(median, 0, i-1, i/2);
        delete[] median;
        int idx = partition(arr, l, r, mom);

        if( idx-l == k-1 ) return arr[idx];
        if( idx-l  > k-1 ) return median_of_medians(arr, l, idx-1, k);
        return median_of_medians(arr, idx+1, r, k-idx+l-1);
    }

    throw domain_error("value of 'k' out of domain.\n");
}


int main()
{
    int n = 9, i = 7;
    int arr[] = {1,4,3,2,5,8,7,6,9,10};
    int x = median_of_medians(arr, 0, n-1, i);
    cout << "The " << i << "'th order statistic is : " << x << endl;
    return 0;
}
