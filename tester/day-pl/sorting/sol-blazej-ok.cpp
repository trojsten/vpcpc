#include <cstdio>
#include <vector>
#include <queue>
#include <stack>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <set>
#include <string>
#define scanf(arg...) (scanf(arg)?:0)
#define MAXN 100007
#define czapa 131072
#define MOD 1000000007LL
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

LL a,b,n,res;
LL d[czapa];
int t[MAXN];
string pom[MAXN];

string to_string(LL i) {
	string res = "";
	while (i) {
		res = char((i%10) + 48) + res;
		i /= 10;
	}
	return res;
}

bool cmp(int i, int j) {
	return pom[i-1] < pom[j-1];
}

int magic(int x) {
	return x&-x;
}

LL query(int poz) {
	int res = 0;
	while (poz) {
		res = res + d[poz];
		if (res > MOD) res -= MOD;
		poz -= magic(poz);
	}
	return res;
}

void insert(int poz, LL val) {
	while (poz != czapa) {
		d[poz] += val;
		if (d[poz] > MOD) d[poz] -= MOD;
		poz += magic(poz);
	}
} 

int main(){
	scanf("%lld%lld",&a,&b);
	n = b-a+1;
	REP(i,n) t[i] = i+1;
	REP(i,n) pom[i] = to_string(i+a);
	sort(t,t+n,cmp);
	res = 1;
	//REP(i,n) printf("%d\n",t[i]);
	//REP(i,n) printf("%s\n",pom[t[i]-1].c_str());
	REP(i,n) {
		//printf("%s\n",pom[t[i]-1].c_str());
		LL wyn = query(t[i])+1;
		//printf("%lld\n",wyn);
		res += wyn;
		if (res > MOD) res -= MOD;
		insert(t[i],wyn);
	}
	printf("%lld\n",res);
	return 0;
}
