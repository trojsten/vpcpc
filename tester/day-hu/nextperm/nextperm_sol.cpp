//
#include <stdio.h>
#include <stack>
#define maxN 100001
#include <iostream>

using namespace std;

int main(){
   int n;
   scanf("%d", &n);
   int P[n];
   int u=0; P[0]=n;
   for(int i=1; i<=n; i++){
      scanf("%d", &P[i]);
      if(P[i-1]<P[i]) u=i-1;
   }
   stack<int> S;
   int i=1,ii=1;
   while(i<=u){
      if(P[i]==ii){
         i++; ii++;
      }else if(!S.empty() && S.top()==P[i]){
         S.pop();
         i++;
      }else{
         S.push(ii);
         ii++;
      }
   }

   i--;
   S.push(P[u]);
   int v=ii++;
   P[i]=v;
   while(!S.empty()){
      int x=S.top(); S.pop();
      P[++i]=x;
   }
   for(ii=v+1;ii<=n;ii++)
      P[ii]=ii;
   for(int i=1;i<n;i++)
      printf("%d ",P[i]);
   printf("%d\n",P[n]);

    return 0;
}
