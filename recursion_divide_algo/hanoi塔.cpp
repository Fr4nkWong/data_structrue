#include <iostream>

int factoria(int);  // 阶乘递归算法
int factoria1(int);  // 阶乘非递归算法
int fibonacci(int);    // 斐波那契数列递归算法
int fibonacci1(int);    // 斐波那契数列非递归算法
void hanoi(int, char, char, char); // hanoi塔问题
int int_split(int, int); // 整数划分


int main(int argc, const char * argv[]) {
    // 阶乘
    printf("阶乘: \n");
    printf("%d\n", factoria(5));
    printf("%d\n", factoria1(5));
    // 斐波那契数列
    printf("斐波那契数: \n");
    printf("%d\n", fibonacci(10));
    printf("%d\n", fibonacci1(10));
    // hanoi塔问题
    printf("hanoi塔: \n");
    hanoi(3, 'A', 'B', 'C');
    // 整数划分
    printf("整数划分: \n");
    printf("%d\n", int_split(6, 6));
    return 0;
}


/**
    @param n   目标数
    @return 目标数的斐波那契值
*/
int factoria(int n) {
    if(n == 0) return 1;
    return n * factoria(n-1);
}


/**
    @param n   目标数
    @return 目标数的斐波那契值
*/
int factoria1(int n) {
    int factoria = n;
    for(int i=n-1; i>=0; i--) {
        if(i == 0) break;
        factoria = factoria * i;
    }
    return factoria;
}


/**
    @param n   目标数
    @return 斐波那契数
*/
int fibonacci(int n) {
    if(n<2) return 1;
    return fibonacci(n-1) + fibonacci(n-2);
}


/**
    @param n   目标数
    @return 斐波那契数
*/
int fibonacci1(int n) {
    if(n == 0 || n == 1) return 1;
    int prev = 1, fibonacci = 1;
    for(int i=2; i<=n; i++) {
        int temp = fibonacci;
        fibonacci = prev + fibonacci;
        prev = temp;
    }
    return fibonacci;
}

void move(int i, int x, int y) {
    static int count = 1;
    printf("第%d次：%d from %c ——> %c\n", count++, i , x , y);
}

/**
    @param n   目标数
    @param A   源柱
    @param B   目标柱
    @param C   辅助柱
 */
void hanoi(int n, char A, char B, char C) {
    if(n>0) {
        hanoi(n-1, A, C, B);
        move(n, A, C);
        hanoi(n-1, C, B, A);
    }
}


/**
   @param n   正整数
   @param m   最大加数的上界
   @return 整数划分的种类数
*/
int int_split(int n, int m) {
    if(n<1 || m<1) return 0;
    if(n==1 || m==1) return 1;
    if(n<m) return int_split(n, n);
    if(n==m) return int_split(n, m-1)+1;
    return int_split(n, m-1) + int_split(n-m, m);
}
