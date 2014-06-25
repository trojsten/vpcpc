/*
Task: Investigation
Author: Michal "Mimino" Danilak
Solution (wrong):
	- keep track of the nodes in the still active subtree
	- always ask on the node which minimizes the maximum path length of its subtrees
	- randomly iterate a couple of times and return the best answer
Complexity: O(N^2)

Challenge case:
Input:
	16
	0 1 2 0 2 3 6 0 0 3 9 10 1 12 7
Expected: 4
Returned: 5

Input:
  22
  0 1 1 0 1 3 0 7 0 7 5 0 7 4 2 1 15 11 3 11 13
Expected: 4
Returned: 5
*/
#include <vector>
#include <algorithm>
using namespace std;

const int MAX = 100000;
int N, n;
vector<int> graph[MAX];
bool used[MAX];

pair<int, int> count(int node, int parent)
{
	int res1 = 0, res2 = 0;
	for (int i = 0; i < graph[node].size(); ++i)
	{
		int next = graph[node][i];
		if (next != parent && !used[next])
		{
			pair<int, int> temp = count(next, node);
			res2 = max(res2, max(temp.second, res1+temp.first));
			res1 = max(res1, temp.first);
		}
	}
	return make_pair(res1+1, res2);
}

void collect(vector<int> & active, int node, int parent)
{
	active.push_back(node);
	for (int i = 0; i < graph[node].size(); ++i)
	{
		int next = graph[node][i];
		if (next != parent && !used[next])
			collect(active, next, node);
	}
}

int solve(vector<int> & active)
{
	if (active.size() == 0)
		return 0;
	if (active.size() == 1)
		return 1;

	vector<int> best_nodes;
	int best_sz = 1000000000;
	for (int i = 0; i < active.size(); ++i)
	{
		int node = active[i], sz = 0;
		for (int j = 0; j < graph[node].size(); ++j)
		{
			int next = graph[node][j];
			if (!used[next])
				sz = max(sz, count(next, node).second);
		}
		if (sz < best_sz)
		{
			best_nodes.clear();
			best_sz = sz;
		}
		if (sz == best_sz)
			best_nodes.push_back(node);
	}
	int result = 0, node = best_nodes[rand() % best_nodes.size()];
	used[node] = true;
	for (int i = 0; i < graph[node].size(); ++i)
	{
		int next = graph[node][i];
		if (!used[next])
		{
			vector<int> new_active;
			collect(new_active, next, node);
			result = max(result, solve(new_active));
		}
	}
	return result + 1;
}

int solve()
{
	vector<int> active;
	for (int i = 0; i < N; ++i)
	{
		used[i] = false;
		active.push_back(i);
	}
	return solve(active);
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

	int answer = 1000000000;
	for (int i = 0; i < 100; ++i)
		answer = min(answer, solve());
	printf("%d\n", answer);
}
