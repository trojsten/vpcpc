/*
Task: Investigation
Author: Michal "Mimino" Danilak
Complexity: O(N*2^N)
*/
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

const int MAX = 100000;
int N, n;
vector<int> graph[MAX];

inline int two(int n) { return 1<<n; }

int dfs(int node, int active)
{
	int result = two(node);
	for (int i = 0; i < graph[node].size(); ++i)
	{
		int next = graph[node][i];
		if (active&two(next))
			result |= dfs(next, active^two(node));
	}
	return result;
}

map<int, int> dp;
int solve(int active)
{
	if (!active)
		return 0;
	map<int, int>::iterator iter = dp.find(active);
	if (iter != dp.end())
		return iter->second;

	int result = 1000000000;
	for (int i = 0; i < N; ++i)
		if (active&two(i))
		{
			int act = 0;
			for (int j = 0; j < graph[i].size(); ++j)
			{
				int next = graph[i][j];
				if (active&two(next))
					act = max(act, solve(dfs(next, active^two(i))));
			}
			result = min(result, act+1);
		}
	return dp[active] = result;
}

int main()
{
	scanf("%d", &N);
	for (int i = 1; i < N; ++i)
	{
		scanf("%d", &n);
		graph[i].push_back(n);
		graph[n].push_back(i);
	}
	printf("%d\n", solve(two(N)-1));
}
