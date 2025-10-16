#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TOTAL 500000      /* 50 万条 */
#define MAX_LEN 10        /* 最长 20 字母 */
#define MIN_LEN 1         /* 最短 1 字母  */

int main(void)
{
    /* 临时缓冲区，只需 20+1 字节 */
    char buf[MAX_LEN + 1];

    /* 1. 播种 */
    srand((unsigned)time(NULL));

    /* 2. 生成 50 万行 */
    for (size_t i = 0; i < TOTAL; ++i) {
        /* 随机长度 1..20 */
        int len = MIN_LEN + rand() % (MAX_LEN - MIN_LEN + 1);

        /* 逐字母填 a-z */
        for (int k = 0; k < len; ++k)
            buf[k] = 'a' + rand() % 26;
        buf[len] = '\0';

        /* 3. 输出：长度 空格 单词 换行 */
        printf("%d %s\n", len, buf);
    }
    return 0;
}