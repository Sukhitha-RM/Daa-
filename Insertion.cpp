#include <iostream>
#include <vector>
#include <algorithm> // Required for upper_bound and rotate

using namespace std;

// Optimized Insertion Sort using STL
void insertionSort(vector<int>& arr) {
    for (auto it = arr.begin(); it != arr.end(); ++it) {
        // Find the first element greater than *it in the sorted prefix
        auto const insertion_point = upper_bound(arr.begin(), it, *it);
        
        // Rotate the elements to "insert" the current value into its place
        rotate(insertion_point, it, next(it));
    }
}

int main() {
    int n;
    cout << "Enter size: ";
    if (!(cin >> n) || n <= 0) return 0;

    vector<int> arr(n);
    cout << "Enter " << n << " integers: ";
    for (int& x : arr) cin >> x;

    insertionSort(arr);

    cout << "Sorted: ";
    for (int x : arr) cout << x << " ";
    cout << endl;

    return 0;
}
