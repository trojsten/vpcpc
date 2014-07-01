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

Point P1[Maxn];
Point P2[Maxn];
PPair R1[Maxm];
PPair R2[Maxm];

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

int main (int argc, char *argv[]){
   ifstream TinF(argv[1]);
   ifstream CoutF(argv[2]);
//   ifstream ToutF(argv[3]);
   int n1,m1,n2,m2;
   TinF>>n1>>m1;
   for(int i=1;i<=n1;i++){
      TinF>>P1[i].x>>P1[i].y;
   }
   for(int i=1;i<=m1;i++){
      TinF>>R1[i].a>>R1[i].b;
   }
   TinF>>n2>>m2;
   for(int i=1;i<=n2;i++){
      TinF>>P2[i].x>>P2[i].y;
   }
   for(int i=1;i<=m2;i++){
      TinF>>R2[i].a>>R2[i].b;
   }
   int a,b;
   CoutF>>a>>b;
   if (CoutF.fail()){
cerr<<"Wrong answer"<<endl;
      return 1;
   }
   if(a<1 || a>n1 || b<1 || b>n2){
cerr<<"Wrong answer"<<endl;
      return 1;
   }
   for(int i=1;i<=m1;i++)
      if(a!=R1[i].a && a!=R1[i].b &&
         Cross(P1[a],P2[b],P1[R1[i].a],P1[R1[i].b])){
cerr<<"Wrong answer"<<endl;
         return 1;
      }
   for(int i=1;i<=m2;i++)
      if(b!=R2[i].a && b!=R2[i].b &&
         Cross(P1[a],P2[b],P2[R2[i].a],P2[R2[i].b])){
cerr<<"Wrong answer"<<endl;
         return 1;
      }
   cerr<<"OK"<<endl;
	return 0;
}
