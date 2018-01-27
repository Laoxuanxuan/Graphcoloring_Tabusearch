#include"head.h"
void main()
{
	srand((unsigned int)time(NULL));
	clock_t  stt = clock();
	int k;
	k = 52;
	int ver[N + 1];//����N�����㣬�����±�Ϊ������ţ�����ֵΪ������ɫ
	int Arc[N + 1][N + 1];//�洢����Ϣ���ڽӱ�

	int i, j;
	for (i = 1; i <= N; i++)
	{
		ver[i] = random(k) + 1;//�����������ɫ
		for (j = 1; j <= N; j++)
			Arc[i][j] = 0;//��ʼ��������
	}
	char *graph = "DSJC500.5.col";
	initial(Arc, graph);
	int fs = Countfs(Arc, ver, N);
	int bestfssofar = fs;
	int Adjcol[N + 1][MAX_K];//����Adjacent-Color Table
	Creat_Adjcol(Arc, ver, N, k, Adjcol);//��ʼ��Adjacent-Color Table
	int Tabutable[N + 1][MAX_K];//������ɱ�
	for (i = 1; i <= N; i++)
		for (j = 1; j <= k; j++)
			Tabutable[i][j] = 0;//��ʼ�����ɱ�
	long int step = 1;//��¼��������
	
	int Vconflict[N + 1];
	int Conflict_loc[N + 1];
	initial_conflict(ver, Arc, Vconflict, Conflict_loc);

	while (fs != 0)
	{
		Neiaction(Arc, ver, N, k, Adjcol, Tabutable, &fs, step, &bestfssofar, Vconflict, Conflict_loc);
		if (step % 100000 == 0)
			printf("��ǰ���Ž⣺%d\t����������%d\n", bestfssofar, step);
		step++;
	}
	Output(step, k, graph, stt, ver);
}