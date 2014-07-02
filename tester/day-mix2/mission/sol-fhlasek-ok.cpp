/* Written by Filip Hlasek 2014 */
#include <cstdio>
#include <map>
#define REP(i,b) for(int i=0;i<(b);i++)

using namespace std;

#define INF 1000000001
#define MAXN 2222
// All N vertices are splitted into two: i (input) and i + N (output)

// pair(vertex_index, Distance)
map<int, int> graph[MAXN];
int N;

int Distance[MAXN];
int ComeFrom[MAXN];

int BellmanFord(int start, int goal) {
  REP(i, N) { Distance[i] = INF; ComeFrom[i] = -1; }
  Distance[start] = 0;
  REP(step, N + 1) {
    REP(i, N)
      for (map<int, int>::iterator it = graph[i].begin(); it != graph[i].end(); ++it) {
        if (Distance[it->first] > Distance[i] + it->second) {
          ComeFrom[it->first] = i;
          Distance[it->first] = Distance[i] + it->second;
        }
      }
  }
  for (int i = goal; ComeFrom[i] != -1; i = ComeFrom[i]) {
    int j = ComeFrom[i];
    int t = graph[j][i];
    graph[j].erase(graph[j].find(i));
    graph[i][j] = -t;
  }

  return Distance[goal];
}

int main(int argc, char *argv[]) {
  int M, B, E, H;
  scanf("%d%d%d%d%d", &N, &M, &B, &E, &H); B--; E--; H--;
  REP(i, N) graph[i][i + N] = 0;
  REP(i, M) {
    int u, v, t;
    scanf("%d%d%d", &u, &v, &t); u--; v--;
    graph[u + N][v] = graph[v + N][u] = t;
  }
  graph[B + N][2 * N] = 0;
  graph[H + N][2 * N] = 0;

  E += N;
  N = 2 * N + 1;

  int ans1 = BellmanFord(E, N - 1);
  int ans2 = BellmanFord(E, N - 1);
  if (ans1 == INF || ans2 == INF) printf("-1\n");
  else printf("%d\n", ans1 + ans2);

  return 0;
}
