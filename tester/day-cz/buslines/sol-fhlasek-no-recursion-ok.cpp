/* Written by Filip Hlasek 2014 */
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <stack>
#define REP(i,b) for(int i=0;i<(b);i++)

using namespace std;

#define MAXN 1000001
vector<int> graph[MAXN];
int N;
long long ans[MAXN];

int subtree_size[MAXN], parent[MAXN];
stack<int> s;

void dfs() {
  parent[0] = -1;
  s.push(0);
  while (!s.empty()) {
    int node = s.top(); s.pop();
    if (!subtree_size[node]) {
      s.push(node);
      subtree_size[node]++;
      REP(i, graph[node].size()) if (graph[node][i] != parent[node]) {
        parent[graph[node][i]] = node;
        s.push(graph[node][i]);
      }
    }
    else {
      ans[node] = (long long)N * (N - 1) / 2;
      REP(i, graph[node].size()) if (graph[node][i] != parent[node]) {
        int tmp = subtree_size[graph[node][i]];
        subtree_size[node] += tmp;
        ans[node] -= (long long)tmp * (tmp - 1) / 2;
      }
      int tmp = N - subtree_size[node];
      ans[node] -= (long long)tmp * (tmp - 1) / 2;
    }
  }
}

int main(int argc, char *argv[]) {
  scanf("%d", &N);
  REP(i, N - 1) {
    int x, y;
    scanf("%d%d", &x, &y); x--; y--;
    graph[x].push_back(y);
    graph[y].push_back(x);
  }
  dfs();
  REP(i, N) printf("%lld\n", 2 * ans[i]);
  return 0;
}
