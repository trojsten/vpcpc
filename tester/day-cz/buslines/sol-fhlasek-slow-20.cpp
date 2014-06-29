/* Written by Filip Hlasek 2014 */
/* Complexity: O(N^3) means it should get at least 20 points */
#include <cstdio>
#include <cstdlib>
#include <vector>
#define REP(i,b) for(int i=0;i<(b);i++)

using namespace std;

#define MAXN 1000001
vector<int> graph[MAXN];
int N;
long long ans[MAXN];

bool dfs(int start, int goal, int from) {
  if (start == goal) {
    ans[start]++;
    return true;
  }
  REP(i, graph[start].size()) {
    if (graph[start][i] != from && dfs(graph[start][i], goal, start)) {
      ans[start]++;
      return true;
    }
  }
  return false;
}

int main(int argc, char *argv[]) {
  scanf("%d", &N);
  REP(i, N - 1) {
    int x, y;
    scanf("%d%d", &x, &y); x--; y--;
    graph[x].push_back(y);
    graph[y].push_back(x);
  }
  REP(i, N) REP(j, i) dfs(i, j, -1);
  REP(i, N) printf("%lld\n", 2 * ans[i]);
  return 0;
}
