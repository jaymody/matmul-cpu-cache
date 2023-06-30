/* Making matrix multiplication 10x faster by making it cache-aware.

$ gcc -O3 main2.c && ./a.out

Slow: 4.142s
Fast: 0.482s
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *slow_matrix_multiplication(int *A, int *B, int M, int N, int O) {
    int *C = malloc(M * O * sizeof(int));
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < O; j++) {
            C[i * M + j] = 0;
            for (int k = 0; k < N; k++) {
                C[i * M + j] += A[i * M + k] * B[k * N + j];
            }
        }
    }
    return C;
}
int *fast_matrix_multiplication(int *A, int *B, int M, int N, int O) {
    int *C = malloc(M * O * sizeof(int));
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < O; j++)
            C[i * M + j] = 0;
        for (int k = 0; k < N; k++)
            for (int j = 0; j < O; j++)
                C[i * M + j] += A[i * M + k] * B[k * N + j];
    }
    return C;
}

int main() {
    /* set random number generator seed */
    srand(time(NULL));

    /* initialize A and B with random integers between 0 and 9 */
    int M = 1000, N = 2000, O = 3000;
    int *A = malloc(M * N * sizeof(int));
    int *B = malloc(N * O * sizeof(int));

    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            A[i * M + j] = rand() % 10;

    for (int i = 0; i < N; i++)
        for (int j = 0; j < O; j++)
            B[i * N + j] = rand() % 10;

    clock_t start;
    double elapsed;

    start = clock();
    int *C1 = slow_matrix_multiplication(A, B, M, N, O);
    elapsed = (double)(clock() - start) / (double)(CLOCKS_PER_SEC);
    printf("Slow: %.3fs\n", elapsed);

    start = clock();
    int *C2 = fast_matrix_multiplication(A, B, M, N, O);
    elapsed = (double)(clock() - start) / (double)(CLOCKS_PER_SEC);
    printf("Fast: %.3fs\n", elapsed);

    for (int i = 0; i < M * O; i++) {
        assert(C1[i] == C2[i]);
    }
}
