/*
Task: Universities
Author: Michal "Mimino" Danilak
Complexity: O(N*log(N))
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
int label[MAX];

int label_tree(int node)
{
	label[node] = -1;
	int used = 0, more = 0;
	for (int i = 0; i < graph[node].size(); ++i)
	{
		int next = graph[node][i];
		if (!label[next])
		{
			int next_used = label_tree(next);
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

long long _best_happy_sum[2*MAX], * best_happy_sum = _best_happy_sum + MAX;
int min_balance, max_balance;

void update(int balance, long long happy_sum)
{
	if (min_balance <= balance && balance <= max_balance)
		best_happy_sum[balance] = max(best_happy_sum[balance], happy_sum);
	else
	{
		best_happy_sum[balance] = happy_sum;
		min_balance = min(min_balance, balance);
		max_balance = max(max_balance, balance);
	}
}

void discover(int node, int parent, int root_label, int balance, long long happy_sum)
{
	balance += (color[node] == 'B' ? -1 : 1);
	happy_sum += happy[node];
	update(balance, happy_sum);
	for (int i = 0; i < graph[node].size(); ++i)
	{
		int next = graph[node][i];
		if (next != parent && label[next] < root_label)
			discover(next, node, root_label, balance, happy_sum);
	}
}

long long _gbest_happy_sum[2*MAX], * gbest_happy_sum = _gbest_happy_sum + MAX;
int gmin_balance, gmax_balance;

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
	label_tree(0);

	for (int node = 0; node < N; ++node)
	{
		gmin_balance = gmax_balance = 0;
		gbest_happy_sum[0] = -INF;

		int balance = (color[node] == 'B' ? -1 : 1);
		for (int i = 0; i < graph[node].size(); ++i)
		{
			int next = graph[node][i];
			if (label[next] < label[node])
			{
				min_balance = max_balance = 0;
				best_happy_sum[0] = -INF;
				update(balance, happy[node]);
				discover(next, node, label[node], balance, happy[node]);

				result = max(result, best_happy_sum[0]);
				for (int j = min_balance; j <= max_balance; ++j)
				{
					int k = balance-j;
					if (gmin_balance <= k && k <= gmax_balance)
						result = max(result, best_happy_sum[j] + gbest_happy_sum[k] - happy[node]);
				}

				for (int j = min_balance; j <= max_balance; ++j)
				{
					if (gmin_balance <= j && j <= gmax_balance)
						gbest_happy_sum[j] = max(gbest_happy_sum[j], best_happy_sum[j]);
					else
						gbest_happy_sum[j] = best_happy_sum[j];
				}
				gmin_balance = min(gmin_balance, min_balance);
				gmax_balance = max(gmax_balance, max_balance);
			}
		}
	}
	printf("%lld\n", result);

	return 0;
}
