/* Written by Filip Hlasek 2014 */
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <string>
#include <algorithm>
#include <cmath>
#include <cstring>

#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define FORD(i,a,b) for(int i=(a);i>=(b);i--)
#define REP(i,b) for(int i=0;i<(b);i++)

using namespace std;

#define MAXN 111111
vector<int> childern[MAXN];
int best, N;

int dfs(int vertex) {
  int mask = 0, forbidden = 0;
  REP(i, childern[vertex].size()) {
    int tmp = dfs(childern[vertex][i]);
    forbidden |= mask & tmp;
    mask |= tmp;
  }

  int ans = 0;
  while ((mask & (1 << ans)) || (1 << ans) <= forbidden) {
    mask ^= (1 << ans) & mask;
    ans++;
  }
  mask |= (1 << ans);
  best = max(ans, best);
  return mask;
}

int main(int argc, char *argv[]) {
  scanf("%d", &N);
  REP(i, N - 1) {
    int parent;
    scanf("%d", &parent);
    childern[parent].push_back(i + 1);
  }
  dfs(0);
  printf("%d\n", best + 1);
  return 0;
}
