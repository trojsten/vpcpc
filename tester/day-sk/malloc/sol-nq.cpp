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

int main() {
    int n, q;
    scanf("%d%d", &n, &q);
    vector<bool> A(n, true);

    while (q--) {
        int cmd;
        scanf("%d", &cmd);
        if (cmd == 1) {
            int el;
            scanf("%d", &el);
            int start = 0;
            bool found = false;
            REP(end, n)
                if (!A[end]) {
                    start = end + 1;
                } else if (end - start + 1 == el) {
                    found = true;
                    break;
                }
            if (found) {
                printf("%d\n", start);
                REP(i, el)
                    A[start + i] = false;
            } else {
                printf("-1\n");
            }
        } else {
            int start, el;
            scanf("%d%d", &start, &el);
            int cnt = 0;
            REP(i, el)
                if (!A[start + i]) {
                    ++cnt;
                    A[start + i] = true;
                }
            printf("%d\n", cnt);
        }
    }
}
