#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

typedef long long int ll;

vector<pair<pair<int, int>, pair<int, int> > > pro, orp;
vector<int> num;

inline int pos(int w)
{
	return lower_bound(num.begin(), num.end(), w) - num.begin();
}

ll tablica[1005][1005];

int main()
{
	int n;
	scanf("%d", &n);
	for(int i = 0; i < n; i++)
	{
		int a, b, c, d;
		scanf("%d%d%d%d", &a, &b, &c, &d);
		pro.push_back(make_pair(make_pair(a, b), make_pair(c, d)));
		num.push_back(a); num.push_back(b); num.push_back(c); num.push_back(d);
	}
	int m;
	scanf("%d", &m);
	for(int i = 0; i < m; i++)
	{
		int a, b, c, d;
		scanf("%d%d%d%d", &a, &b, &c, &d);
		orp.push_back(make_pair(make_pair(a, b), make_pair(c, d)));
		num.push_back(a); num.push_back(b); num.push_back(c); num.push_back(d);
	}
	sort(num.begin(), num.end());
	num.resize(unique(num.begin(), num.end()) - num.begin());
	for(int i = 0; i < (int) pro.size(); i++)
	{
		int x1 = pos(pro[i].first.first);
		int x2 = pos(pro[i].second.first);
		int y1 = pos(pro[i].first.second);
		int y2 = pos(pro[i].second.second);
		for(int x = x1; x < x2; x++)
			for(int y = y1; y < y2; y++)
				tablica[x][y] = ((ll) (num[x + 1] - num[x])) * (num[y + 1] - num[y]);
	}
	for(int i = 0; i < (int) orp.size(); i++)
	{
		int x1 = pos(orp[i].first.first);
		int x2 = pos(orp[i].second.first);
		int y1 = pos(orp[i].first.second);
		int y2 = pos(orp[i].second.second);
		ll wyn = 0LL;
		for(int x = x1; x < x2; x++)
			for(int y = y1; y < y2; y++)
				wyn += tablica[x][y];
		printf("%lld\n", wyn);
	}
	return 0;
}
