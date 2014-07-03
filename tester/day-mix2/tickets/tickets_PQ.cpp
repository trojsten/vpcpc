#include <iostream>
#include <queue>
#include <list>
#define maxN 100001
using namespace std;

class Elem{
   public :
   int last; int id ;
   Elem() {};
   Elem(int x , int y) { last = x ; id = y;}
   bool operator <(const Elem&) const;
 };
 bool Elem:: operator < (const Elem& jobb ) const {
   return last > jobb.last ;
 }

int main(){
   list<Elem> R[maxN];
   int A[maxN];
   priority_queue <Elem> C;
   int n,m, a,last;
   cin >> n; cin >> m;
   for ( int i=1; i<=m; i++) {
      cin >>a >> last;
      R[a].push_front(Elem(last, i));
   }
   int sol=0;
   for (int x=1; x<=n; x++) {
      for(Elem y:R[x])
         C.push(y);
      if (C. size() >0){
         Elem e=C.top(); C.pop();
         A[x]=e.id;
         sol++;
      }
      while (C.size() >0 && C.top().last==x)
         C.pop();
 }// for x
    cout <<sol<< endl ;
   for (int x=1; x<=n; x++)
      if (A[x]>0)
         cout << x<<" "<<A[x]<<endl ;

 return 0;
} // end main
