#include <stdio.h>
#include <stdlib.h>
#define MAX 1000000

typedef struct {
    int distance;
    int data;
} Data;
typedef enum {false, true} bool;

typedef struct {
    Data items[MAX];
    int front;
    int rear;
} Queue;

void InitQueue(Queue *q);
bool IsFull(Queue *q);
bool IsEmpty(Queue *q);
Data Peek(Queue *q);
bool EnQueue(Queue *q, int item, int dist);
bool DeQueue(Queue *q);

typedef struct _gNode {
    int id;
    struct _gNode *next;
} gNode;

typedef struct {
    int num;
    gNode **heads;
} Graph;

int getCloseContacts(Graph *g, int max, int numPatients, int *patients);

void CreateGraph(Graph *g, int num);
void DestroyGraph(Graph *g);
void AddEdge(Graph *g, int src, int dest);
void PrintGraph(Graph *g) {
    for (int i=0; i<g->num; i++) {
        gNode *current = g->heads[i];
        printf("\n%d: ", i);
        while (current->next != NULL) {
            current = current->next;
            printf("%d ", current->id);
        }
    }
}

int main() {
    Graph g;
    int numPeople, maxDistance, numPatients, numConnections;
    scanf("%d %d %d %d ", &numPeople, &maxDistance, &numPatients, &numConnections);

    CreateGraph(&g, numPeople);

    int arrPatients[numPatients];
    // scanning for the ids of patients
    for (int i=0; i<numPatients; i++) {
        int id;
        scanf(" %d", &id);
        arrPatients[i] = id;
    }

    // scanning for the pairs of connections between two people
    for (int i=0; i<numConnections; i++) {
        int src, dest;
        scanf(" %d %d", &src, &dest);
        AddEdge(&g, src, dest);
    }

    int num = getCloseContacts(&g, maxDistance, numPatients, arrPatients);
    printf("%d", num);
    PrintGraph(&g);
    DestroyGraph(&g);
}

int getCloseContacts(Graph *g, int max, int numPatients, int *patients) {
    // list of closeContacts
    bool *closeContacts = (bool *)malloc(sizeof(bool) * g->num);
    for (int i=0; i<g->num; i++) {
        closeContacts[i] = false;
    }
    // patients should not be added to closeContacts
    for (int i=0; i<numPatients; i++) {
        closeContacts[patients[i]] = true;
    }
    int total = 0;
    // list of visited nodes
    bool *visited = (bool *)malloc(sizeof(bool) * g->num);
    // num is
    for (int i=0; i<numPatients; i++) {
        // refresh list of visited nodes for every patient
        for (int i=0; i<g->num; i++) {
            visited[i] = false;
        }
        // initialize queue for each patient
        Queue q;
        InitQueue(&q);
        EnQueue(&q, patients[i], 0);
        int count = 0;
        printf("%d:\n", i);
        while (!IsEmpty(&q)) {
            gNode* cur; 
            Data node = Peek(&q);
            int vtx = node.data;
            int dist = node.distance;
            DeQueue(&q);
            // once we reach the first dequeued node that exceeds the maximum distance,
            // break from the while loop
            if (dist == max+1) break;
            
            // if we already visited the node, move on to the next iteration
            // of the while loop
            if (visited[vtx]) continue;
            else {
                // increment count only if id is not in the list of closeContacts
                // as we do not want duplicate counts;
                if (!closeContacts[vtx]) {
                    printf("%d ", vtx);
                    count++;
                };
                visited[vtx] = true;
                closeContacts[vtx] = true;

                cur = g->heads[vtx];
                while (cur->next != NULL) {
                    cur = cur->next;
                    if (!visited[cur->id]) {
                        // enqueue the current id with the new distance value
                        EnQueue(&q, cur->id, dist + 1);
                    }
                }

            }
        } 
        printf("\n");
        total += count;
    }
    free(visited);
    free(closeContacts);
    return total;
}


void CreateGraph(Graph *g, int num) {
    g->num = num;
    g->heads = (gNode **)malloc(sizeof(gNode*) * num);
    for (int i=0; i<num; i++) {
        // making dummy nodes
        g->heads[i] = (gNode *)malloc(sizeof(gNode));
        g->heads[i]->next = NULL;
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

    currentSrc = g->heads[src];
    currentDest = g->heads[dest];

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
bool EnQueue(Queue *q, int item, int dist) {
    if (IsFull(q)) return false;
    q->items[q->rear].data = item;
    q->items[q->rear].distance = dist;
    q->rear = (q->rear + 1) % MAX;
    return true;
}
bool DeQueue(Queue *q) {
    if (IsEmpty(q)) return false;
    q->front = (q->front + 1) % MAX;
    return true;
}