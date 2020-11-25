#include <stdio.h>
#include <stdlib.h>
#define MAX 10000

typedef enum {false, true} bool;
typedef int Data;

typedef struct {
    Data items[MAX];
    int front;
    int rear;
} Queue;

void InitQueue(Queue *q);
bool IsFull(Queue *q);
bool IsEmpty(Queue *q);
Data Peek(Queue *q);
bool EnQueue(Queue *q, int item);
bool DeQueue(Queue *q);

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


    int num = calculateNumCountries(&g);
    printf("%d\n", num);
    DestroyGraph(&g);
}

int calculateNumCountries(Graph *g) {
    bool *visited = (bool *)malloc(sizeof(bool) * g->num);
    for (int i=0; i<g->num; i++) {
        visited[i] = false;
    }
    Queue q;
    InitQueue(&q);
    int total = 0;
    for (int i=0; i<g->num; i++) {
        EnQueue(&q, i);
        bool count = false;
        while (!IsEmpty(&q)) {
            gNode* cur;
            int vtx = Peek(&q);
            DeQueue(&q);
            // Skip if the vertex has been visited.
            if (visited[vtx]) continue;
            else {
                visited[vtx] = true;
                count = true;
            }
            // Enqueue the vertex if it has been unvisited.
            cur = g->heads[vtx]->next;
            while (cur != NULL) {
                if (!visited[cur->id])
                    EnQueue(&q, cur->id);
                cur = cur->next;
            }
        }
        if (count) total++;

    }
    free(visited);
    return total;
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
        return;
    }

    while (currentSrc->next != NULL) {
        // check for duplicates
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

void InitQueue(Queue *q) {
    q->front = 0;
    q->rear = 0;
}
bool IsFull(Queue *q) {
    return q->front == (q->rear + 1) % MAX;
}
bool IsEmpty(Queue *q) {
    return q->rear == q->front;
}
Data Peek(Queue *q) {
    return q->items[q->front];
}
bool EnQueue(Queue *q, int item) {
    if (IsFull(q)) return false;
    q->items[q->rear] = item;
    q->rear = (q->rear + 1) % MAX;
    return true;
}
bool DeQueue(Queue *q) {
    if (IsEmpty(q)) return false;
    q->front = (q->front + 1) % MAX;
    return true;
}