#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 1000

typedef enum { false, true } bool;
typedef int Data;
typedef struct {
	Data items[MAX];
	int top;
} Stack;

// initialize an empty stack
void InitStack(Stack *pstack) {
	pstack->top = -1;
}

// check if stack is full
// and return a bool value
bool IsFull(Stack *pstack) {
	return pstack->top == MAX - 1;
}

// check if stack is empty
// and return a bool value
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

// countHeight returns an integer value corresponding to the height of the string.
// 0 is returned if the any errors occur.
int countHeight(char* s, int len) {
	int height = 0;
    int maxHeight = 0;
	
	Stack stack;
	InitStack(&stack);
	
	for (int i=0; i<len; i++) {
        if (s[i] == '/') {
            // increment height if '/'
            height++;
            // if pushing '/' to stack fails, return 0
			if (!Push(&stack, s[i])) return 0;

		} else if (s[i] == '\\') {
            height--;
            // if Popping stack fails, the mountain string isn't correct
            // as '/' char wasn't found before '\'
            // so return 0
            if (!Pop(&stack)) return 0;
        }
        // maxHeight is assigned the value of height if smaller than height.
        if (maxHeight < height) 
            maxHeight = height;
	}
    // if the stack is not empty, there number of '/' and '\' are not equal,
    // so return 0
    if (IsEmpty(&stack)) {
        return maxHeight;
    } else return 0;
}


int main() {
	char str[MAX];
	int result = 0;
    // assuming a non-blank input string containing '/' and '\'
	scanf("%s", str);
	int len = strlen(str);
	result = countHeight(str, len);
	
	printf("%d\n", result);
}
