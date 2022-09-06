#include<iostream>
#include<vector>
#include<sstream>
#include<string.h>

#define WRITE 0
#define RED 1
#define BLUE -1

using namespace std;

vector<vector<int>> G;
int ver = 0;

void dfs_color(int u, int* color, int curcolor)
{
	color[u] = curcolor;
	for (vector<int>::iterator iter = G[u].begin(); iter != G[u].end(); ++iter)
	{
		if (color[*iter] == WRITE)
			dfs_color(*iter, color, -curcolor);
	}
}

int main()
{

	int dst_ver;
	string str;

	while (getline(cin, str))
	{
		
		G.push_back(vector<int>());
		
		stringstream stream(str);
		stream >> dst_ver;
		while (stream >> dst_ver)
		{
			G[ver].push_back(dst_ver);
		}
		++ver;
	}

	for (int i = 0; i < ver; ++i)
	{
		for (vector<int>::iterator iter = G[i].begin(); iter != G[i].end(); ++iter)
		{
			int v = (*iter);
			G[v].push_back(i);
		}
	}

	int* color = new int[ver];
	memset(color, 0, ver * sizeof(int));

	dfs_color(0,color,BLUE);

	cout << "wo yi yue du guan yu chao xi de shuo ming\n";
	for (int i = 0; i < ver; ++i)
	{
		if (color[i] == BLUE)
			cout << i << "\n";
	}

	return 0;
}