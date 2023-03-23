/* 常见的排序算法 
 * 传入参数: array[], 待排序的数组
 *           length, 排序的数组长度 
 * 返回值: void 
 * T: 升序, F 降序
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/* 显示数组元素 */
void show_array(int *array, int length)
{
    for(int i = 0; i < length; i++)
        printf("%d ", array[i]);
    puts("");
}

/* 交两个元素的值 */
void swap(int* first, int* second)
{
    int temp = *first;
    *first = *second;
    *second = temp;
}
/**
 * 1、选择排序法 
 * 选择排序法是, 在长度为N的数组中经过N - 1轮排序,
 * 将数据从大到小,或从小到大进行排序, 每一轮都选择
 * 一个最大值,或最小值与给定的值进行比较交换。
*/
void select_sort_T(int array[], int length)
{
    int min, pos;
    for(int i = 0; i < length - 1; i++)
    {
        min = array[i]; /* 假定第一元素为最小值 */
        pos = i;
        for(int j = i + 1; j < length; j++)
        {
            if(array[j] < min)  /* 从第二个元素开始,逐一与第一个元素作比较 */
            {
                min = array[j];
                pos = j;
            }
        }
        array[pos] = array[i];
        array[i] = min;
        show_array(array,length);
    }
}

void select_sort_F(int array[], int length)
{
    int max, pos;
    for(int i = 0; i < length - 1; i++)
    {
        max = array[i];
        pos = i;
        for(int j = i + 1; j < length; j++)
        {
            if(array[j] > max)
            {
                max = array[j];
                pos = j;
            }
        }
        array[pos] = array[i];
        array[i] = max;
        show_array(array,length);
    }
}

/**
 *  冒泡排序法
 *  冒泡排序法, 是将N个数据中每两个数据逐一比较,
 * 将最大值或最小值向后交换,每一轮都将一个最值,
 *  交换到最后 
 **/

