#include <iostream>
#include <fstream>
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
#include <ctime>
using namespace std; 

#define DEBUG(x) cerr << '>' << #x << ':' << x << endl;
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

struct Point
{
	Point() {}
	Point(int _x, int _y): x(_x), y(_y) {}

	int x, y;
	Point operator-(const Point & p) const { return Point(x-p.x, y-p.y); }
};

inline ll cross_product(const Point & v1, const Point & v2) 
	{ return (ll)v1.x * v2.y - (ll)v1.y * v2.x; }

inline ll direction(const Point & segment1, const Point & segment2, const Point & point) 
	{ return cross_product(point - segment1, segment2 - segment1); }

bool compx(Point p1, Point p2) { return p1.x < p2.x; }

void trans1(vector<Point> & points)
{
}

void itrans1(vector<Point> & points)
{
}

void trans2(vector<Point> & points)
{
	REP(i, points.size()) { swap(points[i].x, points[i].y); points[i].y = -points[i].y; }
}

void itrans2(vector<Point> & points)
{
	REP(i, points.size()) { points[i].y = -points[i].y; swap(points[i].x, points[i].y); }
}

void trans3(vector<Point> & points)
{
	REP(i, points.size())
	{
		int x = points[i].x, y = points[i].y;
		points[i].x = x + y;
		points[i].y = y - x;
	}
}

void itrans3(vector<Point> & points)
{
	REP(i, points.size())
	{
		int x = points[i].x, y = points[i].y;
		points[i].x = (x - y) / 2;
		points[i].y = (x + y) / 2;
	}
}

void trans4(vector<Point> & points)
{
	trans3(points);
	trans2(points);
}

void itrans4(vector<Point> & points)
{
	itrans2(points);
	itrans3(points);
}

typedef void transf(vector<Point> & points);

transf * forw[] = {trans1, trans2, trans3, trans4},
	* back[] = {itrans1, itrans2, itrans3, itrans4};

bool check(vector<Point> & points, int n, vector<pair<Point, Point> > & result)
{
	if (points.size() < 2) return true;
	if (n == result.size())
		return false;
	vector<Point> points1, points2;
	REP(i, points.size())
		if (direction(result[n].first, result[n].second, points[i]) >= 0)
			points1.push_back(points[i]);
		else
			points2.push_back(points[i]);
	return check(points1, n+1, result) && check(points2, n+1, result);
}

void find_lines(vector<Point> & points, vector<pair<Point, Point> > & lines)
{
	REP(i, 4)
	{
		forw[i](points);
		sort(points.begin(), points.end(), compx);
		int x = points[points.size()/2].x;
		vector<Point> line;
		line.push_back(Point(x, x%2));
		line.push_back(Point(x, x%2+2));
		back[i](line);
		bool ok = true;
		REP(j, lines.size())
			if (!direction(lines[j].first, lines[j].second, line[0]) &&
				!direction(lines[j].first, lines[j].second, line[1]))
			{
				ok = false;
				break;
			}
		if (ok)
			lines.push_back(make_pair(line[0], line[1]));
		back[i](points);
	}
}

void apply(list<vector<Point> > & groups, pair<Point, Point> line)
{
	for (list<vector<Point> >::iterator iter = groups.begin(); iter != groups.end(); )
	{
		vector<Point> & group = *iter;
		vector<Point> v1, v2;
		REP(j, group.size())
			if (direction(line.first, line.second, group[j]) >= 0) v1.push_back(group[j]);
			else v2.push_back(group[j]);
		if (v1.size() < v2.size()) v1.swap(v2);
		if (v1.size() < 2)
			iter = groups.erase(iter);
		else
		{
			v1.swap(*iter);
			if (v2.size() >= 2) groups.push_back(v2);
			++iter;
		}
	}
}

void solve(list<vector<Point> > & groups, vector<pair<Point, Point> > & result)
{
	while (groups.size())
	{
		vector<pair<Point, Point> > lines;
		for (list<vector<Point> >::iterator iter = groups.begin(); iter != groups.end(); ++iter)
			find_lines(*iter, lines);
		random_shuffle(lines.begin(), lines.end());
		int best_val = 0, best;
		REP(i, lines.size())
		{
			int act_val = 0;
			for (list<vector<Point> >::iterator iter = groups.begin(); iter != groups.end(); ++iter)
			{
				vector<Point> & group = *iter;
				int a = 0, b = 0;
				REP(j, group.size())
					if (direction(lines[i].first, lines[i].second, group[j]) >= 0) ++a;
					else ++b;
				act_val += min(a, b);
			}

			if (act_val > best_val)
			{
				best_val = act_val;
				best = i;
			}
		}

		result.push_back(lines[best]);
		apply(groups, lines[best]);
	}
}

void normalize(vector<Point> & points, vector<pair<Point, Point> > & result)
{
	REP(i, result.size())
	{
		pair<Point, Point> temp = result[i];
		swap(result[i], result.back());
		result.pop_back();
		if (!check(points, 0, result))
		{
			result.push_back(temp);
			swap(result[i], result.back());
		}
		else
			--i;
	}
}

string tc = "7";
const int KOSTKA = 20;
const int POKUSU = 2;
const int MUTACE = 200;

void modify(vector<Point> & points, vector<pair<Point, Point> > & result)
{
	list<vector<Point> > groups, old_groups;
	groups.push_back(points);
	vector<pair<Point, Point> > old, best = result;
	old.swap(result);
	REP(i, old.size())
		if (rand() % KOSTKA)
		{
			result.push_back(old[i]);
			apply(groups, old[i]);
		}
  old_groups = groups;
  REP(i, POKUSU) {
	  solve(groups, result);
    if(best.size() > result.size()) best = result;
    groups = old_groups;
  }
  result = best;

	//normalize(points, result);

	if (result.size() > old.size() && rand() % MUTACE)
		result = old;
}

#define FROM_FILE
#ifdef FROM_FILE
ifstream fin((tc + ".in").c_str());
#else
istream & fin = cin;
#endif

void save(vector<pair<Point, Point> > & result)
{
#ifdef FROM_FILE
	ofstream fout(("B" + tc + ".out").c_str());
	cout << "New record: " << result.size() << endl;
	REP(i, result.size())
		fout << result[i].first.x << " " << result[i].first.y << " " << result[i].second.x << " " << result[i].second.y << endl;
	fout.close();
#else
	cout << "New record: " << result.size() << endl;
	REP(i, result.size())
		cout << result[i].first.x << " " << result[i].first.y << " " << result[i].second.x << " " << result[i].second.y << endl;
#endif
}

int main()
{
	cout << "Running tc " << tc << endl;
	srand(time(NULL));

	int N;
	fin >> N;
	vector<Point> points, backup;
	REP(i, N)
	{
		Point p;
		fin >> p.x >> p.y;
		points.push_back(p);
	}
	backup = points;
	
	int best = INF;
#ifdef FROM_FILE
	ifstream fin2(("B" + tc + ".out").c_str());
	best = 0;
	string line;
	while (getline(fin2, line))
		++best;
	fin2.close();
	cout << "Current best is " << best << endl;
#endif

	vector<pair<Point, Point> > result;
	list<vector<Point> > groups;
	groups.push_back(points);
	solve(groups, result);
	normalize(points, result);
	while (true)
	{	
		modify(points, result);	
		if (!check(points, 0, result))
		{
			DEBUG("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
			return 0;
		}

		cout << "Found: " << result.size() << endl;
		//cout << ".";
		if (result.size() < best)
		{
			best = result.size();
			save(result);
		}
	}

	return 0;
}
