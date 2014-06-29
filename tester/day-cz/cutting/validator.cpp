#include <iostream>
#include <sstream>
#include <bitset>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <cctype>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <algorithm>
#include <functional>
using namespace std;

#define DEBUG(x) cout << '>' << #x << ':' << x << endl;
#define REP(i,n) for(int i=0;i<(n);i++)
#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define FORD(i,a,b) for(int i=(a);i>=(b);i--)
inline bool EQ(double a, double b) { return fabs(a-b) < 1e-9; }

const int INF = 1<<29;
typedef long long ll;

inline int two(int n) { return 1 << n; }
inline int test(int n, int b) { return (n>>b)&1; }
inline void set_bit(int & n, int b) { n |= two(b); }
inline void unset_bit(int & n, int b) { n &= ~two(b); }
inline int last_bit(int n) { return n & (-n); }
inline int ones(int n) { int res = 0; while(n && ++res) n-=n&(-n); return res; }

template<class T> void chmax(T & a, const T & b) { a = max(a, b); }
template<class T> void chmin(T & a, const T & b) { a = min(a, b); }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

const int MAX = 10000;
int N, xs[MAX], ys[MAX];
int L, X1[MAX], Y1[MAX], X2[MAX], Y2[MAX];

long long cross(int X1, int Y1, int X2, int Y2)
{
	return (long long)X1 * Y2 - (long long)X2 * Y1;
}

bool which_side(int p, int l)
{
	return cross(X2[l]-X1[l], Y2[l]-Y1[l], xs[p]-X1[l], ys[p]-Y1[l]) <= 0;
}

vector<bool> bs[MAX];

bool cmp(vector<bool> * b1, vector<bool> * b2)
{
	return (*b1) < (*b2);
}

vector<bool> * pointers[MAX];

int main(int argc, char ** argv)
{
	FILE * fin = fopen(argv[1], "r");
	FILE * fout = fopen(argv[2], "r");

	fscanf(fin, "%d", &N);
	REP(i, N) fscanf(fin, "%d%d", xs+i, ys+i);
	fclose(fin);

	fscanf(fout, "%d", &L);
	REP(i, L) fscanf(fout, "%d%d%d%d", X1+i, Y1+i, X2+i, Y2+i);
	fclose(fout);

	REP(p, N)
	{
		pointers[p] = bs+p;
		bs[p].resize(L);
		REP(l, L)
			bs[p][l] = which_side(p, l);
	}
	sort(pointers, pointers+N, cmp);
	REP(p, N-1)
		if (bs[p] == bs[p+1])
			return 1;

	return 0;
}
