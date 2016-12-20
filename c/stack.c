
#include <stdlib.h>
#include <stdio.h>

struct node_t {
    int value;
    struct node_t *next;
};

struct stack_t {
    int count;
    struct node_t *top;
};

typedef struct node_t node;
typedef struct stack_t stack;

stack *init();
int push(stack *s, int value);
int pop(stack *s);
int print(stack *s);

int main () {
    int i = 0;
    int count = 0;
    int value = 0;

    stack *s = init();

    scanf("%d", &count);
    for (i = 0; i < count; i++) {
        scanf("%d",&value);
        push(s, value);
    }

    print(s);
    push(s, 5);
    push(s, 6);
    print(s);
    pop(s);
    pop(s);
    pop(s);
    pop(s);
    pop(s);
    pop(s);
    pop(s);
    pop(s);
    pop(s);

    return 0;

}

int print(stack *s)
{
    if (!s) return 0;
    node *n = s->top;
    printf("--- STACK [%d] ---\n", s->count);
    while (n) {
        printf ("%d, ", n->value);
        n = n->next;
    }
    printf("\n");
    return 0;
}

stack *init()
{
    stack *s = (stack*)malloc(sizeof(stack));
    s->top = 0;
    s->count = 0;

    return s;
}

int push(stack *s, int value)
{
    if (!s) return 0;

    node *n = (node*)malloc(sizeof(node));
    n->value = value;

    n->next = s->top;
    s->top = n;
    s->count++;

    printf("pushed %d\n", value);

    return value;
}

int pop(stack *s)
{
    if (!s) return 0;
    if (!s->count) return 0;

    node *n = s->top;
    int value = n->value;

    s->top = n->next;
    free(n);

    s->count--;
    printf("popped %d\n", value);

    return value;
}

