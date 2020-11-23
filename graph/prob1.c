#include <stdio.h>
#include <stdlib.h>

typedef enum {false, true} bool;

typedef struct _gNode {
    int color;
    int id;
    struct _gNode *next;
} gNode;

typedef struct {
    int num;
    gNode **heads;
} Graph;

int calculateNumCountries(Graph *g);

void PrintGraph(Graph *g);
void CreateGraph(Graph *g, int num, int *regions);
void DestroyGraph(Graph *g);
void AddEdge(Graph *g, int src, int dest);

int main() {
    Graph g;

    int numRegion, numEdge;
    scanf("%d %d ", &numRegion, &numEdge);

    int arrRegions[numRegion];
    for (int i=0; i<numRegion; i++) {
        int num;
        scanf(" %d", &num);
        arrRegions[i] = num;
    }
    CreateGraph(&g, numRegion, arrRegions);

    for (int i=0; i<numEdge; i++) {
        int a, b;
        scanf(" %d %d", &a, &b);
        AddEdge(&g, a, b);
    }

    // for (int i=0; i<numRegion; i++) {
    //     printf("%d: %d\n", i, g.heads[i]->color);
    // }
    int num = calculateNumCountries(&g);
    printf("%d\n", num);
    //PrintGraph(&g);
    DestroyGraph(&g);
}

int calculateNumCountries(Graph *g) {
    bool *visited = (bool *)malloc(sizeof(bool) * g->num);
    for (int i=0; i<g->num; i++) {
        visited[i] = false;
    }
    
    int total = 0;
    for (int i=0; i<g->num; i++) {
        gNode *current = g->heads[i];
        int count = 1;
        if (visited[i]) continue;
        else visited[i] = true;
        while (current->next != NULL) {
            current = current->next;
            if (visited[current->id]) count = 0;
            else visited[current->id] = true;  
        }
        total += count;
    }
    return total;
}

void PrintGraph(Graph *g) {
    for (int i=0; i<g->num; i++) {
        gNode *current = g->heads[i];
        printf("%d: ", i);
        while(current->next != NULL) {
            current = current->next;
            printf("%d ", current->id);
        }
        printf("\n");
    }
}

void CreateGraph(Graph *g, int num, int *regions) {
    g->num = num;
    g->heads = (gNode **)malloc(sizeof(gNode*) * num);
    for (int i=0; i<num; i++) {
        // making dummy nodes
        g->heads[i] = (gNode *)malloc(sizeof(gNode));
        g->heads[i]->next = NULL;
        g->heads[i]->color = regions[i];
        g->heads[i]->id = i;
    }
}
void DestroyGraph(Graph *g) {
    for (int i=0; i<g->num; i++) {
        gNode *current = g->heads[i];
        while (current != NULL) {
            gNode *temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(g->heads);
}
void AddEdge(Graph *g, int src, int dest) {
    gNode *newNode1, *newNode2, *currentSrc, *currentDest;

    // find the color of the src and dest
    // if they're not equal, don't add edge
    currentSrc = g->heads[src];
    currentDest = g->heads[dest];
    if (currentSrc->color != currentDest->color) {
        // printf("%d->%d: c: %d %d\n", src, dest, currentSrc->color, currentDest->color);
        return;
    }

    while (currentSrc->next != NULL) {
        if (currentSrc->next->id == dest) return;
        currentSrc = currentSrc->next;
    }
    while (currentDest->next != NULL) {
        currentDest = currentDest->next;
    }

    newNode1 = (gNode *)malloc(sizeof(gNode));
    newNode1->id = dest;
    newNode1->next = NULL;
    currentSrc->next = newNode1;

    
    newNode2 = (gNode *)malloc(sizeof(gNode));
    newNode2->id = src;
    newNode2->next = NULL;
    currentDest->next = newNode2;
}

