/* Written by Filip Hlasek 2014 */
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>

#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define FORD(i,a,b) for(int i=(a);i>=(b);i--)
#define REP(i,b) for(int i=0;i<(b);i++)

using namespace std;

#define INF 1000000001
#define MAXN 1111
int N;
vector<int> graph[MAXN], cost[MAXN];
bool visited[MAXN];

int M, U[MAXN], V[MAXN], T[MAXN];
void reset_graph() {
  REP(i, N) { graph[i].clear(); cost[i].clear(); visited[i] = false; }
  REP(i, M) {
    graph[U[i]].push_back(V[i]);
    graph[V[i]].push_back(U[i]);
    cost[U[i]].push_back(T[i]);
    cost[V[i]].push_back(T[i]);
  }
}

priority_queue<pair<int, int> > pq;
int Distance[MAXN], ComeFrom[MAXN];
void add(int v, int d, int from) {
  if (Distance[v] <= d || visited[v]) return;
  Distance[v] = d;
  pq.push(make_pair(-d, v));
  ComeFrom[v] = from;
}

// Finds the shortest path from start to end and marks all its vertices visited
int delete_way(int start, int end) {
  REP(i, N) Distance[i] = INF;
  while (!pq.empty()) pq.pop();
  add(start, 0, -1);
  while (!pq.empty()) {
    int d = -pq.top().first, v = pq.top().second; pq.pop();
    if (Distance[v] != d) continue;
    if (v == end) {
      for (int i = v; i != -1; i = ComeFrom[i]) visited[i] = true;
      return Distance[v];
    }
    REP(i, graph[v].size()) add(graph[v][i], d + cost[v][i], v);
  }
  return INF;
}

// It is looking for a way from A to B and than from B to C
// not intersecting the first way
int solve(int A, int B, int C) {
  reset_graph();
  int ans = delete_way(A, B) + delete_way(B, C);
  REP(i, N) if (i != A && i != B && i != C) {
    int edges[3][2] = {{A, i}, {i, B}, {B, C}};
    int perm[3] = {0, 1, 2};
    do {
      reset_graph();
      visited[A] = visited[B] = visited[C] = visited[i] = true;
      long long total = 0;
      REP(i, 3) {
        int a = edges[perm[i]][0], b = edges[perm[i]][1];
        visited[a] = false; visited[b] = false;
        total += delete_way(a, b);
        visited[a] = true; visited[b] = true;
      }
      ans = min((long long)ans, total);
    } while(next_permutation(perm, perm + 3));
  }
  return ans;
}

int main(int argc, char *argv[]) {
  int B, E, H;
  scanf("%d%d%d%d%d", &N, &M, &B, &E, &H); B--; E--; H--;
  REP(i, M) { scanf("%d%d%d", U + i, V + i, T + i); U[i]--; V[i]--; }
  int ans = min(solve(B, E, H), solve(H, E, B));
  if (ans >= INF) printf("-1\n");
  else printf("%d\n", ans);
  return 0;
}
