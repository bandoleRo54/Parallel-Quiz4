#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <omp.h>
using namespace std;

// Parallel Binary Search for ordered data
int parallelBinarySearch(const vector<int>& arr, int x) {
    int left = 0;
    int right = arr.size() - 1;
    int foundIndex = -1;

    // Continue while there is a valid search interval and target not found
    while (left <= right && foundIndex == -1) {
        int segmentSize = right - left + 1;
        int P = omp_get_max_threads();  // use available threads
        int segLen = segmentSize / P;
        if (segLen == 0) segLen = 1;    // ensure at least one element per thread

        // For keeping track of the candidate segment for the next round
        int newLeft = left, newRight = right;
        bool segmentChosen = false;

        #pragma omp parallel for shared(foundIndex, newLeft, newRight, segmentChosen)
        for (int i = 0; i < P; i++) {
            // Compute the boundaries for thread i’s segment.
            int segStart = left + i * segLen;
            int segEnd = (i == P - 1) ? right : segStart + segLen - 1;
            if (segStart > right) continue; // out of range

            // Check if the target is exactly at one of the boundaries.
            if (arr[segStart] == x) {
                #pragma omp critical
                { foundIndex = segStart; }
            }
            if (arr[segEnd] == x) {
                #pragma omp critical
                { foundIndex = segEnd; }
            }

            // If not found, then using sorted order,
            // if x lies between the segment boundaries, mark this segment.
            if (!segmentChosen && arr[segStart] < x && x < arr[segEnd]) {
                #pragma omp critical
                {
                    // If multiple threads qualify, only the first update is used.
                    if (!segmentChosen) {
                        newLeft = segStart;
                        newRight = segEnd;
                        segmentChosen = true;
                    }
                }
            }
        }

        // Update the search boundaries if a segment was chosen.
        if (segmentChosen) {
            left = newLeft;
            right = newRight;
        } else {
            // If no segment qualifies, we exit (x is not in the array).
            break;
        }
    }
    return foundIndex;
}

int main(int argc, char* argv[]) {
    srand(static_cast<unsigned int>(time(nullptr)));
    const int n = atoi(argv[1]);
    vector<int> data;

    // Generate random values.
    for (int i = 0; i < n; i++) {
        data.push_back(rand() % 100);
    }
    // Sort the array since binary search requires ordering.
    sort(data.begin(), data.end());

    // Pick a random target from the array for demonstration.
    int target = data[rand() % n];

    cout << "Ordered array:\n";
    for (int num : data)
        cout << num << " ";
    cout << "\nSearching for: " << target << "\n";

    int index = parallelBinarySearch(data, target);
    if (index != -1)
        cout << "Found at index " << index << endl;
    else
        cout << "Not found" << endl;

    return 0;
}
