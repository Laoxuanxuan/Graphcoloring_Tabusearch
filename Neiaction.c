#include"head.h"
void Creat_Adjcol(int Arc[][N + 1], int *ver, int n, int k, int Adjcol[][MAX_K]);//����Adjacent-Color Table
void Neiaction(int Arc[][N + 1], int *ver, int n, int k, int Adjcol[][MAX_K], int Tabutable[][MAX_K], int *fs, int step, int *bestfssofar, int *Vconflict, int *Conflict_loc);//һ��������
int random(int k);//1/k�Ŀ��ܷ���0

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
void Neiaction(int Arc[][N + 1], int *ver, int n, int k, int Adjcol[][MAX_K], int Tabutable[][MAX_K], int *fs, int step, int *bestfssofar, int *Vconflict, int *Conflict_loc)//ִ��һ���������ĺ���
{
	int i, j, t, ii;
	int deltfs;//��ͻ��������С��ֵ
	int u, oldcol, newcol;//�������Ķ�����ţ�����ɫ������ɫ
	int toldcol;
	int tabudeltfs = 500, ctabudeltfs = 1;//��¼���ɶ�������õ�
	int tabu_u, tabu_oldcol, tabu_newcol;
	int notabudeltfs = 500, cnotabudeltfs = 1;//��¼�ǽ��ɶ�������õ�
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
				if (!judge_tabu(Tabutable, i, j, step))//���һ�������ǽ��ɵ�
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
				else//���һ�������Ƿǽ��ɵ�
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
	}//ȷ�������������Ķ�����ţ�����ɫ������ɫ
	
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
	/*���½��ɱ�*/
	set_tabu(u, oldcol, fs, Tabutable, step);
	//printf("��ǰ���Ž�Ϊ��%d\t", *bestfssofar);

	ver[u] = newcol;
	/*���´��ͻ�ڵ�������������ɫ��*/
	new_ConAdj(u, oldcol, newcol, ver, Arc, Adjcol, Vconflict, Conflict_loc);
}

int random(int k)//1/k�Ŀ��ܷ���0
{
	int t;
	t = rand() % k;
	return t;
}
