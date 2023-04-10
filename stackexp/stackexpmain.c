#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef char element;

typedef struct {
    element stack[MAX];
    int top;
} Stacktype;

void init_stack(Stacktype* s) {
    s->top = -1;
}

int is_empty(Stacktype* s) {
    return (s->top == -1);
}

int is_full(Stacktype* s) {
    return (s->top == (MAX - 1));
}

void push(Stacktype* s, element item) {
    if (is_full(s)) {
        fprintf(stderr, "스택 가득 참\n");
        return;
    }
    else {
        s->stack[++(s->top)] = item;
    }
}

element pop(Stacktype* s) {
    if (is_empty(s)) {
        fprintf(stderr, "스택 빔\n");
        return 0;
    }
    else {
        return s->stack[(s->top)--];
    }
}

element peek(Stacktype* s) {
    if (is_empty(s)) {
        fprintf(stderr, "스택 빔\n");
        return 0;
    }
    else {
        return s->stack[(s->top)];
    }
}

int is_number(char ch) {
    return (ch >= '0' && ch <= '9');
}

int is_operator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

int eval(char exp[]) {
    int i = 0, op1, op2;
    char ch;
    int len = strlen(exp);
    Stacktype s;

    init_stack(&s);

    for (i = 0; i < len; i++) {
        ch = exp[i];

        if (is_number(ch)) {
            push(&s, ch);
        }
        else if (is_operator(ch)) {
            op2 = pop(&s) - '0';
            op1 = pop(&s) - '0';

            switch (ch) {
            case '+':
                push(&s, op1 + op2 + '0');
                break;
            case '-':
                push(&s, op1 - op2 + '0');
                break;
            case '*':
                push(&s, op1 * op2 + '0');
                break;
            case '/':
                push(&s, op1 / op2 + '0');
                break;
            }
        }
        else {
            fprintf(stderr, "잘못된 입력: %c\n", ch);
            return 0;
        }
        
    }
    return pop(&s) - '0';
}

int main(void) {
    char exp[MAX];
    int result;

    printf("후위 표기식 입력: ");
    scanf_s("%s", exp,MAX);

    result = eval(exp);

    if (result != 0) {
        printf("계산 결과: %d\n", result);
    }

    return 0;
}