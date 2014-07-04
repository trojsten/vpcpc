#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

typedef long double ld;

const ld minfty = -1e30;

vector<pair<int, ld> > graf[100005];
vector<pair<pair<int, int>, int> > kraw;

int n, k;

struct lista
{
	vector<ld> v;
	bool empty() const
	{
		return v.empty();
	}
	int dlugosc() const
	{
		return (int) v.size() - 1;
	}
	void clear()
	{
		v.clear();
	}
	void ustaw(int p, ld val)
	{
		przypisz(p, max(val, operator[](p)));
	}
	void przypisz(int p, ld val)
	{
		v.resize(max((int) v.size(), p + 1), minfty);
		v[p] = val;
	}
	ld operator[](int x) const
	{
		if(x >= (int) v.size())
			return minfty;
		return v[x];
	}
};

bool jest[100005];
int roz[100005];

int licz_rozmiary(int w, int o)
{
	if(!jest[w])
		return 0;
	roz[w] = 1;
	for(int i = 0; i < (int) graf[w].size(); i++)
	{
		if(graf[w][i].first != o)
			roz[w] += licz_rozmiary(graf[w][i].first, w);
	}
	return roz[w];
}

int licz_centroid(int w, int o, int pol)
{
	int a = 0;
	for(int i = 0; i < (int) graf[w].size(); i++)
	{
		if(graf[w][i].first != o && jest[graf[w][i].first] && roz[graf[w][i].first] > pol)
			a = graf[w][i].first;
	}
	if(a == 0)
		return w;
	return licz_centroid(a, w, pol);
}

void wypelniaj(int w, int o, lista &tab, int poz, ld sum)
{
	tab.ustaw(poz, sum);
	for(int i = 0; i < (int) graf[w].size(); i++)
	{
		if(graf[w][i].first != o && jest[graf[w][i].first])
			wypelniaj(graf[w][i].first, w, tab, poz + 1, sum + graf[w][i].second);
	}
}

lista licz(int w)
{
	licz_rozmiary(w, -1);
	int f = licz_centroid(w, -1, roz[w] / 2);
	lista wyn;
	wyn.ustaw(0, 0.0l);
	jest[f] = false;
	for(int i = 0; i < (int) graf[f].size(); i++)
	{
		if(jest[graf[f][i].first])
		{
			lista tab = licz(graf[f][i].first);
			if(tab.empty())
				return tab;
			for(int j = tab.dlugosc() + 1; j >= 1; j--)
				tab.przypisz(j, tab[j - 1] + graf[f][i].second);
			tab.przypisz(0, 0.0l);
			for(int j = 0; j <= tab.dlugosc() && j <= k; j++)
			{
				if(wyn[k - j] + tab[j] >= 0)
					return lista();
			}
			for(int j = 0; j <= tab.dlugosc(); j++)
				wyn.ustaw(j, tab[j]);
		}
	}
	jest[f] = true;
	lista ret;
	wypelniaj(w, -1, ret, 0, 0.0l);
	for(int i = ret.dlugosc() - 1; i >= 0; i--)
		ret.ustaw(i, ret[i + 1]);
	return ret;
}

bool sprawdz(ld c)
{
	for(int i = 1; i <= n; i++)
	{
		graf[i].clear();
		jest[i] = true;
	}
	for(int i = 0; i < (int) kraw.size(); i++)
	{
		graf[kraw[i].first.first].push_back(make_pair(kraw[i].first.second, kraw[i].second - c));
		graf[kraw[i].first.second].push_back(make_pair(kraw[i].first.first, kraw[i].second - c));
	}
	lista wynik = licz(1);
	if(wynik.empty())
		return true;
	return false;
}

int main()
{
	scanf("%d%d", &n, &k);
	ld a = 0, b = 0, c;
	for(int i = 1; i < n; i++)
	{
		int a, bb, c;
		scanf("%d%d%d", &a, &bb, &c);
		kraw.push_back(make_pair(make_pair(a, bb), c));
		b = max(b, (ld) (c + 1));
	}
	while (b-a >= (1e-7))
	{
		c = (a + b) / 2;
		if(sprawdz(c))
			a = c;
		else
			b = c;
	}
	printf("%.7Lf\n", a);
	return 0;
}
