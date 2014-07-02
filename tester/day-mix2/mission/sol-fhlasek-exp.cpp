/* Written by Filip Hlasek 2014 */
#include <cstdio>
#include <vector>
#include <algorithm>

#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define FORD(i,a,b) for(int i=(a);i>=(b);i--)
#define REP(i,b) for(int i=0;i<(b);i++)

using namespace std;

#define INF 1000000001
#define MAXN 21

int graph[MAXN][MAXN], N, M, B, E, H;
int dp[1 << MAXN][MAXN];

int solve(int mask, int v) {
  int & ans = dp[mask][v];
  if (ans) return ans;
  if (v == H) return (mask & (1 << E)) ? 0 : INF;
  mask |= 1 << v;
  ans = INF;
  REP(i, N) if (!(mask & (1 << i)) && graph[v][i]) {
    ans = min(ans, graph[v][i] + solve(mask, i));
  }
  return ans;
}

int main(int argc, char *argv[]) {
  scanf("%d%d%d%d%d", &N, &M, &B, &E, &H); B--; E--; H--;
  REP(i, M) {
    int u, v, t;
    scanf("%d%d%d", &u, &v, &t); u--; v--;
    graph[u][v] = graph[v][u] = t;
  }

  int ans = solve(0, B);
  if (ans == INF) printf("-1\n");
  else printf("%d\n", ans);

  return 0;
}
