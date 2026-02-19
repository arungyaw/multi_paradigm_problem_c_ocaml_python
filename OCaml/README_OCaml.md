# OCaml Implementation (Functional)

## Description

This implementation calculates the mean, median, and mode of a list of
integers. It follows a functional programming approach using OCaml.

## What It Contains

-   Immutable list-based design
-   Parsing input using string operations
-   Use of higher-order functions such as `List.map`, `List.fold_left`,
    and `List.filter`
-   Sorting using `List.sort`
-   Mode computation using run-length grouping
-   Proper handling of invalid or empty input

## How to Compile

``` bash
ocamlc -o stats stats.ml
```

## How to Run

``` bash
./stats
```

Enter integers separated by spaces when prompted.

## License

Academic use only.
