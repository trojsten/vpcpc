/* Written by Filip Hlasek 2014 */
#include <cstdio>
#include <vector>
#include <algorithm>

#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define FORD(i,a,b) for(int i=(a);i>=(b);i--)
#define REP(i,b) for(int i=0;i<(b);i++)

using namespace std;

#define INF 1000000001
#define MAXN 1000
#define MAX_STEPS 100000000

vector<int> graph[MAXN], cost[MAXN];
int N, M, B, E, H;
bool visited[MAXN];
int STEPS = 0;

int solve(int v) {
  if (++STEPS > MAX_STEPS) return INF;
  if (v == H) return visited[E] ? 0 : INF;
  visited[v] = true;
  int ans = INF;
  REP(i, graph[v].size()) if (!visited[graph[v][i]]) {
    int n = graph[v][i];
    ans = min(ans, cost[v][i] + solve(n));
  }
  visited[v] = false;
  return ans;
}

int main(int argc, char *argv[]) {
  scanf("%d%d%d%d%d", &N, &M, &B, &E, &H); B--; E--; H--;
  REP(i, M) {
    int u, v, t;
    scanf("%d%d%d", &u, &v, &t); u--; v--;
    graph[u].push_back(v);
    graph[v].push_back(u);
    cost[u].push_back(t);
    cost[v].push_back(t);
  }

  int ans = solve(B);
  if (ans == INF) printf("-1\n");
  else printf("%d\n", ans);

  return 0;
}
