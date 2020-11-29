#include<stdio.h>


int knap_sack(int, int[], int[], int[], int);
int v_mat[200][200]; // 价值矩阵，前i个物品装入容量为j的背包中获得的最大价值


/*
 取最大值
 */
int max(int a, int b) {
   if(a>=b)
       return a;
   else return b;
}


int main() {
    int s; // 获得的最大价值
    int w[15]; // 物品的重量
    int v[15]; // 物品的价值
    int x[15]; // 物品的选取状态
    int n=5,i;
    int c; // 背包最大容量
    printf("请输入背包的最大容量:\n");
    scanf("%d", &c);
    printf("输入物品数:\n");
    scanf("%d", &n);
    printf("请分别输入物品的重量:\n");
    for(i=0; i<n; i++) scanf("%d", &w[i]);
    printf("请分别输入物品的价值:\n");
    for(i=0; i<n; i++) scanf("%d", &v[i]);
    s = knap_sack(n, w, v, x, c);
    printf("最大物品价值为:\n");
    printf("%d\n", s);
    return 0;
}
 

/*
 背包算法
 @param n - 物品数量
 @param w - 物品重量
 @param v - 物品价值
 @param x - 物品选择情况
 @param c - 背包容量
*/
int knap_sack(int n, int w[], int v[], int x[], int c) {
    int i,j;
    // 填表,其中第一行和第一列全为0
    for(i=0; i<=n; i++) v_mat[i][0]=0;
    for(j=0; j<=c; j++) v_mat[0][j]=0;
    for(i=1; i<=n; i++) {
        printf("\n----------------\n");
        printf("%d  %d  %d  ", i, w[i-1], v[i-1]);
        for(j=1;j<=c;j++) {
            if(j<w[i-1]) {
                v_mat[i][j]=v_mat[i-1][j];
                printf("[%d][%d]=%2d  ",i , j, v_mat[i][j]);
            } else {
                v_mat[i][j]=max(v_mat[i-1][j], v_mat[i-1][j-w[i-1]]+v[i-1]);
                printf("[%d][%d]=%2d  ", i, j, v_mat[i][j]);
            }
        }
        printf("\n----------------\n");
    }
    // 判断哪些物品被选中
    j=c;
    for(i=n; i>=1; i--) {
        if(v_mat[i][j]>v_mat[i-1][j]) {
            x[i]=1;
            j=j-w[i-1];
        } else {
            x[i]=0;
        }
    }
    printf("选中的物品是:\n");
    for(i=1; i<=n; i++) printf("%d ", x[i]);
    printf("\n");
    return v_mat[n][c];
}
