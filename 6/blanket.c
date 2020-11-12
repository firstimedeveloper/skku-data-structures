#include <stdio.h>
#include <stdlib.h>

int up = '^'; int down = 'V';

typedef enum {false, true} bool;
typedef int Data;

typedef struct _btNode {
    Data item;
    struct _btNode* lc;
    struct _btNode* rc;
} btNode;

void DestroyNode(btNode *node) {
    if (node != NULL) {
        DestroyNode(node->lc);
        DestroyNode(node->rc);   
    }
    free(node);
} 

btNode* CreateNode(Data item) {
    btNode *node = (btNode *)malloc(sizeof(btNode));
    node->item = item;
    node->lc = NULL;
    node->rc = NULL;
    return node;
}
btNode* CreateLeftSubtree(btNode *node) {
    btNode *child = CreateNode(up);
    node->lc = child;
    return child;
}

btNode* CreateRightSubtree(btNode *node) {
    btNode *child = CreateNode(down);
    node->rc = child;
    return child;
}

void fold(btNode *root, int num) {
    if (num == 0) return;
    fold(CreateLeftSubtree(root), num-1);
    printf("%c", root->item);
    fold(CreateRightSubtree(root), num-1);
}


int main() {
    int orientation, folds, dir;
    scanf("%d %d", &orientation, &folds);
    
    if (orientation == 0) {
        int temp = up;
        up = down;
        down = temp;
    }

    btNode *root = CreateNode(up);
    fold(root, folds);
    DestroyNode(root);
}