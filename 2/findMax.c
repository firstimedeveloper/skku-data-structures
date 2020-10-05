#include <stdio.h>

int main() {
    int i = 0;
    int j = 0;

    int arr[4][3] = {{1,2,3}, {2,3,9}, {3,4,5}, {4,5,6}};

    int max = 0;
    for (i=0; i<4; i++) {
        for (j=0; j<3; j++) {
            if (arr[i][j] > max) {
                max = arr[i][j];
            }
        }
    }
    printf("max: %d\n", max);
}