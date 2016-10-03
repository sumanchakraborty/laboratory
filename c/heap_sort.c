
#include <stdio.h>
#include <stdlib.h>

int heapify(int *A, int S, int I);
int heapsort(int *arr, int n);

int heapify(int *arr, int n, int i)
{
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    if (l < n && arr[l] > arr[largest]) {
        largest = l;
    }

    if (r < n && arr[r] > arr[largest]) {
        largest = r;
    }

    if (largest != i) {
        int tmp = arr[largest];
        arr[largest] = arr[i];
        arr[i] = tmp;
        heapify(arr, n, largest);
    }

    return 0;
}

int heapsort(int *arr, int n)
{
    int i = 0;

    // bottom-up
    for (i = n/2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    // pick-up max
    for (i = n - 1; i >= 0; i--) {
        int tmp = arr[0];
        arr[0] = arr[i];
        arr[i] = tmp;
        heapify(arr, i, 0);
    }

    return 0;
}

int printarr(int *arr, int n)
{
    int i = 0;
    for (i = 0; i < n; i++) {
        printf("%d, ", arr[i]);
    }
    printf("\n");
    return 0;
}

int main () {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr)/sizeof(arr[0]);

    printf("before:\t");
    printarr(arr, n);

    heapsort(arr, n);

    printf("after:\t");
    printarr(arr, n);

    return 0;
}

