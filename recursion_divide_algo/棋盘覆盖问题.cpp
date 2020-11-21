#include <iostream>
#include <math.h>

int binary_search(int[], int, int);  // 二分查找
int int_multiply(char*, char*, int, int); // 大整数乘法
void chess_board(int, int, int, int, int**, int); // 棋盘覆盖
int** init_board(int, int, int);
void print_board(int**, int);

# define SIZE 4 // 棋盘的长宽


int main(int argc, const char * argv[]) {
    // 二分查找
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int a_len = sizeof(a)/sizeof(int);
    int search = 8;
    printf("查找数%d的下标为：%d\n", search, binary_search(a, a_len, search));
    // 大整数乘法
    char x1[] = "100";
    char x2[] = "11";
    int x1_len = sizeof(x1)/sizeof(char);
    int x2_len = sizeof(x2)/sizeof(char);
    printf("\n大整数乘法: 按位分裂第二个乘数(十进制)\n%s*%s=%d\n", x1, x2, int_multiply(x1, x2, x1_len, x2_len));
    // 棋盘覆盖
    printf("\n棋盘覆盖：9为特殊格子\n");
    int dr=0, dc=1; // 特殊格子坐标(x,y)
    int** board = init_board(dr, dc, SIZE); // 初始化棋盘
    chess_board(0, 0, dr, dc, board, SIZE);
    return 0;
}


/**
    @param a   数组
    @param len   数组长度
    @param x   查找数
    @return 目标数的下标
*/
int binary_search(int a[], int len, int x) {
    int left = 0, right = len - 1;
    while(left <= right) {
        int mid = (left+right)/2;
        if(a[mid] == x) return mid;
        if(x < a[mid]) right = mid - 1;
        if(x > a[mid]) left = mid + 1;
    }
    return -1;
}


int get_int(char str[], int len) {
    int num = 0;
    for(int i=0; i<len-1; i++) {
        num += (str[i]-'0')*pow(10, len-2-i);
    }
    return num;
}
int *get_int_arr(char str[], int len) {
    int* arr = (int *)malloc(sizeof(int)*len);
    for(int i=0; i<len-1; i++) {
        arr[i] = str[i]-'0';
    }
    return arr;
}
/**
    @param str1 数1
    @param str2 数2
    @param len1 数1长度
    @param len2 数2长度
    @return 乘法结果
*/
int int_multiply(char* str1, char* str2, int len1, int len2) {
    int x1 = get_int(str1, len1);
    int* x2_arr = get_int_arr(str2, len2);
    int sum = 0;
    for(int i=0; i<len2-1; i++) {
        sum += (x1 * x2_arr[i])*pow(10, len2-2-i);
    }
    return sum;
}


void print_board(int** board, int size) {
    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            printf("%d\t", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
int** init_board(int dr, int dc, int size) {
    int** board = (int**)malloc(sizeof(int*)*size);
    for(int i=0; i<size; i++) {
        board[i] = (int*)malloc(sizeof(int)*size);
        for(int j=0; j<size; j++) {
            board[i][j] = 0;
        }
    }
    board[dr][dc] = 9;
    print_board(board, size);
    return board;
}
/**
    @param tr 棋盘基准的行号
    @param tc 棋盘基准的列号
    @param dr 特殊方格的行号
    @param dc 特殊方格的列号
    @param board 棋盘
    @param size 棋盘的长宽
*/
void chess_board(int tr, int tc, int dr, int dc, int** board, int size) {
    print_board(board, SIZE);
    if(size == 1) return;
    int s = size/2;
    if(dr<tr+s && dc<tc+s) { // 特殊方格在左上角子棋盘
        chess_board(tr, tc, dr, dc, board, s);
    } else {
        board[tr+s-1][tc+s-1] = 1;
        chess_board(tr, tc, tr+s-1, tc+s-1, board, s);
    }
    if(dr<tr+s && dc>=tc+s) { // 特殊方格在右上角子棋盘
        chess_board(tr, tc+s, dr, dc, board, s);
    } else {
        board[tr+s-1][tc+s] = 1;
        chess_board(tr, tc+s, tr+s-1, tc+s, board, s);
    }
    if(dr>=tr+s && dc<tc+s) { // 特殊方格在左下角子棋盘
        chess_board(tr+s, tc+s, dr, dc, board, s);
    } else {
        board[tr+s][tc+s-1] = 1;
        chess_board(tr+s, tc, dr, dc, board, s);
    }
    if(dr>=tr+s && dc>=tc+s) { // 特殊方格在右下角子棋盘
        chess_board(tr+s, tc+s, dr, dc, board, s);
    } else {
        board[tr+s][tc+s] = 1;
        chess_board(tr+s, tc+s, dr, dc, board, s);
    }
}
