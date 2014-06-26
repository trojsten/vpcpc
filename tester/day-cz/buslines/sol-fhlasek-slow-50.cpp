/* Written by Filip Hlasek 2014 */
/* Complexity: O(N^2) means it should get 50 points */
#include <cstdio>
#include <cstdlib>
#include <vector>
#define REP(i,b) for(int i=0;i<(b);i++)

using namespace std;

#define MAXN 1000001
vector<int> graph[MAXN];
int N;
long long ans[MAXN];

// Returns a subtree size
int dfs(int node, int parent) {
  int subtree_size = 1;
  REP(i, graph[node].size()) if (graph[node][i] != parent) {
    subtree_size += dfs(graph[node][i], node);
  }
  ans[node] += subtree_size;
  return subtree_size;
}

int main(int argc, char *argv[]) {
  scanf("%d", &N);
  REP(i, N - 1) {
    int x, y;
    scanf("%d%d", &x, &y); x--; y--;
    graph[x].push_back(y);
    graph[y].push_back(x);
  }
  REP(i, N) dfs(i, -1);
  REP(i, N) printf("%lld\n", ans[i] / 2);
  return 0;
}
