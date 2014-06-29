// Always answers with the area of the new poster
#include <cstdio>

int main()
{
	int n;
	scanf("%d", &n);
	while(n--)
	{
		int a;
		scanf("%d%d%d%d", &a, &a, &a, &a);
	}
	scanf("%d", &n);
	while(n--)
	{
		int a, b, c, d;
		scanf("%d%d%d%d", &a, &b, &c, &d);
		printf("%lld\n", ((long long) c - a) * ((long long) d - b));
	}
	return 0;
}
