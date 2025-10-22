#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INITVOL 100
struct STACK
{
    int *data;
    int top;
    int vol;
};
typedef struct STACK stack;

struct QUEUE
{
    stack master;
    stack temp;
};
typedef struct QUEUE queue;

int init(stack *s);
void destroy(stack *s);
void push(stack *s, int e);
void pop(stack *s, int *e);
int is_empty(stack s);
int qinit(queue *q);
void qdestroy(queue *q);
void enqueue(queue *q, int e);
void dequeue(queue *q, int *e);
void sprint(stack s)
{
    printf("\ndepth:%d\nbottom-> ", s.top + 1);
    for (int i = 0; i <= s.top; i++)
        printf("%d ", s.data[i]);
    printf("<-top\n");
    return;
}
void qprint(queue q)
{

    printf("\nlength:%d\nfront-> ", q.master.top + 1);
    for (int i = 0; i <= q.master.top; i++)
        printf("%d ", q.master.data[i]);
    printf("<-rear\n");
    return;
}
int main()
{
    stack a;
    queue b;
    init(&a);
    qinit(&b);
    push(&a, 3);
    push(&a, 5);
    push(&a, 7);
    sprint(a);
    int y;
    pop(&a, &y);
    sprint(a);
    enqueue(&b, 1);
    enqueue(&b, 2);
    enqueue(&b, 5);
    qprint(b);
    dequeue(&b, &y);
    qprint(b);
    return 0;
}
int init(stack *s)
{
    s->data = (int *)malloc(INITVOL * sizeof(int));
    if (s->data == NULL)
        return 0;
    s->top = -1;
    s->vol = INITVOL;
    return 1;
}
void destroy(stack *s)
{
    if (s->data == NULL)
        return;
    free(s->data);
    s->top = -1;
    s->vol = 0;
    return;
}
void push(stack *s, int e)
{
    if (s->top == s->vol - 1)
    {
        int *temp = (int *)malloc((s->vol + INITVOL) * sizeof(int));
        if (!temp)
            return;
        memcpy(temp, s->data, s->vol * sizeof(int));
        free(s->data);
        s->data = temp;
        s->vol += INITVOL;
    }
    s->data[s->top + 1] = e;
    s->top++;
}
void pop(stack *s, int *e)
{
    if (is_empty(*s))
    {
        fprintf(stderr, "cannot pop\n");
        return;
    }

    *e = s->data[s->top];
    s->top--;
    return;
}
int is_empty(stack s)
{
    return s.top == -1;
}
int qinit(queue *q)
{
    int res = init(&(q->master)) && init(&(q->temp));
    return res;
}
void qdestroy(queue *q)
{
    destroy(&(q->master));
    destroy(&(q->temp));
    return;
}
void enqueue(queue *q, int e)
{
    push(&(q->master), e);
    return;
}
void dequeue(queue *q, int *e)
{
    if (is_empty(q->master))
    {
        fprintf(stderr, "cannot dequeue\n");
        return;
    }
    while (q->master.top > 0)
    {
        int t;
        pop(&(q->master), &t);
        push(&(q->temp), t);
    }
    pop(&(q->master), e);
    while (q->temp.top >= 0)
    {
        int t;
        pop(&(q->temp), &t);
        push(&(q->master), t);
    }
    return;
}