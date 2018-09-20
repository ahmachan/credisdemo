#include <stdio.h>
#include "additionSubtraction.h"

// 实现减法
int sub(int a, int b)
{
    return a - b;
}

int add(int a, int b)
{
    return a + b;
}

//指针函数
int *appendCopy(int data[], int a[], int n)
{
    int i = 0;
    //for (int i = 0; i < n; i++)//定义变量，只能在C99标准里使用
    for (i = 0; i < n; i++)
    {
        int m = n--;
        a[i] = data[i]+m;
    }
    return a;
}

/*
double appendSum(double a[], int n)
{
    double sum = 0;
    for (int i = 0; i < n; i++)
        sum += a[i];
    return sum;
}
*/
