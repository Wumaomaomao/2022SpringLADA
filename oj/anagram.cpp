#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<algorithm>

using namespace std;
typedef pair<bool, string> value;

int main()
{
	map<string, value> hashmap;
	int N;
	cin >> N;

	while (--N, N >= 0)
	{
		string t, sorted;
		cin >> t;
		sorted = t;
		sort(sorted.begin(), sorted.end());

		if (hashmap.find(sorted) != hashmap.end())
		{
			map<string,value>::iterator iter = hashmap.find(sorted);
			(*iter).second.first = true;
			string temp = (*iter).second.second;
			if (t < temp)
				(*iter).second.second = t;
		}
		else
		{
			hashmap.insert(make_pair(sorted, make_pair(false, t)));
		}
	}

	vector<string> res;

	for (map<string, value>::iterator iter = hashmap.begin(); iter != hashmap.end(); ++iter)
	{
		if ((*iter).second.first == true)
			res.push_back((*iter).second.second);
	}

	sort(res.begin(), res.end());

	cout << "wo yi yue du guan yu chao xi de shuo ming\n" << res.size() << endl;
	
	for (vector<string>::iterator iter = res.begin(); iter != res.end(); ++iter)
	{
		cout << (*iter) << endl;
	}

	return 0;
}