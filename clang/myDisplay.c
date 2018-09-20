#include <string.h>
#include "myDisplay.h"
#include "additionSubtraction.h"

//显示计算结果
void dispResult(int x,int y){
    int s = add(x, y);
    printf("%d+%d=%d\n",x,y,s);
    s=sub(x, y);
    printf("%d-%d=%d\n",x,y,s);

    char str1[]="abc";    
    char str2[4]="abc";//C语言编译器会在字符串末尾补上'\0'作为空值得标志，其也独占一字符
    if(strcmp(str1,str2)){
       printf("%s == %s \n",str1,str2);
    }else{
        printf("%s != %s\n",str1,str2);
    }

    //C语言没有字符数组么?怎么与C字符串区分呢？
    //请注意：char string1 [3]={‘a','b','c'};此string1后面不会有'\0'标志的，所以不能说C字符串变量。
    char str3[3]={'a','b','c'};
    if(strcmp(str1,str3)){
       printf("%s == %s \n",str1,str3);
    }else{
       printf("%s != %s \n",str1,str3);
    }

    int clen = 4;
    int ca[4];//ca[4]
    int carr[] = {3, 5, 7 ,8};
    int *p;
    p = appendCopy(carr, ca, clen);
    printf("%d,%d,%d,%d \n",p[0],p[1],p[2],p[3]);

    //printf("sum is:%d",apppendSum(carr));
}