#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;

// Sorts the 'row'-th row of M in ascending order if ascending is true,
// or in descending order if ascending is false.
void sortRow(vector<vector<int>>& M, int row, bool ascending) {
    if (ascending) {
        sort(M[row].begin(), M[row].end());
    } else {
        sort(M[row].begin(), M[row].end(), greater<int>());
    }
}

// Transposes an n x n matrix M in-place.
void transpose(vector<vector<int>>& M) {
    int n = M.size();
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            swap(M[i][j], M[j][i]);
        }
    }
}

// Performs the alternative Shearsort on the n x n matrix M using transposition.
void alternativeShearSort(int n, vector<vector<int>>& M) {
    // Determine number of iterations: ceil(log2(n)) + 1.
    int iterations = ceil(log2(n)) + 1;
    
    for (int iter = 0; iter < iterations; ++iter) {
        // Step 1: Sort rows in alternating order.
        for (int row = 0; row < n; ++row) {
            // Even-indexed row: ascending, odd-indexed: descending.
            sortRow(M, row, (row % 2 == 0));
        }
        
        // Step 2: Transpose the matrix.
        transpose(M);
        
        // Step 3: Sort all rows in ascending order.
        for (int row = 0; row < n; ++row) {
            sortRow(M, row, true);
        }
        
        // Step 4: Transpose the matrix back to original orientation.
        transpose(M);
    }
}

// Utility function to print the matrix.
void printMatrix(const vector<vector<int>>& M) {
    for (const auto& row : M) {
        for (int num : row) {
            cout << num << "\t";
        }
        cout << "\n";
    }
}

int main(int argc, char* argv[]) {
    srand(static_cast<unsigned int>(time(0)));  // Seed random number generator
    
    int n = atoi(argv[1]);
    
    // Create an n x n matrix and fill it with random values between 0 and 99.
    vector<vector<int>> matrix(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matrix[i][j] = rand() % 100;
        }
    }
    
    cout << "\nOriginal Matrix:\n";
    printMatrix(matrix);
    
    // Perform the alternative Shearsort.
    alternativeShearSort(n, matrix);
    
    cout << "\nSorted Matrix (Alternative Shearsort):\n";
    printMatrix(matrix);
    
    return 0;
}
