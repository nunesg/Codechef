#include <bits/stdc++.h>

using namespace std;

struct no{
	
	int sub, p;
	char c;
	no *l, *r;
	
	no(){sub = 1;}
	no(char a) : sub(1), c(a), p((rand()<<16)^rand()), l(NULL), r(NULL) {}
	
	void recalc(){
		sub=1;
		if(l) sub+=l->sub;
		if(r) sub+=r->sub;
	}
	
	void infixa(){
		if(l) l->infixa();
		cout << c;
		if(r) r->infixa();
	}
	
};

typedef struct no * No;

struct treap{
	
	No root;
	
	treap() : root(NULL) {}
	
	int get_size(No p){ return p ? p->sub : 0; }
	
	void split(No p, No &l, No &r, int x){
		l = r = NULL;
		if(!p) return;
		
		int a = get_size(p->l)+1;
		
		if(a<=x) split(p->r, p->r, r, x-a), l=p;
		else split(p->l, l, p->l, x), r=p;
		
		p->recalc();
	}
	
	No merge(No l, No r){
		if(!l || !r) return l ? l : r;
		
		if(l->p >= r->p){
			l->r = merge(l->r, r);
			l->recalc();
			return l;
		}else{
			r->l = merge(l, r->l);
			r->recalc();
			return r;
		}
	}
	
	void insert(string &s, int p){
		No l, r;
		l = r = NULL;
		split(root, l, r, p);
		root = merge(merge(l, build(s)), r);
	}
	
	No build(string &s){
		
		No ans = NULL;
		for(int i=0; i<s.size(); i++){
			ans = merge(ans, new no(s[i]));
		}
		return ans;
	}
	
	No printa_range(int a, int b){
		No l, r, m, mid;
		l = r = m = mid = NULL;
		split(root, l, m, a-1);
		split(m, mid, r, b-a+1);
		mid->infixa(); cout << "\n";
		root= merge(merge(l, mid), r);
	}
	
};

treap T;
int q;
string s;

int main(){
	srand(time(NULL));
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> q;
	char op;
	int a, b;
	while(q--){
		
		cin >> op >> a;
		
		if(op == '+'){
			cin >> s;
			T.insert(s, a);
			
		}else{
			cin >> b;
			T.printa_range(a, a+b-1);
			
		}
	}
}
