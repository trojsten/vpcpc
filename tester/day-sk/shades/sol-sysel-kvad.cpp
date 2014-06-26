#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define FOR(i,n) for(int i = 0; i < n; i++)

int main(){
	vector<vector<int> > D;

	int n,l,pom;
	scanf("%d",&n);
	D.reserve(n+1);
	FOR(i,n+1){
		scanf("%d",&l);
		vector<int> V;
		V.reserve(l);
		FOR(j,l){
			scanf("%d",&pom);
			V.push_back(pom);
		}
		D.push_back(V);
	}

	long long res = 0LL;
	bool ok;

	FOR(i,n){
		l = D[i].size() - 1;
		pom = D[n].size() - l;
		FOR(j,pom){
			ok = true;
			FOR(k,l){
				if(((long long)D[n][j+k])*D[i][k+1]!=((long long)D[n][j+k+1])*D[i][k]){
					ok = false;
					break;
				}
			}
			if(ok) res++;
		}
	}

	printf("%lld\n",res);
}