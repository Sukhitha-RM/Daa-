#include <iostream>
#include <vector>
#include <algorithm> // Required for std::sort

// Function to perform binary search
int binarySearch(const std::vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;

    while (left <= right) {
        // Calculate the middle index to prevent potential overflow with very large arrays
        int mid = left + (right - left) / 2;

        // Check if the target is at the middle
        if (arr[mid] == target) {
            return mid;
        }

        // If target is greater, ignore the left half
        if (arr[mid] < target) {
            left = mid + 1;
        }

        // If target is smaller, ignore the right half
        else {
            right = mid - 1;
        }
    }

    // If the loop finishes without finding the element, it's not present
    return -1;
}

int main() {
    // The array MUST be sorted for binary search to work correctly
    std::vector<int> numbers = {2, 5, 9, 12, 17, 37, 86};
    int target = 17;

    int result_index = binarySearch(numbers, target);

    if (result_index == -1) {
        std::cout << "Element " << target << " is not present in array" << std::endl;
    } else {
        std::cout << "Element " << target << " is present at index " << result_index << std::endl;
    }

    return 0;
}
