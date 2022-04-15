#include<stdio.h>
#include"mm.h"

int main()
{
    printf("mycalloc:\n");
    int **arr = mycalloc(2, sizeof(int*));
    for(int i = 0; i < 2; i++) {
        arr[i] = mycalloc(3, sizeof(int));
    }

    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 3; j++) {
            printf("%d ", arr[i][j]);
        }
        putchar('\n');
    }

    for(int i = 0; i < 2; i++) {
        myfree(arr[i]);
    }
    myfree(arr);



    printf("myrealloc\n");
    int size = 0;

    printf("陣列長度：");
    scanf("%d", &size);
    int *arr1 = mycalloc(size, sizeof(int));

    printf("指定元素：\n");
    for(int i = 0; i < size; i++) {
        printf("arr1[%d] = ", i);
        scanf("%d" , arr1 + i);
    }

    printf("顯示元素：\n");
    for(int i = 0; i < size; i++) {
        printf("arr1[%d] = %d\n", i, *(arr1 + i));
    }

    int *arr2 = myrealloc(arr1, sizeof(int) * size * 2);
    printf("顯示元素：\n");
    for(int i = 0; i < size * 2; i++) {
        printf("arr2[%d] = %d\n", i, *(arr2 + i));
    }

    printf("arr1 位址：%p\n", arr1);
    printf("arr2 位址：%p\n", arr2);

    myfree(arr2);

    return 0;
}
