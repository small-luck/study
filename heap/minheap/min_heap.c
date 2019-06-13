#include "min_heap.h"

void min_heap_insert(int * heap, int * n, int item)
{
    int i, parent; //i为当前节点，parent为i的父节点
    
    if ((*n) == HEAP_SIZE) {
        printf("head is full\n");
        return;
    }

    i = ++(*n);
    parent = i / 2;

    //如果堆的元素不止1个并且插入的值大于父节点的值
    while ((i > 1) && (item < heap[parent])) {
        heap[i] = heap[parent]; //父节点值下移
        i = parent; //把父节点作为当前节点
        parent /= 2;    //向上移动调整
    }
    heap[i] = item;
}

int min_heap_delete(int * heap, int * n)
{
    int item, temp;
    int child, parent;

    //若为空堆
    if (*n == 0) {
        printf("heap is empty\n");
        return -1;
    }

    item = heap[1]; //将最大堆的最大元素赋给item
    temp = heap[(*n)--];    //堆的最后节点关键字值
    parent = 1;
    child = 2 * parent;
    while (child <= (*n)) {
        if (child < *n && heap[child] > heap[child+1])
            child++;    //找出堆中最小关键字值的节点

        //把最大节点关键字值与最后节点关键字值比较
         if (temp <= heap[child])
            break;
         else {
            //若堆中存在比最后节点关键字值大的节点,则交换位置
            heap[parent] = heap[child];
            parent = child;
            child *= 2;
         }
    }    
    heap[parent] = temp;    //插入正确位置

    return item;
}


int main(int argc, char* argv[])
{
    int item, i;
    int n = 0;

    for (i = 1; i < HEAP_SIZE; i++) {
        scanf("%d", &item);
        min_heap_insert(heap, &n, item);
    }

    for (i = 1; i <= n; i++) {
        printf("%d ", heap[i]);
    }
    printf("\n");

    item = min_heap_delete(heap, &n);
    printf("the daleted data is: %d\n", item);

    for (i = 1; i <= n; i++) {
        printf("%d ", heap[i]);
    }
    printf("\n");

    return 0;
}