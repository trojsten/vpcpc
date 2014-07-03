//tickets
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <list>
#define maxN 100001

using namespace std;
struct Req{
  int id, last;
  Req(){};
  Req(int xid, int xlast){
    id=xid; last=xlast;
  }
};

int n;
int T[maxN];
int E[maxN];
list<Req> R[maxN];
int A[maxN];

int Find(int x){
	int Nx = x;
	while (T[Nx] >= 0)
		Nx = T[Nx];
//path compression
   int xx;
	while (x != Nx){
		xx = T[x];
		T[x] = Nx;
		x = xx;
	}
	return Nx;
}
int Union(int Nx, int Ny){
	if (Nx == Ny)
		return Nx;
	if (T[Nx] > T[Ny]){//
      T[Ny] += T[Nx];
      T[Nx] = Ny;
      return Ny;
	}else{
      T[Nx] += T[Ny];
      T[Ny] = Nx;
      return Nx;
	}
}
int FindEmpty(int first, int last){
//Global: T,E
   int wb=Find(last);
   int feb=E[wb];
   if (first<=feb){
      int we=Find(feb-1);
      int fe=E[we];
      int web=Union(we,wb);
      E[web]=fe;
   }
   return feb;
}

int main (){
   int m,first,last;
   scanf("%d %d",&n, &m);
//init Union-Find
   for(int i=0;i<=n;i++){
      T[i]=-1;
      E[i]=i;
      A[i]=0;
   }
//read requests
   for(int i=1;i<=m;i++){
      scanf("%d %d",&first, &last);
      R[first].push_front(Req(i, last));
   }
   int sol=0;
   for(int x=n;x>0;x--){
      for(Req y:R[x]){
         int d=FindEmpty(x, y.last);
         if(x<=d){
            sol++;
            A[d]=y.id;
         }
      }
   }

   printf("%d\n", sol);
   for(int x=1;x<=n;x++)
      if(A[x]>0)
         printf("%d %d\n", x, A[x]);

	return 0;
}
