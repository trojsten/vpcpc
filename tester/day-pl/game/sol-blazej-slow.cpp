#include <cstdio>
#include <vector>
#include <queue>
#include <stack>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <set>
#define scanf(arg...) (scanf(arg)?:0)
#define MAXN 1000
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

int a,b;
int testy;
bool wyn[MAXN+3][MAXN+3];

bool check(int i, int j) {
	if (!wyn[j%i][i]) return true;
	int pot = i;
	while (pot <= j) {
		if (!wyn[min(i,j-pot)][max(i,j-pot)]) return true;
		pot *= i;
	}
	return false;
}

int main(){
	scanf("%d",&testy);
	
	FOR(i,1,MAXN) FOR(j,i,MAXN) {
		wyn[i][j] = check(i,j);
	}
	
	while(testy--) {
		scanf("%d%d",&a,&b);
		puts(wyn[min(b,a)][max(a,b)] ? "Mirek" : "Kamil");
	}
	return 0;
}
