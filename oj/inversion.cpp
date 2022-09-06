#include<iostream>
using namespace std;

typedef long long int ll;

ll Merge(string* arr, ll s, ll e)
{
	ll Mid = (s + e) / 2;
	ll pa = s;
	ll pb = Mid + 1;
	ll cnt = 0;
	ll len = e - s + 1;

	string* temp = new string[len];

	ll idx = 0;
	while (pa < Mid + 1 && pb < e + 1)
	{
		if (arr[pa] <= arr[pb])
		{
			temp[idx] = arr[pa];
			++pa;
			++idx;
		}
		else if (arr[pa] > arr[pb])
		{
			temp[idx] = arr[pb];
			cnt += Mid - pa + 1;
			++pb;
			++idx;
		}
	}

	if (idx != len)
	{
		if (pa != Mid + 1)
		{
			for (int k = pa; k < Mid + 1; ++k)
			{
				temp[idx] = arr[k];
				++idx;
			}
		}
		else if (pb != e + 1)
		{
			for (ll k = pb; k < e + 1; ++k)
			{
				temp[idx] = arr[k];
				++idx;
			}
		}
	}

	if (idx != len)
	{
		cout << "error!" << endl;
		exit(-1);
	}
	else
	{
		for (ll i = 0; i < len; ++i)
		{
			arr[s + i] = temp[i];
		}
	}

	delete []temp;

	return cnt;
}

ll Inversion(string* arr, ll s, ll e)
{
	if (s >= e)
		return 0;
	else if (s < e)
	{
		ll Mid = (s + e) / 2;
		ll left = Inversion(arr, s, Mid);
		ll right = Inversion(arr, Mid + 1, e);
		ll inver = Merge(arr, s, e);
		return left + right + inver;
	}
}

int main()
{

	ll N;
	cin >> N;

	string* arr = new string[N];

	for (ll idx = 0; idx < N; ++idx)
	{
		cin >> arr[idx];
	}

	ll inver_cnt = Inversion(arr, 0, N - 1);

	delete[]arr;
	cout << "wo yi yue du guan yu chao xi de shuo ming\n";
	cout << inver_cnt;

	return 0;
}