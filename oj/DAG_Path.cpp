#include<iostream>
#include<stdio.h>
#include<stack>
#include<string.h>
#define M 900000
#define N 20000

using namespace std;

struct Node
{
	int to, net;
	int val;
};

int n, m = 0;

int tot = 0;
Node edge[M];
int head[N];

int indegree[N];
int Topo[N];
int MaxLen[N];

void initgra()
{
	memset(head, 0, N * sizeof(int));
	memset(indegree, 0, N * sizeof(int));
	
	cin >> n;
	 
	int u, v, val;
	while(scanf("%d%d%d", &u, &v, &val) != EOF)
	//while (cin >> u >> v>> val)
	{
		++tot;
		edge[tot].to = v;
		edge[tot].net = head[u];
		edge[tot].val = val;
		head[u] = tot;
		indegree[v]++;
		++m;
	}

}

void Topoorder()
{
	stack<int> s;
	int seq = 0;

	for (int i = 0; i < n; ++i)
	{
		if (indegree[i] == 0)
		{
			s.push(i);
		}
	}

	while (!s.empty())
	{
		int v = s.top();
		s.pop();
		Topo[seq] = v;
		++seq;
		for (int i = head[v]; i != 0; i = edge[i].net)
		{
			int u = edge[i].to;
			--indegree[u];
			if (indegree[u] == 0)
			{
				s.push(u);
			}
		}
	}
}

void Maxlen()
{
	memset(MaxLen, 0, N * sizeof(int));
	MaxLen[0] = 0;
	for (int i = 0; i < n; ++i)
	{
		int u = Topo[i];

		for (int i = head[u]; i != 0; i = edge[i].net)
		{
			int v = edge[i].to;
			if (MaxLen[u] + edge[i].val > MaxLen[v])
			{
				MaxLen[v] = MaxLen[u] + edge[i].val;
			}
		}

	}
}

int main()
{
	initgra();

	Topoorder();

	Maxlen();

	cout << "I have read the rules about plagiarism punishment\n";
	for (int i = 1; i < n; ++i)
	{
		cout << MaxLen[i] << ' ';


	}
	
	return 0;
}