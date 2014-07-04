#include <cstdio>
#include <vector>
#include <queue>
#include <stack>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <set>
#define scanf(arg...) (scanf(arg)?:0)
#define MAXN 100007
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

const double EPS = 1e-7;
const double INF = 1e12;

double s,c;
double sciezka[MAXN];
int n,k,a,b,centroid,ilosc,ogr,maks_gleb;
int ile[MAXN], cent[MAXN], gleb[MAXN], wyn_gleb[MAXN];
pair<double,int> wyn[MAXN][2], akt_wyn[2];
vector<pair<int,double> > v[MAXN];
vector<int> poz[MAXN];
bool bylo[MAXN];

void dfs(int x, int f) {
	ile[x] = 1;
	FOREACH(it,v[x]) if (it->ST != f && !bylo[it->ST]) {
		dfs(it->ST,x);
		ile[x] += ile[it->ST];
	} 
}

void dfs2(int x, int f) {
	bool mozna = true;
	FOREACH(it,v[x]) if (it->ST != f && !bylo[it->ST]) {
		if (ile[it->ST]*2 > ilosc) {
			mozna = false;
			dfs2(it->ST,x);
		}
	}
	if ((ilosc - ile[x])*2 > ilosc) mozna = false;
	if (mozna) centroid = x;  
}

void dfs3(int x, int f) {
	maks_gleb = max(maks_gleb,gleb[x]);
	FOREACH(it,v[x]) if (it->ST != f && cent[it->ST] > ogr) {
		gleb[it->ST] = gleb[x] + 1;
		sciezka[it->ST] = sciezka[x] + it->ND - s;
		dfs3(it->ST,x);
	}
}

void popraw(pair<double,int> *tab, pair<double,int> val){
	if (tab[0].ST < val.ST) {
		if (tab[0].ND != val.ND) tab[1] = tab[0];
		tab[0] = val;
	}
	else if (tab[1].ST < val.ST && tab[0].ND != val.ND) 
		tab[1] = val;
}

void dfs4(int x, int f, int poddrzewo) {
	popraw(wyn[gleb[x]],MP(sciezka[x],poddrzewo));
	FOREACH(it,v[x]) if (it->ST != f && cent[it->ST] > ogr) 
		dfs4(it->ST,x,poddrzewo);
}

void rob(int x, int war) {
	dfs(x,-1); ilosc = ile[x];
	dfs2(x,-1); 
	int pom = centroid;
	poz[war].PB(pom);
	cent[pom] = war;
	bylo[pom] = true;
	FOREACH(it,v[pom]) if (!bylo[it->ST]) rob(it->ST,war+1);
}

bool path_through(int x) {
	//printf("srednia %lf przez %d\n",s,x);
	double res = -1.0;
	gleb[x] = maks_gleb = 0; sciezka[x] = 0.0; ogr = cent[x]; 
	
	//if (wyn_gleb[x] != 0 && 2*wyn_gleb[x] < k) return 0.0;
	dfs3(x,-1); 
	//wyn_gleb[x] = maks_gleb;
	if (2*maks_gleb < k) return false;
	
	FOR(i,1,maks_gleb) wyn[i][0] = wyn[i][1] = MP(-INF,-1);
	FOREACH(it,v[x]) if (cent[it->ST] > ogr) dfs4(it->ST,x,it->ST);
	
	/*printf("%d\n",maks_gleb);
	FOR(i,1,maks_gleb) {
		printf("%d : %lf %d | %lf %d\n",i,wyn[i][0].ST,wyn[i][0].ND,wyn[i][1].ST,wyn[i][1].ND);
	}*/
	
	akt_wyn[0] = akt_wyn[1] = MP(-INF,-1);
	FORD(i,maks_gleb,k) {
		popraw(akt_wyn,wyn[i][0]);
		popraw(akt_wyn,wyn[i][1]);		
	}
	
	FOR(i,1,maks_gleb) {
		if (k-i > 0 && k-i <= maks_gleb) {
			popraw(akt_wyn,wyn[k-i][0]);
			popraw(akt_wyn,wyn[k-i][1]);		
		}
		if (k - i == 0) popraw(akt_wyn,MP(0.0,-1));
		//printf("%d : %lf %d | %lf %d\n",i,akt_wyn[0].ST,akt_wyn[0].ND,akt_wyn[1].ST,akt_wyn[1].ND);
		double pom = wyn[i][0].ST + ((akt_wyn[0].ND == wyn[i][0].ND) ? akt_wyn[1].ST : akt_wyn[0].ST);
		//printf("%lf\n",pom);
		res = max(res,pom);
	}
	//if (res >= 0.0) puts("WYSZLO");
	return res >= 0.0;
}

bool check() {
	FOR(g,1,n) if (!poz[g].empty()) {
		FOREACH(it,poz[g])
			if (path_through(*it)) return true;
	} 
	return false;
}

int main(){
	scanf("%d%d",&n,&k);
	REP(i,n-1) {
		scanf("%d%d%lf",&a,&b,&c);
		v[a].PB(MP(b,c));
		v[b].PB(MP(a,c));
	}
	
	rob(1,1);
	double l = 0.0;
	double p = 1000000.0;
	while (p-l >= EPS) {
		s = (p+l)/2.0;
		if (check()) l = s; else p = s;
	}
	printf("%.7lf\n",l);
	return 0;
}
