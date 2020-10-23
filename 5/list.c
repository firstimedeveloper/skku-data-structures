#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum {false, true} bool;
typedef int Data;

typedef struct _Node {
    Data item;
    struct _Node *next;
    struct _Node *prev;
} Node;

typedef struct {
    Node *head;
    int len;
} Link;

void InitLink(Link *l) {
    Node *d1, *d2;
    d1 = (Node *)malloc(sizeof(Node));
    d2 = (Node *)malloc(sizeof(Node));

    d1->prev = d2;
    d1->next = d2;
    d2->prev = d1;
    d2->next = NULL;

    l->head = d1;
    l->len = 0;
}

bool IsEmpty(Link *l) {
    return l->len == 0;
}

bool InsertPos(Link *l, int pos, int item) {
    Node *current, *newNode;
    if (pos < 0 || pos > l->len) 
        return false;
    newNode = (Node *)malloc(sizeof(Node));
    newNode->item = item;
    newNode->prev = NULL;
    newNode->next = NULL;

    if (pos < l->len/2) {
        current = l->head;
        for(int i=0; i<pos; i++) {
            current = current->next;
        }
    } else {
        current = l->head->prev;
        for (int i=l->len; i>=pos; i--) {
            current = current->prev;
        }
    }
    
    newNode->prev = current;
    newNode->next = current->next;
    current->next->prev = newNode;
    current->next = newNode;
    l->len++;
    return true;
}

bool RemovePos(Link *l, int pos) {
    if (IsEmpty(l) || pos < 0 || pos >= l->len) 
        return false;
    
    Node *current, *temp;
    if (pos < l->len/2) {
        current = l->head;
        for(int i=0; i<pos; i++) {
            current = current->next;
        }
    } else {
        current = l->head->prev;
        for (int i=l->len; i>=pos; i--) {
            current = current->prev;
        }
    }
    temp = current->next; 
<<<<<<< HEAD
    current->next = temp->next;
=======
    temp->next->prev = current;
    current->next = temp->next;

>>>>>>> bidirectional
    l->len--;
    free(temp);
    return true;
}

void PrintAll(Link *l) {
    for(Node *i=l->head->next; i != NULL; i=i->next) {
        if (i->next == NULL) return;
        printf("%c", i->item);
    }
}

void ClearList(Link *l) {
    while (l->head->next->next != NULL) {
        RemovePos(l, l->len-1);
    }
    free(l->head->prev);
    free(l->head);
}

int main() {
    Link l;
    InitLink(&l);
    int num; // number of operations
    int cursor = 0;
    char line[8]; // line
    char op[6]; // name of operation
    char let; // letter that comes after the operation
    scanf("%d ", &num);
    for(int i=0; i<num; i++) {
        fgets(line, 8, stdin);
        int ret = sscanf(line, "%s %c\n", op, &let);
        if (strcmp(op, "erase") == 0) {
<<<<<<< HEAD
            if (cursor != 0 && l.len != 0) {    
=======
            if (cursor != 0 && l.len != 0) {
>>>>>>> bidirectional
                RemovePos(&l, --cursor);
            }
        }
        if (ret == 2) {
            if (strcmp(op, "add") == 0) {
                if (let == '_') 
                    let = ' ';
                InsertPos(&l, cursor, let);
                cursor++;
            } else if (strcmp(op, "move") == 0 && l.len > 0) {
                if (let == 'l') {
                    if (l.len - cursor < l.len) 
                        cursor--;
                } else if (let == 'r') {
                    if (l.len > cursor)
                        cursor++;
                }
            }
        }
        // PrintAll(&l);
        // printf("% d\n%d\n", cursor, l.len);
            
    }
    PrintAll(&l);
    ClearList(&l);
}