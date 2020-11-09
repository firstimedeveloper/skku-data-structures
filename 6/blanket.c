#include <stdio.h>
#include <string.h>


#define MAX 10000000

// idea:
// No. fold (n) |  string
// 1             ^
// 2           V ^ ^
// 3         VV^ ^ V^^
// 4     ^^VV^VV ^ VV^^V^^
// ...
// The middle ^ doesn't change, but you can see
// that n == the right side of n+1
// and that fliped(n) == left side of n+1
// The above would be the answers for when the first digit of the input
// is 1 (the second picture) but the same applies for when the digit == 0.
// The above can be implemented iteratively or recursively.

char* flip(char *str) {
    // i starts at (index==strlen-1) since 
    // we have to flip the strip horizonatally and vertically
    char newStr[MAX];
    int idx=0;
    for (int i=strlen(str)-1; i>0; i--) {
        if (str[i] == 'V')
            //printf("^");
            newStr[idx] = '^';
        else 
            //printf("V");
            newStr[idx] = 'V';
        idx++;
    }
    return newStr;
}

void fold(char *str, int num, int orient) {
    if (num ==)
}

int main() {
    // The names up and down are chosen as 
    // they look like arrows pointing up or down.
    char down = 'V'; // starting char for when orientation == 0
    char up = '^'; // starting char for when orientation == 1
    
    int orientation, folds; // first, second digits of input
    scanf("%d %d", &orientation, &folds);

    printf("%c", up);

    char str[MAX] = '^';
    char temp[MAX] = '^';
    for (int i=0; i<folds; i++) { 
        temp = flip(temp);
    }
    
}