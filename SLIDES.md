
Faster matrix multiplication via CPU caches.

---

What is matrix multiplication?

---

$$
AB = C
$$

$$
\begin{bmatrix}
1 & 2 & 3\\
4 & 5 & 6
\end{bmatrix}
\begin{bmatrix}
5 & 1 \\
3 & 2 \\
6 & 4
\end{bmatrix}
=
\begin{bmatrix}
29 & 17 \\
71 & 38
\end{bmatrix}
$$

$$
C_{i,j} = \sum_k A_{i,k}B_{k,j}
$$

---

$$
\begin{bmatrix}
\color{Red}1 & \color{Red}2 & \color{Red}3\\
4 & 5 & 6
\end{bmatrix}
\begin{bmatrix}
\color{Red}5 & 1 \\
\color{Red}3 & 2 \\
\color{Red}6 & 4
\end{bmatrix}
=
\begin{bmatrix}
\color{Red}29 & 17 \\
71 & 38
\end{bmatrix}
$$

$$
1(5) + 2(3) + 3(6) = 29
$$

---
$$
\begin{bmatrix}
1 & 2 & 3\\
\color{Red} 4 & \color{Red} 5 & \color{Red} 6
\end{bmatrix}
\begin{bmatrix}
5 & \color{Red} 1 \\
3 & \color{Red} 2 \\
6 & \color{Red} 4
\end{bmatrix}
=
\begin{bmatrix}
29 & 17 \\
71 & \color{Red} 38
\end{bmatrix}
$$

$$
4(1) + 5(2) + 6(4) = 38
$$

---

Matrix multiplication is useful for a lot of things!

---

Computer graphics (i.e. rotating an object in 3D space)

![](https://upload.wikimedia.org/wikipedia/en/7/74/Cube_rotation.gif)

---

Neural networks (essentially just a series of matrix multiplications)

![](https://thumbs.gfycat.com/DeafeningComplicatedBluetonguelizard-size_restricted.gif)

---

Let's code it!

---

Setup:

```C
#include <stdio.h>
#include <stdlib.h>
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

    /* matrix algorithm here ... */
}
```

---

Initial implementation:

```C
for (int i = 0; i < M; i++) {
    for (int j = 0; j < O; j++) {
        C[i][j] = 0;
        for (int k = 0; k < N; k++)
            C[i][j] += A[i][k] * B[k][j];
    }
}
```

On my computer, this takes `4.142s`

---

Much faster implementation:

```C
for (int i = 0; i < M; i++) {
    for (int j = 0; j < O; j++)
        C[i][j] = 0;

    for (int k = 0; k < N; k++)
        for (int j = 0; j < O; j++)
            C[i][j] += A[i][k] * B[k][j];
}
```

---

This alternative algorithms takes `0.482s` on my computer.

That's almost 10x faster!!! What the hell is going on!

---
![](https://2018media.idtech.com/2021-05/computer-parts-diagram.png?f9a309a218)
The RAM is where our data is stored (i.e. our arrays).

The CPU is where instruction are executed on that data (i.e. add/multiply/increment).

---

**Problem:** Loading data from RAM (and storing it back into RAM) is super slow compared to executing an instruction (like addition)!!!

In the time it takes to **access data from RAM (100ns)**, your CPU could have executed 100s of instructions.

---

**Solution**: Modern computers have a special type of memory embedded directly onto the CPU called the **CPU Cache**, which only taking about **1ns** to access!

---

**Caveat 1**: While accessing the cache is much faster, there is a lot less of it (at best, a couple of MB, compared to the many GB of RAM).

---

**Caveat 2:** We don't get to _directly_ get to control what gets loaded into the cache. The CPU will automatically load _blocks_ of memory when you access memory at a given RAM address.

---

```
int matrix[4][3] = { {1, 4, 2}, {3, 6, 8}, {1, 2, 5}, {6, 3, 8}};
```

Hypothetically, your RAM might look like this:

| Address | 0 | 1 | ... | 300 | 301 | 302 | 303 | 304 | 305 | ... |
|-|-|-|-|-|-|-|-|-|-|-|
| Value |  |  |  | 1 | 4 | 2 | 3 | 6 | 8 | |

---

If you then access: `matrix[0][1]`, the cache would load address 301 to 304 (block size = 4).

| Cache | 4 | 2 | 3 | 6|
|-|-|-|-|-|

| Address | 0 | 1 | ... | 300 | 301 | 302 | 303 | 304 | 305 | ... |
|-|-|-|-|-|-|-|-|-|-|-|
| Value |  |  |  | 1 | **4** | **2** | **3** | **6** | 8 | |

---

So, if you then later access `matrix[0][2]` (which corresponds to address 302, which is in the cache), it will be super fast We call this a **cache hit**.

But if you try to access  `matrix[3][2]` (not in cache), it will be slow. We call this a **cache miss**.

---

**Takeaway**: When accessing arrays, it's best to access them row-wise, so we maximize cache hits.

---

```C
for (int i = 0; i < M; i++) {
    for (int j = 0; j < O; j++) {
        C[i][j] = 0;
        for (int k = 0; k < N; k++)
            C[i][j] += A[i][k] * B[k][j]; // BAD ❌!!! We are accessing B column-wise
    }
}
```

---

By swapping the two inner loops, we access B row-wise and maximize cache-hits.

```C
for (int i = 0; i < M; i++) {
    for (int j = 0; j < O; j++)
        C[i][j] = 0;

    for (int k = 0; k < N; k++)
        for (int j = 0; j < O; j++)
            C[i][j] += A[i][k] * B[k][j]; // GOOD ✅!!! We are accessing B row-wise
}
```