void bubble_sort_T(int array[], int length)
{
    int temp;
    for(int i = 0; i < length - 1; i++)
    {
        for(int j = 0; j < length - i - 1; j++)
        {
            if(array[j] > array[j + 1])
            {
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
        show_array(array,length);
    }
}

void bubble_sort_F(int array[], int length)
{
    int temp;
    for(int i = 0; i < length - 1; i++)
    {
        for(int j = 0; j < length - i - 1; j++)
        {
            if(array[j] < array[j + 1])
            {
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
        show_array(array,length);
    }
}

void bubbleSort(int array[], int length)
{
    bool is_sorted = false;
    while(!is_sorted)
    {
        is_sorted = true;
        for(int i = 0; i < length - 1; i++)
        {
            if(array[i] > array[i + 1])
            {
                int temp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = temp;
                is_sorted = false;
            }
        }
    }   
}

void bubble_sort(int array[], int length)
{
    if (length == 1)
        return;
    bool swapped = false;
    for(int i = 0; i < length - 1; i++)
    {
        if(array[i] > array[i + 1])
        {
            int temp = array[i];
            array[i] = array[i + 1];
            array[i + 1] = temp;
            swapped = true;
        }
    }
    if(swapped)
        bubble_sort(array, length - 1);
}


/* 交换排序法 */

void transfer_sort_T(int array[], int length)
{
    int temp;
    for(int i = 0; i < length - 1; i++)
    {
        for(int j = i + 1; j < length; j++)
        {
            if(array[i] > array[j])
            {
                temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
        show_array(array,length);
    }
}

void transfer_sort_F(int array[], int length)
{
    int temp;
    for(int i = 0; i < length - 1; i++)
    {
        for(int j = i + 1; j < length; j++)
        {
            if(array[i] < array[j])
            {
                temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
        show_array(array,length);
    }
}


/* 插入排序法 */
void insert_sort_T(int array[], int length)
{
    int temp;
    int pos;
    for(int i = 1; i < length; i++)
    {
        temp = array[i];
        pos = i - 1;
        while((pos >= 0) && (temp < array[pos]))
        {
            array[pos + 1] = array[pos];
            pos--;
        }
        array[pos + 1] = temp;
        show_array(array,length);
    }
}

void insert_sort_F(int array[], int length)
{
    int temp;
    int pos;
    for(int i = 1; i < length; i++)
    {
        temp = array[i];
        pos = i - 1;
        while((pos >= 0) && (temp > array[pos]))
        {
            array[pos + 1] = array[pos];
            pos--;
        }
        array[pos + 1] = temp;
        show_array(array,length);
    }
}

/* 折半排序法 */
void reduce_sort_T(int array[], int left, int right)
{
    int length = 10;
    int middle, temp;
    int i = left, j = right;
    middle = array[(left + right) / 2];/* 求中间元素的值 */
    do {
        while(array[i] < middle && i < right)
        i++;
        while(array[j] > middle && j > left)
        j--;
        if(i <= j)
        {
            temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            i++,j--;
        }
    }while(i <= j); /* i <= j 结束 */

    if(left < j)
        reduce_sort_T(array,left, j);
    if(right > i)
        reduce_sort_T(array,i, right); 
    show_array(array,length);  
}

void reduce_sort_F(int array[], int left, int right)
{
    int length = 10;
    int middle, temp;
    int i = left, j = right;
    middle = array[(left + right) / 2];/* 求中间元素的值 */
    do {
        while(array[i] > middle && i < right)
        i++;
        while(array[j] < middle && j > left)
        j--;
        if(i <= j)
        {
            temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            i++,j--;
        }
    }while(i <= j); /* i <= j 结束 */

    if(left < j)
        reduce_sort_F(array,left, j);
    if(right > i)
        reduce_sort_F(array,i, right);
    show_array(array,length);
}


/* test for sort */
void select_sort_test(int arr[], int length)
{
    int array[length];
    memcpy(array,arr,4 *length); 
    printf("排序前的数组: \n");
    show_array(array, length);
    printf("升序排序过程(selcet sort):\n");
    select_sort_T(array, length);
    printf("排序后的数组(selcet sort):\n");
    show_array(array, length);

    memcpy(array,arr,4 *length); 
    printf("排序前的数组: \n");
    show_array(array, length);
    printf("降序排序过程(selcet sort):\n");
    select_sort_F(array, length);
    printf("排序后的数组(selcet sort):\n");
    show_array(array, length);
}

void bubble_sort_test(int arr[], int length)
{
    int array[length];
    memcpy(array,arr,4 *length);
    printf("排序前的数组: \n");
    show_array(array, length);
    printf("升序排序过程(buble sort):\n");
    bubble_sort_T(array, length);
    printf("排序后的数组(buble sort):\n");
    show_array(array, length);

    memcpy(array,arr,4 *length);
    printf("排序前的数组: \n");
    show_array(array, length);
    printf("降序排序过程(buble sort):\n");
    bubble_sort_F(array, length);
    printf("排序后的数组(buble sort):\n");
    show_array(array, length); 
}

void transfer_sort_test(int arr[], int length)
{
    int array[length];
    memcpy(array,arr,4 *length);
    printf("排序前的数组: \n");
    show_array(array, length);
    printf("升序排序过程(transfer sort):\n");
    transfer_sort_T(array, length);
    printf("排序后的数组(transfer sort):\n");
    show_array(array, length);

    memcpy(array,arr,4 *length);
    printf("排序前的数组: \n");
    show_array(array, length);
    printf("降序排序过程(transfer sort):\n");
    transfer_sort_F(array, length);
    printf("排序后的数组(transfer sort):\n");
    show_array(array, length); 
}

void insert_sort_test(int arr[], int length)
{
    int array[length];
    memcpy(array,arr,4 *length);
    printf("排序前的数组: \n");
    show_array(array, length);
    printf("升序排序过程(insert sort):\n");
    insert_sort_T(array, length);
    printf("排序后的数组(insert sort):\n");
    show_array(array, length);

    memcpy(array,arr,4 *length);
    printf("排序前的数组: \n");
    show_array(array, length);
    printf("降序排序过程(insert sort):\n");
    insert_sort_F(array, length);
    printf("排序后的数组(insert sort):\n");
    show_array(array, length); 
}

void reduce_sort_test(int arr[], int left, int right, int length)
{
    int array[length];
    memcpy(array,arr,4 *length);
    printf("排序前的数组: \n");
    show_array(array, length);
    printf("升序排序过程(reduce sort):\n");
    reduce_sort_T(array, left, right);
    printf("排序后的数组(reduce sort):\n");
    show_array(array, length);

    memcpy(array,arr,4 *length);
    printf("排序前的数组: \n");
    show_array(array, length);
    printf("降序排序过程(reduce sort):\n");
    reduce_sort_F(array, left, right);
    printf("排序后的数组(reduce sort):\n");
    show_array(array, length); 
}


int main(int argc, char* argv[])
{
    int array[10] = {3, 6, 4, 1, 7, 2, 9, 8, 0, 5};
    puts("\n=================================");
    int length = sizeof(array) / sizeof(int);
    select_sort_test(array, length);
    puts("\n=================================");
    bubble_sort_test(array, length);
    puts("\n=================================");
    transfer_sort_test(array, length);
    puts("\n=================================");
    insert_sort_test(array, length);
    puts("\n=================================");
    reduce_sort_test(array, 0, 9, length);
    return 0;
}