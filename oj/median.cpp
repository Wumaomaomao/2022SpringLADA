#include<iostream>
#include<algorithm>
using namespace std;

typedef long long ll;

ll Patition(ll* data, ll s, ll e)
{
	ll pivot = data[s];
	data[s] = data[e];
	data[e] = pivot;

	ll idx = s;

	for (ll i = s; i < e; ++i)
	{
		if (data[i] <= pivot)
		{
			ll temp = data[i];
			data[i] = data[idx];
			data[idx] = temp;
			++idx;
		}
	}
	ll temp = data[idx];
	data[idx] = data[e];
	data[e] = temp;

	return idx;
}

void PatitionSelect(ll* data, ll s, ll e, ll k)
{
	if (s >= e)
		return;
	else
	{
		ll desidx = s + k - 1;
		ll pivot = Patition(data, s, e);

		if (pivot == desidx)
			return;
		else if (pivot > desidx)
		{
			PatitionSelect(data, s, pivot - 1, k);
		}
		else
		{
			PatitionSelect(data, pivot + 1, e, k - (pivot - s) - 1);
		}
	}


}

int main()
{
	ll n, k, s, e, mid;
	cin >> k >> n;

	s = 0; e = n - 1; 

	if (n % 2 == 1)
		mid = n / 2 + 1;
	else
		mid = n / 2;

	ll* data = new ll[n];

	for (ll i = 0; i < n; ++i)
		cin >> data[i];

	PatitionSelect(data, s, e, mid);

	/*for (ll i = 0; i < n; ++i)
		cout << data[i] << ' ';
	cout << endl;*/

	PatitionSelect(data, s, mid - 1, mid - k + 1);

	/*for (ll i = 0; i < n; ++i)
		cout << data[i] << ' ';
	cout << endl;*/

	PatitionSelect(data, mid + 1, e, k);

	/*for (ll i = 0; i < n; ++i)
		cout << data[i] << ' ';
	cout << endl;*/

	sort(data + (mid - k - 1), data + (mid + k));

	/*for (ll i = 0; i < n; ++i)
		cout << data[i] << ' ';
	cout << endl;*/

	for (ll i = mid - k - 1; i <= mid + k - 2; ++i)
		cout << data[i] << ' ';
	cout << data[mid + k - 1];
	return 0;
}