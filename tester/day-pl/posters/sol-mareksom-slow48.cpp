#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

const int ROZ = (1 << 21) + 10;
const int ILE = 8 * 100 * 1000;

typedef long long int ll;

struct drzewo
{
	int ileTutaj;
	int zakryte;
	int dlugosc;
	void podlicz(const drzewo &l, const drzewo &p)
	{
		if(ileTutaj > 0)
			zakryte = dlugosc;
		else
			zakryte = l.zakryte + p.zakryte;
	}
};

drzewo drz[ROZ];

void dorzuc(int w, int a, int b, int p, int k)
{
	if(b < p || k < a)
		return;
	if(a <= p && k <= b)
	{
		drz[w].ileTutaj++;
		drz[w].podlicz(drz[w * 2], drz[w * 2 + 1]);
		return;
	}
	dorzuc(w * 2, a, b, p, (p + k) / 2);
	dorzuc(w * 2 + 1, a, b, (p + k) / 2 + 1, k);
	drz[w].podlicz(drz[w * 2], drz[w * 2 + 1]);
}

void zabierz(int w, int a, int b, int p, int k)
{
	if(b < p || k < a)
		return;
	if(a <= p && k <= b)
	{
		drz[w].ileTutaj--;
		drz[w].podlicz(drz[w * 2], drz[w * 2 + 1]);
		return;
	}
	zabierz(w * 2, a, b, p, (p + k) / 2);
	zabierz(w * 2 + 1, a, b, (p + k) / 2 + 1, k);
	drz[w].podlicz(drz[w * 2], drz[w * 2 + 1]);
}

ll odczyt(int w, int a, int b, int p, int k, bool wsio)
{
	if(b < p || k < a)
		return 0LL;
	wsio = wsio || (drz[w].ileTutaj > 0);
	if(a <= p && k <= b)
	{
		if(wsio)
			return drz[w].dlugosc;
		return drz[w].zakryte;
	}
	return odczyt(w * 2, a, b, p, (p + k) / 2, wsio)
		+ odczyt(w * 2 + 1, a, b, (p + k) / 2 + 1, k, wsio);
}

int n, m, n2;
ll odp[ILE];

vector<int> num;
inline int poz(int w) { return lower_bound(num.begin(), num.end(), w) - num.begin(); }

int main()
{
	vector<pair<pair<int, int>, pair<int, int> > > v;
	vector<pair<pair<int, int>, pair<int, int> > > zap;
	scanf("%d", &n);
	for(int i = 0; i < n; i++)
	{
		int a, b, c, d;
		scanf("%d%d%d%d", &a, &b, &c, &d);
		num.push_back(b);
		num.push_back(d);
		v.push_back(make_pair(make_pair(a, 1), make_pair(b, d)));
		v.push_back(make_pair(make_pair(c, -1), make_pair(b, d)));
	}
	scanf("%d", &m);
	for(int i = 0; i < m; i++)
	{
		int a, b, c, d;
		scanf("%d%d%d%d", &a, &b, &c, &d);
		num.push_back(b);
		num.push_back(d);
		zap.push_back(make_pair(make_pair(a, c), make_pair(b, d)));
		v.push_back(make_pair(make_pair(a, 0), make_pair(0, 0)));
		v.push_back(make_pair(make_pair(c, 0), make_pair(0, 0)));
	}
	sort(v.begin(), v.end());
	sort(num.begin(), num.end());
	num.resize(unique(num.begin(), num.end()) - num.begin());
	n2 = 1;
	while(n2 < (int) num.size())
		n2 *= 2;
	for(int i = 1; i < (int) num.size(); i++)
		drz[n2 + i].dlugosc = num[i] - num[i - 1];
	for(int i = n2 - 1; i >= 1; i--)
		drz[i].dlugosc = drz[i * 2].dlugosc + drz[i * 2 + 1].dlugosc;
	int ost = v[0].first.first;
	for(int i = 0; i < (int) v.size(); i++)
	{
		for(int j = 0; j < (int) zap.size(); j++)
		{
			if(zap[j].first.first < v[i].first.first && v[i].first.first <= zap[j].first.second)
			{
				int p = poz(zap[j].second.first) + 1;
				int k = poz(zap[j].second.second);
				odp[j] += (v[i].first.first - ost) * odczyt(1, p, k, 0, n2 - 1, false);
			}
		}
		ost = v[i].first.first;
		if(v[i].first.second > 0) // pocz
		{
			int p = poz(v[i].second.first) + 1;
			int k = poz(v[i].second.second);
			dorzuc(1, p, k, 0, n2 - 1);
		}
		else if(v[i].first.second < 0) // kon
		{
			int p = poz(v[i].second.first) + 1;
			int k = poz(v[i].second.second);
			zabierz(1, p, k, 0, n2 - 1);
		}
	}
	for(int i = 0; i < m; i++)
		printf("%lld\n", odp[i]);
	return 0;
}
