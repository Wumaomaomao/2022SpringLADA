#include<iostream>
#include<string.h>
#include<vector>
#include<algorithm>
#define N 22223
#define M 222223
using namespace std;

struct edge
{
	int u, v;
	edge(int x, int y)
	{
		u = x;
		v = y;
	}
	bool operator >(edge p)
	{
		if (u > p.u)
			return true;
		else {
			if (u == p.u && v > p.v)
				return true;
			else return false;
		};
	}
	bool operator <(edge p)
	{
		if (u < p.u)
			return true;
		else {
			if (u == p.u && v < p.v)
				return true;
			else return false;
		};
	}
	bool operator ==(edge p)
	{
		if (u == p.u && v == p.v)
			return true;
		else return false;
	}
};
struct Node
{
	int to, net;
	bool cut;

};
int n, m;
int tot = 1;
int head[N];
bool cutp[N];
Node e[M];
int back[N];
int discovertime[N];
int seq = 0;

void initgra()
{
	memset(head, 0, N * sizeof(int));
	int u, v;
	while (cin >> u >> v)
	{
		if (u > v)
		{
			int t = u;
			u = v;
			v = t;
		}
		++tot;
		e[tot].net = head[u];
		e[tot].to = v;
		e[tot].cut = false;
		head[u] = tot;
		++tot;
		e[tot].net = head[v];

		e[tot].to = u;
		e[tot].cut = false;
		head[v] = tot;
	}
}

void dfs(int u, int fa)
{
	int child = 0;
	discovertime[u] = ++seq;
	back[u] = discovertime[u];

	for (int k = head[u]; k != 0; k = e[k].net)
	{
		if (discovertime[e[k].to] == 0)//white
		{
			++child;
			int v = e[k].to;
			dfs(v, u);
			if (back[v] >= discovertime[v])
			{
				e[k].cut = true;
				e[k ^ 1].cut = true;
			}
			if (back[v] >= discovertime[u])
			{
				cutp[u] = true;
			}
			if (back[v] < back[u])
				back[u] = back[v];
		}
		else
		{
			int v = e[k].to;
			if (v != fa)
			{
				if (discovertime[v] < back[u])
					back[u] = discovertime[v];
			}
		}
	}

	if (u == fa)
	{
		if (child <= 1)
			cutp[u] = false;
		else cutp[u] = true;
	}
}

int main()
{
	cin >> n;

	initgra();

	memset(discovertime, 0, N * sizeof(int));
	memset(back, 0, N * sizeof(int));
	memset(cutp, false, N * sizeof(bool));
	for (int i = 0; i <= n; ++i)
	{
		if (!discovertime[i])
			dfs(i, i);
	}

	cout << "wo yi yue du guan yu chao xi de shuo ming\n";
	for (int i = 0; i < n; ++i)
	{
		if (cutp[i] == true)
			cout << i << endl;
	}
	vector<edge> ans;
	for (int i = 0; i < n; ++i)
	{
		for (int k = head[i]; k != 0; k = e[k].net)
		{
			if (i < e[k].to && e[k].cut == true)
			{
				ans.push_back(edge(i, e[k].to));

			}
		}
	}

	sort(ans.begin(), ans.end());
	for (vector<edge>::iterator iter = ans.begin(); iter < ans.end(); ++iter)
	{
		cout << (*iter).u << ' ' << (*iter).v << endl;
	}
	return 0;
}
