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
#include <list>
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

    list<PI> L;
    L.push_back(PI(0, n));

    while (q--) {
        int cmd;
        scanf("%d", &cmd);
        if (cmd == 1) {
            int el, u = -1;
            scanf("%d", &el);
            FORE(i, L) if (i->second >= el) {
                u = i->first;
                if (i->second > el) {
                    i->first += el;
                    i->second -= el;
                } else {
                    L.erase(i);
                }
                break;
            }
            printf("%d\n", u);
        } else {
            int u, el;
            scanf("%d%d", &u, &el);
            list<PI>::iterator i = L.begin();
            while (i != L.end() && i->first + i->second < u)
                ++i;
            if (i == L.end()) {
                L.push_back(PI(u, el));
                printf("%d\n", el);
                continue;
            }
            list<PI>::iterator j = i;
            int cnt = 0;
            while (j != L.end() && j->first <= u + el) {
                cnt += min(u + el, j->first + j->second) - max(u, j->first);
                ++j;
            }
            printf("%d\n", el - cnt);
            if (i == j) {
                L.insert(j, PI(u, el));
            } else {
                int new_u = min(u, i->first);
                list<PI>::iterator k = j;
                --k;
                int new_el = max(u + el, k->first + k->second) - new_u;
                L.erase(i, j);
                L.insert(j, PI(new_u, new_el));
            }
        }
    }
}
