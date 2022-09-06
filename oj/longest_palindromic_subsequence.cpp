#include<iostream>
#include<stdio.h>
#include<string>
#include<string.h>

using namespace std;

int main()
{
	string s;
	char ch;
	while (scanf_s("%c", &ch) != EOF)
	{
		if (ch != ' ' && ch != '\n')
		{
			s += ch;
		}
	}
	short n = s.length();

	short** dp = new short* [n];
	for (short i = 0; i < n; ++i)
	{
		dp[i] = new short[n];
		memset(dp[i], 0, sizeof(short) * n);
	}

	for (short i = n - 1; i >= 0; --i)
	{
		dp[i][i] = 1;
		for (short j = i + 1; j < n; ++j)
		{
			if (s[i] == s[j])
			{
				dp[i][j] = dp[i + 1][j - 1] + 2;
			}
			else
			{
				if (dp[i + 1][j] > dp[i][j - 1])
				{
					dp[i][j] = dp[i + 1][j];
				}
				else dp[i][j] = dp[i][j - 1];
			}
		}
	}
	cout << "I have read the rules about plagiarism punishment\n";
	cout << dp[0][n-1];
	return 0;
}