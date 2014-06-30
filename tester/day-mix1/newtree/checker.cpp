#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#define Maxn 1000001
#define Maxm 2000001

using namespace std;

typedef long long int int64;
typedef struct{
  int64 x,y;
  int id;
}Point;
typedef struct{
  int a,b;
}PPair;

Point P[Maxn];

int Turn(Point P0,Point P1,Point P2){
   int64 crossp=(P1.x-P0.x)*(P2.y-P0.y)-(P2.x-P0.x)*(P1.y-P0.y);
   if (crossp<0)
      return -1;
   else if (crossp>0)
      return 1;
   else
      return 0;
}
bool Between(Point P1,Point P2,Point Q){
//In: P1-P2-Q colinear
//Out: P1-Q-P2
   return   (abs(P1.x-Q.x)<=abs(P2.x-P1.x)) &&
            (abs(P2.x-Q.x)<=abs(P2.x-P1.x)) &&
            (abs(P1.y-Q.y)<=abs(P2.y-P1.y)) &&
            (abs(P2.y-Q.y)<=abs(P2.y-P1.y)) ;
}
bool Cross(Point p1, Point p2, Point q1, Point q2){
	int fpq1 = Turn(p1, p2, q1);
  	int fpq2 = Turn(p1, p2, q2);
  	int fqp1 = Turn(q1, q2, p1);
  	int fqp2 = Turn(q1, q2, p2);

  	return  (fpq1 * fpq2 < 0) && (fqp1 * fqp2 < 0) ||
         fpq1 == 0 && Between(p1, p2, q1) ||
         fpq2 == 0 && Between(p1, p2, q2) ||
         fqp1 == 0 && Between(q1, q2, p1) ||
         fqp2 == 0 && Between(q1, q2, p2);
}
bool SIntree(Point a, Point b, Point c, Point s){
   return Turn(a,b,s)>0 && Turn(b,c,s)>0 && Turn(c,a,s)>0 ;
}
bool Intree(Point a, Point b, Point c, Point s){
   return Turn(a,b,s)>=0 && Turn(b,c,s)>=0 && Turn(c,a,s)>=0 ;
}

int main (int argc, char *argv[]){
   ifstream TinF(argv[1]);
   ifstream ToutF(argv[3]);
   int b0,c0;
   ToutF>>b0>>c0;
   ToutF.close();

   ifstream CoutF(argv[2]);

   int n,a;
   Point Q;
   TinF>>n>>a;
   TinF>>Q.x>>Q.y;

   for(int i=1;i<=n;i++){
      TinF>>P[i].x>>P[i].y;
   }

   int b,c;
   CoutF>>b>>c;
   if (CoutF.fail()){
cerr<<"Wrong answer"<<endl;
      return 1;
   }
   if(b0==0 && c0==0){
      if (b==0 && c==0){
            cerr<<"OK"<<endl;
	return 0;
      }else{
cerr<<"Wrong answer"<<endl;
      return 1;
      }
   }
   if(b<1 || b>n || c<1 || c>n || a==b || a==c || b==c){
cerr<<"Wrong answer"<<endl;
      return 1;
   }
   if(!SIntree(P[a],P[b],P[c], Q)){
cerr<<"Wrong answer"<<endl;
      return 1;
   }
   for(int i=1;i<=n;i++)
      if(a!=i && b!=i && c!=i && Intree(P[a],P[b],P[c], P[i])){
cerr<<"Wrong answer"<<endl;
         return 1;
      }

   cerr<<"OK"<<endl;
	return 0;
}
