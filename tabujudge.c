#include"head.h"
void set_tabu(int u, int oldcol, int *fs, int Tabutable[][MAX_K], int step);
int Aspiration(int u, int oldcol, int newcol, int Adjcol[][MAX_K], int *fs, int *bestfssofar);
int judge_tabu(int Tabutable[][MAX_K], int v, int c, int step);

void set_tabu(int u, int oldcol, int *fs, int Tabutable[][MAX_K], int step)//设置禁忌步长,更新禁忌表
{
	int t;
	t = rand() % 10 + 1;
	Tabutable[u][oldcol] =  *fs + t + step;
}

int judge_tabu(int Tabutable[][MAX_K], int v, int c, int step)//判断邻域动作是否为禁忌的
{
	if(Tabutable[v][c] < step)
		return 1;
	else
		return 0;
}

int Aspiration(int u, int oldcol, int newcol, int Adjcol[][MAX_K],int *fs,int *bestfssofar)//解禁策略
{
	int tdeltfs = Adjcol[u][newcol] - Adjcol[u][oldcol];
	int tfs = *fs + tdeltfs;
	if (tfs < *bestfssofar)
		return 1;
	else
		return 0;
}