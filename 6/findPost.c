#include <stdio.h>
#include <stdlib.h>
#define MAX 1000

typedef enum {false, true} bool;
typedef int btData;

typedef struct _btNode {
    btData item;
    struct _btNode *lc;
    struct _btNode *rc;
} btNode;

btNode* CreateNode(btData item) {
    btNode *node = (btNode *)malloc(sizeof(btNode));

    node->item = item;
    node->lc = NULL;
    node->rc = NULL;

    return node;
}

void DestroyNode(btNode *node) {
    if (node != NULL) {
        DestroyNode(node->lc);
        DestroyNode(node->rc);
        
    }
    free(node);
} 

bool CreateLeftSubTree(btNode *root, btNode *node) {
    if (root->lc != NULL)
        return false;
    root->lc = node;
    return true;
}

bool CreateRightSubTree(btNode *root, btNode *node) {
    if (root->rc != NULL)
        return false;
    root->rc = node;
    return true;
}
//LRC
void PostOrder(btNode *root) {
    if (root != NULL) {
        PostOrder(root->lc);
        PostOrder(root->rc);
        printf("%d ", root->item);
    }
}

// The items that go in to the stack are pointers to btNode
typedef btNode* Data;

typedef struct {
	Data items[MAX];
	int top;
} Stack;
// initialize an empty stack
void InitStack(Stack *pstack) {
	pstack->top = -1;
}
// check if stack is full and return a bool value
bool IsFull(Stack *pstack) {
	return pstack->top == MAX - 1;
}
// check if stack is empty and return a bool value
bool IsEmpty(Stack *pstack) {
	return pstack->top == -1;
}
// read the last (top) item of the stack
Data Peek(Stack *pstack) {
	if (IsEmpty(pstack))
		return false; //error: empty stack
	return pstack->items[pstack->top];
}
// insert an item to the stack
bool Push(Stack *pstack, Data item) {
	if (IsFull(pstack))
		return false;
	pstack->items[++(pstack->top)] = item;
	return true;
}
// remove an item from the stack
bool Pop(Stack *pstack) {
	if (IsEmpty(pstack))
		return false;
	--(pstack->top);
	return true;
}

int main() {
    int maxNodes;
    scanf("%d ", &maxNodes);
    int preorderedArr[maxNodes];
    int inorderedArr[maxNodes];

    int current;
    // for line 2: preordered
    for (int i=0; i<maxNodes; i++) {
        scanf(" %d", &current);
        preorderedArr[i] = current;
    }
    scanf("\n");
    // for line 3: inordered
    for (int i=0; i<maxNodes; i++) {
        scanf(" %d", &current);
        inorderedArr[i] = current;
    }

    // first number of the preordered array is the root node
    int rootNum = preorderedArr[0];
    btNode *root = CreateNode(rootNum);

    Stack stack;
    InitStack(&stack);
    Push(&stack, root);

    // i == 1 as the root node is already in the stack
    // i is the index for the preorderedArr
    int i=1;
    // j is the index for the inorderedArr
    int j=0;
    while (i < maxNodes) {
        btNode *peek = Peek(&stack);
        // while top of stack doesn't equal inordered (at index j)
        while (peek->item != inorderedArr[j]) {
            //push preorder into stack
            btNode *newNode = CreateNode(preorderedArr[i]);
            CreateLeftSubTree(peek, newNode);
            Push(&stack, newNode);
            // peek gets a new value since stack was pushed
            peek = Peek(&stack);
            i++;
        }

        btNode *temp;
        // while top of stack is the same as inordered
        while (!IsEmpty(&stack) && peek->item == inorderedArr[j]) {
            // Pop the stack
            temp = peek;
            Pop(&stack);
            peek = Peek(&stack);
            j++;
        }
        if (i >= maxNodes)
            break;
        btNode *newNode = CreateNode(preorderedArr[i]);
        CreateRightSubTree(temp, newNode);
        Push(&stack, newNode);
        i++;
    }
    // print created binary tree in postorder form
    PostOrder(root);
    // recursively free all the nodes starting with the root node
    DestroyNode(root);
}
