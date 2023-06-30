Demonstration of matrix multiplication being 10x faster when you make sure to access the array row-wise so that cpu cache hits are maximizes.

```shell
$ gcc -O3 main1.c && ./a.out

Slow: 4.142s
Fast: 0.482s
```

```shell
$ gcc -O3 main2.c && ./a.out

Slow: 3.623s
Fast: 0.446s
```
