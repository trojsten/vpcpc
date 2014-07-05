#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#define Maxn 1000001
#define Maxm 3000001

using namespace std;

typedef long long int int64;
typedef struct{
  int64 x,y;
  int id;
}Point;
typedef struct{
  int a,b;
}PPair;

int n[2], m[2];
Point Q,R;
Point P[2][Maxn];
PPair S[2][Maxm];
int mini[2];
bool w;
int Turn(Point P0,Point P1,Point P2){
   int64 crossp=(P1.x-P0.x)*(P2.y-P0.y)-(P2.x-P0.x)*(P1.y-P0.y);
   if (crossp<0)
      return -1;
   else if (crossp>0)
      return 1;
   else
      return 0;
}
//
void ReadIn() {
   int64 x,y;
   scanf("%d %d", &n[0], &m[0]);
   int min1=1,min2=1;
	for (int i=1; i<=n[0]; i++){
      scanf("%lld %lld", &x,&y);
		P[0][i].x=x; P[0][i].y=y;
		P[0][i].id=i;
		if (y<P[0][min1].y || y==P[0][min1].y && x<P[0][min1].x) min1=i;
	}
	int ix,iy;
	for (int i=1; i<=m[0]; i++){
      scanf("%d %d", &ix,&iy);
		S[0][i].a=ix; S[0][i].b=iy;
	}
//
	scanf("%d %d", &n[1], &m[1]);
	for (int i=1; i<=n[1]; i++){
      scanf("%lld %lld", &x,&y);
		P[1][i].x=x; P[1][i].y=y;
		P[1][i].id=i;
		if (y<P[1][min2].y || y==P[1][min2].y && x<P[1][min2].x) min2=i;
	}
	for (int i=1; i<=m[1]; i++){
      scanf("%d %d", &ix,&iy);
		S[1][i].a=ix; S[1][i].b=iy;;
	}
	mini[0]=min1; mini[1]=min2;
	if(P[0][min1].y<P[1][min2].y){
      w=false;
	}else if(P[0][min1].y>P[1][min2].y){
      w=true;
	}else{//
	   if(P[0][min1].x<P[1][min2].x){
         w=false;
	   }else{
         w=true;
	   }
      for(int i=1; i<=n[w]; i++){
         if(P[w][i].y==P[w][mini[w]].y && P[w][i].x>P[w][mini[w]].x )
            mini[w]=i;
      }
      cout<<P[0][mini[0]].id<<" "<<P[0][mini[1]].id<<endl;
      exit(0);
	}
}
bool Sless(Point p1, Point p2, Point q1, Point q2){
   int pq1=Turn(p1,p2,q1);
   int pq2=Turn(p1,p2,q2);
   int qp1=Turn(q1,q2,p1);
   int qp2=Turn(q1,q2,p2);
   return pq1<=0 && pq2<=0 || qp1>=0 && qp2>=0;
}
bool Between(Point p1,Point p2, Point p3){
//Global: P
//In: P[i1]-P[i2]-P[i3] colinear
   return   (abs(p1.x-p3.x)<=abs(p2.x-p1.x)) &&
            (abs(p2.x-p3.x)<=abs(p2.x-p1.x)) &&
            (abs(p1.y-p3.y)<=abs(p2.y-p1.y)) &&
            (abs(p2.y-p3.y)<=abs(p2.y-p1.y)) ;
}
//
int main (){
   ReadIn();
   Point a=P[w][mini[w]]; Point b=P[!w][mini[!w]];
   for(int i=1;i<=n[w];i++)
      if(P[w][i].y<b.y && a.y<P[w][i].y) a=P[w][i];
   Point c,c1,c2;
   c=a; c1.id=0;
   for(int i=1;i<=m[w]; i++){
      int taba=Turn(a,b,P[w][S[w][i].a]);
      int tabb=Turn(a,b,P[w][S[w][i].b]);
      int ta=Turn(P[w][S[w][i].a],P[w][S[w][i].b], a);
      int tb=Turn(P[w][S[w][i].a],P[w][S[w][i].b], b);
      if(taba<0 && tabb>0 && ta*tb<0){
         if(c1.id==0 || Sless(c1,c2,P[w][S[w][i].a],P[w][S[w][i].b])){
               c1=P[w][S[w][i].a]; c2=P[w][S[w][i].b];
            }
      }else if(taba>0 && tabb<0 && ta*tb<0){
         if(c1.id==0 || Sless(c1,c2,P[w][S[w][i].b],P[w][S[w][i].a])){
               c1=P[w][S[w][i].b]; c2=P[w][S[w][i].a];
            }
      }
   }
   if(c1.id==0){
      if(w)
         cout<<b.id<<" "<<a.id<<endl;
      else
         cout<<a.id<<" "<<b.id<<endl;
      return 0;
   }
   if(c1.y<=b.y){
      c=c1;
      for(int i=i;i<=n[w];i++)
         if(Turn(a,b,P[w][i])<0 && Turn(c1,c2,P[w][i])<0 &&
            (Turn(b,c,P[w][i])<0 ||  Turn(b,c,P[w][i])==0 && Between(b,c,P[w][i])))
            c=P[w][i];
   }else{
      c=c2;
      for(int i=i;i<=n[w];i++)
         if(Turn(a,b,P[w][i])>0 && Turn(c1,c2,P[w][i])<0 &&
            (Turn(b,c,P[w][i])>0 ||  Turn(b,c,P[w][i])==0 && Between(b,c,P[w][i])))
            c=P[w][i];
   }
   if(w)
      cout<<b.id<<" "<<c.id<<endl;
   else
      cout<<c.id<<" "<<b.id<<endl;
	return 0;
}
