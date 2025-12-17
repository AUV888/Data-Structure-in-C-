#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "hash_adt.h"
#include "trie.h"
#include "trie_adt.h"
#define INPUT_1_PATH "../data/1M_Domain.txt"
#define INPUT_2_PATH "../data/550K_DomainLess15Char.txt"

int main()
{
    printf("START:\n");
    tset t = NULL;
    hset *s = create_hset();
    InitSet(s);

    FILE *fp = fopen(INPUT_1_PATH, "r");
    if (!fp)
        return 1;
    char line[256];
    while (fgets(line, sizeof(line), fp))
    {
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n')
        {
            line[len - 1] = '\0';
            len--;
        }
        if (SetInsert(s, line) == 0 || tSetInsert(&t, line) == 0)
        {
            printf("Failed to insert: %s\n", line);
        }
    }
    fclose(fp);
    printf("INSERT HASH & TRIE OK\n");
    unsigned long ss = SetSize(s);
    unsigned long ts = tSetSize(t);
    printf("INITIAL SIZE: HASH %ld TIRE %ld\n", ss, ts);
    char a[20] = "bupt.edu.cn", b[20] = "tiktok.com";
    printf("bupt.edu.cn FIND: HASH %d  TRIE %d\n", SetFind(s, a), tSetFind(t, a));
    printf("ERASED tiktok.com IN HASH & TRIE\n");
    SetErase(s, b);
    tSetErase(&t, b);
    int sf = SetFind(s, b);
    int tf = tSetFind(t, b);
    printf("TRY TO FIND tiktok.com: HASH %d TRIE %d\n", sf, tf);
    ss = SetSize(s);
    ts = tSetSize(t);
    printf("SIZE: HASH %ld TRIE %ld\n", ss, ts);
    DestroySet(&s);
    printf("HASH DESTORY OK\n");
    tDestroySet(&t);
    printf("\nTRIE DESTROY OK\n");
    return 0;
}
