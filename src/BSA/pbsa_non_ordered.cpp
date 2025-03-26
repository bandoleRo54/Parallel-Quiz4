#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <omp.h>
using namespace std;

// Parallel search for non-ordered data that checks boundaries.
int parallelSearchNonOrdered(const vector<int>& arr, int x) {
    int n = arr.size();
    int foundIndex = -1;
    int P = omp_get_max_threads();    // number of threads
    int segLen = (n + P - 1) / P;       // ceiling division to cover all elements

    #pragma omp parallel for shared(foundIndex)
    for (int i = 0; i < P; i++) {
        int segStart = i * segLen;
        int segEnd = min(segStart + segLen - 1, n - 1);
        if (segStart < n && arr[segStart] == x) {
            #pragma omp critical
            { foundIndex = segStart; }
        }
        if (segEnd < n && arr[segEnd] == x) {
            #pragma omp critical
            { foundIndex = segEnd; }
        }
    }
    return foundIndex;
}

int main(int argc, char* argv[]) {
    srand(static_cast<unsigned int>(time(nullptr)));
    const int n = atoi(argv[1]);
    vector<int> data;

    // Generate random values (non-ordered).
    for (int i = 0; i < n; i++) {
        data.push_back(rand() % 100);
    }

    // Pick a random target from the array for demonstration.
    int target = data[rand() % n];

    cout << "Non-ordered array: ";
    for (int num : data)
        cout << num << " ";
    cout << "\nSearching for: " << target << "\n";

    int index = parallelSearchNonOrdered(data, target);
    if (index != -1)
        cout << "Found at index " << index << endl;
    else
        cout << "Not found (or not at a segment boundary)" << endl;

    return 0;
}
