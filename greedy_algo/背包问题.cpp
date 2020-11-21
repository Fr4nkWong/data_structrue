#include "stdio.h"
#include "stdlib.h"
#define N 5 /*定义需要放的物件数量*/
#define PSIZE 150 /*定义背包大小*/
 
long item[N]={15,40,50,60,90};/*初始化物件数组，贪心算法要求大小已排序*/
int freespace[N]={0};
 

int classic() {/*经典算法*/
long size = PSIZE;
long used = 0;
int i;
 for(i = N - 1 ; i >= 0 ; i--){
  if((size - used) >= item[i]){/*大小可以放入吗？*/
   used += item[i]; /*放入背包 已使用数加新物件的大小*/
   freespace[i] = 1;
  }
   else { /*大小太大*/
  freespace[i] = 0;
  }
 }/*for*/
 return 1;
}

 
int greedy(){/*贪婪算法*/
int i;
long size = PSIZE;
long used = 0;
for(i = N - 1 ; i >= 0 ; i--){/*先放大的物体，再考虑小的物体*/
 if( (used + item[i]) <= size){/*如果当前物体可以放入*/
  freespace[i] = 1;/*1表示放入*/
  used += item[i];/*背包剩余容量减少*/
 }
 else{
  freespace[i]=0;
 }
}/*for*/
if(size == used)/*返回*/
 return 1;
else
 return 0;
}


int main() {
    int i;/*计数器*/
    printf("\n贪心算法\n");
    if(greedy() == 1) {/*经典算法*/
        printf("结果:\t");
        for(i=0; i<N; i++) {/*输出*/
            if(freespace[i] == 1) {
                if(i % 5 == 0) printf("\n");
                printf("%10ld" , item[i]);
            }
        }
    } else {
        printf("\nNo Result\n");
    }
    printf("\n");
    return 0;
}
