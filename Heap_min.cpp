#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 1. Min-Heapify: Maintains the min-heap property
void minHeapify(int arr[], int n, int i) {
    int smallest = i;       // Initialize smallest as root
    int left = 2 * i + 1;   // left child index
    int right = 2 * i + 2;  // right child index

    // If left child is smaller than current smallest
    if (left < n && arr[left] < arr[smallest])
        smallest = left;

    // If right child is smaller than current smallest
    if (right < n && arr[right] < arr[smallest])
        smallest = right;

    // If smallest is not root, swap and continue heapifying
    if (smallest != i) {
        swap(arr[i], arr[smallest]);
        minHeapify(arr, n, smallest);
    }
}

// 2. Min Heap Sort: Sorts in descending order
void minHeapSort(int arr[], int n) {
    // Build Min-Heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        minHeapify(arr, n, i);

    // One by one extract elements from heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root (smallest) to the end
        swap(arr[0], arr[i]);

        // Call minHeapify on the reduced heap
        minHeapify(arr, i, 0);
    }
}

int main() {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    minHeapSort(arr, n);

    cout << "Sorted array (Descending): \n";
    for (int i = 0; i < n; ++i)
        cout << arr[i] << " ";
    cout << endl;

    return 0;
}
