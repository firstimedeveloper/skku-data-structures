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

int GetPriority(char op)
{
    if (op == '*')
    return 2;
    else if (op == '+')
    return 1;
    else
    return 0;
}
bool ComparePriority(char op1, char op2)
{
    int op1_pr = GetPriority(op1);
    int op2_pr = GetPriority(op2);
    if (op1_pr >= op2_pr)
    return true;
    else
    return false;
}

void ConvInfixToPostfix(char* exp, char* convExp, int len)
{
    Stack stack;
    int idx = 0;
    InitStack(&stack);
    for (int i = 0; i < len; i++)
    {
        if (isdigit(exp[i]))
            convExp[idx++] = exp[i]; // Print an operand.
        else {
            while (!IsEmpty(&stack) && ComparePriority(Peek(&stack), exp[i])) {
                convExp[idx++] = Peek(&stack); // Print an operator.
                Pop(&stack); // Pop an operator.
            }
            Push(&stack, exp[i]); // Push an operator.
        }
    }
    while (!IsEmpty(&stack)) {
        convExp[idx++] = Peek(&stack); // Print an operator.
        Pop(&stack); // Pop an operator.
    }
}



int main() {
    char str[MAX] = "2*3+4/2";
    char postr[MAX];

    ConvInfixToPostfix(str, postr, strlen(str));
    printf("%s", postr);
}

