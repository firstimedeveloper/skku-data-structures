#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int max; // max memory size

typedef enum {false, true} bool;
typedef int Data;


typedef struct _Node {
    Data size;
    Data pos;
    struct _Node *next;
    struct _Node *prev;
} Node;

typedef struct {
    Node *head;
    int count;
    int len;
} Mem;

void InitMem(Mem *m) {
    Node *d1, *d2;
    d1 = (Node *)malloc(sizeof(Node));
    d2 = (Node *)malloc(sizeof(Node));

    d1->prev = d2;
    d1->next = d2;
    d2->prev = d1;
    d2->next = NULL;

    d1->size = 0;
    d1->pos = 0;
    d2->size = 0;
    d2->pos = max;

    m->head = d1;
    m->len = 0;
    m->count = 0;
}

bool IsEmpty(Mem *m) {
    return m->len == 0;
}

// alloc takes in size and returns the starting position of the memory address.
// If there is no space, -1 is returned
int alloc(Mem *m, int size) {
    Node *current, *newNode;

    newNode = (Node *)malloc(sizeof(Node));
    newNode->size = size;
    newNode->pos = 0;
    newNode->prev = NULL;
    newNode->next = NULL;

    unsigned int minAvailSpace = max+1;
    unsigned int avail = 0;
    int count = -1;
    current = m->head;
    for (int i=0; i<=m->count; i++) {
        if (current->next != NULL) {
            avail = current->next->pos - (current->pos + current->size);
            // printf("\navail space %d\n", avail);
            if (avail < minAvailSpace && avail >= size) {
                minAvailSpace = avail;
                newNode->pos = (current->pos + current->size);
                count = i;
            }
        } else break;
        current = current->next;
    }
    // if count hasn't changed from the forloop
    if (count == -1) {  
        return -1;
    } else {
        current = m->head;
        for (int i=0; i<count;i++) {
            current = current->next;
        }
    }
    
    newNode->prev = current;
    newNode->next = current->next;
    current->next = newNode;
    current->next->prev = newNode;

    m->len++;
    m->count++;
    return newNode->pos;
}

void PrintAll(Mem *m) {
    for(Node *i=m->head->next; i != NULL; i=i->next) {
        if (i->next == NULL) return;
        printf(" p%d s%d ", i->pos, i->size);
    }
}

// Assuming that pos and size is always valid
// therefore returns void
void freemem(Mem *m, int pos, int size) {
    Node *current, *temp;

    current = m->head;
    for(int i=0; i<= m->count; i++) {
        if (current->next->pos == pos && current->next->size == size)
            break;
        else current = current->next;
    }

    temp = current->next;
    current->next = temp->next;
    temp->next->prev = current;

    printf("\nfreeing p%d s%d\n", temp->pos, temp->size);
    free(temp);
    m->count--;
    m->len--;
}

void ClearAll(Mem *m) {
    Node *current = m->head;
    while (current->next != NULL) {
        Node *temp;
        temp = current->next;
        current->next = temp->next;
        free(temp);
    }
    free(m->head);
}

int main() {
    char query[20]; //used for reading line by line
    unsigned int num; // number of iteration

    char op[10]; // name of operation: alloc, free
    unsigned int size; // size allocated or freed
    unsigned int pos; // position of memory, used when being freed

    scanf("%d %d\n", &max, &num);

    Mem m;
    InitMem(&m);

    for (int i=0; i<num; i++) {
        fgets(query, 20, stdin);
        int ret = sscanf(query, "%s ", op);
        if (strcmp(op, "alloc") == 0) {
            sscanf(query, "%s %d\n", op, &size);
            int tempPos = alloc(&m, size);
            printf("%d\n", tempPos);
        } else if (strcmp(op, "free") == 0) {
            sscanf(query, "%s %d %d\n", op, &pos, &size);
            freemem(&m, pos, size); // always succeeds
        }
        // PrintAll(&m);
        // printf("\n");
    }
    ClearAll(&m);
}