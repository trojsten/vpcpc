#include <ctime>
#include <cstdio>
#include <vector>
#ifdef WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif
#include <algorithm>
using namespace std;

struct Timer
{
    double T; 

#ifdef WIN32
    LARGE_INTEGER t_act, t_freq;
    double get_time() { QueryPerformanceCounter(&t_act); return double(t_act.QuadPart)/t_freq.QuadPart; }
	void restart() { QueryPerformanceFrequency(&t_freq); T = get_time(); }
    Timer() { restart(); }
#else
    double get_time() { unsigned long long time; __asm__ volatile ("rdtsc" : "=A" (time)); return time / 3.6e9; }
	void restart() { T = get_time(); }
    Timer() { restart(); }
#endif
    double elapsed() { return get_time()-T; }
};

const int MAX = 100000;
long long INF = 1000000000000LL;
int N, cost[MAX];
char color[MAX+1];
vector<int> graph[MAX];
long long result = -INF;

long long _best_sum[2*MAX], * best_sum = _best_sum + MAX;
int min_balance, max_balance;

void update(int balance, long long sum)
{
	if (min_balance <= balance && balance <= max_balance)
		best_sum[balance] = max(best_sum[balance], sum);
	else
	{
		best_sum[balance] = sum;
		min_balance = min(min_balance, balance);
		max_balance = max(max_balance, balance);
	}
}

int MAX_DEPTH, depth;

void dfs(int node, int parent, int balance, long long sum)
{
	++depth;
	balance += (color[node] == 'B' ? -1 : 1);
	sum += cost[node];
	update(balance, sum);
	for (int i = 0; i < graph[node].size(); ++i)
	{
		int next = graph[node][i];
		if (next != parent && depth < MAX_DEPTH)
			dfs(next, node, balance, sum);
	}
	--depth;
}

long long _gbest_sum[2*MAX], * gbest_sum = _gbest_sum + MAX;
int gmin_balance, gmax_balance;

int main()
{
	scanf("%d", &N);
	scanf("%s", color);
	for (int i = 0; i < N; ++i)
		scanf("%d", cost+i);
	for (int i = 1; i < N; ++i)
	{
		int n;
		scanf("%d", &n);
		graph[n-1].push_back(i);
		graph[i].push_back(n-1);
	}

	vector<int> order;
	for (int i = 0; i < N; ++i)
		order.push_back(i);
	random_shuffle(order.begin(), order.end());

	Timer tim;
	MAX_DEPTH = 10;
	for (int i = 0; i < order.size(); ++i)
	{
		int node = order[i];
		gmin_balance = gmax_balance = 0;
		gbest_sum[0] = -INF;

		int balance = (color[node] == 'B' ? -1 : 1);
		for (int i = 0; i < graph[node].size(); ++i)
		{
			int next = graph[node][i];
			min_balance = max_balance = 0;
			best_sum[0] = -INF;
			update(balance, cost[node]);
			dfs(next, node, balance, cost[node]);

			result = max(result, best_sum[0]);
			for (int j = min_balance; j <= max_balance; ++j)
			{
				int k = balance-j;
				if (gmin_balance <= k && k <= gmax_balance)
					result = max(result, best_sum[j] + gbest_sum[k] - cost[node]);
			}

			for (int j = min_balance; j <= max_balance; ++j)
			{
				if (gmin_balance <= j && j <= gmax_balance)
					gbest_sum[j] = max(gbest_sum[j], best_sum[j]);
				else
					gbest_sum[j] = best_sum[j];
			}
			gmin_balance = min(gmin_balance, min_balance);
			gmax_balance = max(gmax_balance, max_balance);
		}
	}

	MAX_DEPTH = N;
	for (int i = 0; i < order.size() && tim.elapsed() < 1.0; ++i)
	{
		int node = order[i];
		gmin_balance = gmax_balance = 0;
		gbest_sum[0] = -INF;

		int balance = (color[node] == 'B' ? -1 : 1);
		for (int i = 0; i < graph[node].size(); ++i)
		{
			int next = graph[node][i];
			min_balance = max_balance = 0;
			best_sum[0] = -INF;
			update(balance, cost[node]);
			dfs(next, node, balance, cost[node]);

			result = max(result, best_sum[0]);
			for (int j = min_balance; j <= max_balance; ++j)
			{
				int k = balance-j;
				if (gmin_balance <= k && k <= gmax_balance)
					result = max(result, best_sum[j] + gbest_sum[k] - cost[node]);
			}

			for (int j = min_balance; j <= max_balance; ++j)
			{
				if (gmin_balance <= j && j <= gmax_balance)
					gbest_sum[j] = max(gbest_sum[j], best_sum[j]);
				else
					gbest_sum[j] = best_sum[j];
			}
			gmin_balance = min(gmin_balance, min_balance);
			gmax_balance = max(gmax_balance, max_balance);
		}
	}
	printf("%lld\n", result);

	return 0;
};