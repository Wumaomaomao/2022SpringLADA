#include<iostream>
#include<string.h>
#define M 123456
#define N 23456
using namespace std;

struct Node
{
	int to, net;
};
Node edge[M * 2];
int tot = 1;
int head[N];
int value[N];
int Maxvalue[N];
bool start[N];
int MaxTime = 0;

int n;

void initvalue()
{
	memset(value, 0, sizeof(int) * N);
	memset(Maxvalue, 0, sizeof(int) * N);
	int idx, val;
	for (int i = 0; i < n; ++i)
	{
		cin >> idx >> val;
		value[idx] = val;
	}

	return;
}

void initgra()
{
	memset(head, 0, N * sizeof(int));
	memset(start, 0, N * sizeof(bool));
	int u, v;
	while (cin >> u >> v)
	{
		edge[tot].to = v;
		edge[tot].net = head[u];
		head[u] = tot;
		++tot;
		start[v] = true;
	}
}

void dfs_CriPath(int u)
{
	Maxvalue[u] += value[u];

	int curMaxval = 0;
	for (int i = head[u]; i != 0; i = edge[i].net)
	{
		int v = edge[i].to;
		if (Maxvalue[v] == 0)
		{
			dfs_CriPath(v);
		}

		if (Maxvalue[v] > curMaxval)
			curMaxval = Maxvalue[v];
	}

	Maxvalue[u] += curMaxval;
}

void TaskSchedule()
{

	for (int v = 1; v <= n; ++v)
	{
		if (start[v] == false)
		{
			dfs_CriPath(v);
			if (Maxvalue[v] > MaxTime)
				MaxTime = Maxvalue[v];
		}
	}

}

int main()
{
	cin >> n;

	initvalue();

	initgra();

	TaskSchedule();

	cout << "I have read the rules about plagiarism punishment\n";

	cout << MaxTime;

	return 0;

}