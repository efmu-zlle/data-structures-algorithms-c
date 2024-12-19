#include <stdio.h>
#include <stdlib.h>

void print_array(int arr[], size_t length) {
    for (int i = 0; i < length; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void merge(int arr[], int l, int m, int r) {
    int left_bucket_length = l;
    int right_bucket_length = r - m;

    int *left_bucket = (int *)malloc(left_bucket_length * sizeof(int));
    int *right_bucket = (int *)malloc(right_bucket_length * sizeof(int));

    int i, j;

    for (i = 0; i < left_bucket_length; i++) {
        left_bucket = arr[i + l];
    }

    for (j = 0; j < right_bucket_length; j++) {
        right_bucket = arr[j + m];
    }

    int k = l;
    i = 0, j = 0;

    while (i < left_bucket_length && j < right_bucket_length) {
        if (left_bucket[i] > right_bucket[j]) {
            arr[k] = left_bucket[i];
            i++;
        } else {
            arr[k] = right_bucket[j];
            j++;
        }
        k++;
    }

    while (i < left_bucket_length) {
        arr[k] = left_bucket[i];
        i++;
        k++;
    }

    while (j < right_bucket_length) {
        arr[k] = right_bucket[j];
        j++;
        k++;
    }
}

void merge_sort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);

        merge(arr, left, mid, right); 
    }
}

int main(void) {
    int array[] = { 6, 1, 2, 5, 4, 3, 7, 8 };
    size_t length = sizeof(array) / sizeof(array[0]);

    printf("before sorting:\n");
    print_array(array, length);

    merge_sort(array, 0, length - 1);

    printf("after sorting:\n");
    print_array(array, length);

    return 0;
}

// index: 0 1 2 3      4 5 6 7  // left: 4, mid: 5, right: 7

// value: 6 1 2 5      4 3 7 8 