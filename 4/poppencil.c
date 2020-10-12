#include <stdio.h>
#include <string.h>
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

bool Dequeue(Queue *q);
bool Enqueue(Queue *q, int item);
int Peek(Queue *q);

bool IsLastItem(Queue *q);
void ProcessQuery(Queue *q, char *str, char *targetStr, int max, int *len);

int main() {
    Queue q;
    InitQueue(&q);

    int num, maxLen;
    num = 5; maxLen = 3;
    char str[MAX], targetStr[MAX];
    // char str[MAX] = "abc";
    char query[5];

    scanf("%d %d\n%s", &num, &maxLen, str);

    int len = strlen(str);
    for(int i=0; i<len; i++) {
        Enqueue(&q, str[i]);
    }
    for (int i=0; i<num+1; i++) {
        fgets(query, 5, stdin);
        ProcessQuery(&q, query, targetStr, maxLen, &len);
    }

    for (int i=0; i<strlen(targetStr); i++) {
        printf("%c\n", targetStr[i]);
    }
    return 0;
}

bool IsLastItem(Queue *q) {
    if (q->front == q->rear-1) {
        return true;
    } else return false;
}

void ProcessQuery(Queue *q, char *str, char *targetStr, int max, int *len) {
    int num;
    char let;

    // count is the value of successful reads
    // ie, if no letter was provided, the value would be 1.
    // if a number and letter was provided, the value would be 2.
    int count = sscanf(str, "%d %c", &num, &let);
    if (count == 1) {
        if (num == 0) {
           let = (char) Peek(q);
            strncat(targetStr, &let, MAX);
            return; 
        } else if (num == 1) {
            if (!IsLastItem(q)) { 
                Dequeue(q);
                --*len;
            }
            return;
        }
    } else if (count == 2) {
        if (num == 2) {
            if (*len != max) {
                Enqueue(q, let);
                ++*len;
            }
            return;
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