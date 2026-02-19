# C Implementation (Procedural)

## Description

This implementation calculates the mean, median, and mode of a list of
integers. It follows a procedural programming approach using C.

## What It Contains

-   Parsing of space-separated integers from standard input
-   Dynamic memory allocation (malloc, realloc, free)
-   Sorting using `qsort`
-   Mean calculation using iteration
-   Median calculation after sorting
-   Mode calculation using frequency counting on sorted data
-   Proper error handling for invalid or empty input

## How to Compile (WSL or Linux)

``` bash
gcc stats.c -o stats
```

## How to Run

``` bash
./stats
```

Enter integers separated by spaces when prompted.

## License

Academic Use only.
