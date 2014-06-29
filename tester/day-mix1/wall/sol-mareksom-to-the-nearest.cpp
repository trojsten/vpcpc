// Goes to the nearest point
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long int ll;

vector<pair<int, int> > bef;
vector<pair<int, int> > aft;

ll licz(int p, int t);

ll getBef(int t, int p)
{
	t += p - bef.back().first;
	p = bef.back().first;
	ll dod = ((ll) bef.back().second) * t;
	bef.pop_back();
	return dod + licz(p, t);
}

ll getAft(int t, int p)
{
	t += aft.back().first - p;
	p = aft.back().first;
	ll dod = ((ll) aft.back().second) * t;
	aft.pop_back();
	return dod + licz(p, t);
}

ll licz(int p, int t)
{
	if(bef.empty() && aft.empty())
		return 0LL;
	if(bef.empty())
		return getAft(t, p);
	else if(aft.empty())
		return getBef(t, p);
	else if(p - bef.back().first < aft.back().first - p)
		return getBef(t, p);
	return getAft(t, p);
}

int main()
{
	int n, p;
	scanf("%d%d", &n, &p);
	ll wyn = 0LL;
	for(int i = 0; i < n; i++)
	{
		int x, c, d;
		scanf("%d%d%d", &x, &c, &d);
		wyn += c;
		if(x < p)
			bef.push_back(make_pair(x, d));
		else if(x > p)
			aft.push_back(make_pair(x, d));
	}
	sort(bef.begin(), bef.end());
	sort(aft.begin(), aft.end());
	reverse(aft.begin(), aft.end());
	printf("%lld\n", licz(p, 0) + wyn);
	return 0;
}
