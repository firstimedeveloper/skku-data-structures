#include <stdio.h>

#define MAX_HEAP 1000

typedef enum {false, true} bool;

typedef char Data;

typedef struct _HNode {
    Data data;
    int priority;
} HNode;

typedef struct {
    HNode items[MAX_HEAP+1];
    int num;
} Heap;

void InitHeap(Heap *h);
bool IsEmpty(Heap *h);
bool IsFull(Heap *h);
bool Insert(Heap *h, Data data, int priority);
// Remove and return the maximum data from the heap
Data Delete(Heap *h);
int GetParent(int idx);
int GetLChild(int idx);
int GetRChild(int idx);
// Return the index of the child with a higher priority 
// given a parent idx.
int GetHighPriorityChild(Heap *h, int idx);

int main() {
    Heap h;
    InitHeap(&h);
    Insert(&h, 'e', 1);
    Insert(&h, 'd', 2);
    Insert(&h, 'c', 3);
    Insert(&h, 'b', 4);
    Insert(&h, 'a', 5);

    for (int i=0; i<5; i++) {
        printf("priority %d, data %c\n", h.items[i+1].priority, h.items[i+1].data);
    }

    return 0;
}

void InitHeap(Heap *h) {
    h->num = 0;
}

bool IsEmpty(Heap *h) {
    return h->num == 0;
}
bool IsFull(Heap *h) {
    return h->num == MAX_HEAP;
}
bool Insert(Heap *h, Data data, int priority) {
    if (IsFull(h)) return false;
    HNode  node;
    int idx = h->num + 1;
    while (idx > 1) {
        int parent = GetParent(idx);
        if (priority > h->items[parent].priority) {
            h->items[idx] = h->items[parent];
            idx = parent;
        }
        else break;
    }
    node.data = data;
    node.priority = priority;
    h->items[idx] = node;
    h->num++; 
     
}
// Remove and return the maximum data from the heap
Data Delete(Heap *h) {
    if (IsEmpty(h)) return false;
    
}

int GetParent(int idx) {
    return idx / 2;
}
int GetLChild(int idx) {
    return 2 * idx;
}
int GetRChild(int idx) {
    return 2 * idx + 1;
}
// Return the index of the child with a higher priority 
// given a parent idx.
int GetHighPriorityChild(Heap *h, int idx)  {
    if (GetLChild(idx) > h->num)
        return 0;
    else if (GetLChild(idx) == h->num)
        return GetLChild(idx);
    else {
        int left = GetLChild(idx);
        int right = GetRChild(idx);
        if (h->items[left].priority > h->items[right].priority) 
            return left;
        else 
            return right;
    }
}



