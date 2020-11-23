#include <stdio.h>

int main() {
    int numRegion, numEdge;
    scanf("%d %d ", &numRegion, &numEdge);
    int arrRegions[numRegion];
    int countRegions = 0;
    int previous = -1;
    for (int i=0; i<numRegion; i++) {
        int num;
        scanf(" %d", &num);
        if (previous == -1) {
            previous = num;
            countRegions++;
            continue;
        }
        if (num != previous) countRegions++;
        previous = num;
    }
    printf("%d", countRegions);

}