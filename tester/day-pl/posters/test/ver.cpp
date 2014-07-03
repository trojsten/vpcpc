/* Weryfikator danych wejsciowych do zadania Posters
 * Autor: Marek Sommer
 */
#include <algorithm>
#include <vector>
#include <cstdio>
#include <string>
#include <set>
#include <utility>
#include "oi.h"

using namespace std;

int min_hanged = 1;
int max_hanged = 100 * 1000;
int min_new = 1;
int max_new = 100 * 1000;

int min_wsp = 0;
int max_wsp = 1000 * 1000 * 1000;

int mn = max_wsp, mx = min_wsp;

void wczytaj_poster(oi::Scanner &in)
{
	int x1, y1, x2, y2;
	x1 = in.readInt(min_wsp, max_wsp);
	in.readSpace();
	y1 = in.readInt(min_wsp, max_wsp);
	in.readSpace();
	x2 = in.readInt(min_wsp, max_wsp);
	in.readSpace();
	y2 = in.readInt(min_wsp, max_wsp);
	in.readEoln();
	mn = min(mn, min(x1, y1));
	mx = max(mx, max(x2, y2));
	if(x2 <= x1)
		in.error("x2 <= x1\n");
	if(y2 <= y1)
		in.error("y2 <= y1\n");
}

int main()
{
  oi::Scanner in(stdin, oi::PL);
  int n = in.readInt(min_hanged, max_hanged);
  in.readEoln();
	for(int i = 0; i < n; i++)
		wczytaj_poster(in);
	int m = in.readInt(min_new, max_new);
	in.readEoln();
	for(int i = 0; i < m; i++)
		wczytaj_poster(in);
	printf("OK, n = %6d, m = %6d, mn = %10d, mx = %10d", n, m, mn, mx);
	if(n <= 10 && m <= 10)
		printf(" | n, m <= 10    ");
	else if(n <= 50 && m <= 50)
		printf(" | n, m <= 50    ");
	else if(n <= 400 && m <= 400)
		printf(" | n, m <= 400   ");
	else if(n <= 1000 && m <= 1000)
		printf(" | n, m <= 1000  ");
	else if(n <= 10000 && m <= 10000)
		printf(" | n, m <= 10000 ");
	else if(n <= 100000 && m <= 100000)
		printf(" | n, m <= 100000");
	else
		printf(" | :(            ");
	if(mx <= 100)
		printf(" | wsp <= 100       ");
	else if(mx <= 30 * 1000)
		printf(" | wsp <= 30000     ");
	else if(mx <= 1000 * 1000 * 1000)
		printf(" | wsp <= 1000000000");
	else
		printf(" | :/               ");
	printf("\n");
  return 0;
}
