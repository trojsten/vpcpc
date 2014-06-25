/*
Task: Investigation
Author: Michal "Mimino" Danilak
Complexity: O(N)
*/
#include <vector>
#include <algorithm>
using namespace std;

const int MAX = 100000;
int N, n;
vector<int> graph[MAX];
int label[MAX];

int dfs(int node)
{
	label[node] = -1;
	int used = 0, more = 0;
	for (int i = 0; i < graph[node].size(); ++i)
	{
		int next = graph[node][i];
		if (!label[next])
		{
			int next_used = dfs(next);
			more |= used & next_used;
			used |= next_used;
		}
	}

	// find nearest biggest power of 2
	more |= more >> 1;
	more |= more >> 2;
	more |= more >> 4;
	more |= more >> 8;
	more |= more >> 16;
	++more;

	int possible = (~used) & (-more);
	label[node] = possible & (-possible);

	used |= label[node];
	used &= -label[node];
	return used;
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
	// label vertices with powers of 2
	dfs(0);
	// find the biggest label we have used and output log_2(label)+1
	int maximum = *max_element(label, label+N), result = 0;
	while (maximum)
	{
		++result;
		maximum >>= 1;
	}
	printf("%d\n", result);

	return 0;
}
