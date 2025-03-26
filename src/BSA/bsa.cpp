#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std; 

// Binary search function assumes that the vector is sorted
int binarySearch(const vector<int>& arr, int x) {
    int left = 0;
    int right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == x)
            return mid;        // Found the target
        else if (arr[mid] < x)
            left = mid + 1;    // Search in the right half
        else
            right = mid - 1;   // Search in the left half
    }
    return -1;  // Not found
}

int main(int argc, char* argv[]) {
    srand(time(nullptr));
    const int n = atoi(argv[1]);
    vector<int> ordered;

    // Generate random values
    for (int i = 0; i < n; i++) {
        ordered.push_back(rand() % 100);
    }
    // Sort the array to make it ordered
    sort(ordered.begin(), ordered.end());

    // Pick a random target from the array
    int target = ordered[rand() % n];

    cout << "Ordered array: ";
    for (int num : ordered)
        cout << num << " ";
    cout << "\nSearching for: " << target << "\n";

    int index = binarySearch(ordered, target);
    if (index != -1)
        cout << "Found at index " << index << endl;
    else
        cout << "Not found" << endl;
    
    return 0;
}
