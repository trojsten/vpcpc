#include <cstdio>
#include <algorithm>
#include <vector>
#define scanf(arg...) (scanf(arg)?:0)

using namespace std;

typedef long long int ll;

const int p = 1e9 + 7;

char aa[25], bb[25];

bool leks(ll a, ll b)
{
   sprintf(aa, "%lld", a);
   sprintf(bb, "%lld", b);
   int i;
   for(i = 0; aa[i] && bb[i]; i++)
   {
       if(aa[i] < bb[i])
           return true;
       if(bb[i] < aa[i])
           return false;
   }
   if(aa[i])
       return false;
   if(bb[i])
       return true;
   return false;
}

ll drz[2100005];
int n2;
void dodaj(int w, ll x)
{
   w += n2;
   while(w)
   {
       drz[w] = (drz[w] + x) % p;
       w /= 2;
   }
}

ll odczyt(int a, int b)
{
   a += n2;
   b += n2;
   ll wyn = drz[a];
   if(a != b)
       wyn = (wyn + drz[b]) % p;
   while((a / 2) != (b / 2))
   {
       if(a % 2 == 0)
           wyn = (wyn + drz[a + 1]) % p;
       if(b % 2 == 1)
           wyn = (wyn + drz[b - 1]) % p;
       a /= 2;
       b /= 2;
   }
   return wyn;
}

int main()
{
   ll a, b;
	 int n;
   scanf("%lld%lld", &a, &b);
   n = b - a + 5;
   n2 = 1;
   while(n2 < n)
       n2 *= 2;
   for(int i = 1; i <= n2 * 2; i++)
       drz[i] = 0;
   vector<ll> v;
   for(ll i = a; i <= b; i++)
       v.push_back(i);
   sort(v.begin(), v.end(), leks);
   for(int i = 0; i < v.size(); i++)
   {
       ll ile = odczyt(0, v[i] - a) + 1;
       dodaj(v[i] - a, ile);
   }
   printf("%lld\n", (odczyt(0, n2 - 1)+1)%p);
	 return 0;
}
