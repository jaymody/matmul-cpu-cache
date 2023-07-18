Demonstrating how to make matrix multiplication faster by taking advantage of the CPU cache.

`main1.c` contains an implementation that runs on statically allocated arrays.

`main2.c` contains an implementation that runs on dynamically allocated arrays.

```shell
$ gcc -O2 main1.c && ./a.out

Slow: 4.034s
Fast: 0.469s
```

```shell
$ gcc -O2 main2.c && ./a.out

Slow: 3.566s
Fast: 0.445s
```
