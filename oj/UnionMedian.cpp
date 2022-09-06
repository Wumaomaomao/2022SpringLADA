#include<stdio.h>
#include<stdlib.h>
#define ll int

ll Select(ll len, ll* arr1, ll s1, ll e1, ll* arr2, ll s2, ll e2)
{
	if (len == 2)
	{
		return arr1[s1] > arr2[s2] ? arr2[s2] : arr1[s1];
	}
	else
	{
		int n = len / 2;
		int mid = n / 2 - 1;
		if (arr1[s1 + mid] < arr2[s2 + mid])
		{
			s1 = s1 + mid + 1;
			e2 = e2 - mid - 1;
		}
		else
		{
			s2 = s2 + mid + 1;
			e1 = e1 - mid - 1;
		}
		return Select(len - ((mid + 1) * 2), arr1, s1, e1, arr2, s2, e2);
	}
}

int main()
{
	ll n;
	scanf_s("%d", &n);

	ll* arr1 = (ll*)malloc(n * sizeof(ll));
	ll* arr2 = (ll*)malloc(n * sizeof(ll));

	for (ll i = 0; i < n; ++i)
	{
		scanf_s("%d", &arr1[i]);
	}
	for (ll i = 0; i < n; ++i)
	{
		scanf_s("%d", &arr2[i]);
	}

	ll median = Select(2*n, arr1, 0, n - 1, arr2, 0, n - 1);
	printf_s("%d",median);

	return 0;
}