#include"head.h"
void main()
{
	srand((unsigned int)time(NULL));
	clock_t  stt = clock();
	int k;
	k = 52;
	int ver[N + 1];//定义N个顶点，数组下标为顶点序号，数组值为顶点颜色
	int Arc[N + 1][N + 1];//存储边信息的邻接表

	int i, j;
	for (i = 1; i <= N; i++)
	{
		ver[i] = random(k) + 1;//随机给顶点颜色
		for (j = 1; j <= N; j++)
			Arc[i][j] = 0;//初始化边数组
	}
	char *graph = "DSJC500.5.col";
	initial(Arc, graph);
	int fs = Countfs(Arc, ver, N);
	int bestfssofar = fs;
	int Adjcol[N + 1][MAX_K];//定义Adjacent-Color Table
	Creat_Adjcol(Arc, ver, N, k, Adjcol);//初始化Adjacent-Color Table
	int Tabutable[N + 1][MAX_K];//定义禁忌表
	for (i = 1; i <= N; i++)
		for (j = 1; j <= k; j++)
			Tabutable[i][j] = 0;//初始化禁忌表
	long int step = 1;//记录迭代次数
	
	int Vconflict[N + 1];
	int Conflict_loc[N + 1];
	initial_conflict(ver, Arc, Vconflict, Conflict_loc);

	while (fs != 0)
	{
		Neiaction(Arc, ver, N, k, Adjcol, Tabutable, &fs, step, &bestfssofar, Vconflict, Conflict_loc);
		if (step % 100000 == 0)
			printf("当前最优解：%d\t迭代次数：%d\n", bestfssofar, step);
		step++;
	}
	Output(step, k, graph, stt, ver);
}