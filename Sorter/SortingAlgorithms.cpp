//
// Created by andy on 29/07/24.
//

#include "SortingAlgorithms.h"

int partition(PagedArray& arr, int low, int high) {
    int pivot = arr[high];  // Escoger el último elemento como pivote
    int i = low - 1;  // Índice del elemento más pequeño
    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            ++i;
            swap(arr, i, j);
        }
    }
    swap(arr, i + 1, high);
    return i + 1;
}

void quickSort(PagedArray& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}


void insertionSort(PagedArray& arr, int n) {
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            arr.setValue(j + 1, arr[j]);
            --j;
        }
        arr[j + 1] = key;
        arr.setValue(j + 1, key);
    }
}

void bubbleSort(PagedArray& arr, int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr, j, j + 1);
            }
        }
    }
}
