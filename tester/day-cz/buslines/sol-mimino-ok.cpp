#include <cstdio>
#include <vector>
using namespace std;

const int MAX = 1000000;
int N, sub[MAX];
vector<int> graph[MAX];
long long result[MAX];

void dfs(int node, int parent)
{
	sub[node] = 1;
	for (int i = 0; i < graph[node].size(); ++i)
	{
		int next = graph[node][i];
		if (next != parent)
		{
			dfs(next, node);
			result[node] += (long long)sub[node] * sub[next];
			sub[node] += sub[next];
		}
	}
	result[node] += (long long)sub[node] * (N-sub[node]);
}

int main()
{
	scanf("%d", &N);
	for (int i = 1; i < N; ++i)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		--x, --y;
		graph[x].push_back(y);
		graph[y].push_back(x);
	}
	dfs(0, -1);
	for (int i = 0; i < N; ++i)
		printf("%lld\n", result[i]);

	return 0;
}