#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const int M = 1000, N = 2000, O = 3000;
static int A[M][N], B[N][O], C[M][O];

int main() {
    /* set random number generator seed */
    srand(time(NULL));

    /* initialize A and B with random integers between 0 and 9 */
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            A[i][j] = rand() % 10;

    for (int i = 0; i < N; i++)
        for (int j = 0; j < O; j++)
            B[i][j] = rand() % 10;

    /* slow matmul algorithm */
    clock_t start = clock();
    memset(C, 0, M * O);
    for (int i = 0; i < M; i++)
        for (int j = 0; j < O; j++)
            for (int k = 0; k < N; k++)
                C[i][j] += A[i][k] * B[k][j];
    double elapsed = (double)(clock() - start) / (double)(CLOCKS_PER_SEC);
    printf("Slow: %.3fs\n", elapsed);

    /* fast matmul algorithm */
    start = clock();
    memset(C, 0, M * O);
    for (int i = 0; i < M; i++)
        for (int k = 0; k < N; k++)
            for (int j = 0; j < O; j++)
                C[i][j] += A[i][k] * B[k][j];
    elapsed = (double)(clock() - start) / (double)(CLOCKS_PER_SEC);
    printf("Fast: %.3fs\n", elapsed);
}
