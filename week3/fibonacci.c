#include <stdio.h>

int fibonacci(int level) {
    int num = 0;
    if (level == 1) {
        return 1;
    } else if (level == 2) {
        return 1;
    } else return fibonacci(level-1) + fibonacci(level-2);
    
}
// 5 + 4
// 1 2 3 4 5 6 7   8  9 10 11 12
// 1 1 2 3 5 8 13 21 34 55 89

int main() {
    int num = fibonacci(20);

    printf("%d\n", num);

    return 0;
}