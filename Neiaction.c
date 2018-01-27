#include"head.h"
void Creat_Adjcol(int Arc[][N + 1], int *ver, int n, int k, int Adjcol[][MAX_K]);//生成Adjacent-Color Table
void Neiaction(int Arc[][N + 1], int *ver, int n, int k, int Adjcol[][MAX_K], int Tabutable[][MAX_K], int *fs, int step, int *bestfssofar, int *Vconflict, int *Conflict_loc);//一次邻域动作
int random(int k);//1/k的可能返回0

void Creat_Adjcol(int Arc[][N + 1], int *ver, int n, int k, int Adjcol[][MAX_K])
{
	int i, j, t;
	for (i = 1; i <= n; i++)
		for (j = 1; j <= k; j++)
			Adjcol[i][j] = 0;
	for (i = 1; i <= n; i++)
		for (j = 1; j <= n; j++)
		{
			t = ver[j];
			if (Arc[i][j] == 1)
				Adjcol[i][t]++;
		}
}
void Neiaction(int Arc[][N + 1], int *ver, int n, int k, int Adjcol[][MAX_K], int Tabutable[][MAX_K], int *fs, int step, int *bestfssofar, int *Vconflict, int *Conflict_loc)//执行一次邻域动作的函数
{
	int i, j, t, ii;
	int deltfs;//冲突边数量减小的值
	int u, oldcol, newcol;//邻域动作的顶点序号，老颜色，新颜色
	int toldcol;
	int tabudeltfs = 500, ctabudeltfs = 1;//记录禁忌动作中最好的
	int tabu_u, tabu_oldcol, tabu_newcol;
	int notabudeltfs = 500, cnotabudeltfs = 1;//记录非禁忌动作中最好的
	int notabu_u, notabu_oldcol, notabu_newcol;
	int tdeltfs;
	int ll;
	for (ii = 1; ii <= Vconflict[0]; ii++)
	{
		i = Vconflict[ii];
		toldcol = ver[i];
		for (j = 1; j <= k; j++)
		{
			if (j != toldcol)
			{
				if (!judge_tabu(Tabutable, i, j, step))//如果一个动作是禁忌的
				{
					tdeltfs = Adjcol[i][j] - Adjcol[i][toldcol];
					if (tdeltfs < tabudeltfs)
					{
						tabudeltfs = tdeltfs;
						tabu_u = i; tabu_oldcol = toldcol; tabu_newcol = j;
						ctabudeltfs = 2;

					}
					else if (tdeltfs == tabudeltfs)
					{
						if (!random(ctabudeltfs)) {
							tabu_u = i; tabu_oldcol = toldcol; tabu_newcol = j;
						}
						ctabudeltfs++;
					}
				}
				else//如果一个动作是非禁忌的
				{
					tdeltfs = Adjcol[i][j] - Adjcol[i][toldcol];
					if (tdeltfs < notabudeltfs)
					{
						notabudeltfs = tdeltfs;
						notabu_u = i; notabu_oldcol = toldcol; notabu_newcol = j;
						cnotabudeltfs = 2;
					}
					else if (tdeltfs == notabudeltfs)
					{
						if (!random(cnotabudeltfs)) {
							notabu_u = i; notabu_oldcol = toldcol; notabu_newcol = j;
						}
						cnotabudeltfs++;
					}
				}
			}
			
		}
	}//确定出了邻域动作的顶点序号，老颜色，新颜色
	
	if (tabudeltfs < notabudeltfs && Aspiration(tabu_u, tabu_oldcol, tabu_newcol, Adjcol, fs, bestfssofar))
	{
		deltfs = tabudeltfs;
		u = tabu_u; oldcol = tabu_oldcol; newcol = tabu_newcol;
	}
	else
	{
		deltfs = notabudeltfs;
		u = notabu_u; oldcol = notabu_oldcol; newcol = notabu_newcol;
	}
	*fs = *fs + deltfs;
	if (*fs < *bestfssofar)
		*bestfssofar = *fs;

	if (*fs < 0)
		ll = 1;
	/*更新禁忌表*/
	set_tabu(u, oldcol, fs, Tabutable, step);
	//printf("当前最优解为：%d\t", *bestfssofar);

	ver[u] = newcol;
	/*更新存冲突节点的两个数组和颜色表*/
	new_ConAdj(u, oldcol, newcol, ver, Arc, Adjcol, Vconflict, Conflict_loc);
}

int random(int k)//1/k的可能返回0
{
	int t;
	t = rand() % k;
	return t;
}
