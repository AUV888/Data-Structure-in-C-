#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INITVOL 100
struct STACK
{
    char *data;
    int top;
    int vol;
};
typedef struct STACK stack;

int init(stack *s);
void destroy(stack *s);
void push(stack *s, char e);
void pop(stack *s, char *e);
int is_empty(stack s);
void sprint(stack s)
{
    printf("\ndepth:%d\nbottom-> ", s.top + 1);
    for (int i = 0; i <= s.top; i++)
        printf("%d ", s.data[i]);
    printf("<-top\n");
    return;
}
int s_palindrome(char *, int);
int r_palindrome(char *, int);
int main()
{
    char a[] = {'a', 'b', 'd', 'b', 'a'};
    printf("stack: %d\n", s_palindrome(a, 5));
    printf("recursion: %d\n", r_palindrome(a, 5));
    return 0;
}
int init(stack *s)
{
    s->data = (char *)malloc(INITVOL * sizeof(char));
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
void push(stack *s, char e)
{
    if (s->top == s->vol - 1)
    {
        char *temp = (char *)malloc((s->vol + INITVOL) * sizeof(char));
        if (!temp)
            return;
        memcpy(temp, s->data, s->vol * sizeof(char));
        free(s->data);
        s->data = temp;
        s->vol += INITVOL;
    }
    s->data[s->top + 1] = e;
    s->top++;
}
void pop(stack *s, char *e)
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
int s_palindrome(char *s, int slen)
{
    stack st;
    init(&st);
    char *p;
    int i;
    for (i = 0; i < slen / 2; i++)
    {
        push(&st, s[i]);
    }
    i += !(i % 2);
    while (i < slen)
    {
        if (is_empty(st))
        {
            destroy(&st);
            return 0;
        }
        char tmp;
        pop(&st, &tmp);
        if (tmp != s[i])
        {
            destroy(&st);
            return 0;
        }
        i++;
    }
    int res = is_empty(st);
    destroy(&st);
    return res;
}
int r_palindrome(char *s, int slen)
{
    if (slen <= 1)
        return 1;
    else if (s[0] == s[slen - 1])
        return r_palindrome(s + 1, slen - 2);
    else
        return 0;
}