/* Generator danych wejsciowych do zadania Posters
   Autor: Marek Sommer
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <cstring>
#include <cstdio>
#include <set>
#include <cmath>

#include "oi.h"

using namespace std;

typedef long long int ll;
typedef long double ld;

// HINT: Uzywamy liczb losowych wylacznie z pakietu oi.h
oi::Random RG(0xC0FFEE);

inline ll rand_range(ll a,ll b) { return (RG.randSLL()%(b-a+1))+a; }
inline int rand_range(int a,int b) { return (RG.rand()%(b-a+1))+a; }
int rand_range_without(int a,int b,int c) { if(a==b && b==c) printf("rand_rang_without(%d,%d,%d)\n",a,b,c); while(true) { int x = rand_range(a,b); if(x != c) return x; } }
inline int rand_bool() { return rand_range(0,1); }

class Prostokat
{
public:
	int x1, y1, x2, y2;

	Prostokat(int x1, int y1, int x2, int y2) : x1(x1), y1(y1), x2(x2), y2(y2) {}
	friend ostream& operator << (ostream &out, const Prostokat &prostokat)
	{
		out << prostokat.x1 << " " << prostokat.y1 << " " << prostokat.x2 << " " << prostokat.y2;
		return out;
	}
	Prostokat outer() const
	{
		return Prostokat(x1 - 1, y1 - 1, x2 + 1, y2 + 1);
	}
	static Prostokat losowy(int min_wsp, int max_wsp)
	{
		int x1 = rand_range(min_wsp, max_wsp);
		int x2 = x1; while(x2 == x1)
			x2 = rand_range(min_wsp, max_wsp);;
		int y1 = rand_range(min_wsp, max_wsp);
		int y2 = y1;
		while(y2 == y1)
			y2 = rand_range(min_wsp, max_wsp);;
		return Prostokat(min(x1, x2), min(y1, y2), max(x1, x2), max(y1, y2));
	}
};

class TestCase
{
public:
	friend ostream& operator << (ostream& out, const TestCase& testCase)
	{
		out << testCase.hanged.size() << "\n";
		for(Prostokat p : testCase.hanged)
			out << p << "\n";
		out << testCase.newp.size() << "\n";
		for(Prostokat p : testCase.newp)
			out << p << "\n";
    return out;
	}
	const vector<Prostokat> &getHanged() const { return hanged; }
	const vector<Prostokat> &getNewp() const { return newp; }

protected:
	TestCase() {}
	vector<Prostokat> hanged, newp;
};

class SpecialCase1 : public TestCase
{
public:
	SpecialCase1()
	{
		hanged.push_back(Prostokat(0, 0, 5, 4));
		newp.push_back(Prostokat(0, 0, 5, 4));
	}
};

class SpecialCase2 : public TestCase
{
public:
	SpecialCase2()
	{
		hanged.push_back(Prostokat(1, 1, 2, 2));
		for(int i = 0; i <= 2; i++)
			for(int j = 0; j <= 2; j++)
				if(i != 1 || j != 1)
					newp.push_back(Prostokat(i, j, i + 1, j + 1));
	}
};

class RandomCase : public TestCase
{
public:
	RandomCase(int n, int m, int min_wsp, int max_wsp)
	{
		for(int i = 0; i < n; i++)
			hanged.push_back(Prostokat::losowy(min_wsp, max_wsp));
		for(int i = 0; i < m; i++)
			newp.push_back(Prostokat::losowy(min_wsp, max_wsp));
	}
};

class PaskiCase : public TestCase
{
public:
	PaskiCase(int n, int m, int min_wsp, int max_wsp)
	{
		for(int i = 0; i < n; i++)
		{
			int y = rand_range(min_wsp, max_wsp - 2);
			hanged.push_back(Prostokat(min_wsp, y, max_wsp, y + rand_range(1, 2)));
		}
		for(int i = 0; i < m; i++)
		{
			int x = rand_range(min_wsp, max_wsp - 2);
			newp.push_back(Prostokat(x, min_wsp, x + rand_range(1, 2), max_wsp));
		}
	}
};

class InnerRandomCase : public TestCase
{
public:
	InnerRandomCase(int n, int min_wsp, int max_wsp)
	{
		for(int i = 0; i < n; i++)
		{
			Prostokat p = Prostokat::losowy(min_wsp + 2, max_wsp - 2);
			newp.push_back(p);
			hanged.push_back(p.outer());
			newp.push_back(p.outer().outer());
		}
	}
};

class DolosujCase : public TestCase
{
public:
	DolosujCase(const TestCase &testCase, int ile, int min_wsp, int max_wsp, int typ = 0)
	{
		hanged = testCase.getHanged();
		newp = testCase.getNewp();
		if(typ <= 0)
		{
			for(int i = 0; i < ile; i++)
				hanged.push_back(Prostokat::losowy(min_wsp, max_wsp));
		}
		if(typ >= 0)
		{
			for(int i = 0; i < ile; i++)
				newp.push_back(Prostokat::losowy(min_wsp, max_wsp));
		}
	}
};

class RamkaCase : public TestCase
{
public:
	RamkaCase(const TestCase &testCase)
	{
		hanged = testCase.getHanged();
		newp = testCase.getNewp();
		int mnx = 1000 * 1000 * 1000, mxx = 0;
		int mny = mnx, mxy = mxx;
		for(Prostokat p : hanged)
		{
			mnx = min(mnx, p.x1); mxx = max(mxx, p.x2);
			mny = min(mny, p.y1); mxy = max(mxy, p.y2);
		}
		for(Prostokat p : newp)
		{
			mnx = min(mnx, p.x1); mxx = max(mxx, p.x2);
			mny = min(mny, p.y1); mxy = max(mxy, p.y2);
		}
		newp.push_back(Prostokat(mnx, mny, mxx, mxy));
		RG.randomShuffle(newp.begin(), newp.end());
	}
};

void write(const char* filename, const TestCase& testCase) {
  cout << "Writing " << filename << "..." << endl;
  ofstream file(filename);
  file << testCase;
  file.close();
}

void testGroup(const vector<TestCase>& cases) {
  static int test_no = 0;
  ++test_no;
  for (int i = 0; i < (int) cases.size(); ++i) {
    stringstream ss;
    ss << "0";
    ss << test_no;
		ss << ".";
    if (cases.size() > 1U) {
      ss << char('a' + i);
			ss << ".";
    }
    ss << "in";
    write(ss.str().c_str(), cases[i]);
  }
}

void make_sample()
{
	FILE *f = fopen("00.sample.in", "w");
	fprintf(f, "2\n0 1 3 5\n2 3 6 6\n2\n1 0 5 4\n4 2 7 7\n");
	fclose(f);
}

/*
    |   | wzorcówka | brut | brut2 | brut3 | heury (_b, _b2) +
		|   |    100p   | 12p  |  48p  |  24p  |        0p       | n, m <= ? | wsp <= ? |
----+---+-----------+------+-------+-------+-----------------+-----------+----------+
 0p | 0 |     ok    |  ok  |   ok  |   ok  |        x        |    2      |    7     |
12p | 1 |     ok    |  ok  |   ok  |   ok  |        x        |    10     |   100    |
12p | 2 |     ok    |  x   |   ok  |   ok  |        x        |    50     |   10^9   |
12p | 3 |     ok    |  x   |   ok  |   x   |        x        |   400     |   10^5   |
12p | 4 |     ok    |  x   |   ok  |   x   |        x        |   1000    |   10^9   |
13p | 5 |     ok    |  x   |   x   |   x   |        x        |   10000   |   10^5   |
13p | 6 |     ok    |  x   |   x   |   x   |        x        |   10000   |   10^9   |
13p | 7 |     ok    |  x   |   x   |   x   |        x        |  100000   |   10^5   |
13p | 8 |     ok    |  x   |   x   |   x   |        x        |  100000   |   10^9   |
*/

