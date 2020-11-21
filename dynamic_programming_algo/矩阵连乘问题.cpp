
#include<iostream>
using namespace std;
 
const int N=7; // 矩阵的维度


/*
 @param p - 矩阵链，p[0],p[1]代表第一个矩阵的行数和列数，p[1],p[2]代表第二个矩阵的行数和列数...
 @param m - 存储最优结果的矩阵
 @param s - 存储选择最优结果路线的矩阵
 @param length - p的长度. 如果有六个矩阵，length=7
 */
void matrix_chain_oder(int *p, int m[N][N], int s[N][N], int length) {
    int n=length-1;
    int l,i,j,k,q=0;
    //m[i][i]只有一个矩阵，所以相乘次数为0，即m[i][i]=0;
    for(i=1;i<length;i++) {
        m[i][i]=0;
    }
    //l表示矩阵链的长度
    // l=2时，计算 m[i,i+1],i=1,2,...,n-1 (长度l=2的链的最小代价)
    for(l=2;l<=n;l++) {
        for(i=1;i<=n-l+1;i++) {
            j=i+l-1; //以i为起始位置，j为长度为l的链的末位，
            m[i][j]=0x7fffffff;
            //k从i到j-1,以k为位置划分
            for(k=i;k<=j-1;k++) {
                q=m[i][k]+m[k+1][j]+p[i-1]*p[k]*p[j];
                if(q<m[i][j]) {
                    m[i][j]=q;
                    s[i][j]=k;
                }
            }
        }
    }
    printf("%d\n", m[1][N-1]);
}


/*
 @param s - 存储选择最优结果路线的矩阵
 @param i - 矩阵下标
 @param j - 
 */
void print_answer(int s[N][N], int i, int j) {
    if(i==j) {
        printf("A%d", i);
    }
    else {
        printf("(");
        print_answer(s,i,s[i][j]);
        print_answer(s,s[i][j]+1,j);
        printf(")");
    }
}


//void print_arr(int arr[N][N], char *str) {
//    printf("\n%s", str);
//    for(int i=0; i<=N; i++) {
//        for(int j=0; j<N; j++) {
//            printf("%d\t", arr[i][j]);
//        }
//        printf("\n");
//    }
//}


int main() {
    int p[N]={30,35,15,5,10,20,25};
    int m[N][N],s[N][N];
    matrix_chain_oder(p,m,s,N);
    print_answer(s,1,N-1);
    printf("\n");
    return 0;
}
