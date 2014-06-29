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

class Tree {
public:
  vector<int> V;
  vector<pair<int, int> > E;
};

Tree subtree;
map<int, long long> diffs;
void dfs(int v, int parent, int diff=0, long long happiness=0) {
  subtree.V.push_back(v);

  diff += get_color(v);
  happiness += h[v];

  if (!diffs.count(diff)) diffs[diff] = happiness;
  diffs[diff] = max(diffs[diff], happiness);

  REP(i, graph[v].size()) if (graph[v][i] != parent) {
    subtree.E.push_back(make_pair(v, graph[v][i]));
    dfs(graph[v][i], v, diff, happiness);
  }
}

void solve(Tree tree) {

  if (tree.V.size() < 2) return;

  REP(i, tree.V.size()) graph[tree.V[i]].clear();
  REP(i, tree.E.size()) {
    graph[tree.E[i].first].push_back(tree.E[i].second);
    graph[tree.E[i].second].push_back(tree.E[i].first);
  }
  int center = tree.V[rand() % tree.V.size()];

  vector<Tree> subtrees;
  map<int, long long> global_diffs;
  global_diffs[0] = 0;
  REP(i, graph[center].size()) {
    int n = graph[center][i];
    subtree.V.clear(); subtree.E.clear();
    diffs.clear();
    dfs(n, center);
    subtrees.push_back(subtree);
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
  }

  REP(i, subtrees.size()) solve(subtrees[i]);
}

int main(int argc, char *argv[]) {
  scanf("%d", &N);
  scanf("%s", color);
  REP(i, N) scanf("%d", h + i);
  Tree tree;
  REP(i, N - 1) {
    int v;
    scanf("%d", &v); v--;
    tree.E.push_back(make_pair(v, i + 1));
  }

  REP(i, N) tree.V.push_back(i);
  solve(tree);

  printf("%lld\n", best);

  return 0;
}
