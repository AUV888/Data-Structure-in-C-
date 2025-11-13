#define NOT_FOUND 0
#define EMPTY 0
#define FOUND 1

int Parent(int bt[], int x)
{
    for (int i = 1; i <= bt[0]; i++)
    {
        if (bt[i] == x)
            return bt[i / 2];
    }
    return NOT_FOUND;
}

int LChild(int bt[], int x)
{
    for (int i = 1; i <= bt[0]; i++)
    {
        if (bt[i] == x)
            return bt[2 * x];
    }
    return NOT_FOUND;
}

int DeleteLChild(int **bt, int x)
{
    for (int i = 1; i <= (*bt)[0]; i++)
    {
        if ((*bt)[i] == x)
        {
            int j = 2 * i, cnt = 1;
            while (j <= (*bt)[0])
            {
                for (int k = 0; k < cnt; k++)
                    if (j + k <= (*bt)[0])
                        (*bt)[j + k] = EMPTY;
                    else
                        break;
                j *= 2;
                cnt *= 2;
            }
            return FOUND;
        }
    }
    return NOT_FOUND;
}