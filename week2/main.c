#include <stdio.h>

int main() {
    int a[6] = {5, 3, 11, 2, 4, 6};
    int *pend = a+6;
    // int *pi = NULL;
    int *psmallest = a;

    for (int *pi=a+1; pi<pend; pi++) {
        if (*pi < *psmallest) {
            psmallest = pi;
        }
    }
    printf("smallest number: %d\n", *psmallest);
    return 0;
}