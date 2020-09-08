#include <stdio.h>

void multBy(int num, int *arrptr, int len) {
    for(int i=0; i<len; i++) {
        arrptr[i] = arrptr[i] * num;
    }
}

int main() {
    int a[5] = {1,2,3,4,5};
    int len = sizeof(a)/sizeof(a[0]);
    int num = 1;
    printf("Multiply by: ");
    scanf("%d", &num);
    multBy(num,a,len);
    for(int i=0; i<len; i++) {
        printf("%d\n", a[i]);
    }

    return 0;
}