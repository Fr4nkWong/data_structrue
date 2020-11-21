
#include<iostream>
using namespace std;

void lcs_length(int, int, char*, char*, int**, int**);
void lcs(int, int, char*, int**);
int** create_matrix(int, int);


void print_matrix(int** arr, int m, int n) {
    for(int i=0; i<=m; i++) {
        for(int j=0; j<=n; j++) {
            printf("%d\t", arr[i][j]);
        }
        printf("\n");
    }
}


int main() {
    int x_len=7, y_len=6;
    char x_arr[] = "ABCBDAB";
    char y_arr[]= "BDCABA";
    int** c_mat = create_matrix(x_len, y_len); // (y+1)*(x+1)
    int** b_mat = create_matrix(x_len, y_len);
    lcs_length(x_len, y_len, x_arr, y_arr, c_mat, b_mat);
    printf("X列排列:'%s', Y行排列:'%s'\n", x_arr, y_arr);
    printf("长度矩阵:\n");
    print_matrix(c_mat, x_len, y_len); // m*n
    int max_len = c_mat[x_len][y_len];
    printf("最长公共子序列的长度: %d\n", max_len);
    printf("问题编号矩阵:\n");
    print_matrix(b_mat, x_len, y_len);
    printf("最长公共子序列为:\n");
    for(int i=x_len; i>0; i--) {
        int flag = 0;
        for(int j=y_len; j>0; j--) {
            if(c_mat[i][j] == max_len) { // 距离矩阵中寻找所有长度为最大值的点
                lcs(i, j, x_arr, b_mat);
                flag = 1;
                printf("\n-------------\n");
            }
        }
        if(!flag) break;
    }
//    lcs(x_len, y_len, x_arr, b_mat);
    printf("\n");
    return 0;
}


/*
 计算最优解序列的长度
 @param m - 行长=X序列的长度+1
 @param n - 列长=Y序列的长度+1
 @param x - X序列
 @param y - Y序列
 @param c_mat - c_mat[i][j]存储x[i]和y[j]的最长公共子序列的长度
 @param b_mat - b_mat[i][j]记录c[i][i]的值是由哪个子问题的解得到的
 */
void lcs_length(int m, int n, char* x, char* y, int** c_mat, int** b_mat) {
    for(int i=1; i<=m; i++) { // 遍历X
        for(int j=1; j<=n; j++) { // 遍历Y
            if(x[i-1] == y[j-1]) { // 去右下
                c_mat[i][j] = c_mat[i-1][j-1]+1;
                b_mat[i][j] = 1;
            } else if(c_mat[i-1][j] >= c_mat[i][j-1]) { // 去下
                c_mat[i][j] = c_mat[i-1][j];
                b_mat[i][j] = 2;
            } else { // 去右
                c_mat[i][j] = c_mat[i][j-1];
                b_mat[i][j] = 3;
            }
        }
    }
}


/*
 构造公共最长子序列
 @param i - 行下标，x[i]
 @param j - 列下标，y[j]
 @param x - X序列
 @param b_mat - b_mat[i][j]记录c_mat[i][i]的值是由哪个子问题解出的
 */
void lcs(int i, int j, char* x, int** b_mat) {
    if(i==0 || j==0) return;
    if(b_mat[i][j] == 1) {
        printf("b:%d 回左上 (%d,%d) %c\n", b_mat[i][j],i, j, x[i-1]);
        lcs(i-1, j-1, x, b_mat);
        printf("%c", x[i-1]);
    } else if(b_mat[i][j] == 2) {
        printf("b:%d 回上 (%d,%d)\n", b_mat[i][j], i, j);
        // lcs(i, j-1, x, b_mat);
        lcs(i-1, j, x, b_mat);
    } else {
        printf("b:%d 回左 (%d,%d)\n", b_mat[i][j], i, j);
        // lcs(i-1, j, x, b_mat);
        lcs(i, j-1, x, b_mat);
    }
}


/*
 创建矩阵
 @param m - 行数，X元素的个数
 @param n - 列数，Y元素的个数
 */
int** create_matrix(int m, int n) {
    int** matrix = (int **)malloc(sizeof(int *) * m+1); // 行有m+1个
    for(int i=0; i<=m; i++) {
        matrix[i] = (int *)malloc(sizeof(int) * n+1); // 列有n+1个
        for(int j=0; j<=n; j++) {
            matrix[i][j] = 0;
        }
    }
    return matrix;
}
