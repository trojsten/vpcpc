#include <cstdio>
#include <cstring>
#include <queue>
#include <map>
#include <algorithm>

using namespace std;

#define FOR(i,n) for(int i = 0; i < n; i++)

struct Frac{
	int p;
	int q;

	Frac(int _p = 0, int _q = 1){
		p=_p;
		q=_q;
	}

	bool operator<(const Frac & that) const{
		return ((long long)p)*that.q < ((long long)q)*that.p;
	}

};

struct Node{
	map<Frac,Node*> C;
	Node * backlink;
	int ends;

	Node(){
		backlink = 0;
		ends = 0;
	}

	Node * next(const Frac & f){
		map<Frac,Node*>::iterator it;
		it = C.find(f);
		if(it != C.end()){
			return it->second;
		} else if (backlink != 0){
			return backlink->next(f);
		} else {
			return this;
		}
	}

	Node * move_or_create(const Frac & f){
		map<Frac,Node*>::iterator it;
		it = C.find(f);
		if(it != C.end()){
			return it->second;
		} else {
			Node * n = new Node();
			C[f] = n;
			return n;
		} 
	}

};

int main(){
	int n,l;
	int last, act;
	Node * node;
	Node * root = new Node();
	
	scanf("%d",&n);
	FOR(i,n){
		scanf("%d",&l);
		scanf("%d",&last);
		node = root;
		FOR(j,l-1){
			scanf("%d",&act);
			node = node->move_or_create(Frac(act,last));
			last = act;
		}
		node->ends++;
	}

	queue<Node *> Q;
	for(map<Frac,Node*>::iterator it = root->C.begin(); it != root->C.end(); ++it){
		it->second->backlink = root;
		Q.push(it->second);
	}
	while(!Q.empty()){
		node = Q.front();
		Q.pop();
		node->ends += node->backlink->ends;
		for(map<Frac,Node*>::iterator it = node->C.begin(); it != node->C.end(); ++it){
			it->second->backlink = node->backlink->next(it->first);
			Q.push(it->second);
		}
	}

	scanf("%d",&l);
	scanf("%d",&last);
	node = root;
	long long res = node->ends;
	FOR(j,l-1){
		scanf("%d",&act);
		node = node->next(Frac(act,last));
		last = act;
		res += node->ends;
	}

	printf("%lld\n",res);

}