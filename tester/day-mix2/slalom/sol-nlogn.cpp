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

PI operator - (const PI& a, const PI& b) {
    return PI(a.first - b.first, a.second - b.second);
}

double size(const PI& a) {
    return sqrt(SQR((LL) a.first) + SQR((LL) a.second));
}

LL dot_product(const PI& u, const PI& v) {
    return (LL) u.first * v.first + (LL) u.second * v.second;
}

LL cross_product(const PI& u, const PI& v) {
    return (LL) u.first * v.second - (LL) u.second * v.first;
}

bool ccw(const PI& a, const PI& b, const PI& c) {
    return cross_product(b - a, c - a) > 0;
}

void compute_convex_hull(vector<PI>& P) {
    vector<PI> H;
    FORE(p, P) {
        while (SIZE(H) >= 2 && !ccw(H[SIZE(H) - 2], H[SIZE(H) - 1], *p))
            H.pop_back();
        H.push_back(*p);
    }
    P.swap(H);
}

bool hulls_intersect(const vector<PI>& lower, const vector<PI>& upper) {
    int j = 0;
    FORD(i, SIZE(lower) - 2, 1) {
        while (upper[j].first <= lower[i].first)
            ++j;
        assert(0 < j && j < SIZE(upper));
        if (ccw(upper[j - 1], upper[j], lower[i]))
            return true;
    }
    j = 0;
    FORD(i, SIZE(upper) - 2, 1) {
        while (lower[j].first >= upper[i].first)
            ++j;
        assert(0 < j && j < SIZE(lower));
        if (ccw(lower[j - 1], lower[j], upper[i]))
            return true;
    }
    return false;
}

double point_point_distance(const PI& a, const PI& b) {
    return size(b - a);
}

double point_line_distance(const PI& a, const PI& b, const PI& c) {
    PI d = b - c;
    PI n(-d.second, d.first);
    LL t = dot_product(n, b - a);
    return abs(t / size(n));
}

double hulls_distance(const vector<PI>& lower, const vector<PI>& upper) {
    double res = 1e20;
    int j = 0;
    FORD(i, SIZE(lower) - 2, 0) {
        PI normal(lower[i + 1].second - lower[i].second, lower[i].first - lower[i + 1].first);
        assert(cross_product(normal, lower[i + 1] - lower[i]) > 0);
        while (j < SIZE(upper) && cross_product(normal, upper[j] - lower[i + 1]) > 0) {
            res = min(res, point_point_distance(upper[j], lower[i + 1]));
            ++j;
        }
        while (j < SIZE(upper) && cross_product(normal, upper[j] - lower[i]) > 0) {
            res = min(res, point_line_distance(upper[j], lower[i], lower[i + 1]));
            ++j;
        }
    }
    while (j < SIZE(upper)) {
        res = min(res, point_point_distance(upper[j], lower[0]));
        ++j;
    }
    return res;
}

int main() {
    int n;
    scanf("%d", &n);
    vector<PI> upper(n), lower(n);
    REP(i, n) {
        int x, y1, y2;
        scanf("%d%d%d", &x, &y1, &y2);
        lower[i] = PI(x, y1);
        upper[i] = PI(x, y2);
    }

    if (n == 1) {
        printf("%.10lf\n", (double) (upper[0].second - lower[0].second));
        return 0;
    }

    sort(lower.rbegin(), lower.rend());
    sort(upper.begin(), upper.end());
    compute_convex_hull(lower);
    compute_convex_hull(upper);

    assert(SIZE(lower) >= 2);
    assert(SIZE(upper) >= 2);
    assert(lower[0].first == upper[SIZE(upper) - 1].first);
    assert(lower[0].second <= upper[SIZE(upper) - 1].second);
    assert(lower[SIZE(lower) - 1].first == upper[0].first);
    assert(lower[SIZE(lower) - 1].second <= upper[0].second);

    if (hulls_intersect(lower, upper)) {
        printf("Impossible\n");
        return 0;
    }

    printf("%.10lf\n", min(hulls_distance(lower, upper), hulls_distance(upper, lower)));
}
