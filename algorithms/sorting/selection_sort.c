#include <stdio.h>
// @note: to know how it works https://www.youtube.com/watch?v=jZzyERW7h1A&list=PLhQjrBD2T381WAHyx1pq-sBfykqMBI7V4&index=4 01:12:43 - Selection Sort

void print_array(int arr[], size_t length) {
    for (int i = 0; i < length; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void selection_sort(int arr[], size_t length) {
    for (int i = 0; i < length - 1; i++) {
        int index_min = i;
        for (int j = i + 1; j < length; j++) {
            if (arr[j] < arr[index_min]) {
                index_min = j;
            }
        }

        int temp = arr[i];
        arr[i] = arr[index_min];
        arr[index_min] = temp;
    }
}

int main(void) {
    int array[] = { 6, 1, 2, 5, 4, 3, 7, 8 };
    size_t length = sizeof(array) / sizeof(array[0]);
    
    printf("before sorting:\n");
    print_array(array, length);

    selection_sort(array, length);

    printf("after sorting:\n");
    print_array(array, length);
    
    return 0;
}
