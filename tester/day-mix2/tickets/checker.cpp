#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#define Maxn 100001
#define Maxm 1000001

using namespace std;

typedef long long int int64;
struct Req{
  int a, b;
/*
  Req(){};
  Req(int xa, int xb){
   a=xa; b=xb;
  }
*/
};

Req R[Maxm];
bool S[Maxn];

int main (int argc, char *argv[]){
   ifstream TinF(argv[1]);
   ifstream CoutF(argv[2]);
   ifstream ToutF(argv[3]);
   int n,m,sol,vsol;
   ToutF>>sol;
   ToutF.close();

   TinF>>n>>m;
   for(int i=1;i<=n;i++) S[i]=false;
   for(int i=1;i<=m;i++){
      TinF>>R[i].a>>R[i].b;
   }

   int x,xs;
   CoutF>>vsol;
   if (CoutF.fail()){
      cerr<<"Output format error"<<endl;
      return 1;
   }
   if(sol!=vsol){
      cerr<<"Wrong answer"<<endl;
      return 1;
   }
   for(int i=1;i<=sol;i++){
       CoutF>>x>>xs;
      if (CoutF.fail()){
         cerr<<"Output format error"<<endl;
         return 1;
      }
      if(x<1 || x>n || xs<1 || xs>m){
         cerr<<"Wrong answer"<<endl;
         return 1;
      }
      if(S[x] || x<R[xs].a || x>R[xs].b){
         cerr<<"Wrong answer"<<endl;
         return 1;
      }
      S[x]=true;
      vsol--;
   }
   if(vsol!=0){
      cerr<<"Wrong answer"<<endl;
         return 1;
   }
   cerr<<"OK"<<endl;
	return 0;
}
