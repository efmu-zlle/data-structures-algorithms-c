#include <stdio.h>

void print_array(int arr[], size_t length) {
    for (int i = 0; i < length; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void swap(int *a, int *b) {  
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int l, int r) {
    int pivot = arr[r], k = l - 1;
    for (int i = l; i < r; i++) {
        if (pivot >= arr[i]) {
            swap(&arr[++k], &arr[i]);
        }
    }
    swap(&arr[k + 1], &arr[r]);
    return k + 1;
}

void quick_sort(int arr[], int left, int right) {
    if (left < right) {
        int p = partition(arr, left, right);

        quick_sort(arr, left, p - 1);
        quick_sort(arr, p + 1, right);
    }
}

int main(void) {
    int array[] = { 6, 1, 2, 5, 4, 3, 7, 8 };
    size_t length = sizeof(array) / sizeof(array[0]);

    printf("before sorting:\n");
    print_array(array, length);

    quick_sort(array, 0, length - 1);

    printf("after sorting:\n");
    print_array(array, length);

    return 0;
}