#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>

#define deb(a)

using namespace std;

const int ROZ = (1 << 21) + 10;
const int ILE = 8 * 100 * 1000;

typedef int ll;

int t; // zegarek, który zawsze wskazuje aktualną godzinę

struct drzewo
{
	int ileTutaj;
	int dlugosc;
	int zakryte;
	int czas;
	int ileCalych;
	ll wynik;
	void spusc(drzewo &l, drzewo &p)
	{
		wynik += ((ll) ileCalych) * dlugosc;
		l.ileCalych += ileCalych;
		p.ileCalych += ileCalych;
		czas += ileCalych;
		ileCalych = 0;
		wynik += ((ll) (t - czas)) * zakryte;
		if(ileTutaj > 0)
		{
			l.ileCalych += (t - czas);
			p.ileCalych += (t - czas);
		}
		czas = t;
	}
	void podlicz(const drzewo &l, const drzewo &p)
	{
		if(ileTutaj > 0)
			zakryte = dlugosc;
		else
			zakryte = l.zakryte + p.zakryte;
	}
	void wypisz()
	{
		printf("ileTutaj = %d, dlugosc = %d, zakryte = %d, czas = %d, ileCalych = %d, wynik = %d\n", ileTutaj, dlugosc, zakryte, czas, ileCalych, wynik);
	}
};

int n2;
drzewo drz[ROZ];

inline void spusc(int w)
{
	if(w >= n2)
		drz[w].spusc(drz[0], drz[0]);
	else
		drz[w].spusc(drz[w * 2], drz[w * 2 + 1]);
	deb( printf("po spuszczeniu [%d] = ", w);
	drz[w].wypisz(); )
}

void dorzuc(int w, int a, int b, int p, int k, int v)
{
	spusc(w);
	if(b < p || k < a)
		return;
	if(a <= p && k <= b)
	{
		drz[w].ileTutaj += v;
		drz[w].podlicz(drz[w * 2], drz[w * 2 + 1]);
		return;
	}
	dorzuc(w * 2, a, b, p, (p + k) / 2, v);
	dorzuc(w * 2 + 1, a, b, (p + k) / 2 + 1, k, v);
	drz[w].podlicz(drz[w * 2], drz[w * 2 + 1]);
}

void dorzuc(int a, int b, int v)
{
	deb( printf("dorzuc(%d, %d, %d)\n", a, b, v); )
	dorzuc(1, a, b, 0, n2 - 1, v);
}

ll odczyt(int w, int a, int b, int p, int k)
{
	spusc(w);
	if(b < p || k < a)
		return 0LL;
	if(a <= p && k <= b)
		return drz[w].wynik;
	return odczyt(w * 2, a, b, p, (p + k) / 2)
		+ odczyt(w * 2 + 1, a, b, (p + k) / 2 + 1, k);
}

ll odczyt(int a, int b)
{
	deb( printf("odczyt(%d, %d) = ", a, b); )
	ll res = odczyt(1, a, b, 0, n2 - 1);
	deb( printf("%d\n", res); )
	return res;
}

int n, m;
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
		v.push_back(make_pair(make_pair(a, -1), make_pair(b, d)));
		v.push_back(make_pair(make_pair(c, -2), make_pair(b, d)));
	}
	scanf("%d", &m);
	for(int i = 0; i < m; i++)
	{
		int a, b, c, d;
		scanf("%d%d%d%d", &a, &b, &c, &d);
		num.push_back(b);
		num.push_back(d);
		zap.push_back(make_pair(make_pair(a, c), make_pair(b, d)));
		v.push_back(make_pair(make_pair(a, i), make_pair(b, d)));
		v.push_back(make_pair(make_pair(c, i + m), make_pair(b, d)));
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
	for(int i = 0; i < (int) v.size(); i++)
	{
		t = v[i].first.first;
		int p = poz(v[i].second.first) + 1;
		int k = poz(v[i].second.second);
		if(v[i].first.second == -1) // początek prostokąta
			dorzuc(p, k, 1);
		else if(v[i].first.second == -2) // koniec prostokąta
			dorzuc(p, k, -1);
		else if(v[i].first.second < m) // początek zapytania
			odp[v[i].first.second] = -odczyt(p, k);
		else // koniec zapytania
			odp[v[i].first.second - m] += odczyt(p, k);
	}
	for(int i = 0; i < m; i++)
		printf("%d\n", odp[i]);
	return 0;
}
