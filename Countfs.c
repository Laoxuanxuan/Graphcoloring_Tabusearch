/*�����ͻ�������ĺ���*/
#include"head.h"
int Countfs(int Arc[][N + 1], int *ver, int n);

int Countfs(int Arc[][N + 1], int *ver, int n)
{
	int Vcolor;//�����涥�������ɫ
	int i, j;//ѭ������
	int fs = 0;//��ͻ������
	for(i = 1; i <= N; i++)
		for (j = 1; j <= N; j++)
		{
			if (Arc[i][j] == 1 && ver[i] == ver[j])
				fs++;
		}
	return fs / 2;
}