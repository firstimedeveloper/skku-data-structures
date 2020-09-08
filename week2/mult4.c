#include <stdio.h>

void mult4(int *arrptr, int len);

int main() {
    int a[5] = {1,2,3,4,5};
    int len = sizeof(a)/sizeof(a[0]);
    printf("Before: ") ;
    for(int i=0; i<len; i++) {
        printf("%d ", a[i]);
    }

    mult4(a, len);
    printf("\nAfter: ");
    for(int i=0; i<len; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    return 0;
}

void mult4(int *arrptr, int len) {
    for(int i=0; i<len; i++) {
        *(arrptr+i) = *(arrptr+i)*4;
    }
}