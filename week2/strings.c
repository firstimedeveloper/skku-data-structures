#include <stdio.h>
#include <ctype.h>

int wordCount(char *s) {
    int count = 0;
    while(*s != '\0') {
        while (isspace(*s)) ++s;
        if (*s != '\0') {
            ++count;
            while(*s != '\0' && !isspace(*s)) ++s;
        }
    }
    return count;
}

int main() {
    char *s = " jun hyuk ";

    int num = wordCount(s);
    printf("%d\n", num);

    return 0;
}