const int maly = 30 * 1000;

int main()
{
	make_sample();
  RG.setSeed(42);
  {
    const TestCase t[] = {
			SpecialCase1(),
			SpecialCase2(),
			RandomCase(10, 10, 0, 4), // many posters on a small wall
			RandomCase(10, 10, 0, 100), // large wall
    };
    testGroup(vector<TestCase>(t, t + sizeof(t) / sizeof(TestCase)));
  }
  RG.setSeed(142);
  {
    const TestCase t[] = {
			DolosujCase(PaskiCase(47, 47, 0, 1000 * 1000 * 1000), 3, 0, 1000 * 1000 * 1000),
			RamkaCase(DolosujCase(PaskiCase(47, 46, 0, 100), 3, 0, 1000 * 1000 * 1000)),
			RamkaCase(RandomCase(50, 49, 0, 1000 * 1000 * 1000)),
    };
    testGroup(vector<TestCase>(t, t + sizeof(t) / sizeof(TestCase)));
  }
  RG.setSeed(14241);
  {
    const TestCase t[] = {
			RamkaCase(DolosujCase(InnerRandomCase(199, 0, maly), 201, 0, maly, -1)),
			RandomCase(400, 400, 0, maly),
    };
    testGroup(vector<TestCase>(t, t + sizeof(t) / sizeof(TestCase)));
  }
  RG.setSeed(7142417);
  {
    const TestCase t[] = {
			RamkaCase(PaskiCase(1000, 999, 0, 1000 * 1000 * 1000)),
			RandomCase(512, 512, 0, 1000 * 1000 * 1000),
			RandomCase(1000, 1000, 0, 1000 * 1000 * 1000),
    };
    testGroup(vector<TestCase>(t, t + sizeof(t) / sizeof(TestCase)));
  }
  RG.setSeed(8253528);
  {
    const TestCase t[] = {
			RamkaCase(PaskiCase(10000, 9999, 0, maly)),
			RandomCase(8192, 8192, 0, maly),
			RandomCase(10000, 10000, 0, maly),
    };
    testGroup(vector<TestCase>(t, t + sizeof(t) / sizeof(TestCase)));
  }
  RG.setSeed(25352);
  {
    const TestCase t[] = {
			RamkaCase(DolosujCase(InnerRandomCase(4999, 0, 1000 * 1000 * 1000), 5001, 0, 1000 * 1000 * 1000, -1)),
			RandomCase(8192, 8192, 0, 1000 * 1000 * 1000),
			RandomCase(10000, 10000, 0, 1000 * 1000 * 1000),
    };
    testGroup(vector<TestCase>(t, t + sizeof(t) / sizeof(TestCase)));
  }
  RG.setSeed(253);
  {
    const TestCase t[] = {
			RamkaCase(DolosujCase(InnerRandomCase(49999, 0, maly), 50001, 0, maly, -1)),
			RandomCase(100000, 100000, 0, maly),
    };
    testGroup(vector<TestCase>(t, t + sizeof(t) / sizeof(TestCase)));
  }
  RG.setSeed(53);
  {
    const TestCase t[] = {
			DolosujCase(RamkaCase(PaskiCase(100000 - 100, 99999 - 100, 0, 1000 * 1000 * 1000)), 100, 0, 1000 * 1000 * 1000),
			RandomCase(100000, 100000, 0, 1000 * 1000 * 1000),
    };
    testGroup(vector<TestCase>(t, t + sizeof(t) / sizeof(TestCase)));
  }
	return 0;
}
