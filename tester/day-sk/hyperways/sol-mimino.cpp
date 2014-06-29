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

const int INF = 1<<29;
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

const int MAX = 1000000;
int N, M;
map<int, int> graph[MAX];

int dfsc, visited[MAX], back[MAX];
int last_answer, cur_answer;

int dfs(int node, int parent)
{
	visited[node] = back[node] = ++dfsc;
	for (map<int, int>::iterator iter = graph[node].begin(); iter != graph[node].end(); ++iter)
	{
		int next = iter->first;
		if (next == parent) continue;
		if (visited[next])
			back[node] = min(back[node], visited[next]);
		else
		{
			back[node] = min(back[node], dfs(next, node));
			if (back[next] > visited[node] && iter->second == 1)
			{
				++cur_answer;
				//cerr << "Most: " << next+1 << " " << node+1 << endl;
			}
		}
	}
	return back[node];
}

int main()
{
	scanf("%d%d", &N, &M);
	
	REP(step, M)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		--a, --b;
		if (a == b)
		{
			printf("1\n");
			continue;
		}
		graph[a][b] += 1;
		graph[b][a] += 1;

		dfsc = 0;
		REP(i, N) visited[i] = back[i] = 0;
		last_answer += 1;
		cur_answer = 0;
		REP(i, N)
			if (!visited[i])
				dfs(i, -1);
		printf("%d\n", last_answer-cur_answer);
		//DEBUG(cur_answer)
		last_answer = cur_answer;
	}

	return 0;
}