#include <iostream>
#include <sstream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <cctype>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <algorithm>
#include <functional>
using namespace std; 

#define DEBUG(x) cout << '>' << #x << ':' << x << endl;
#define REP(i,n) for(int i=0;i<(n);i++)
#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define FORD(i,a,b) for(int i=(a);i>=(b);i--)
inline bool EQ(double a, double b) { return fabs(a-b) < 1e-9; }

const int INF = 1000000000;
typedef long long ll;

inline int two(int n) { return 1 << n; }
inline int test(int n, int b) { return (n>>b)&1; }
inline void set_bit(int & n, int b) { n |= two(b); }
inline void unset_bit(int & n, int b) { n &= ~two(b); }
inline int last_bit(int n) { return n & (-n); }
inline int ones(int n) { int res = 0; while(n && ++res) n-=n&(-n); return res; }

template<class T> void chmax(T & a, const T & b) { a = max(a, b); }
template<class T> void chmin(T & a, const T & b) { a = min(a, b); }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

class MincostMaxFlow
{
private:

	struct Edge
	{
		Edge(int s, int d, int cap, int cos): source(s), dest(d), residue(cap), cost(cos) { }
		int source, dest, residue, cost;
	};

	int N;
	vector<vector<int> > graph;
	vector<Edge> edges;

public:

	void Init(int n)
	{
		Clear();
		N = n;
		graph.resize(N);
	}

	void AddEdge(int source, int dest, int cap, int cos)
	{
		if (source >= N || dest >= N) { N = max(source,dest)+1; graph.resize(N); }
		graph[source].push_back(edges.size());
		graph[dest].push_back(edges.size()+1);
		edges.push_back(Edge(source, dest, cap, cos));
		edges.push_back(Edge(dest, source, 0, -cos));
	}

	void Clear() { N = 0; graph.clear(); edges.clear(); }

	// <flow_size, flow_cost>
	pair<int, int> Flow(int source, int dest)
	{
		int resFlow = 0, resCost = 0;
		vector<int> pot(N, INF);
		pot[source] = 0;

		for (int step = 0; step < N; ++step)
			for (int i = 0; i < edges.size(); ++i)
			{
				Edge & e = edges[i];
				if (e.residue > 0)
					pot[e.dest] = min(pot[e.dest], pot[e.source] + e.cost);
			}

		while (1)
		{
			vector<int> prev(N, -1), best(N, INF);
			prev[source] = -2;
			best[source] = 0;

			priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > manage;
			manage.push(make_pair(0, source));

			while (!manage.empty())
			{
				int node = manage.top().second, act = manage.top().first;
				manage.pop();
				if (best[node] < act) continue;

				for (int i = 0; i < graph[node].size(); ++i)
				{
					Edge & e = edges[graph[node][i]];
					int cost = best[node] + pot[node] - pot[e.dest] + e.cost;
					if (e.residue > 0 && cost < best[e.dest])
					{
						best[e.dest] = cost;
						prev[e.dest] = graph[node][i];
						manage.push(make_pair(best[e.dest], e.dest));
					}
				}
			}
			if (prev[dest] == -1) break;

			for (int i = 0; i < N; ++i)
			{
				if (best[i] == INF) pot[i] = INF;
				else if (pot[i] < INF) pot[i] += best[i];
			}

			int fl = INF, node = dest;
			while (prev[node] != -2)
			{
				fl = min(fl, edges[prev[node]].residue);
				node = edges[prev[node]].source;
			}

			node = dest;
			while (prev[node] != -2)
			{
				edges[prev[node]].residue -= fl;
				edges[prev[node]^1].residue += fl;
				resCost += fl * edges[prev[node]].cost;
				node = edges[prev[node]].source;
			}
			resFlow += fl;
		}

		return make_pair(resFlow, resCost);
	}
};

int main()
{
	int N, M, B, E, H;
	scanf("%d%d%d%d%d", &N, &M, &B, &E, &H);
	--B, --E, --H;

	MincostMaxFlow mcmf;
	int source = 2*N, sink=source+1;
	mcmf.Init(sink+1);
	REP(i, N)
		mcmf.AddEdge(2*i, 2*i+1, 1, 0);
	mcmf.AddEdge(2*E, 2*E+1, 1, 0);
	mcmf.AddEdge(source, 2*E, 2, 0);
	mcmf.AddEdge(2*B+1, sink, 1, 0);
	mcmf.AddEdge(2*H+1, sink, 1, 0);
	REP(i, M)
	{
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		--a, --b;
		mcmf.AddEdge(2*a+1, 2*b, 1, c);
		mcmf.AddEdge(2*b+1, 2*a, 1, c);
	}
	pair<int, int> flow = mcmf.Flow(source, sink);
	if (flow.first != 2)
		printf("-1\n");
	else
		printf("%d\n", flow.second);

	return 0;
}