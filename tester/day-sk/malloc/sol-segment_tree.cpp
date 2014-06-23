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

const int LAZY_NONE = 0;
const int LAZY_ZEROS = 1;
const int LAZY_ONES = 2;

struct Node {
    int range_u, range_v;
    int max_segment, max_prefix, max_suffix, total;
    int lazy_flag;

    void recompute(const Node& left, const Node& right) {
        int half_length = (range_v - range_u) / 2;
        max_segment = max(left.max_suffix + right.max_prefix, max(left.max_segment, right.max_segment));
        max_prefix = (left.max_prefix == half_length) ? half_length + right.max_prefix : left.max_prefix;
        max_suffix = (right.max_suffix == half_length) ? half_length + left.max_suffix : right.max_suffix;
        total = left.total + right.total;
    }

    void set_zeros() {
        max_segment = max_prefix = max_suffix = total = 0;
    }

    void set_ones() {
        max_segment = max_prefix = max_suffix = total = range_v - range_u;
    }

    void do_not_be_lazy(Node* left, Node* right) {
        if (lazy_flag != LAZY_NONE) {
            if (lazy_flag == LAZY_ZEROS) {
                set_zeros();
            } else {
                set_ones();
            }
            if (left != NULL) {
                left->lazy_flag = right->lazy_flag = lazy_flag;
            }
            lazy_flag = LAZY_NONE;
        }
    }
};

int n2;
vector<Node> S;

void push_laziness_down(int x) {
    if (x < n2) {
        S[x].do_not_be_lazy(&S[2 * x], &S[2 * x + 1]);
    } else {
        S[x].do_not_be_lazy(NULL, NULL);
    }
}

void allocate_suffix(int x, int el) {
    int r = S[x].range_v - S[x].range_u;
    if (r == el) {
        S[x].lazy_flag = LAZY_ZEROS;
        push_laziness_down(x);
    } else {
        push_laziness_down(2 * x);
        push_laziness_down(2 * x + 1);
        if (r / 2 >= el) {
            allocate_suffix(2 * x + 1, el);
        } else {
            allocate_suffix(2 * x, el - r / 2);
            allocate_suffix(2 * x + 1, r / 2);
        }
        S[x].recompute(S[2 * x], S[2 * x + 1]);
    }
}

int find_segment(int x, int el) {
    if (S[x].max_segment < el)
        return -1;
    if (S[x].range_v - S[x].range_u == el) {
        S[x].lazy_flag = LAZY_ZEROS;
        push_laziness_down(x);
        return S[x].range_u;
    }
    push_laziness_down(2 * x);
    push_laziness_down(2 * x + 1);
    int res = -2;
    if (S[2 * x].max_segment >= el) {
        res = find_segment(2 * x, el);
    } else if (S[2 * x].max_suffix != 0 && S[2 * x].max_suffix + S[2 * x + 1].max_prefix >= el) {
        int k = S[2 * x].max_suffix;
        allocate_suffix(2 * x, k);
        find_segment(2 * x + 1, el - k);
        res = S[2 * x].range_v - k;
    } else {
        res = find_segment(2 * x + 1, el);
    }
    S[x].recompute(S[2 * x], S[2 * x + 1]);
    return res;
}

int u, v;

int reset_segment(int x) {
    push_laziness_down(x);
    if (S[x].range_v <= u || v <= S[x].range_u)
        return 0;
    if (u <= S[x].range_u && S[x].range_v <= v) {
        int res = S[x].total;
        S[x].lazy_flag = LAZY_ONES;
        push_laziness_down(x);
        return res;
    }
    int res = reset_segment(2 * x) + reset_segment(2 * x + 1);
    S[x].recompute(S[2 * x], S[2 * x + 1]);
    return res;
}

int main() {
    int n, q;
    scanf("%d%d", &n, &q);

    n2 = 1;
    while (n2 < n)
        n2 *= 2;
    S.resize(2 * n2);
    REP(i, n2) {
        S[n2 + i].range_u = i;
        S[n2 + i].range_v = i + 1;
        if (i < n) {
            S[n2 + i].set_ones();
        } else {
            S[n2 + i].set_zeros();
        }
        S[n2 + i].lazy_flag = LAZY_NONE;
    }
    FORD(i, n2 - 1, 1) {
        S[i].range_u = S[2 * i].range_u;
        S[i].range_v = S[2 * i + 1].range_v;
        S[i].recompute(S[2 * i], S[2 * i + 1]);
    }

    REP(i, q) {
        int cmd;
        scanf("%d", &cmd);
        if (cmd == 1) {
            int el;
            scanf("%d", &el);
            push_laziness_down(1);
            printf("%d\n", find_segment(1, el));
        } else {
            int el;
            scanf("%d%d", &u, &el);
            v = u + el;
            printf("%d\n", el - reset_segment(1));
        }
    }
}
