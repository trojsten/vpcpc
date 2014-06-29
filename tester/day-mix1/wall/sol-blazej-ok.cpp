#include <cstdio>
#include <vector>
#include <queue>
#include <stack>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <set>
#define scanf(arg...) (scanf(arg)?:0)
#define MAXN 2007
#define INF 4000000000000000000LL
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

int n;
LL p,x,c,d,res,sumad;
LL wyn[MAXN][MAXN][2];
LL pref[MAXN];
pair<LL,LL> t[MAXN];

LL get(int i, int j) {
	return pref[j] - pref[i-1];
}

int main(){
	scanf("%d%lld",&n,&p);
	t[n+1] = MP(p,0);
	FOR(i,1,n) {
		scanf("%lld%lld%lld",&x,&c,&d);
		res += c;
		sumad += d;
		t[i] = MP(x,d);
	}
	sort(t+1,t+n+2);
	
	FOR(i,1,n+1) pref[i] = pref[i-1] + t[i].ND;
	
	FOR(i,1,n+1) {
		if (t[i].ST == p) wyn[i][i][0] = wyn[i][i][1] = 0;
			else wyn[i][i][0] = wyn[i][i][1] = INF;
	}
	
	//FOR(i,1,n+1) FOR(j,i,n+1) printf("%d %d| %lld %lld\n",i,j,wyn[i][j][0],wyn[i][j][1]);
	
	FOR(i,2,n+1) FOR(j,1,n-i+2) {
		wyn[j][j+i-1][0] = wyn[j+1][j+i-1][1] + (sumad - get(j+1,j+i-1))*(t[j+i-1].ST - t[j].ST);
		wyn[j][j+i-1][0] = min(wyn[j][j+i-1][0],wyn[j+1][j+i-1][0] + (sumad - get(j+1,j+i-1))*(t[j+1].ST - t[j].ST));
		wyn[j][j+i-1][0] = min(wyn[j][j+i-1][0],INF);
		
		wyn[j][j+i-1][1] = wyn[j][j+i-2][0] + (sumad - get(j,j+i-2))*(t[j+i-1].ST - t[j].ST);
		wyn[j][j+i-1][1] = min(wyn[j][j+i-1][1],wyn[j][j+i-2][1] + (sumad - get(j,j+i-2))*(t[j+i-1].ST - t[j+i-2].ST));
		wyn[j][j+i-1][1] = min(wyn[j][j+i-1][1],INF);
	}
	
	//FOR(i,1,n+1) FOR(j,i,n+1) printf("%d %d| %lld %lld\n",i,j,wyn[i][j][0],wyn[i][j][1]);
	
	printf("%lld\n",res + min(wyn[1][n+1][0],wyn[1][n+1][1]));
	return 0;
}
