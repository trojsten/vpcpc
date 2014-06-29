#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

typedef long long int ll;

const ll infty = 1LL << 62;

int n, x;

pair<int, int> tab[2005];
ll pref[2005];
ll suf[2005];

ll dp[2005][2005][2];

inline ll licz(int a, int b, int s)
{
	ll w;
	if(s == 0) // lewo
	{
		ll poz = pref[a] + suf[b + 1];
		ll o1 = dp[a + 1][b][0] + (tab[a + 1].first - tab[a].first) * poz;
		ll o2 = dp[a + 1][b][1] + (tab[b].first - tab[a].first) * poz;
		w = min(o1, o2);
	}
	else // prawo
	{
		ll poz = pref[a - 1] + suf[b];
		ll o1 = dp[a][b - 1][0] + (tab[b].first - tab[a].first) * poz;
		ll o2 = dp[a][b - 1][1] + (tab[b].first - tab[b - 1].first) * poz;
		w = min(o1, o2);
	}
	return w >= infty ? infty : w;
}

bool przyp()
{
	scanf("%d%d", &n, &x);
	if(n == 0 && x == 0)
		return false;
	ll wyn = 0LL;
	for(int i = 1; i <= n; i++)
	{
		int c;
		scanf("%d%d%d", &tab[i].first, &c, &tab[i].second);
		wyn += c;
	}
	tab[n + 1].first = x;
	tab[n + 1].second = 0;
	sort(tab + 1, tab + n + 2);
	pref[0] = 0LL;
	suf[n + 2] = 0LL;
	for(int i = 1; i <= n + 1; i++)
		pref[i] = tab[i].second + pref[i - 1];
	for(int i = n + 1; i >= 1; i--)
		suf[i] = tab[i].second + suf[i + 1];
	for(int i = 1; i <= n + 1; i++)
	{
		for(int j = 0; j < 2; j++)
		{
			if(tab[i].first == x)
				dp[i][i][j] = 0LL;
			else
				dp[i][i][j] = infty;
		}
	}
	for(int d = 2; d <= n + 1; d++)
		for(int i = d; i <= n + 1; i++)
			for(int j = 0; j < 2; j++)
				dp[i - d + 1][i][j] = licz(i - d + 1, i, j);
	printf("%lld\n", wyn + min(dp[1][n + 1][0], dp[1][n + 1][1]));
	return false;
}

int main()
{
	while(przyp())
		;
	return 0;
}
