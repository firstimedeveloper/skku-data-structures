
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
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

int EvalPostfix(char* exp, int len)
{
    Stack stack;
    int op1, op2;
    InitStack(&stack);
    for (int i = 0; i < len; i++) {
        if (isdigit(exp[i]))
            Push(&stack, exp[i] - '0');
        else if (exp[i] == '-') {
            Push(&stack, -1);
        } else {
            op2 = Peek(&stack); 
            Pop(&stack);
            op1 = Peek(&stack); 
            Pop(&stack);
            if (exp[i] == '+')
                Push(&stack, op1 + op2);         
            else if (exp[i] == '*')
                Push(&stack, op1 * op2);
        }
    }
    return Peek(&stack);
}



int main() {
    char str[MAX] = "-2233*+*23*+*";

    int num = EvalPostfix(str, strlen(str));
    printf("%d", num);
}

