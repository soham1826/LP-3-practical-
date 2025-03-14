#include <bits/stdc++.h> // C++ Program to multiply two matrices using threads
using namespace std; 

// Maximum size of matrix
#define MAX 4 

// Maximum number of threads
#define MAX_THREAD 4 

int matA[MAX][MAX];
int matB[MAX][MAX];
int matC[MAX][MAX];

// Step index for the thread (to keep track of row to be multiplied)
int step_i = 0;

// Function to perform matrix multiplication for a part of the matrix
void* multi(void* arg) {
    int i = step_i++; // i denotes the row number of the resultant matC

    for (int j = 0; j < MAX; j++) {
        for (int k = 0; k < MAX; k++) {
            matC[i][j] += matA[i][k] * matB[k][j];
        }
    }

    return NULL;
}

// Driver Code
int main() {
    // Generating random values in matA and matB
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            matA[i][j] = rand() % 10; 
            matB[i][j] = rand() % 10; 
        }
    }

    // Displaying matA
    cout << endl << "Matrix A" << endl;
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++)
            cout << matA[i][j] << " "; 
        cout << endl; 
    }

    // Displaying matB
    cout << endl << "Matrix B" << endl;
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++)
            cout << matB[i][j] << " "; 
        cout << endl; 
    }

    // Declaring four threads
    pthread_t threads[MAX_THREAD];

    // Creating four threads, each evaluating its own part of the result matrix
    for (int i = 0; i < MAX_THREAD; i++) {
        pthread_create(&threads[i], NULL, multi, (void*)NULL);
    }

    // Joining and waiting for all threads to complete
    for (int i = 0; i < MAX_THREAD; i++) {
        pthread_join(threads[i], NULL);
    }

    // Displaying the result matrix
    cout << endl << "Multiplication of A and B" << endl;
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++)
            cout << matC[i][j] << " ";
        cout << endl; 
    }

    return 0;
}
