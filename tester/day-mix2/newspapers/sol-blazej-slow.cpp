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
typedef pair<int,int> PII;

const double EPS = 1e-7;
const double INF = 1e12;

double c,res;
double sciezka[MAXN];
int n,k,a,b,dl;
int gleb[MAXN];
vector<pair<int,double> > v[MAXN];

void dfs(int x, int f) {
	if (gleb[x] >= k) {
		if (res < sciezka[x]/double(gleb[x])) {
			res = sciezka[x]/double(gleb[x]);
			dl = gleb[x];
		}
	}
	FOREACH(it,v[x]) if (it -> ST != f) {
		gleb[it->ST] = gleb[x] + 1;
		sciezka[it->ST] = sciezka[x] + it->ND;
		dfs(it->ST,x);
	}
}

void licz(int x) {
	sciezka[x] = 0.0;
	gleb[x] = 0;
	dfs(x,-1);
}

int main(){
	scanf("%d%d",&n,&k);
	REP(i,n-1) {
		scanf("%d%d%lf",&a,&b,&c);
		v[a].PB(MP(b,c));
		v[b].PB(MP(a,c));
	}
	
	FOR(i,1,n) licz(i);
	printf("%.7lf\n",res);
	return 0;
}
