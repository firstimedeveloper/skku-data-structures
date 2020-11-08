#include <stdio.h>
#include <stdlib.h>

typedef enum {false, true} bool;
typedef int Data;

typedef struct _bTreeNode {
    Data item;
    struct _bTreeNode *lc;
    struct _bTreeNode *rc;
} Node;

Node* CreateNode(Data item);
void DestroyNode(Node *n);
bool CreateLeftSubTree(Node *root, Node *left);
bool CreateRightSubTree(Node *root, Node *left);

void Inorder(Node *root);
void Preorder(Node *root);
void Postorder(Node *root);
void Levelorder(Node *root);

int main() {
    Node *n1 = CreateNode(1);
    Node *n2 = CreateNode(2);
    Node *n3 = CreateNode(3);
    Node *n4 = CreateNode(4);
    Node *n5 = CreateNode(5);
    Node *n6 = CreateNode(6);

    

    CreateLeftSubTree(n1, n2);
    CreateRightSubTree(n1, n3);
    
    CreateLeftSubTree(n2, n4);
    CreateRightSubTree(n2, n5);

    CreateLeftSubTree(n3, n6);
    
    Inorder(n1);
    printf("\n");
    Preorder(n1);
    printf("\n");
    Postorder(n1);
    printf("\n");

    DestroyNode(n1);
    DestroyNode(n2);
    DestroyNode(n3);
    DestroyNode(n4);
    DestroyNode(n5);
    DestroyNode(n6);
    return 0;
}

Node* CreateNode(Data item) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->item = item;
    node->lc = NULL;
    node->rc = NULL;

    return node;
}

void DestroyNode(Node *n) {
    free(n);
}
bool CreateLeftSubTree(Node *root, Node *left) {
    if (root->lc != NULL)
        return false;
    root->lc = left;
    return true;
}
bool CreateRightSubTree(Node *root, Node *right) {
    if (root->rc != NULL)
        return false;
    root->rc = right;
    return true;
}

void Inorder(Node *root) {
    if (root != NULL) {
        Inorder(root->lc);
        printf("%d ", root->item);
        Inorder(root->rc);
    }
}
void Preorder(Node *root) {
    if (root != NULL) {
        printf("%d ", root->item);
        Preorder(root->lc);
        Preorder(root->rc);
    }
}
void Postorder(Node *root) {
    if (root != NULL) {
        Postorder(root->lc);
        Postorder(root->rc);
        printf("%d ", root->item);
    }
}
void Levelorder(Node *root);