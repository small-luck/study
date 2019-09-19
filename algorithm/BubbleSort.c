#include <stdio.h>

void BubbleSort(int data[], int len)
{
    int i, j;
    int temp;

    for (i = 0; i < len; i++) {
        for (j = i+1; j < len; j++) {
            if (data[i] > data[j]) {
                temp = data[i];
                data[i] = data[j];
                data[j] = temp;
            }
        }
    }
}

int main()
{
    int data[] = {20, 89, 2, 45, 33, -3};
    int i;
    BubbleSort(data, 6);
    for (i = 0; i < 6; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");
    return 0;
}

