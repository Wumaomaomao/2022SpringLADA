#include<iostream>
#include<vector>
#include<string>
#include<string.h>
#include<stdlib.h>
#include<stack>
#include<algorithm>
#include<iostream>
#include<sstream>

using namespace std;

struct vertex
{
	int point_cnt;
	int indegree;
	int achieve;
	vector<int> ver;
	bool operator < (vertex v) const 
	{
		if (achieve > v.achieve)
			return true;
		else return false;
	}
	bool operator == (vertex v) const
	{
		if (achieve == v.achieve)
			return true;
		else return false;
	}
	bool operator > (vertex v) const
	{
		if (achieve < v.achieve)
			return true;
		else return false;
	}
};
int ver = 0;
vector<vector<int>> G;
vector<vector<int>> GT;
vector<vertex> Gcprv;
int cprver = 0;
vector<vector<int>> Gcpr;
stack<int> s;

vector<vector<int>> achieve;

int achieveMax = 0;

void dfs_push(int u, int fa, bool* visited)
{
	visited[u] = true;
	vector<int> neighbor = G[u];
	for (vector<int>::iterator iter = neighbor.begin(); iter != neighbor.end(); ++iter)
	{
		if (visited[*iter] == false)
		{
			dfs_push(*iter, u, visited);
		}
	}
	s.push(u);
}

void dfs_pushstack()
{
	bool* visited = new bool[ver];
	memset(visited, 0, sizeof(bool) * ver);
	for (int v = 0; v < ver; ++v)
	{
		if (visited[v] == false)
			dfs_push(v, v, visited);
	}

	//delete[]visited;
}

void dfs_scc(int u, int cprveridx, int* scc)
{
	Gcprv[cprveridx - 1].point_cnt++;
	Gcprv[cprveridx - 1].ver.push_back(u);
	scc[u] = cprveridx;
	vector<int> neighbor = GT[u];
	for (vector<int>::iterator iter = neighbor.begin(); iter != neighbor.end(); ++iter)
	{
		if (scc[*iter] == 0)
		{
			
			dfs_scc(*iter, cprveridx, scc);
		}
		else
		{
			if (scc[*iter] != scc[u])
			{
				if (find(Gcpr[scc[*iter]-1].begin(), Gcpr[scc[*iter] - 1].end(), cprveridx - 1) == Gcpr[scc[*iter] - 1].end())
				{
					Gcpr[scc[*iter] - 1].push_back(cprveridx - 1);
					Gcprv[cprveridx - 1].indegree++;
				}
			}
		}
	}
	
}

void dfs_compress()
{
	int* scc = new int[ver];
	memset(scc, 0, sizeof(int) * ver);

	while (!s.empty())
	{
		if (scc[s.top()] == 0)
		{
			++cprver;
			Gcprv.push_back(vertex());
			Gcpr.push_back(vector<int>());
			dfs_scc(s.top(),  cprver, scc);
		}
		s.pop();
	}
	//delete[]scc;
}

void TransGra()
{
	for (int u = 0; u < ver; ++u)
	{
		vector<int> neighbor = G[u];
		for (vector<int>::iterator iter = neighbor.begin(); iter != neighbor.end(); ++iter)
		{
			GT[*iter].push_back(u);
		}
	}
}

void dfs_visited(int u, bool* visited)
{
	visited[u] = true;
	vector<int> neighbor = Gcpr[u];
	for (vector<int>::iterator iter = neighbor.begin(); iter != neighbor.end(); ++iter)
	{
		if (visited[*iter] == false)
		{
			dfs_visited(*iter, visited);
		}
	}
}

void dfs_achieve(int u, bool* visited, bool* update)
{
	update[u] = true;
	visited[u] = true;
	vector<int> neighbor = Gcpr[u];
	for (vector<int>::iterator iter = neighbor.begin(); iter != neighbor.end(); ++iter)
	{
		if (visited[*iter] == false)
		{
			dfs_achieve(*iter, visited, update);
		}
		//if (Gcprv[*iter].achieve == Gcprv[*iter].point_cnt - 1 && visited[*iter] == false)
		/*if (update[*iter] == false && visited[*iter] == false)
		{
			dfs_achieve(*iter, visited, update);
			Gcprv[u].achieve += (Gcprv[*iter].achieve + 1);
		}
		if (visited[*iter] == false)
		{
			//achieve[u].push_back(*iter);
			//achieve[u].insert(achieve[u].begin(),achieve[*iter].begin(), achieve[*iter].end());
			Gcprv[u].achieve += (Gcprv[*iter].achieve + 1);
			dfs_visited(*iter, visited);
		}*/
		//if ()
		
	}
	if (Gcprv[u].achieve > achieveMax)
		achieveMax = Gcprv[u].achieve;
}

void impact()
{
	bool* update = new bool[cprver];
	bool* visited = new bool[cprver];
	
	for (int idx = 0; idx < cprver; ++idx)
	{
		Gcprv[idx].achieve = Gcprv[idx].point_cnt - 1;
		//achieve.push_back(vector<int>());
	}
	memset(update, 0, cprver * sizeof(bool));
	int impation = 0;
	for (int idx = 0; idx < cprver; ++idx)
	{

		if (Gcprv[idx].indegree == 0)
		{
			impation = 0;
			memset(visited, 0, cprver * sizeof(bool));
			dfs_achieve(idx, visited, update);
			for (int idx = 0; idx < cprver; ++idx)
			{
				if (visited[idx] == true)
				{
					impation += Gcprv[idx].point_cnt;
				}
			}
			Gcprv[idx].achieve = impation - 1;
			if (Gcprv[idx].achieve > achieveMax)
				achieveMax = Gcprv[idx].achieve;
		}
	};
	//delete[]visited;
	sort(Gcprv.begin(), Gcprv.end());
	vector<int> ans;

	for (vector<vertex>::iterator iter = Gcprv.begin(); iter != Gcprv.end(); ++iter)
	{
		if ((*iter).achieve >= achieveMax)
		{
			for (vector<int>::iterator i = (*iter).ver.begin(); i != (*iter).ver.end(); ++i)
			{
				ans.push_back(*i);
			}
		}
	}

	sort(ans.begin(), ans.end());

	cout << "I have read the rules about plagiarism punishment\n";
	cout << achieveMax << endl;
	for (vector<int>::iterator iter = ans.begin(); iter != ans.end(); ++iter)
	{
		cout << *iter << " ";
	}
}


int main()
{
	int dst_ver;
	string str;

	while (getline(cin, str))
	{
		G.push_back(vector<int>());
		GT.push_back(vector<int>());
		stringstream stream(str);

		while (stream >> dst_ver)
		{
			G[ver].push_back(dst_ver);
		}
		/*int idx = 0;
		string temp;
		while (str[idx] != '\0')
		{
			if (str[idx] != ' ')
				temp = temp + str[idx];
			else
			{
				temp = temp + '\0';
				int v = atoi(temp.c_str());
				G[ver].push_back(v);
				temp = "";
			};
			++idx;
		}
		if (temp != "")
		{
			temp = temp + '\0';
			int v = atoi(temp.c_str());
			G[ver].push_back(v);
			temp = "";
		}*/
		++ver;
	}

	dfs_pushstack();
	TransGra();
	dfs_compress();
	impact();

	return 0;
}