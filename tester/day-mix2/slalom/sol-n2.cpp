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

LL cross_product(const PI& u, const PI& v) {
    return (LL) u.first * v.second - (LL) u.second * v.first;
}

LL dot_product(const PI& u, const PI& v) {
    return (LL) u.first * v.first + (LL) u.second * v.second;
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

bool point_inside_hull(const PI& p, const vector<PI>& H) {
    REP(i, SIZE(H) - 1)
        if (!ccw(H[i], H[i + 1], p))
            return false;
    return true;
}

bool point_inside_hull(const vector<PI>& P, const vector<PI>& H) {
    FORE(p, P)
        if (point_inside_hull(*p, H))
            return true;
    return false;
}

double point_point_distance(const PI& a, const PI& b) {
    return sqrt(SQR((LL) a.first - b.first) + SQR((LL) a.second - b.second));
}

double point_line_distance(const PI& p, const PI& f, const PI& g) {
    LL a = f.second - g.second;
    LL b = g.first - f.first;
    LL c = - (a * f.first + b * f.second);
    assert(a * g.first + b * g.second + c == 0);
    double length = sqrt(SQR(a) + SQR(b));
    return fabs(a * p.first + b * p.second + c) / length;
}

double point_segment_distance(const PI& p, const PI& a, const PI& b) {
    double res = min(point_point_distance(p, a), point_point_distance(p, b));
    PI normal(b.second - a.second, a.first - b.first);
    assert(dot_product(normal, b - a) == 0);
    int sa = (cross_product(normal, a - p) > 0) ? 1 : -1;
    int sb = (cross_product(normal, b - p) > 0) ? 1 : -1;
    if (sa * sb == -1)
        res = min(res, point_line_distance(p, a, b));
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
        printf("%d\n", upper[0].second - lower[0].second);
        return 0;
    }

    sort(lower.rbegin(), lower.rend());
    compute_convex_hull(lower);
    sort(upper.begin(), upper.end());
    compute_convex_hull(upper);

    if (point_inside_hull(lower, upper) || point_inside_hull(upper, lower)) {
        printf("Impossible\n");
        return 0;
    }

    double res = 1e40;
    FORE(p, lower) REP(i, SIZE(upper) - 1)
        res = min(res, point_segment_distance(*p, upper[i], upper[i + 1]));
    FORE(p, upper) REP(i, SIZE(lower) - 1)
        res = min(res, point_segment_distance(*p, lower[i], lower[i + 1]));

    printf("%.10lf\n", res);
}
