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

#define BUF_LENGTH 256
char buf[BUF_LENGTH];

char impossible_string[] = "Impossible\n";

const double EPS = 1e-9;

bool compare_doubles(double correct, double contestant) {
    if (fabs(correct - contestant) <= EPS)
        return true;
    double bound_a = correct * (1 - EPS);
    double bound_b = correct * (1 + EPS);
    double lower = min(bound_a, bound_b);
    double upper = max(bound_a, bound_b);
    return lower <= contestant && contestant <= upper;
}

bool test(FILE* correct, FILE* contestant) {
    assert(fgets(buf, BUF_LENGTH, correct) == buf);
    bool correct_is_impossible = (strcmp(buf, impossible_string) == 0);
    double correct_answer;
    if (!correct_is_impossible)
        assert(sscanf(buf, "%lf", &correct_answer) == 1);

    if (fgets(buf, BUF_LENGTH, contestant) == NULL)
        return false;
    bool contestant_said_impossible = (strcmp(buf, impossible_string) == 0);
    double contestant_answer;
    if (!contestant_said_impossible)
        if (sscanf(buf, "%lf", &contestant_answer) != 1)
            return false;

    if (correct_is_impossible && contestant_said_impossible)
        return true;
    if (correct_is_impossible || contestant_said_impossible)
        return false;
    return compare_doubles(correct_answer, contestant_answer);
}

// ./tester OUR_OUTPUT CONTESTANTS_OUTPUT
int main(int argc, char* argv[]) {
    assert(argc == 3);
    FILE* correct = fopen(argv[1], "r");
    assert(correct != NULL);
    FILE* contestant = fopen(argv[2], "r");
    assert(contestant != NULL);
    bool ok = test(correct, contestant);
    fclose(correct);
    fclose(contestant);
    if (!ok) {
        printf("WA\n");
        return 47;
    } else {
        printf("OK\n");
        return 0;
    }
}
