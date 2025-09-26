#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#define N 500
// SwapInt，交换x和y指向的内存地址的值
void SwapInt(int *x, int *y);

// ThreeIntSort，输入的整数存放在x1，x2，x3指向的内存地址
// 输出：要求x1，x2，x3地址中存放的整数是按照从小到大的顺序排好的
// 返回值：true，排序成功；false，排序失败。
int ThreeIntSort(int *x1, int *x2, int *x3);

// FourIntSort，输入的整数存放在x1，x2，x3，x4指向的内存地址
// 输出：要求x1，x2，x3，x4地址中存放的整数是按照从小到大的顺序排好的
// 返回值：true，排序成功；false，排序失败。
int FourIntSort(int *x1, int *x2, int *x3, int *x4);

// FiveIntSort，输入的整数存放在x1，x2，x3，x4，x5指向的内存地址
// 输出：要求x1，x2，x3，x4，x5地址中存放的整数是按照从小到大的顺序排好的
// 返回值：true，排序成功；false，排序失败。
int FiveIntSort(int *x1, int *x2, int *x3, int *x4, int *x5);

int cmp(int *a, int *b, int *comp_count)
{
	(*comp_count)++;
	if (*a > *b)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

struct Permutations
{
	int len;
	int arr[N][5];
	int min_exc;
	int max_exc;
	int tot;
};

void Generate_Permutations(int n, struct Permutations *p)
{
	if (n == 3)
	{
		p->max_exc = INT_MIN;
		p->min_exc = INT_MAX;
		p->tot = 0;
		p->len = 0;
		int cnt = 0;
		for (int i = 10; i < 10 + n; i++)
		{
			for (int j = 10; j < 10 + n; j++)
			{
				for (int k = 10; k < 10 + n; k++)
				{
					if (i != j && j != k && k != i)
					{
						p->arr[cnt][0] = i;
						p->arr[cnt][1] = j;
						p->arr[cnt][2] = k;
						cnt++;
						p->len++;
					}
				}
			}
		}
	}
	else if (n == 4)
	{
		p->len = 0;
		p->max_exc = INT_MIN;
		p->min_exc = INT_MAX;
		p->tot = 0;
		int cnt = 0;
		for (int i = 10; i < 10 + n; i++)
		{
			for (int j = 10; j < 10 + n; j++)
			{
				for (int k = 10; k < 10 + n; k++)
				{
					for (int l = 10; l < 10 + n; l++)
					{
						if (i != j && i != k && i != l &&
							j != k && j != l &&
							k != l)
						{
							p->arr[cnt][0] = i;
							p->arr[cnt][1] = j;
							p->arr[cnt][2] = k;
							p->arr[cnt][3] = l;
							cnt++;
							p->len++;
						}
					}
				}
			}
		}
	}
	else if (n == 5)
	{
		p->len = 0;
		p->max_exc = INT_MIN;
		p->min_exc = INT_MAX;
		p->tot = 0;
		int cnt = 0;
		for (int i = 10; i < 10 + n; i++)
		{
			for (int j = 10; j < 10 + n; j++)
			{
				for (int k = 10; k < 10 + n; k++)
				{
					for (int l = 10; l < 10 + n; l++)
					{
						for (int m = 10; m < 10 + n; m++)
						{
							if (i != j && i != k && i != l && i != m &&
								j != k && j != l && j != m &&
								k != l && k != m &&
								l != m)
							{
								p->arr[cnt][0] = i;
								p->arr[cnt][1] = j;
								p->arr[cnt][2] = k;
								p->arr[cnt][3] = l;
								p->arr[cnt][4] = m;
								cnt++;
								p->len++;
							}
						}
					}
				}
			}
		}
	}
	return;
}

int main()
{
	struct Permutations P3, P4, P5;
	Generate_Permutations(3, &P3);
	Generate_Permutations(4, &P4);
	Generate_Permutations(5, &P5);
	// 验证ThreeInt
	for (int i = 0; i < P3.len; i++)
	{
		printf("a=%d b=%d c=%d ", P3.arr[i][0], P3.arr[i][1], P3.arr[i][2]);
		int time = ThreeIntSort(&P3.arr[i][0], &P3.arr[i][1], &P3.arr[i][2]);
		if (time == -1)
		{
			printf("无法排序\n");
			continue;
		}
		P3.tot += time;
		if (time < P3.min_exc)
		{
			P3.min_exc = time;
		}
		if (time > P3.max_exc)
		{
			P3.max_exc = time;
		}
		if (P3.arr[i][0] < P3.arr[i][1] < P3.arr[i][2])
		{
			printf(" 通过\n");
		}
		else
		{
			printf("错误！\n");
		}
	}
	printf("------\n3数排序最好结果:%d\t最坏结果%d\t平均结果%f\n------\n", P3.min_exc, P3.max_exc, 1.0 * P3.tot / P3.len);
	// 验证FourInt
	for (int i = 0; i < P4.len; i++)
	{
		printf("a=%d b=%d c=%d d=%d ", P4.arr[i][0], P4.arr[i][1], P4.arr[i][2], P4.arr[i][3]);
		int time = FourIntSort(&P4.arr[i][0], &P4.arr[i][1], &P4.arr[i][2], &P4.arr[i][3]);
		if (time == -1)
		{
			printf("无法排序\n");
			continue;
		}
		P4.tot += time;
		if (time < P4.min_exc)
		{
			P4.min_exc = time;
		}
		if (time > P4.max_exc)
		{
			P4.max_exc = time;
		}
		if (P4.arr[i][0] < P4.arr[i][1] < P4.arr[i][2] < P4.arr[i][3])
		{
			printf(" 通过\n");
		}
		else
		{
			printf("错误！\n");
		}
	}
	printf("------\n4数排序最好结果:%d\t最坏结果%d\t平均结果%f\n------\n", P4.min_exc, P4.max_exc, 1.0 * P4.tot / P4.len);
	// 验证FiveInt
	for (int i = 0; i < P5.len; i++)
	{
		printf("a=%d b=%d c=%d d=%d ", P5.arr[i][0], P5.arr[i][1], P5.arr[i][2], P5.arr[i][3], P5.arr[i][4]);
		int time = FiveIntSort(&P5.arr[i][0], &P5.arr[i][1], &P5.arr[i][2], &P5.arr[i][3], &P5.arr[i][4]);
		if (time == -1)
		{
			printf("无法排序\n");
			continue;
		}
		P5.tot += time;
		if (time < P5.min_exc)
		{
			P5.min_exc = time;
		}
		if (time > P5.max_exc)
		{
			P5.max_exc = time;
		}
		if (P5.arr[i][0] < P5.arr[i][1] < P5.arr[i][2] < P5.arr[i][3] < P5.arr[i][4])
		{
			printf(" 通过\n");
		}
		else
		{
			printf("错误！\n");
		}
	}
	printf("------\n5数排序最好结果:%d\t最坏结果%d\t平均结果%f\n------\n", P5.min_exc, P5.max_exc, 1.0 * P5.tot / P5.len);
	return 0;
}

int ThreeIntSort(int *x1, int *x2, int *x3)
/*ThreeIntSort中，比较语句总是3次，无论最好、最差还是平均。*/
{
	int three_cnt = 0;
	if (x1 == NULL || x2 == NULL || x3 == NULL)
		return -1;
	// 展开的冒泡排序
	if (cmp(x1, x2, &three_cnt))
	{
		SwapInt(x1, x2);
	}
	if (cmp(x2, x3, &three_cnt))
	{
		SwapInt(x2, x3);
	}
	if (cmp(x1, x2, &three_cnt))
	{
		SwapInt(x1, x2);
	}
	return three_cnt;
}
int FourIntSort(int *x1, int *x2, int *x3, int *x4)
{
	int four_cnt = 0;
	/*FourIntSort中，比较语句总是6次，无论最好、最差还是平均。*/
	if (x1 == NULL || x2 == NULL || x3 == NULL || x4 == NULL)
		return -1;
	// 展开的冒泡排序
	if (cmp(x1, x2, &four_cnt))
	{
		SwapInt(x1, x2);
	}
	if (cmp(x2, x3, &four_cnt))
	{
		SwapInt(x2, x3);
	}
	if (cmp(x3, x4, &four_cnt))
	{
		SwapInt(x3, x4);
	}
	if (cmp(x1, x2, &four_cnt))
	{
		SwapInt(x1, x2);
	}
	if (cmp(x2, x3, &four_cnt))
	{
		SwapInt(x2, x3);
	}
	if (cmp(x1, x2, &four_cnt))
	{
		SwapInt(x1, x2);
	}
	return four_cnt;
}
int FiveIntSort(int *x1, int *x2, int *x3, int *x4, int *x5)
{
	int five_cnt = 0;
	/*FiveIntSort中，比较语句总是3次，无论最好、最差还是平均。*/
	if (x1 == NULL || x2 == NULL || x3 == NULL || x4 == NULL || x5 == NULL)
		return -1;
	// 展开的冒泡排序
	if (cmp(x1, x2, &five_cnt))
	{
		SwapInt(x1, x2);
	}
	if (cmp(x2, x3, &five_cnt))
	{
		SwapInt(x2, x3);
	}
	if (cmp(x3, x4, &five_cnt))
	{
		SwapInt(x3, x4);
	}
	if (cmp(x4, x5, &five_cnt))
	{
		SwapInt(x4, x5);
	}
	if (cmp(x1, x2, &five_cnt))
	{
		SwapInt(x1, x2);
	}
	if (cmp(x2, x3, &five_cnt))
	{
		SwapInt(x2, x3);
	}
	if (cmp(x3, x4, &five_cnt))
	{
		SwapInt(x3, x4);
	}
	if (cmp(x1, x2, &five_cnt))
	{
		SwapInt(x1, x2);
	}
	if (cmp(x2, x3, &five_cnt))
	{
		SwapInt(x2, x3);
	}
	if (cmp(x1, x2, &five_cnt))
	{
		SwapInt(x1, x2);
	}
	return five_cnt;
}
void SwapInt(int *x, int *y)
{
	int t = *x;
	*x = *y;
	*y = t;
}
