#include <stdio.h>

#define MAX 5

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
bool Enqueue(Queue *q, int item);
bool Dequeue(Queue *q);

int main() {
    Queue q;
    InitQueue(&q);
    if (IsEmpty(&q)) {
        printf("q is empty\n");
    }
    int num = 100;
    while (num > 0) {
        Enqueue(&q, num--);
        printf("start of q: %d\nvalue of rear: %d\n", Peek(&q), q.rear);
        Dequeue(&q);
    }
    return 0;
}

void InitQueue(Queue *q) {
    q->front = 0;
    q->rear = 0;
}
bool IsFull(Queue *q) {
    return q->rear == MAX;
}
bool IsEmpty(Queue *q) {
    return q->rear == 0 && q->front == 0;
}
Data Peek(Queue *q) {
    return q->items[q->front];
}
bool Enqueue(Queue *q, int item) {
    if (IsFull(q)) return false;
    q->items[q->rear] = item;
    q->rear = (q->rear + 1) % MAX;
    return true;
}
bool Dequeue(Queue *q) {
    if (IsEmpty(q)) return false;
    q->front = (q->front + 1) % MAX;
    return true;
}