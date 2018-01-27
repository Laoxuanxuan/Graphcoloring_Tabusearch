#include"head.h"

void initial(int Arc[][N + 1], char *graph);

void initial(int Arc[][N + 1], char *graph)//将图的顶点之间的相互关系存到邻接矩阵中
{
	FILE* fp = NULL;
	errno_t err = 0;
	err = fopen_s(&fp, graph, "r");
	if (err == 0)
	{
		int t1 = 0, t2 = 0, c = 0;//t1，t2暂存从文件中读入的数字
		char s[5];
		while (1)
		{
			if(fscanf(fp, "%s", s) != EOF)//读取每行的e
			{
				fscanf(fp, "%d", &t1);//读每行第一个数存入t1
				fscanf(fp, "%d", &t2);//读每行第二个数存入t2
				Arc[t1][t2] = 1;
				Arc[t2][t1] = 1;
			}
			else
			{
				printf("无向图边信息读取完毕！\n");
				break;
			}
			c++;//记录循环次数的变量+1
		}
		printf("边总数为%d\n", c);
	}
}



