#include <stdlib.h>
#include <stdio.h>

// SwapInt，交换x和y指向的内存地址的值
bool SwapInt(int *x, int *y);

// ThreeIntSort，输入的整数存放在x1，x2，x3指向的内存地址
// 输出：要求x1，x2，x3地址中存放的整数是按照从小到大的顺序排好的
// 返回值：true，排序成功；false，排序失败。
bool ThreeIntSort(int *x1, int *x2, int *x3);

// FourIntSort，输入的整数存放在x1，x2，x3，x4指向的内存地址
// 输出：要求x1，x2，x3，x4地址中存放的整数是按照从小到大的顺序排好的
// 返回值：true，排序成功；false，排序失败。
bool FourIntSort(int *x1, int *x2, int *x3, int *x4);

// ThreeIntSort，输入的整数存放在x1，x2，x3，x4，x5指向的内存地址
// 输出：要求x1，x2，x3，x4，x5地址中存放的整数是按照从小到大的顺序排好的
// 返回值：true，排序成功；false，排序失败。
bool FiveIntSort(int *x1, int *x2, int *x3, int *x4, int *x5);

int main()
{
	int a, b, c, d, e;

	// 从命令行或其他方式读入5个整数，放在a b c d e五个变量里
	// 补充实现代码

	if (ThreeIntSort(/*补充实现代码*/))
		printf("\n 前三个整数排序结果：%d %d %d\n", a, b, c);

	if (FourIntSort(/*补充实现代码*/))
		printf("\n 前四个整数排序结果：%d %d %d %d\n", a, b, c, d);

	if (FiveIntSort(/*补充实现代码*/))
		printf("\n 前五个整数排序结果：%d %d %d %d %d\n", a, b, c, d, e);

	return 0;
}

bool ThreeIntSort(int *x1, int *x2, int *x3)
{
	// 补充实现代码
}
bool FourIntSort(int *x1, int *x2, int *x3, int *x4)
{
	// 补充实现代码
}
bool FiveIntSort(int *x1, int *x2, int *x3, int *x4, int *x5)
{
	// 补充实现代码
}

bool SwapInt(int *x, int *y)
{
	// 补充实现代码
}
