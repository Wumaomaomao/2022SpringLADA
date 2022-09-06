#include<stdio.h>
#include<math.h>

#define MaxLen 100000

int MaxProfit(int len, int* prices)
{
	int hold_0 = 0;
	int hold_1 = -prices[0];
	int hold_2 = -prices[0];
	int sold_1 = 0;
	int sold_2 = 0;

	for (int i = 1; i < len; ++i)
	{
		hold_1 = fmax(hold_1, hold_0 - prices[i]);
		sold_1 = fmax(sold_1, hold_1 + prices[i]);
		hold_2 = fmax(hold_2, sold_1 - prices[i]);
		sold_2 = fmax(sold_2, hold_2 + prices[i]);
	}

	return fmax(sold_1, sold_2);
}
int main()
{
	int prices[MaxLen];

	int len = 0;
	while (scanf_s("%d", &prices[len]) != EOF)
	{
		++len;
	}

	int Profit = MaxProfit(len,  prices);
	printf_s("%d", Profit);

	return 0;
}