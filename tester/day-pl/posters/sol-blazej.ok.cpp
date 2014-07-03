#include <cstdio>
#include <vector>
#include <queue>
#include <stack>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <set>
#define MAXN 100007
#define czapa 524288
#define PB push_back
#define MP make_pair
#define ST first
#define ND second

#define REP(i,n) for(int i=0;i<(n);i++)
#define FOR(a,b,c) for(int a=b;a<=(c);a++)
#define FORD(a,b,c) for (int a=b;a>=(c);a--)
#define VAR(v,n) __typeof(n) v=(n)
#define ALL(c) c.begin(),c.end()
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();i++)

using namespace std;

typedef long long LL;  

struct wezel{
	int dlug_przed;      //stala wartosc
	int akt_dlug;        //jak wyglada dany przedzial patrzac tylko na to, co sie dzialo scisle wewnatrz tego przedzialu bazowego 
	LL akt_wyn;	         //calkowity (poprawny) wynik dla danego przedzialu bazowego w ostatnim czasie aktualizacji
	int akt_czas;	     //ostatni czas aktualizacji
	int ile_przysloniec; //ile razy dany przedzial bazowy jest przysloniety
	int ile_razy;        //ile razy miedzy aktualnym czasem a ostatnim czasem aktualizacji tego przedzialu bazowego caly przedzial byl zasloniety
	wezel(int _dlp = 0, int _ad = 0, LL _aw = 0, int _ac = 0, int _ilep = 0, int _iler = 0): 
		dlug_przed(_dlp), akt_dlug(_ad), akt_wyn(_aw), akt_czas(_ac), ile_przysloniec(_ilep), ile_razy(_iler) {};
};

int ile[2],iley,ilex;
int pozy[4*MAXN];
int t[2][MAXN][4];
pair<int, pair<int, int> > taby[4*MAXN], tabx[4*MAXN];
wezel d[2*czapa];
LL wyn[MAXN];

LL rek_zejscie(int polewej, int w, int l, int p, int rodzaj, int czas, int rozmiar) {
	if (d[w].ile_przysloniec) d[w].ile_razy = czas - d[w].akt_czas;
	d[w].akt_wyn += LL(d[w].akt_dlug) * LL(czas - d[w].ile_razy - d[w].akt_czas) + LL(d[w].ile_razy) * LL(d[w].dlug_przed);
	if (rozmiar != 1) {
		d[2*w].ile_razy += d[w].ile_razy;
		d[2*w+1].ile_razy += d[w].ile_razy;
	}
	d[w].ile_razy = 0;
	d[w].akt_czas = czas;
	
	if (polewej == l && p-l+1 == rozmiar) {
		d[w].ile_przysloniec += rodzaj;
		return d[w].akt_wyn;
	}
	
	LL res = 0;
	if (polewej + rozmiar/2  > l) 
		res += rek_zejscie(polewej,w*2,l,min(p,polewej + rozmiar/2 - 1),rodzaj,czas,rozmiar/2);
	if (polewej + rozmiar/2  <= p) 
		res += rek_zejscie(polewej + rozmiar/2,w*2+1,max(l,polewej + rozmiar/2),p,rodzaj,czas,rozmiar/2);
		
	d[w].akt_dlug = 0;
	if (d[2*w].ile_przysloniec) d[w].akt_dlug += d[2*w].dlug_przed; else d[w].akt_dlug += d[2*w].akt_dlug;
	if (d[2*w+1].ile_przysloniec) d[w].akt_dlug += d[2*w+1].dlug_przed; else d[w].akt_dlug += d[2*w+1].akt_dlug;
	return res;
}

int main(){	
	REP(g,2) {
		scanf("%d",&ile[g]);
		REP(i,ile[g]) {
			REP(j,4) scanf("%d",&t[g][i][j]);
			taby[iley++] = MP(t[g][i][1],MP(i,2+g));
			taby[iley++] = MP(t[g][i][3],MP(i,6+g));
			tabx[ilex++] = MP(t[g][i][0],MP(i,g));
			tabx[ilex++] = MP(t[g][i][2],MP(i,2+g));
		}
	}
	
	sort(taby,taby+iley);
	int wsk = 0;
	REP(i,iley) {
		if (i && taby[i].ST != taby[i-1].ST) ++wsk;
		t[taby[i].ND.ND&1][taby[i].ND.ST][taby[i].ND.ND/2] = wsk;
		pozy[wsk] = taby[i].ST;
	}
	
	REP(i,wsk) d[i+czapa].dlug_przed = pozy[i+1] - pozy[i];
	FORD(i,czapa-1,1) d[i].dlug_przed = d[i*2].dlug_przed + d[i*2+1].dlug_przed;
	
	sort(tabx,tabx+ilex);
	REP(i,ilex) {
		int l = t[tabx[i].ND.ND&1][tabx[i].ND.ST][1];
		int p = t[tabx[i].ND.ND&1][tabx[i].ND.ST][3]-1;
		if (tabx[i].ND.ND == 0) rek_zejscie(0,1,l,p,1,tabx[i].ST,czapa);
		if (tabx[i].ND.ND == 1) wyn[tabx[i].ND.ST] = -rek_zejscie(0,1,l,p,0,tabx[i].ST,czapa);
		if (tabx[i].ND.ND == 2) rek_zejscie(0,1,l,p,-1,tabx[i].ST,czapa);
		if (tabx[i].ND.ND == 3) wyn[tabx[i].ND.ST] += rek_zejscie(0,1,l,p,0,tabx[i].ST,czapa);
	}
	
	REP(i,ile[1]) printf("%lld\n",wyn[i]);
	return 0;
}
