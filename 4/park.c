#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 1000

typedef enum {false, true} bool;
typedef struct {
    int time;
    int size;
    bool ok; // this indicates success or failure as returning NULL is not possible.
} Team;
typedef struct {
    Team items[MAX];
    int front;
    int rear;
} Queue;

void InitQueue(Queue *q);
bool IsFull(Queue *q);
bool IsEmpty(Queue *q);
Team Peek(Queue *q);
bool Enqueue(Queue *q, Team t);
bool Dequeue(Queue *q);
void handleTeams(Queue *q, int team, int time, int *total);

// making these global
int maxPersons, maxTime;

int main() {
    Queue q;
    InitQueue(&q);
    int numTeams;
    char str[MAX];
    // first line
    fgets(str, MAX, stdin);
    sscanf(str, "%d %d %d\n", &numTeams, &maxPersons, &maxTime);
    // second line
    fgets(str, MAX, stdin);
    char *team = strtok(str, " ");

    int totalCount = 0; // total number of people in the park.
    int now = 0; // current time.
    while (team != NULL) {
        if (now == numTeams) break;
        handleTeams(&q, atoi(team), now, &totalCount);
        team = strtok(NULL, " "); 
        now++;
    }
    return 0;
}

void handleTeams(Queue *q, int team, int currentTime, int *total) {
    Team t;
    t = Peek(q);
    // checking if team at the front of the queue == current time
    // this works because t.time = entrance time + maxTime.
    // so t.time will only equal currentTime if amount equal to (maxTime) has passed. 
    // Realistically, I wouldn't need to check t.ok,
    // but since there is a (slim) chance that an uninitialized t.time == currentTime,
    // this would be safer.
    if ((t.time == currentTime) && t.ok != false) {
        Dequeue(q);
        *total -= t.size;
    }

    if (*total + team > maxPersons) {
        printf("0 ");
        return;
    } else {
        t.size = team;
        t.time = currentTime + maxTime;
        t.ok = true;
        Enqueue(q, t);
        *total += team;
        printf("1 ");
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
    return q->front == q->rear;
}
Team Peek(Queue *q) {
    if (IsEmpty(q)) {
        Team t;
        t.ok = false;
        return t;
    }
    return q->items[q->front];
}
bool Enqueue(Queue *q, Team t) {
    if (IsFull(q)) 
        return false;
    q->items[q->rear] = t;
    q->rear = (q->rear + 1) % MAX;
    return true;
}
bool Dequeue(Queue *q) {
    if (IsEmpty(q)) 
        return false;
    q->front = (q->front + 1) % MAX;
    return true;
}
