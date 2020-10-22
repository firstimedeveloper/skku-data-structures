#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum {false, true} bool;
typedef int Data;

typedef struct _Node {
    Data item;
    struct _Node *next;
} Node;

typedef struct {
    Node *head;
    int len;
} Link;

void InitLink(Link *l) {
    l->head = (Node *)malloc(sizeof(Node));
    l->head->next = NULL;
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
    newNode->next = NULL;

    current = l->head;
    for(int i=0; i<pos; i++) {
        current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;
    l->len++;
    return true;
}

bool RemovePos(Link *l, int pos) {
    Node *current, *temp;
    if (IsEmpty(l) || pos < 0 || pos >= l->len) 
        return false;

    current = l->head;
    for (int i=0; i<pos; i++) {
        current = current->next;
    }
    temp = current->next; 
    current->next = current->next->next;
    l->len--;
    free(temp);
    return true;
}

void PrintAll(Link *l) {
    for(Node *i=l->head->next; i != NULL; i=i->next) {
        printf("%c", i->item);
    }
}

void ClearList(Link *l) {
    while (l->head->next != NULL) {
        RemovePos(l, l->len-1);
    }
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
            RemovePos(&l, --cursor);
        }
        if (ret == 2) {
            if (strcmp(op, "add") == 0) {
                if (let == '_') 
                    let = ' ';
                InsertPos(&l, cursor, let);
                cursor++;
            } else if (strcmp(op, "move") == 0) {
                if (let == 'l')
                    if (l.len - cursor != l.len) 
                        cursor--;
                else if (let == 'r')
                    if (l.len + cursor != l.len)
                        cursor++;
            }
        }
            
    }
    PrintAll(&l);
    ClearList(&l);
}