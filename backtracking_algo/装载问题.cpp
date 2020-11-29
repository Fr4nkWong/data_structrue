#include <iostream>
using namespace std;

int n; //集装箱数
int cw; // 当前载重量, current weight
int bestw; //最优载重重量
int r;  //剩余集装箱重量
int c1; //第一艘轮船的载重量
int c2; //第二艘轮船的载重量
int x[100]; //当前解
int bestx[100]; //当前最优解
int w[100]; //集装箱重量数组

void OutPut() {
    int restweight = 0;
    for(int i = 1; i <= n; ++i)
        if(bestx[i] == 0)
           restweight += w[i];
    if(restweight > c2) printf("不能装入\n");
    else {
        printf("船1装入的货物为:");
        for(int i = 1; i <= n; ++i)
            if(bestx[i] == 1) printf(" %d", i);
        printf("\n船2装入的货物为:");
        for(int i = 1; i <= n; ++i)
            if(bestx[i] != 1) printf(" %d", i);
        printf("\n");
    }
}


void BackTrack(int i) {
    if(i > n) {
        if(cw > bestw) {
            for(int i = 1; i <= n; ++i) bestx[i] = x[i];
            bestw = cw;
        }
        return;
    }
    r -= w[i];
    if(cw + w[i] <= c1) { //约束条件
        cw += w[i];
        x[i] = 1;
        BackTrack(i + 1);
        x[i] = 0;
        cw -= w[i];
    }
    if(cw + r > bestw) { //限界函数
        x[i] = 0;
        BackTrack(i + 1);
    }
    r += w[i];
 
}


void Initialize() {
    bestw = 0;
    r = 0;
    cw = 0;
    for(int i = 1; i <= n; ++i)
        r += w[i];
}


void InPut() {
    printf("2艘货船的载重量:\n");
    scanf("%d %d", &c1, &c2);
    printf("输入货物数量:\n");
    scanf("%d", &n);
    printf("依次输入%d个货物重量:\n", n);
    for(int i = 1; i <= n; ++i)
        scanf("%d", &w[i]);
}


int main()
{
    InPut();
    Initialize();
    BackTrack(1);
    OutPut();
}
