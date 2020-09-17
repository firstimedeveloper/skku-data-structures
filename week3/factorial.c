#include <stdio.h>

int factorial(int num) {
    printf("recursive call for %d\n", num);

    if (num == 0) return 0;
    else {
        return num + factorial(num - 1);
    } 
}

int main() {
    int num = factorial(5);

    printf("%d\n", num);

    return 0;
}