/* Written by Filip Hlasek 2014 */
#include <cstdio>
#include <cstdlib>
#include <vector>
#define REP(i,b) for(int i=0;i<(b);i++)

using namespace std;

#define MAXN 1000001
vector<int> graph[MAXN];
int N;
long long ans[MAXN];

// Returns the number of vertices in the subtree
int dfs(int node, int parent) {
  ans[node] = (long long)N * (N - 1) / 2;
  int subtree_size = 1;
  REP(i, graph[node].size()) if (graph[node][i] != parent) {
    int tmp = dfs(graph[node][i], node);
    subtree_size += tmp;
    ans[node] -= (long long)tmp * (tmp - 1) / 2;
  }
  int tmp = N - subtree_size;
  ans[node] -= (long long)tmp * (tmp - 1) / 2;
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
  dfs(0, -1);
  REP(i, N) printf("%lld\n", ans[i]);
  return 0;
}
