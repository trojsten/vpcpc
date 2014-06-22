#include <cstdio>
#include <algorithm>
#include <vector>

#define MAX_N 1000000
#define FOR(i,n) for(int i = 0; i < n; i++)

int U[2][MAX_N];
int S[2][MAX_N];
int G[MAX_N+1];
int V[MAX_N];

int get(int d, int v){
	if(U[d][v] != v){
		U[d][v] = get(d,U[d][v]);
	}
	return U[d][v];
}

bool join(int d, int a, int b){
	a = get(d,a);
	b = get(d,b);
	if(a == b) return false;
	if(S[d][a] < S[d][b]){
		std::swap(a,b);
	}
	S[d][a] += S[d][b];
	U[d][b] = a;
	return true;
}

int next(int v){
	return get(1,G[v]);
}

bool check(int v, int t){
	if(V[v] == t) return true;
	V[v] = t;
	return false;
}


int main(){
	int n, m;
	int a, b, a2, b2, meet;
	
	scanf("%d",&n);
	scanf("%d",&m);

	FOR(k,2) FOR(i,n){
		U[k][i] = i;
		S[k][i] = 1;
		G[i] = n;
		V[i] = -1;
	}
	G[n] = n;
	
	FOR(i,m){
		scanf("%d",&a);
		scanf("%d",&b);
		--a; --b;
		if(join(0,a,b)){
			G[b]=a;
			printf("0\n");
		} else {
			meet = -1;
			a=get(1,a);
			b=get(1,b);
			a2 = a; b2 = b;
			std::vector<int> J;
			while(meet == -1){
				if(check(a,i)) meet = a;
				else if(check(b,i)) meet = b;
				a = next(a);
				b = next(b);
			}
			J.push_back(meet);
			while(a2 != meet){
				J.push_back(a2);
				a2 = next(a2);
			}
			while(b2 != meet){
				J.push_back(b2);
				b2 = next(b2);
			}
			FOR(i, J.size()-1) join(1, J[i],J[i+1]);
			G[get(1,meet)] = G[meet];
			printf("%d\n",J.size());
		}
			
	}

}