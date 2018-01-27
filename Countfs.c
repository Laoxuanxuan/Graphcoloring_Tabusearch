/*计算冲突边数量的函数*/
#include"head.h"
int Countfs(int Arc[][N + 1], int *ver, int n);

int Countfs(int Arc[][N + 1], int *ver, int n)
{
	int Vcolor;//用来存顶点结点的颜色
	int i, j;//循环变量
	int fs = 0;//冲突边数量
	for(i = 1; i <= N; i++)
		for (j = 1; j <= N; j++)
		{
			if (Arc[i][j] == 1 && ver[i] == ver[j])
				fs++;
		}
	return fs / 2;
}