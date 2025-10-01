#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define init_len 5
typedef int elem;

struct ListStruct
{
    elem *val;
    int len;
    int head_idx;
    int volume;
};

typedef struct ListStruct list;

int InitList(list *l)
{
    if (l == NULL)
    {
        fprintf(stderr, "Cannot Initialize Such List\n");
        return 0;
    }
    l->val = (elem *)malloc(init_len * sizeof(elem));
    l->len = 0;
    l->head_idx = 0;
    l->volume = init_len;
    return 1;
}

void DestroyList(list *l)
{
    if (l == NULL || l->val == NULL)
    {
        fprintf(stderr, "Cannot Destroy Empty List\n");
        return;
    }
    free(l->val);
    l->val = NULL;
    l->len = 0;
    l->head_idx = 0;
    l->volume = 0;
    return;
}

void GetElem(list l, int idx, elem *e) // index count from 1
{
    if (idx < 1 || idx > l.len) // error
    {
        fprintf(stderr, "Cannot Fetch: Illeagal Index\n");
        return;
    }
    int real_idx = (idx + l.head_idx - 1) % l.volume;
    *e = l.val[real_idx];
    return;
}

void ListInsert(list *l, int idx, elem e)
{
    if (idx < 1 || idx > l->len + 1) // error
    {
        fprintf(stderr, "Cannot Insert: Illeagal Index\n");
        return;
    }
    if (l->len + 1 > l->volume) // expand volume
    {
        int new_volume = l->volume * 2;
        elem *copy = (elem *)malloc(l->volume * sizeof(elem));
        if (copy == NULL)
        {
            fprintf(stderr, "Cannot Re-allocate Memory\n");
            return;
        }
        memcpy(copy, l->val, l->volume * sizeof(elem));
        free(l->val);
        l->val = (elem *)malloc(new_volume * sizeof(elem));
        if (l->val == NULL)
        {
            fprintf(stderr, "Cannot Re-allocate Memory\n");
            return;
        }

        for (int i = 0; i < l->len; i++)
        {
            int real = (l->head_idx + i + l->volume) % l->volume;
            l->val[i] = copy[real];
        }
        free(copy);
        l->volume = new_volume;
        l->head_idx = 0;
    }
    if (idx == 1) // insert at head
    {
        l->head_idx = (l->head_idx + l->volume - 1) % l->volume;
        l->val[l->head_idx] = e;
        l->len++;
        return;
    }
    else if (idx == l->len + 1) // insert at tail
    {
        l->val[(l->head_idx + l->len) % l->volume] = e;
        l->len++;
        return;
    }

    if (idx > l->len / 2) // move rear part
    {
        for (int i = l->len; i >= idx; i--)
        {
            int cur_real = (l->head_idx + i - 1) % l->volume;
            int tar_real = (l->head_idx + i) % l->volume;
            l->val[tar_real] = l->val[cur_real];
        }
        int real_idx = (idx + l->head_idx - 1) % l->volume;
        l->val[real_idx] = e; // insert the element
    }
    else // move front part
    {
        l->head_idx = (l->head_idx + l->volume - 1) % l->volume;
        for (int i = 1; i < idx; i++)
        {
            int cur_real = (l->head_idx + i + 1) % l->volume;
            int tar_real = (l->head_idx + i) % l->volume;
            l->val[tar_real] = l->val[cur_real];
        }
        int real_idx = (l->head_idx + idx - 1) % l->volume;
        l->val[real_idx] = e;
    }

    l->len++;
    return;
}

void ListDelete(list *l, int idx, elem *e)
{
    if (idx < 1 || idx > l->len)
    {
        fprintf(stderr, "Cannot Delete: Illegal Index\n");
        return;
    }
    int real_idx = (l->head_idx + idx - 1) % l->volume;
    *e = l->val[real_idx];
    if (idx == 1)
    {
        l->head_idx = (l->head_idx + 1) % l->volume;
    }
    else if (idx == l->len)
    {
    }
    else if (idx > l->len / 2)
    {
        for (int i = idx; i <= l->len - 1; i++)
        {
            int cur_real = (l->head_idx + i - 1) % l->volume;
            int nxt_real = (l->head_idx + i) % l->volume;
            l->val[cur_real] = l->val[nxt_real];
        }
    }
    else
    {
        for (int i = idx - 1; i >= 1; i--)
        {
            int cur_real = (l->head_idx + i) % l->volume;
            int pre_real = (l->head_idx + i - 1) % l->volume;
            l->val[cur_real] = l->val[pre_real];
        }
        l->head_idx = (l->head_idx + 1) % l->volume;
    }
    l->len--;
    return;
}

void PrintList(list l) // for debug usage
{
    if (l.len == 0)
    {
        printf("Empty List\n");
        return;
    }
    for (int i = 0; i < l.len; i++)
    {
        int r = (l.head_idx + i) % l.volume;
        printf("%d ", l.val[r]);
    }
    printf("\n");
}

int main()
{
    list L;
    int temp;
    InitList(&L);
    ListInsert(&L, 1, 3);
    PrintList(L);
    ListInsert(&L, 2, 4);
    PrintList(L);
    ListInsert(&L, 3, 5);
    PrintList(L);
    ListInsert(&L, 1, 7);
    PrintList(L);
    ListInsert(&L, 4, 9);
    PrintList(L);
    GetElem(L, 4, &temp);
    printf("Get Element [4]: %d\n", temp);
    ListInsert(&L, 3, 11);
    PrintList(L);
    ListDelete(&L, 4, &temp);
    PrintList(L);
    ListDelete(&L, 1, &temp);
    PrintList(L);
    ListDelete(&L, 4, &temp);
    PrintList(L);
    DestroyList(&L);
    PrintList(L);
    return 0;
}