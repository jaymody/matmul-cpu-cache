Demonstrating how to make matrix multiplication faster by taking advantage of the CPU cache.

`main1.c` contains an implementation that runs on statically allocated arrays.

`main2.c` contains an implementation that runs on dynamically allocated arrays.

```shell
$ gcc -O3 main1.c && ./a.out

Slow: 3.873s
Fast: 0.482s
```

```shell
$ gcc -O3 main2.c && ./a.out

Slow: 3.520s
Fast: 0.457s
```
