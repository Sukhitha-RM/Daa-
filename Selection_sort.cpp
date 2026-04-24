#include <iostream>
#include <vector>
#include <algorithm> // for swap

using namespace std;

// Selection Sort function
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        // Swap the found minimum element with the first element
        swap(arr[i], arr[minIndex]);
    }
}

int main() {
    int n;
    cout << "Enter number of elements: ";
    
    // Check if input is a valid positive integer
    if (!(cin >> n) || n <= 0) {
        cout << "Invalid size. Please enter a positive integer." << endl;
        return 1;
    }

    vector<int> arr(n);
    cout << "Enter " << n << " integers: ";
    for (int i = 0; i < n; i++) {
        if (!(cin >> arr[i])) {
            cout << "Invalid input. Please enter integers only." << endl;
            return 1;
        }
    }

    selectionSort(arr);

    cout << "Sorted array: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
