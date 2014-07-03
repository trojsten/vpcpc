#include <cstdio>

int tab[1005][1005];

int main()
{
	int n;
	scanf("%d", &n);
	while(n--)
	{
		int a, b, c, d;
		scanf("%d%d%d%d", &a, &b, &c, &d);
		for(int i = a; i < c; i++)
			for(int j = b; j < d; j++)
				tab[i][j] = 1;
	}
	scanf("%d", &n);
	while(n--)
	{
		int a, b, c, d;
		scanf("%d%d%d%d", &a, &b, &c, &d);
		int wyn = 0;
		for(int i = a; i < c; i++)
			for(int j = b; j < d; j++)
				wyn += tab[i][j];
		printf("%d\n", wyn);
	}
	return 0;
}
