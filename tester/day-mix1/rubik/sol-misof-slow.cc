#include <cassert>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> outb = { 0, 3, 6, 9, 21, 33, 45, 48, 51, 54 };

vector< vector<int> > clockwise = {
{
    6,  3,  0,
    7,  4,  1,
    8,  5,  2,
   12, 13, 14, 15, 16, 17, 18, 19, 20,  9, 10, 11, 
   21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32,
   33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44,
   45, 46, 47,
   48, 49, 50,
   51, 52, 53,
},
{
    0,  1,  2,
    3,  4,  5,
   44, 32, 20,
   33, 21,  9,  6, 13, 14, 15, 16, 17, 18, 19, 45,
   34, 22, 10,  7, 25, 26, 27, 28, 29, 30, 31, 46,
   35, 23, 11,  8, 37, 38, 39, 40, 41, 42, 43, 47,
   36, 24, 12,
   48, 49, 50,
   51, 52, 53,
},
{
    0,  1, 11,
    3,  4, 23,
    6,  7, 35,
    9, 10, 47, 36, 24, 12,  8, 16, 17, 18, 19, 20,
   21, 22, 50, 37, 25, 13,  5, 28, 29, 30, 31, 32,
   33, 34, 53, 38, 26, 14,  2, 40, 41, 42, 43, 44,
   45, 46, 39,
   48, 49, 27,
   51, 52, 15,
},
{
   14, 26, 38,
    3,  4,  5,
    6,  7,  8,
    9, 10, 11, 12, 13, 53, 39, 27, 15,  2, 19, 20,
   21, 22, 23, 24, 25, 52, 40, 28, 16,  1, 31, 32,
   33, 34, 35, 36, 37, 51, 41, 29, 17,  0, 43, 44,
   45, 46, 47,
   48, 49, 50,
   18, 30, 42,
},
{
   41,  1,  2,
   29,  4,  5,
   17,  7,  8,
    0, 10, 11, 12, 13, 14, 15, 16, 51, 42, 30, 18,
    3, 22, 23, 24, 25, 26, 27, 28, 48, 43, 31, 19,
    6, 34, 35, 36, 37, 38, 39, 40, 45, 44, 32, 20,
    9, 46, 47,
   21, 49, 50,
   33, 52, 53,
},
{
    0,  1,  2,
    3,  4,  5,
    6,  7,  8,
    9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
   21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32,
   42, 43, 44, 33, 34, 35, 36, 37, 38, 39, 40, 41, 
   51, 48, 45,
   52, 49, 46,
   53, 50, 47,
},
};

vector< vector<int> > counterclockwise;

void invert() {
    counterclockwise.resize(6);
    for (int a=0; a<6; ++a) {
        counterclockwise[a].resize(54);
        for (int b=0; b<54; ++b) counterclockwise[a][ clockwise[a][b] ] = b;
    }
}

void sanity_check() {
    for (int a=0; a<6; ++a)
        for (int b=0; b<54; ++b) {
            assert( clockwise[a][b] >= 0 );
            assert( clockwise[a][b] < 54 );
            for (int c=0; c<b; ++c) assert( clockwise[a][b] != clockwise[a][c] );
            assert( counterclockwise[a][ clockwise[a][b] ] == b );
            assert( clockwise[a][ counterclockwise[a][b] ] == b );
        }
}

string execute(const string &initial, const string &instructions, const vector<bool> &directions) {
    int L = instructions.size();
    string curr = initial;
    for (int i=0; i<L; ++i) {
        string nxt(54,'.');
        if (directions[i]) {
            // clockwise
            for (int j=0; j<54; ++j) nxt[j] = curr[ clockwise[ instructions[i]-'A' ][j] ];
        } else {
            for (int j=0; j<54; ++j) nxt[j] = curr[ counterclockwise[ instructions[i]-'A' ][j] ];
        }
        curr = nxt;
    }
    return curr;
}

int main() {
    invert();
    sanity_check();
    string initial;
    for (int i=0; i<9; ++i) { string tmp; cin >> tmp; initial += tmp; }
    
    string instructions;
    vector<bool> directions;
    int N, M;
    cin >> N >> M;
    for (int n=0; n<N; ++n) { string ins; int dir; cin >> ins >> dir; instructions += ins; directions.push_back(dir==-1); }

    while (M--) {
        string ins; int idx, dir;
        cin >> idx >> ins >> dir;
        instructions[idx-1] = ins[0];
        directions[idx-1] = (dir==-1);
        string result = execute( initial, instructions, directions );
        for (int i=0; i<9; ++i) cout << string( result.begin()+outb[i], result.begin()+outb[i+1] ) << "\n";
    }
}
