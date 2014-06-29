#include <cstdio>
#include <vector>
#include <queue>
#include <stack>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <set>
#define scanf(arg...) (scanf(arg)?:0)
#define MAXN
#define INF
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

LL a,b;
int testy;

bool check(LL a, LL b) {
	if (a == 0LL || b == 0LL) return false;
	if (a > b) swap(a,b);
	
	if (!check(b%a,a)) return true;
	LL wiel = b/a - 1;
	
	if (a&1LL) return (wiel&1LL);
	return (((wiel%(a+1))&1LL) || wiel%(a+1) == a); 
}

int main(){
	scanf("%d",&testy);
	while(testy--) {
		scanf("%lld%lld",&a,&b);
		puts(check(a,b) ? "Mirek" : "Kamil");
	}
	return 0;
}
