/* Written by Filip Hlasek 2014 */
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <map>

#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define FORD(i,a,b) for(int i=(a);i>=(b);i--)
#define REP(i,b) for(int i=0;i<(b);i++)

using namespace std;

#define MAXN 111000
int N;
vector<int> graph[MAXN];
char color[MAXN];
int h[MAXN];

int get_color(int v) { return color[v] == 'B' ? +1 : -1; }

long long best = -(long long)MAXN * MAXN;

map<int, long long> diffs;
void dfs(int v, int parent, int diff=0, long long happiness=0) {
  diff += get_color(v);
  happiness += h[v];

  if (!diffs.count(diff)) diffs[diff] = happiness;
  diffs[diff] = max(diffs[diff], happiness);

  REP(i, graph[v].size()) if (graph[v][i] != parent) {
    dfs(graph[v][i], v, diff, happiness);
  }
}

int get_center(int v, int parent, int N) {
  int ans = -1;
  REP(i, graph[v].size()) if (parent != graph[v][i]) {
    int tmp = get_center(graph[v][i], v, N);
    if (tmp >= 0) return tmp;
    ans += tmp;
  }
  if (2 * (-ans) > N) return v;
  return ans;
}

int getN(int v, int parent=-1) {
  int ans = 1;
  REP(i, graph[v].size()) if (parent != graph[v][i]) ans += getN(graph[v][i], v);
  return ans;
}

void solve(int v) {
  int N = getN(v);
  if (N < 2) return;

  int center = get_center(v, -1, N);

  map<int, long long> global_diffs;
  global_diffs[0] = 0;
  REP(i, graph[center].size()) {
    int n = graph[center][i];
    diffs.clear();
    dfs(n, center);
    for (map<int, long long>::iterator it = diffs.begin(); it != diffs.end(); ++it) {
      int diff = -it->first - get_color(center);
      if (global_diffs.count(diff)) {
        best = max(best, it->second + h[center] + global_diffs[diff]);
      }
    }
    for (map<int, long long>::iterator it = diffs.begin(); it != diffs.end(); ++it) {
      if (!global_diffs.count(it->first)) global_diffs[it->first] = it->second;
      global_diffs[it->first] = max(global_diffs[it->first], it->second);
    }
    REP(j, graph[n].size()) if (graph[n][j] == center) {
      graph[n].erase(graph[n].begin() + j);
      break;
    }
    solve(n);
  }
}

int main(int argc, char *argv[]) {
  scanf("%d", &N);
  scanf("%s", color);
  REP(i, N) scanf("%d", h + i);
  REP(i, N - 1) {
    int v;
    scanf("%d", &v); v--;
    graph[v].push_back(i + 1);
    graph[i + 1].push_back(v);
  }
  solve(0);
  printf("%lld\n", best);
  return 0;
}
