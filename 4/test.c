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
bool IsLastItem(Queue *q);

void ProcessQuery(Queue *q, char *str, char *targetStr, int max);

// bool IsMaxLength(Queue *q, int max) {
//     if (q->front == (q->rear + 1) % max)
// }


void modifyNum(int *len) {
    --*len;
}

int main() {
    Queue q;
    InitQueue(&q);

    char str[MAX] = "abc";

    int len = strlen(str);
    int *lenptr = &len;
    for (int i=0; i<len; i++) {
        Enqueue(&q, str[i]);
    }
    printf("%d\n", len);
    modifyNum(&len);
    modifyNum(&len);    
    printf("%d\n", len);

}


bool IsLastItem(Queue *q) {
    if (q->front == q->rear-1) {
        return true;
    } else return false;
}

void ProcessQuery(Queue *q, char *str, char *targetStr, int max) {
    int num;
    char let;
    for (int i=0; i<5; i++) {
        if (str[i] == ' ')
            continue;
        else if (str[i] == '0') {
            // printf("%c", Peek(q));
            let = (char) Peek(q);
            strncat(targetStr, &let, MAX);
        } else if (str[i] == '1') {
            // TODO handle queue having only one character
            Dequeue(q);
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