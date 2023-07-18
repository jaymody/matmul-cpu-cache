#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int M = 1000, N = 2000, O = 3000;
    int *A = malloc(M * N * sizeof(int));
    int *B = malloc(N * O * sizeof(int));
    int *C;

    /* initialize A and B with random integers between 0 and 9 */
    srand(time(NULL));
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            A[i * M + j] = rand() % 10;

    for (int i = 0; i < N; i++)
        for (int j = 0; j < O; j++)
            B[i * N + j] = rand() % 10;

    clock_t start;
    double elapsed;

    /* slow matmul algorithm */
    start = clock();
    C = calloc(M * O, sizeof(int));
    for (int i = 0; i < M; i++)
        for (int j = 0; j < O; j++)
            for (int k = 0; k < N; k++)
                C[i * M + j] += A[i * M + k] * B[k * N + j];
    elapsed = (double)(clock() - start) / (double)(CLOCKS_PER_SEC);
    printf("Slow: %.3fs\n", elapsed);

    /* fast matmul algorithm */
    start = clock();
    C = calloc(M * O, sizeof(int));
    for (int i = 0; i < M; i++)
        for (int k = 0; k < N; k++)
            for (int j = 0; j < O; j++)
                C[i * M + j] += A[i * M + k] * B[k * N + j];
    elapsed = (double)(clock() - start) / (double)(CLOCKS_PER_SEC);
    printf("Fast: %.3fs\n", elapsed);
}
