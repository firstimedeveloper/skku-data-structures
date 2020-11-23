#include <stdio.h>
#include <stdlib.h>
#define MAX 1000

typedef enum { false, true } bool;
typedef int Data;
typedef struct {
	Data items[MAX];
	int top;
} Stack;

// initialize an empty stack
void InitStack(Stack *pstack) {
	pstack->top = -1;
}

// check if stack is full
// and return a bool value
bool IsFull(Stack *pstack) {
	return pstack->top == MAX - 1;
}

// check if stack is empty
// and return a bool value
bool IsEmpty(Stack *pstack) {
	return pstack->top == -1;
}

// read the last (top) item of the stack
Data Peek(Stack *pstack) {
	if (IsEmpty(pstack))
		return false; //error: empty stack
	return pstack->items[pstack->top];
}

// insert an item to the stack
bool Push(Stack *pstack, Data item) {
	if (IsFull(pstack))
		return false;
	pstack->items[++(pstack->top)] = item;
	return true;
}

// remove an item from the stack
bool Pop(Stack *pstack) {
	if (IsEmpty(pstack))
		return false;
	--(pstack->top);
	return true;
}
typedef struct _GNode {
    int id;
    struct _GNode *next;
} GNode;

typedef struct {
    int num;
    GNode **heads;
} Graph;

void CreateGraph(Graph *g, int num);
void DestroyGraph(Graph *g);
// adding an undirected edge between src and dest
void AddEdge(Graph *g, int src, int dest);
void PrintGraph(Graph *g);
void DFS(Graph *g);
void BFS(Graph * g);

int main() {
    Graph g;
    CreateGraph(&g, 5);
    AddEdge(&g, 0, 1);
    AddEdge(&g, 0, 2);
    AddEdge(&g, 0, 4);
    AddEdge(&g, 1, 2);
    AddEdge(&g, 2, 3);
    AddEdge(&g, 2, 4);
    AddEdge(&g, 3, 4);

    PrintGraph(&g);
    DFS(&g);
    DestroyGraph(&g);
    
}



void CreateGraph(Graph *g, int num) {
    g->num = num;
    g->heads = (GNode **)malloc(sizeof(GNode*) * num);
    for (int i=0; i<num; i++) {
        // making dummy nodes
        g->heads[i] = (GNode *)malloc(sizeof(GNode));
        g->heads[i]->next = NULL;
    }
}
void DestroyGraph(Graph *g) {
    for (int i=0; i<g->num; i++) {
        GNode *current = g->heads[i];
        while (current != NULL) {
            GNode *temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(g->heads);
}
// adding an undirected edge between src and dest
void AddEdge(Graph *g, int src, int dest) {
    GNode *newNode1, *newNode2, *current;

    newNode1 = (GNode *)malloc(sizeof(GNode));
    newNode1->id = dest;
    newNode1->next = NULL;

    current = g->heads[src];
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode1;

    newNode2 = (GNode *)malloc(sizeof(GNode));
    newNode2->id = src;
    newNode2->next = NULL;

    current = g->heads[dest];
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode2;
}


void PrintGraph(Graph *g) {
    for (int i=0; i<g->num; i++) {
        GNode *current = g->heads[i];
        printf("%d: ", i);
        while(current->next != NULL) {
            current = current->next;
            printf("%d ", current->id);
        }
        printf("\n");
    }
}
void DFS(Graph *g) {
    Stack s;
    bool *visited = (bool *)malloc(sizeof(bool) * g->num);
    for (int i=0; i<g->num; i++) {
        visited[i] = false;
    }
    InitStack(&s);
    Push(&s, 0);
    while (!IsEmpty(&s)) {
        GNode *current;
        int vtx = Peek(&s);
        Pop(&s);

        if (visited[vtx]) continue;
        else {
            visited[vtx] = true;
            printf("%d ", vtx);
        }

        current = g->heads[vtx]->next;
        while (current != NULL) {
            if (!visited[current->id])
                Push(&s, current->id);
            current = current->next;
        }
    }
}
void BFS(Graph * g);