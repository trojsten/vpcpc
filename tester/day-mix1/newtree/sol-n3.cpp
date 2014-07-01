// {{{
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <complex>
#include <numeric>
#define REP(i, n) for (int i = 0; i < (int) (n); ++i)
#define FOR(i, a, b) for (int i = (int) (a); i <= (int) (b); ++i)
#define FORD(i, a, b) for (int i = (int) (a); i >= (int) (b); --i)
#define FORE(it, c) for (__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define SIZE(x) ((int) ((x).size()))
#define DEBUG(x) { cerr << #x << ": " << (x) << endl; }
#define SQR(x) ((x) * (x))
#define INF 1023456789
using namespace std;

template<typename T, typename U> ostream& operator << (ostream& os, const pair<T, U>& p) {
    os << "(" << p.first << "," << p.second << ")"; return os;
}

template<typename T> ostream& operator << (ostream& os, const vector<T>& v) {
    os << "["; FORE(i, v) { if (i != v.begin()) os << ", "; os << *i; } os << "]"; return os;
}

typedef long long LL;
typedef pair<int, int> PI;
typedef pair<int, PI> TRI;
typedef vector<int> VI;
typedef vector<VI> VVI;
// }}}

LL crossproduct(const PI& u, const PI& v) {
    return (LL) u.first * v.second - (LL) u.second * v.first;
}

PI operator - (const PI& u, const PI& v) {
    return PI(u.first - v.first, u.second - v.second);
}

bool ccw(const PI& a, const PI& b, const PI& c) {
    return crossproduct(b - a, c - a) > 0;
}

bool check(const PI& a, const PI& b, const PI& c, const PI& w, const vector<PI>& T) {
    if (!(ccw(a, b, w) && ccw(b, c, w) && ccw(c, a, w)))
        return false;
    REP(i, SIZE(T)) if (T[i] != a && T[i] != b && T[i] != c)
        if (!(ccw(b, a, T[i]) || ccw(c, b, T[i]) || ccw(a, c, T[i])))
            return false;
    return true;
}

int main() {
    int n, a;
    scanf("%d%d", &n, &a);
    --a;
    PI w;
    scanf("%d%d", &w.first, &w.second);
    vector<PI> T(n);
    REP(i, n)
        scanf("%d%d", &T[i].first, &T[i].second);

    VI b_candidates;
    REP(i, n) if (ccw(T[a], T[i], w))
        b_candidates.push_back(i);
    VI c_candidates;
    REP(i, n) if (ccw(T[i], T[a], w))
        c_candidates.push_back(i);

    FORE(b, b_candidates) FORE(c, c_candidates)
        if (check(T[a], T[*b], T[*c], w, T)) {
            printf("%d %d\n", *b + 1, *c + 1);
            return 0;
        }

    printf("0 0\n");
}
