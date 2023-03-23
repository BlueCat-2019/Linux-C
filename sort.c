/* 常见的排序算法 
 * 传入参数: array[], 待排序的数组
 *           length, 排序的数组长度 
 * 返回值: void 
 */

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
        for(int j = i + 1; j < length - 1; j++)
        {
            if(array[j] < min)  /* 从第二个元素开始,逐一与第一个元素作比较 */
            {
                min = array[j];
                pos = j;
            }
        }
        array[i] = min;
        array[pos] = array[i];
    }
}

void select_sort_F(int array[], int length)
{
    int max, pos;
    for(int i = 0; i < length - 1; i++)
    {
        max = array[i];
        pos = i;
        for(int j = i + 1; j < length - 1; j++)
        {
            if(array[j] > max)
            {
                max = array[j];
                pos = j;
            }
        }
        array[i] = max;
        array[pos] = array[i];
    }
}