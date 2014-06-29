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

int n,poz;
LL p,x,c,d,res,sumad,wyn,pomwyn;
pair<LL,LL> t[MAXN];

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
	wyn = INF;
	
	FOR(i,1,n+1) if (t[i].ST == p) poz = i;
	
	//lewo,prawo
	pomwyn = 0;
	FOR(i,1,poz-1) pomwyn += t[i].ND*(t[poz].ST-t[i].ST);
	FOR(i,poz+1,n+1) pomwyn += t[i].ND*(t[i].ST-t[poz].ST + 2*(t[poz].ST - t[1].ST));
	wyn = min(wyn,pomwyn);
	
	//prawo,lewo
	pomwyn = 0;
	FOR(i,poz+1,n+1) pomwyn += t[i].ND*(t[i].ST-t[poz].ST);
	FOR(i,1,poz-1) pomwyn += t[i].ND*(t[poz].ST-t[i].ST + 2*(t[n+1].ST - t[poz].ST));
	wyn = min(wyn,pomwyn);
	
	FOR(l,1,poz-1) FOR(p,poz+1,n+1) {
		//lewo,prawo
		pomwyn = 0;
		FOR(i,l,poz-1) pomwyn += t[i].ND*(t[poz].ST-t[i].ST);
		FOR(i,poz+1,p) pomwyn += t[i].ND*(t[i].ST-t[poz].ST + 2*(t[poz].ST - t[l].ST));
		FOR(i,1,l-1) pomwyn += t[i].ND*(t[poz].ST-t[i].ST + 2*(t[poz].ST - t[l].ST) + 2*(t[p].ST - t[poz].ST));
		FOR(i,p+1,n+1) pomwyn += t[i].ND*(t[i].ST-t[poz].ST + 2*(t[poz].ST - t[l].ST) + 2*(t[p].ST - t[poz].ST) + 2*(t[poz].ST-t[1].ST));
		wyn = min(wyn,pomwyn);
		
		//prawo,lewo
		pomwyn = 0;
		FOR(i,poz+1,p) pomwyn += t[i].ND*(t[i].ST-t[poz].ST);
		FOR(i,l,poz-1) pomwyn += t[i].ND*(t[poz].ST-t[i].ST + 2*(t[p].ST - t[poz].ST));
		FOR(i,p+1,n+1) pomwyn += t[i].ND*(t[i].ST-t[poz].ST + 2*(t[poz].ST - t[l].ST) + 2*(t[p].ST - t[poz].ST));
		FOR(i,1,l-1) pomwyn += t[i].ND*(t[poz].ST-t[i].ST + 2*(t[poz].ST - t[l].ST) + 2*(t[p].ST - t[poz].ST) + 2*(t[n+1].ST-t[poz].ST));
		wyn = min(wyn,pomwyn);
		
	}
	
	printf("%lld\n",res + wyn);
	return 0;
}
