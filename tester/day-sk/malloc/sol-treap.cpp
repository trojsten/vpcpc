// {{{
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <complex>
#include <numeric>
#define REP(i, n) for (int i = 0; i < (int) (n); ++i)
#define FOR(i, a, b) for (int i = (int) (a); i <= (int) (b); ++i)
#define FORD(i, a, b) for (int i = (int) (a); i >= (int) (b); --i)
#define FORE(it, c) for (__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define SIZE(x) ((int) ((x).size()))
#define DEBUG(x) { cerr << #x << ": " << (x) << endl; }
#define SQR(x) ((x) * (x))
#define INF 1023456789
using namespace std;

template<typename T, typename U> ostream& operator << (ostream& os, const pair<T, U>& p) {
    os << "(" << p.first << "," << p.second << ")"; return os;
}

template<typename T> ostream& operator << (ostream& os, const vector<T>& v) {
    os << "["; FORE(i, v) { if (i != v.begin()) os << ", "; os << *i; } os << "]"; return os;
}

typedef long long LL;
typedef pair<int, int> PI;
typedef pair<int, PI> TRI;
typedef vector<int> VI;
typedef vector<VI> VVI;
// }}}

struct Node {
    int rank, u, v, max_segment, total;
    Node *left, *right;

    Node(int _u, int _v) : rank(rand()), u(_u), v(_v), max_segment(_v - _u), total(_v - _u), left(NULL), right(NULL) {}

    void disown_left() {
        if (left != NULL) {
            total -= left->total;
            if (right != NULL) {
                max_segment = max(v - u, right->max_segment);
            } else {
                max_segment = v - u;
            }
        }
    }

    void disown_right() {
        if (right != NULL) {
            total -= right->total;
            if (left != NULL) {
                max_segment = max(v - u, left->max_segment);
            } else {
                max_segment = v - u;
            }
        }
    }

    void accept_left(Node* son) {
        left = son;
        if (left != NULL) {
            total += left->total;
            max_segment = max(max_segment, left->max_segment);
        }
    }

    void accept_right(Node* son) {
        right = son;
        if (right != NULL) {
            total += right->total;
            max_segment = max(max_segment, right->max_segment);
        }
    }

    Node* first() {
        return (left == NULL) ? this : left->first();
    }

    Node* last() {
        return (right == NULL) ? this : right->last();
    }
};

Node* merge(Node* a, Node* b) {
    if (a == NULL)
        return b;
    if (b == NULL)
        return a;
    if (a->rank > b->rank) {
        a->disown_right();
        a->accept_right(merge(a->right, b));
        return a;
    } else {
        b->disown_left();
        b->accept_left(merge(a, b->left));
        return b;
    }
}

typedef pair<Node*, Node*> PNodes;

PNodes split_before(Node* a, int key) {
    if (a == NULL)
        return PNodes(NULL, NULL);
    if (a->v < key) {
        a->disown_right();
        PNodes t = split_before(a->right, key);
        a->accept_right(t.first);
        return PNodes(a, t.second);
    } else {
        a->disown_left();
        PNodes t = split_before(a->left, key);
        a->accept_left(t.second);
        return PNodes(t.first, a);
    }
}

PNodes split_after(Node* a, int key) {
    if (a == NULL)
        return PNodes(NULL, NULL);
    if (a->u <= key) {
        a->disown_right();
        PNodes t = split_after(a->right, key);
        a->accept_right(t.first);
        return PNodes(a, t.second);
    } else {
        a->disown_left();
        PNodes t = split_after(a->left, key);
        a->accept_left(t.second);
        return PNodes(t.first, a);
    }
}

typedef pair<Node*, PNodes> TNodes;

TNodes split_segment(Node* a, int el) {
    assert(a != NULL);
    if (a->left != NULL && a->left->max_segment >= el) {
        a->disown_left();
        TNodes t = split_segment(a->left, el);
        a->accept_left(t.second.second);
        return TNodes(t.first, PNodes(t.second.first, a));
    }
    if (a->v - a->u >= el) {
        TNodes t = TNodes(a, PNodes(a->left, a->right));
        a->disown_left();
        a->left = NULL;
        a->disown_right();
        a->right = NULL;
        return t;
    }
    assert(a->right != NULL);
    a->disown_right();
    TNodes t = split_segment(a->right, el);
    a->accept_right(t.second.first);
    return TNodes(t.first, PNodes(a, t.second.second));
}

Node* root = NULL;

int main() {
    srand(0xdeadbeef);
    int n, q;
    scanf("%d%d", &n, &q);
    root = merge(new Node(-1, -1), merge(new Node(0, n), new Node(n + 1, n + 1)));

    while (q--) {
        int cmd;
        scanf("%d", &cmd);
        if (cmd == 1) {
            int el;
            scanf("%d", &el);
            if (root->max_segment >= el) {
                TNodes t = split_segment(root, el);
                int u = t.first->u, v = t.first->v;
                printf("%d\n", u);
                if (v - u == el) {
                    root = merge(t.second.first, t.second.second);
                } else {
                    root = merge(t.second.first, merge(new Node(u + el, v), t.second.second));
                }
            } else {
                printf("-1\n");
            }
        } else {
            int u, el;
            scanf("%d%d", &u, &el);
            PNodes a = split_before(root, u);
            PNodes b = split_after(a.second, u + el);
            if (b.first == NULL) {
                printf("%d\n", el);
                root = merge(a.first, merge(new Node(u, u + el), b.second));
            } else {
                Node* x = b.first->first();
                Node* y = b.first->last();
                printf("%d\n", (el - b.first->total) + max(0, u - x->u) + max(0, y->v - (u + el)));
                int new_u = min(u, x->u);
                int new_v = max(u + el, y->v);
                root = merge(a.first, merge(new Node(new_u, new_v), b.second));
            }
        }
    }
}
