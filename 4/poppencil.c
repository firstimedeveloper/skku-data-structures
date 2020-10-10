#include <stdio.h>
#include <string.h>
#define MAX 10

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

bool Dequeue(Queue *q);
bool Enqueue(Queue *q, int item);
int Peek(Queue *q);

void ProcessQuery(Queue *q, char *str, int max);

int main() {
    Queue q;
    InitQueue(&q);

    int num, maxLen;
    num = 5; maxLen = 3;
    char str[MAX];
    // char str[MAX] = "abc";
    char query[5];

    scanf("%d %d\n%s", &num, &maxLen, str);

    for(int i=0; i<strlen(str); i++) {
        Enqueue(&q, str[i]);
    }
    for (int i=0; i<num; i++) {
        fgets(query, 5, stdin);
        ProcessQuery(&q, query, maxLen);
    }
    return 0;
}

void ProcessQuery(Queue *q, char *str, int max) {
    int num;
    char let;
    for (int i=0; i<5; i++) {
        if (str[i] == ' ')
            continue;
        else if (str[i] == '0') {
            printf("%d", Peek(q));
        } else if (str[i] == '1') {
            if ()
            Dequeue(&q);
        } else if (str[i] == '2') {
            
        }
    }
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
bool Dequeue(Queue *q) {
    if (IsEmpty(q)) return false;
    q->front = (q->front + 1) % MAX;
    return true;
}
bool Enqueue(Queue *q, int item) {
    if (IsFull(q)) return false;
    q->items[q->rear] = item;
    q->rear = (q->rear + 1) % MAX;
    return true;
}
int Peek(Queue *q) {
    return q->items[q->front];
}