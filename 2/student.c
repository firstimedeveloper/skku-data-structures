#include <stdio.h>

typedef struct {
    char name[10];
    int scores[3];
} student;

void changeScore(student *sptr, int num, int score) {
    sptr->scores[num] = score;
}

int main() {
    student s1 = {"Jun", 80, 70, 60};
    student *sptr = &s1;

    changeScore(sptr, 2, 90);

    printf("Name: %s\nScores:\n", s1.name);
    for (int i=0; i<3; i++) {
        printf("%d\n", s1.scores[i]);
    }

    return 0;
}