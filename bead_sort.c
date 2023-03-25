#include <stdio.h>
#include <stdlib.h>

/** Create easy access of elements from a 2D matrix stored in memory as a 1D
 * array
 */
#define BEAD(i, j) beads[i * max + j]

/**
 * Displays the array, passed to this method
 * @param [in] arr array to display
 * @param [in] n number of elements in the array
 */
void display(const int *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\n");
}

/** This is where the sorting of the array takes place
 * @param [in,out] a array to be sorted
 * @param [in] len Array Size
 */
void bead_sort(int *a, size_t len)
{
    int i, j, max, sum;
    unsigned char *beads;

    /* 找出数组中最大的元素 */
    for (i = 1, max = a[0]; i < len; i++)
        if (a[i] > max)
            max = a[i];

    /* 以最大元素为列,申请二维数组空间 */
    beads = calloc(1, max * len);

    /* mark the beads */
    for (i = 0; i < len; i++)
        for (j = 0; j < a[i]; j++) BEAD(i, j) = 1; /* 根据数组元素的值初始化每一列: 例如, a[i] = 5,那么i行有5个连续的 1 */

    for (j = 0; j < max; j++)
    {
        /* count how many beads are on each post */
        for (sum = i = 0; i < len; i++)
        {
            sum += BEAD(i, j);  /* 每列的元素和 */
            BEAD(i, j) = 0;     /* 每列元素清0 */
        }
        /* mark bottom sum beads */
        for (i = len - sum; i < len; i++) BEAD(i, j) = 1; /* 每列元素从 总行数-sum 开始置 1 */
    }

    for (i = 0; i < len; i++)
    {
        for (j = 0; j < max && BEAD(i, j); j++)     /* 数数,数每行连续为1的个数 */
            ;
        a[i] = j;
    }
    free(beads);
}
/** @} */

/** Main function */
int main(int argc, const char *argv[])
{
    int n;
    printf("Enter size of array:\n");
    scanf("%d", &n);  // E.g. 8 1 2 3

    printf("Enter the elements of the array\n");
    int i;
    int *arr = (int *)malloc(n * sizeof(int));
    for (i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    printf("Original array: ");
    display(arr, n);

    bead_sort(arr, n);

    printf("Sorted array: ");
    display(arr, n);

    free(arr);
    return 0;
}
