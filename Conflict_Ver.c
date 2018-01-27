#include"head.h"
void initial_conflict(int *ver, int Arc[][N + 1], int *Vconflict, int *Conflict_loc);
void new_ConAdj(int u, int oldcol, int newcol, int *ver, int Arc[][N + 1], int Adjcol[][MAX_K], int *Vconflict, int *Conflict_loc);
void initial_conflict(int *ver, int Arc[][N + 1], int *Vconflict, int *Conflict_loc)
{
	int i, j, c;
	for (i = 0; i <= N; i++)
	{
		Vconflict[i] = 0;
		Conflict_loc[i] = 0;
	}
	for (i = 1; i <= N; i++)
	{
		for(j = 1; j <= N; j++)
			if (Arc[i][j] == 1 && ver[j] == ver[i])
			{
				c = Vconflict[0] + 1;
				Vconflict[c] = i;
				Conflict_loc[i] = c;
				Vconflict[0]++;
				break;
			}
	}
}

void new_ConAdj(int u, int oldcol, int newcol, int *ver, int Arc[][N + 1], int Adjcol[][MAX_K], int *Vconflict, int *Conflict_loc)
{
	int i, l, c, t;
	if (Adjcol[u][oldcol] != 0 && Adjcol[u][newcol] == 0)
	{
		l = Conflict_loc[u];
		c = Vconflict[0];
		t = Vconflict[c];
		Vconflict[l] = t;
		Vconflict[c] = 0;
		Conflict_loc[u] = 0;
		Conflict_loc[t] = l;
		Vconflict[0]--;
	}
	else if (Adjcol[u][oldcol] == 0 && Adjcol[u][newcol] != 0)
	{
		c = Vconflict[0];
		Vconflict[c + 1] = u;
		Conflict_loc[u] = c + 1;
		Vconflict[0]++;
	}
	for (i = 1; i <= N; i++)
		if (Arc[u][i] == 1)
		{
			if (ver[i] == oldcol && Adjcol[i][oldcol] == 1)
			{
				l = Conflict_loc[i];
				c = Vconflict[0];
				t = Vconflict[c];
				Vconflict[l] = t;
				Vconflict[c] = 0;
				Conflict_loc[i] = 0;
				Conflict_loc[t] = l;
				Vconflict[0]--;
			}
			else if (ver[i] == newcol && Adjcol[i][newcol] == 0)
			{
				c = Vconflict[0];
				Vconflict[c + 1] = i;
				Conflict_loc[i] = c + 1;
				Vconflict[0]++;
			}
			Adjcol[i][oldcol]--;
			Adjcol[i][newcol]++;
		}
}