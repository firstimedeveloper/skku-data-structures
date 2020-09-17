#include <stdio.h>

void binary(int num) {
    if (num == 0)
        return;
    else {
        binary(num/2);
        printf("%d", num % 2);
    }
}
// 5 / 2 = 2
// 4 / 2 = 2
// 2 / 2 = 0
// 5 / 2 = 1
// (5%2) == 1
// 5-(5%2)

// 0 1  2  3   4   5   6   7    8    9   10
// 0 1 10 11 100 101 110 111 1000 1001 1010
int main() {
    binary(109);


    return 0;
}