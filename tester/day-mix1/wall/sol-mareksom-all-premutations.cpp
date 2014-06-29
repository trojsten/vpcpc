#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

inline int bez(int x)
{
	return x < 0 ? -x : x;
}

bool przyp()
{
	int n, x;
	scanf("%d%d", &n, &x);
	if(n == 0 && x == 0)
		return false;
	vector<pair<int, int> > v;
	int wyn = 0;
	v.push_back(make_pair(x, 0));
	for(int i = 1; i <= n; i++)
	{
		int y, c, d;
		scanf("%d%d%d", &y, &c, &d);
		v.push_back(make_pair(y, d));
		wyn += c;
	}
	int heh = 1e9;
	sort(v.begin() + 1, v.end());
	do
	{
		int o = 0;
		int t = 0;
		for(int i = 1; i < (int) v.size(); i++)
		{
			t += bez(v[i].first - v[i - 1].first);
			o += v[i].second * t;
		}
		heh = min(heh, o);
	}
	while(next_permutation(v.begin() + 1, v.end()));
	printf("%d\n", wyn + heh);
	return false;
}

int main()
{
	while(przyp())
		;
	return 0;
}
