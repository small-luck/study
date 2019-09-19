#include <stdio.h>

void quickSortEntry(int data[], int low, int high)
{
    if (low < high) {
        int middle = quickSort(data, low, high);

        //递归
        quickSortEntry(data, low, middle - 1);
        quickSortEntry(data, middle + 1, high);
    }
}

int quickSort(int data[], int low, int high) 
{
    //获取一个基准值
    int temp = data[low];

    while (low < high) {
        //先扫描后半部分，如果high所在的值大于基准值，将high--
        while (low < high && data[high] > temp)
            high--;
        //否则将high的值赋给low所在的位置
        data[low] = data[high];
        //再扫描前半部分，如果low所在的值小于基准值，将low++
        while (low < high && data[low] < temp)
            low++;
        //否则将low的值赋给high所在的位置
        data[high] = data[low];
    }
    //最后将基准值放在low或high的位置
    data[low] = temp;

    return low;
}

int main()
{
    int data[] = {20, 3, 10, 22, 100, 8, 78};
    int i;
    quickSortEntry(data, 0, 6);
    for (i = 0; i < 7; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");
    return 0;
}

