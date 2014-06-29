#include <cstdio>

typedef long long int ll;
const int mod = 1e9 + 7;

int main()
{
	ll a, b;
	scanf("%lld%lld", &a, &b);
	int n = (int) (b - a + 1);
	ll wyn = 1LL;
	for(int i = 0; i < n; i++)
		wyn = (wyn * 2) % mod;
	printf("%lld\n", wyn);
	return 0;
}
