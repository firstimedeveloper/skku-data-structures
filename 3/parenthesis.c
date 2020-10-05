#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 30

typedef enum {false, true} bool;
typedef int Data;
typedef struct {
    int top;
    Data items[MAX];
} Stack;

void InitStack(Stack *pStack) {
    pStack->top = -1;
}

bool IsEmpty(Stack *pStack) {
    if (pStack->top == -1) {
        return true;
    }
    return false;
}

bool IsFull(Stack *pStack) {
    if (pStack->top == MAX-1) {
        return true;
    }
    return false;
}

bool Pop(Stack *pStack) {
    if (IsEmpty(pStack)) {
        return false;
    }
    --(pStack->top);
    return true;
}

bool Push(Stack *pStack, int value) {
    if (IsFull(pStack)) {
        return false;
    }
    pStack->items[++(pStack->top)] = value;
    return true;
}

Data Peek(Stack *pStack) {
    if (IsEmpty(pStack)) {
        return false;
    }
    return pStack->items[pStack->top];
}

bool OpenParen(int s) {
    if (s == '(' || s == '[' || s == '{')
        return true;
    else return false;
}

bool ClosedParen(int s) {
    if (s == ')' || s == ']' || s == '}')
        return true;
    else return false;
}

bool IsParen(int s) {
    if (OpenParen(s) || ClosedParen(s))
        return true;
    else return false;
}

// CorrectParen
bool CorrectParen(int open, int close) {
    if (open == '(' && close == ')')
        return true;
    else if (open == '[' && close == ']')
        return true;
    else if (open == '{' && close == '}')
        return true;
    else return false;  
}

int calculateParen(char *s, int len) {
    // () = 2
    // [] = 3
    // {} = -1
    Stack stack;
    InitStack(&stack);
    for (int i=0; i<len; i++) {
        if (OpenParen(s[i])) {
            Push(&stack, s[i]);
        } else if (ClosedParen(s[i])) {
            // add up all the digits on the top of the stack
            // and stop when an OpenParen is reached.
            int temp = 0;
            // goneThruLoop is needed as the value of temp needs to be
            // changed if any value was added to temp in the while loop below.
            bool goneThruLoop = false;
            while(!IsEmpty(&stack) && !OpenParen(Peek(&stack))) {
                temp += Peek(&stack);
                Pop(&stack);
                if (!goneThruLoop) goneThruLoop = true;
            }
            // temp needs to be changed to 1 if nothing has been added to the 
            // value of temp.
            if (!goneThruLoop) temp = 1;
            // peek the stack,
            // if the open and close parens don't match, return 0,
            // pop the stack
            int a = Peek(&stack);
            if (!CorrectParen(a, s[i])) return 0;
            Pop(&stack);
            if (a == '(')
                Push(&stack, 2 * temp);
            else if (a == '[')
                Push(&stack, 3 * temp);
            else if (a == '{')
                Push(&stack, -1 * temp);
        } else return 0; // assuming string is wrong if it has anything other than open/close parens, so return 0
    }
    // adding up the remaining integers left in the stack
    // if any parens are found, return 0
    int result = 0;
    while (!IsEmpty(&stack)) {
        if (IsParen(Peek(&stack))) return 0;
        result += Peek(&stack);
        Pop(&stack);
    }
    return result;
}


int main() {

    char str[MAX];
    scanf("%s", str);

    int answer = calculateParen(str, strlen(str));
    printf("%d\n", answer);
}
