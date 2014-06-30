#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#define Maxn 100007
using namespace std;

typedef long long int64;
typedef struct{
  int64 x,y;
  int id;
}Point;
int n,a,t;
Point T,Q;
Point P[Maxn];
int L[Maxn]; int R[Maxn];

int Turn(int i0, int i1, int i2){
//Global: P
   int64 crossp=(P[i1].x-P[i0].x)*(P[i2].y-P[i0].y)-(P[i2].x-P[i0].x)*(P[i1].y-P[i0].y);
   if (crossp<0)
      return -1;
   else if (crossp>0)
      return 1;
   else
      return 0;
}
bool Between(int i1,int i2, int i3){
//Global: P
//In: P[i1]-P[i2]-P[i3] colinear
   return   (abs(P[i1].x-P[i3].x)<=abs(P[i2].x-P[i1].x)) &&
            (abs(P[i2].x-P[i3].x)<=abs(P[i2].x-P[i1].x)) &&
            (abs(P[i1].y-P[i3].y)<=abs(P[i2].y-P[i1].y)) &&
            (abs(P[i2].y-P[i3].y)<=abs(P[i2].y-P[i1].y)) ;
}
//ordering relation
int RPolsort(const void* a, const void* b) {
  int64 ax =P[*((int*) a)].x - Q.x;
  int64 ay =P[*((int*) a)].y - Q.y;
  int64 bx =P[*((int*) b)].x - Q.x;
  int64 by =P[*((int*) b)].y - Q.y;
  if (ax==bx && ay==by) return 0;
   int64  crossp=ax*by - bx*ay;
   if (crossp > 0)
      return -1;
   else if (crossp < 0)
      return 1;
   else {
      if (abs(ax)<=abs(bx) && abs(ay)<=abs(by))
         return -1;
      else
         return 1;
   }
}
void ReadIn() {
   int64 x,y;
   scanf("%d %d", &n, &a);
   scanf("%lld %lld", &x,&y);
   T.x=x; T.y=y;
	for (int i=0; i<n; i++){
      scanf("%lld %lld", &x,&y);
		P[i].x=x; P[i].y=y;
		P[i].id=i+1;
	}
}
int main (){
   ReadIn();
   t=n; P[n]=T;
   a--;
   int b=-1, c=-1;
   int n1=0, n2=0;
   int aa=-1;
   for(int i=0;i<n;i++){
      int tati=Turn(a,t,i);
      if(tati<0){
         R[n1++]=i;
         if(b<0)
            b=i;
         else{
            int tabi=Turn(a,b,i);
            if(tabi>0 || tabi==0 && Between(a,b,i))
               b=i;
         }
      }else if(tati>0){
         L[n2++]=i;
         if(c<0)
            c=i;
         else{
            int taci=Turn(a,c,i);
            if(taci<0 || taci==0 && Between(a,c,i))
               c=i;
         }
      }else{//a-t-i colinear
         if(i==a) continue;
         if(Between(a,t,i)){
            cout<<"0 0\n";
            cerr<<"1"<<endl;
            return 0;
         }
         if(aa<0 || Between(aa,t,i)){
            aa=i;
         }
      }
   }
   if(n1==0 || n2==0){
      cout<<"0 0\n";
      return 0;
   }
   if(aa<0){//easy case
      if(Turn(b,c,t)>0)
        cout<<P[b].id<<" "<<P[c].id<<endl;
      else
        cout<<"0 0\n";
      return 0;
   }
//
    Q=P[aa];
    qsort(R, n1, sizeof(int),  RPolsort);
    Q=P[a];
    qsort(L, n2, sizeof(int),  RPolsort);
    int i1=0, i2=0;
    while(i1<n1 && i2<n2){
      if(Turn(R[i1],L[i2], t)<=0){
         int u=R[i1];
            do
               i1++;
            while(i1<n1 && Turn(a,u,R[i1])<=0);
        }else{
            if(Turn(R[i1],L[i2], aa)<0){
               cout<<P[R[i1]].id<<" "<<P[L[i2]].id<<endl;
               return 0;
            }else{
               int u=L[i2];
               do
                  i2++;
               while(i2<n2 && Turn(aa,u,L[i2])<=0);
            }
        }
    }
   cout<<"0 0\n";
	return 0;
}
