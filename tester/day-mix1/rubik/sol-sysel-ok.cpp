#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

#define FOR(i, n) for(int i = 0; i < n; i++)

#define PS 54

int ID[PS]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53};

int ROTA[PS]={2,5,8,1,4,7,0,3,6,36,37,38,12,13,14,15,16,17,9,10,11,21,22,23,24,25,26,18,19,20,30,31,32,33,34,35,27,28,29,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53};
int ROTS[PS]={2,5,8,1,4,7,0,3,6,36,37,38,39,40,41,42,43,44,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,51,48,45,52,49,46,53,50,47};
int ROTU[PS]={9,10,11,12,13,14,15,16,17,45,46,47,48,49,50,51,52,53,24,21,18,25,22,19,26,23,20,8,7,6,5,4,3,2,1,0,38,41,44,37,40,43,36,39,42,35,34,33,32,31,30,29,28,27};

int * LISTS[][9]={
	{ROTA,ID,ID,ID,ID,ID,ID,ID,ID},//A
	{ROTU,ROTA,ROTU,ROTU,ROTU,ID,ID,ID,ID},//B
	{ROTS,ROTS,ROTS,ROTU,ROTA,ROTU,ROTU,ROTU,ROTS},//C
	{ROTS,ROTS,ROTU,ROTA,ROTU,ROTU,ROTU,ROTS,ROTS},//D
	{ROTS,ROTU,ROTA,ROTU,ROTU,ROTU,ROTS,ROTS,ROTS},//E
	{ROTU,ROTU,ROTA,ROTU,ROTU,ID,ID,ID,ID}//F
};

void inv(int * A, int * B){
	FOR(i,PS) B[A[i]]=i;
}

template<class T> void join(T * A, int * B, T * C){
	FOR(i,PS) C[i]=A[B[i]];
}

void list_join(int * A[9], int * B){
	int * pom = new int[PS];
	int * pom2 = new int[PS];

	join(ID,ID,pom);
	FOR(i,9){
		join(pom,A[i],pom2);
		swap(pom,pom2);
	}
	join(pom,ID,B);
}

#define TW 65536
int T[2*TW][PS];

int main(){

	int * pom = new int[PS];
	char * cube = new char[PS];
	char * cube2 = new char[PS];
	
	int * R[6];
	FOR(i,6){
		R[i] = new int[PS];
		list_join(LISTS[i],R[i]);
	}

	FOR(i,TW) join(ID,ID,T[TW+i]);

	char buffer[47];
	FOR(r,3){
		scanf("%s",buffer);
		FOR(s,3) cube[r*3+s] = buffer[s];
	}
	FOR(r,3){
		scanf("%s",buffer);
		FOR(g,4) FOR(s,3) cube[g*9+r*3+s+9] = buffer[3*g+s];
	}
	FOR(r,3){
		scanf("%s",buffer);
		FOR(s,3) cube[r*3+s+45] = buffer[s];
	}

	int n, m;
	scanf("%d ",&n);
	scanf("%d ",&m);

	int id,dir;
	char side[47];
	FOR(i,n){
		scanf("%s ",side);
		scanf("%d ",&dir);
		if(dir>0){
			join(ID,R[side[0]-'A'],T[TW+i]);
		} else {
			inv(R[side[0]-'A'],T[TW+i]);
		}
	}
	
	for(int i = TW-1; i > 0; i--){
		join(T[2*i],T[2*i+1],T[i]);
	}

	FOR(i,m){
		scanf("%d ",&id);
		scanf("%s ",side);
		scanf("%d ",&dir);
		--id;
		if(dir>0){
			join(ID,R[side[0]-'A'],T[TW+id]);
		} else {
			inv(R[side[0]-'A'],T[TW+id]);
		}
		for(int x=(TW+id)/2; x > 0; x/= 2){
			join(T[2*x],T[2*x+1],T[x]);
		}
		join(cube,T[1],cube2);
		FOR(r,3){
			FOR(s,3) printf("%c",cube2[r*3+s]);
			printf("\n");
		}
		FOR(r,3){
			FOR(g,4) FOR(s,3) printf("%c",cube2[g*9+r*3+s+9]);
			printf("\n");
		}
		FOR(r,3){
			FOR(s,3) printf("%c",cube2[r*3+s+45]);
			printf("\n");
		}
	}
	return 0;
}
