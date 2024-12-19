#include <stdio.h>

void print_array(int arr[], size_t length) {
    for (int i = 0; i < length; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void insertion_sort(int arr[], size_t length) {
    for (int i = 1; i < length; i++) {
        int curr = arr[i], k = i - 1;
        
        while (k >= 0 && arr[k] > curr) {
            arr[k + 1] = arr[k];
            k--;
        }
        arr[k + 1] = curr;
    }
}

int main(void) {
    int array[] = { 6, 1, 2, 5, 4, 3, 7, 8 };
    size_t length = sizeof(array) / sizeof(array[0]);

    printf("before sorting:\n");
    print_array(array, length);

    insertion_sort(array, length);

    printf("after sorting:\n");
    print_array(array, length);

    return 0;
}