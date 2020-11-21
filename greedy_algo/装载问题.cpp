#include<iostream>
#include<algorithm>
using namespace std;


#define N 10 // 古董数
#define LEN N+1


int main() {
    int c = 10; // 载重量
    int sum = N; // 装入古董的数量
    int tmp = 0; // 装入古董的重量
    int w[LEN] = {0,1,2,3,4,5,6,7,8,9,10};
    cout << "古董数：" << N << "\t载重量：" << c << endl;
    cout<< "每件古董的重量为：";
    for(int i=1; i<=N; i++) {
        printf("\t%d", w[i]);
    }
    cout << endl;
    sort(w+1, w+1+N);
    for(int i = 1; i <= N; ++i) {
        tmp += w[i];//这个要在if外面
        if(tmp >= c) {
            if(tmp == c) //最后一个能装进去
                sum = i;
            else
                sum = i-1;
            break;
        }
        //其余的情况是tmp<c,此时sum肯定等于n
    }
    cout << "最多装" << sum << "个货物上船" << endl;
    return 0;
}
