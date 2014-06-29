#include <cstdio>
#include <algorithm>
#include <vector>

#define MAX_N 1000047
#define FOR(i,n) for(int i = 0; i < n; i++)

int U[2][MAX_N];
int S[2][MAX_N];
int G[MAX_N];
int V[MAX_N];


int get(int d, int v){
	if(U[d][v] != v){
		U[d][v] = get(d,U[d][v]);
	}
	return U[d][v];
}

int n;

void look_at_me(int a, int b, int inf);

int next(int v){
	return get(1,G[v]);
}

bool join(int d, int a, int b){
	int a1 = a;
	int b1 = b;
	a = get(d,a);
	b = get(d,b);
	if(a == b) return false;
	if(S[d][a] < S[d][b]){
		std::swap(a,b);
		std::swap(a1,b1);
	}
	if(d == 0){
		look_at_me(b1,next(b1),n);
		G[b1]=a1;
		printf("0\n");
	}
	S[d][a] += S[d][b];
	U[d][b] = a;
	return true;
}

bool check(int v, int t){
	if(V[v] == t) return true;
	V[v] = t;
	return false;
}

void look_at_me(int a, int b, int inf){
	if(inf == b) return;
	int c = next(b);
	G[b] = a;
	look_at_me(b, c, inf);
}


int main(){
	int m;
	int a, b, a2, b2, meet;
	
	scanf("%d",&n);
	scanf("%d",&m);

	FOR(k,2) FOR(i,n+1){
		U[k][i] = i;
		S[k][i] = 1;
		G[i] = n;
		V[i] = -1;
	}
	
	FOR(i,m){
		scanf("%d",&a);
		scanf("%d",&b);
		--a; --b;
		a=get(1,a);
		b=get(1,b);
		//FOR(j,n) printf("%d %d %d\n",U[0][j],U[1][j],G[j]);
		fflush(stdout);
		if(join(0,a,b)){
			
		} else {
			meet = -1;
			a2 = a; b2 = b;
			std::vector<int> J;
			while(meet == -1){
				if(check(a,i)) meet = a;
				else {
					V[n]=-1;
					if(check(b,i)) meet = b;
				}
				V[n]=-1;
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