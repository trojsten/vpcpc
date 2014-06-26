/*
Task: Universities
Author: Michal "Mimino" Danilak
Complexity: O(N^2)
*/
#include <vector>
#include <algorithm>
using namespace std;

const int MAX = 100000;
const long long INF = 1000000000000;
int N, happy[MAX];
long long result = -INF;
char color[MAX+1];
vector<int> graph[MAX];

void dfs(int node, int parent, int balance, long long happy_sum)
{
	happy_sum += happy[node];
	balance += (color[node] == 'B' ? 1 : -1);
	if (!balance)
		result = max(result, happy_sum);
	for (int i = 0; i < graph[node].size(); ++i)
	{
		int next = graph[node][i];
		if (next != parent)
			dfs(next, node, balance, happy_sum);
	}
}

int main()
{
	scanf("%d%s", &N, color);
	for (int i = 0; i < N; ++i)
		scanf("%d", happy+i);
	for (int i = 1; i < N; ++i)
	{
		int n;
		scanf("%d", &n);
		graph[i].push_back(n-1);
		graph[n-1].push_back(i);
	}
	for (int i = 0; i < N; ++i)
		dfs(i, -1, 0, 0);
	printf("%lld\n", result);

	return 0;
}
