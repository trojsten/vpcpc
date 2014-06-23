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

int n, q, b, m;
vector<bool> A;
VI max_segment, max_prefix, max_suffix, total, lazy_flag;

void set_zeros(int j) {
    lazy_flag[j] = LAZY_ZEROS;
    max_segment[j] = 0;
    max_prefix[j] = 0;
    max_suffix[j] = 0;
    total[j] = 0;
}

void set_ones(int j) {
    lazy_flag[j] = LAZY_ONES;
    max_segment[j] = b;
    max_prefix[j] = b;
    max_suffix[j] = b;
    total[j] = b;
}

void recompute(int j) {
    assert(lazy_flag[j] == LAZY_NONE);
    int offset = j * b;
    max_segment[j] = 0;
    max_prefix[j] = 0;
    max_suffix[j] = 0;
    total[j] = 0;
    int u = 0;
    REP(v, b)
        if (!A[offset + v]) {
            u = v + 1;
        } else {
            ++total[j];
            if (v - u + 1 > max_segment[j]) {
                max_segment[j] = v - u + 1;
            }
            if (u == 0) {
                max_prefix[j] = v + 1;
            }
        }
    max_suffix[j] = b - u;
}

int main() {
    scanf("%d%d", &n, &q);
    b = sqrt(n) + 7;
    m = (n + b - 1) / b;
    A.resize(m * b, false);
    REP(i, n)
        A[i] = true;
    max_segment.resize(m);
    max_prefix.resize(m);
    max_suffix.resize(m);
    total.resize(m);
    lazy_flag.resize(m, LAZY_NONE);
    REP(i, m)
        recompute(i);

    while (q--) {
        int cmd;
        scanf("%d", &cmd);
        if (cmd == 1) {
            int el;
            scanf("%d", &el);
            int s = 0, u = 0;
            bool found = false;
            REP(i, m)
                if (s + max_prefix[i] >= el) {
                    found = true;
                    break;
                } else if (max_prefix[i] == b) {
                    s += b;
                } else if (max_segment[i] >= el) {
                    int offset = i * b;
                    u = 0;
                    REP(v, b)
                        if (!A[offset + v]) {
                            u = v + 1;
                        } else if (v - u + 1 == el) {
                            break;
                        }
                    u += offset;
                    found = true;
                    break;
                } else {
                    s = max_suffix[i];
                    u = (i + 1) * b - max_suffix[i];
                }
            if (found) {
                printf("%d\n", u);
                int j = (u + b - 1) / b;
                int k = (u + el) / b;
                if (j <= k) {
                    if (u % b != 0) {
                        if (lazy_flag[j - 1] == LAZY_ONES) {
                            lazy_flag[j - 1] = LAZY_NONE;
                            FOR(i, (j - 1) * b, u - 1)
                                A[i] = true;
                        }
                        FOR(i, u, j * b - 1)
                            A[i] = false;
                        recompute(j - 1);
                    }
                    FOR(i, j, k - 1)
                        set_zeros(i);
                    if ((u + el) % b != 0) {
                        FOR(i, k * b, u + el - 1)
                            A[i] = false;
                        if (lazy_flag[k] == LAZY_ONES) {
                            lazy_flag[k] = LAZY_NONE;
                            FOR(i, u + el, (k + 1) * b - 1)
                                A[i] = true;
                        }
                        recompute(k);
                    }
                } else {
                    if (lazy_flag[k] == LAZY_ONES)
                        FOR(i, k * b, u - 1)
                            A[i] = true;
                    FOR(i, u, u + el - 1)
                        A[i] = false;
                    if (lazy_flag[k] == LAZY_ONES) {
                        FOR(i, u + el, (k + 1) * b - 1)
                            A[i] = true;
                        lazy_flag[k] = LAZY_NONE;
                    }
                    recompute(k);
                }
            } else {
                printf("-1\n");
            }
        } else {
            int u, el, cnt = 0;
            scanf("%d%d", &u, &el);
            int j = (u + b - 1) / b;
            int k = (u + el) / b;
            if (u / b != (u + el) / b) {
                if (u % b != 0) {
                    if (lazy_flag[j - 1] == LAZY_ONES) {
                        FOR(i, (j - 1) * b, u - 1)
                            A[i] = true;
                    } else if (lazy_flag[j - 1] == LAZY_ZEROS) {
                        FOR(i, (j - 1) * b, u - 1)
                            A[i] = false;
                    }
                    FOR(i, u, j * b - 1) {
                        if ((lazy_flag[j - 1] == LAZY_NONE && !A[i]) || lazy_flag[j - 1] == LAZY_ZEROS)
                            ++cnt;
                        A[i] = true;
                    }
                    lazy_flag[j - 1] = LAZY_NONE;
                    recompute(j - 1);
                }
                FOR(i, j, k - 1) {
                    cnt += b - total[i];
                    set_ones(i);
                }
                if ((u + el) % b != 0) {
                    FOR(i, k * b, u + el - 1) {
                        if ((lazy_flag[k] == LAZY_NONE && !A[i]) || lazy_flag[k] == LAZY_ZEROS)
                            ++cnt;
                        A[i] = true;
                    }
                    if (lazy_flag[k] == LAZY_ONES) {
                        FOR(i, u + el, (k + 1) * b - 1)
                            A[i] = true;
                    } else if (lazy_flag[k] == LAZY_ZEROS) {
                        FOR(i, u + el, (k + 1) * b - 1)
                            A[i] = false;
                    }
                    lazy_flag[k] = LAZY_NONE;
                    recompute(k);
                }
            } else {
                if (lazy_flag[k] == LAZY_ONES) {
                    FOR(i, k * b, u - 1)
                        A[i] = true;
                } else if (lazy_flag[k] == LAZY_ZEROS) {
                    FOR(i, k * b, u - 1)
                        A[i] = false;
                }
                FOR(i, u, u + el - 1) {
                    if ((lazy_flag[k] == LAZY_NONE && !A[i]) || lazy_flag[k] == LAZY_ZEROS)
                        ++cnt;
                    A[i] = true;
                }
                if (lazy_flag[k] == LAZY_ONES) {
                    FOR(i, u + el, (k + 1) * b - 1)
                        A[i] = true;
                } else if (lazy_flag[k] == LAZY_ZEROS) {
                    FOR(i, u + el, (k + 1) * b - 1)
                        A[i] = false;
                }
                lazy_flag[k] = LAZY_NONE;
                recompute(k);
            }
            printf("%d\n", cnt);
        }
    }
}
