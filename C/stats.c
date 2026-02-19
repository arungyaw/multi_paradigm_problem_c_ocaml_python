#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
  C (Procedural): Mean, Median, Mode for a list of integers.
  - Reads one line of space-separated integers from stdin.
  - Sorts the data.
  - Computes mean, median, and mode.
*/

#define MAX_LINE 4096

/* Comparator used by qsort (ascending order) */
static int cmp_ints(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;
    return (x > y) - (x < y);
}

/* Mean: average of all values */
static double mean(const int *a, int n)
{
    long long sum = 0;
    for (int i = 0; i < n; i++)
        sum += a[i];
    return (double)sum / (double)n;
}

/* Median computed after sorting the array */
static double median_after_sort(const int *a, int n)
{
    if (n % 2 == 1)
        return (double)a[n / 2];
    return ((double)a[n / 2 - 1] + (double)a[n / 2]) / 2.0;
}

int main(void)
{
    char line[MAX_LINE];

    printf("Enter integers separated by spaces:\n");
    if (!fgets(line, sizeof(line), stdin))
    {
        printf("Error: please enter at least one integer.\n");
        return 1;
    }

    /*
      Parsing:
      - Split the input line by whitespace (strtok).
      - Convert each token to an integer (strtol) and reject invalid tokens.
      - Store integers in a dynamically grown array (malloc/realloc).
    */
    int capacity = 16;
    int n = 0;
    int *a = (int *)malloc(sizeof(int) * capacity);
    if (!a)
    {
        fprintf(stderr, "Error: memory allocation failed.\n");
        return 1;
    }

    char *tok = strtok(line, " \t\r\n");
    while (tok != NULL)
    {
        char *end = NULL;
        long v = strtol(tok, &end, 10);

        if (end == tok || *end != '\0')
        {
            printf("Error: please enter at least one integer.\n");
            free(a);
            return 1;
        }

        if (n == capacity)
        {
            capacity *= 2;
            int *tmp = (int *)realloc(a, sizeof(int) * capacity);
            if (!tmp)
            {
                fprintf(stderr, "Error: memory allocation failed.\n");
                free(a);
                return 1;
            }
            a = tmp;
        }

        a[n++] = (int)v;
        tok = strtok(NULL, " \t\r\n");
    }

    if (n == 0)
    {
        printf("Error: please enter at least one integer.\n");
        free(a);
        return 1;
    }

    /* Sorting creates the ordering required for median and mode counting */
    qsort(a, n, sizeof(int), cmp_ints);

    double mu = mean(a, n);
    double med = median_after_sort(a, n);

    /*
      Mode:
      - After sorting, equal values are adjacent.
      - First pass finds the largest run length (max frequency).
      - If max frequency is 1, no value repeats, so the dataset has no mode.
      - Second pass prints all values whose run length equals max frequency.
    */
    int max_freq = 1;
    int curr_freq = 1;

    for (int i = 1; i < n; i++)
    {
        if (a[i] == a[i - 1])
        {
            curr_freq++;
        }
        else
        {
            if (curr_freq > max_freq)
                max_freq = curr_freq;
            curr_freq = 1;
        }
    }
    if (curr_freq > max_freq)
        max_freq = curr_freq;

    printf("Count: %d\n", n);
    printf("Mean: %.2f\n", mu);

    if (med == (double)((long long)med))
    {
        printf("Median: %lld\n", (long long)med);
    }
    else
    {
        printf("Median: %.2f\n", med);
    }

    if (max_freq == 1)
    {
        printf("Mode: None\n");
        free(a);
        return 0;
    }

    printf("Mode:");
    curr_freq = 1;
    for (int i = 1; i <= n; i++)
    {
        if (i < n && a[i] == a[i - 1])
        {
            curr_freq++;
        }
        else
        {
            if (curr_freq == max_freq)
            {
                printf(" %d", a[i - 1]);
            }
            curr_freq = 1;
        }
    }
    printf("\n");

    free(a);
    return 0;
}
