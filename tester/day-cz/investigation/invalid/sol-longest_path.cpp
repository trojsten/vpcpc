/*
Task: Investigation
Author: Michal "Mimino" Danilak
Solution (wrong):
	- find the longest path in the tree and output log(path_length)+1
Complexity: O(N)

Challenge case:
Input:
	8
	0 0 0 3 3 4 2
Expected: 4
Returned: 3
*/
#include <vector>
#include <algorithm>
using namespace std;

const int MAX = 100000;
int N, n;
vector<int> graph[MAX];

pair<int, int> longest_path(int node, int parent)
{
	int res1 = 0, res2 = 0;
	for (int i = 0; i < graph[node].size(); ++i)
	{
		int next = graph[node][i];
		if (next != parent)
		{
			pair<int, int> temp = longest_path(next, node);
			res2 = max(res2, max(temp.second, res1+temp.first));
			res1 = max(res1, temp.first);
		}
	}
	return make_pair(res1+1, res2);
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

	int path = longest_path(0, -1).second+1, answer = 0;
	while (path)
	{
		++answer;
		path >>= 1;
	}
	printf("%d\n", answer);
}
