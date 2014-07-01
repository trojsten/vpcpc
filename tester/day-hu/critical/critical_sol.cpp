//critical
#include <iostream>
#include <stdio.h>
#include <list>
#include <queue>
#define maxN 100001

using namespace std;

list<int> G[maxN];
int n;
int T[maxN];
int inDegree[maxN];
int L[maxN];
int Ln[maxN];
bool Sol[maxN];

void readIn(){
    int m,u,v;
    scanf("%d %d", &n,&m);
    for(int i=1;i<=n;i++){
        inDegree[i]=0;
        Sol[i]=false;
    }
    for(int i=0; i<m; i++){
        scanf("%d %d", &u,&v);
        G[u].push_front(v);
        inDegree[v]++;
    }
}

int main(){
    readIn();
    queue<int> Q;
    int last=0;
    for(int x=1;x<=n;x++) Ln[x]=0;
    for(int p=1;p<=n;p++)
      if(inDegree[p]==0){
         Q.push(p);
         T[++last]=p;
         L[p]=1;
         Ln[1]++;
      }
   while(!Q.empty()){
      int p=Q.front(); Q.pop();
      for(int q:G[p]){
         inDegree[q]--;
         if(inDegree[q]==0){
            L[q]=L[p]+1;
            Ln[L[q]]++;
            T[++last]=q;
            Q.push(q);
         }
      }
   }
//for(int x=1;x<=n;x++) cerr<<T[x]<<","; cerr<<endl;
   int Fmax=1, Fp;
   int Soln=0;;
   for(int i=1;i<=n;i++){
      int p=T[i];
      if(Ln[L[p]]==1 && Fmax==L[p]){
         Sol[p]=true;
         Soln++;
      }
      Fp=n+1;
      for(int q:G[p])
         if(L[q]<Fp)
            Fp=L[q];
        Fmax=max(Fmax, Fp);
    }//
    printf("%d\n", Soln);
    for(int x=1;x<=n;x++)
      if(Sol[x]){
        printf("%d", x);
        Soln--;
        if(Soln>0) printf(" ");
      }
    printf("\n");
    return 0;
}
