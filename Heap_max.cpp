#include <iostream>
#include <algorithm>
using namespace std;

// Function to maintain max-heap property
void heapify(int arr[], int n, int i) {
    int largest = i, left = 2*i + 1, right = 2*i + 2;
    if (left < n && arr[left] > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

// Main heap sort function
void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i); // Build heap
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]); // Move root to end
        heapify(arr, i, 0);   // Heapify reduced heap
    }
}
