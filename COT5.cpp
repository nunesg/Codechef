#include <bits/stdc++.h>

using namespace std;



typedef struct no{

	long long key, w, flag;
	no *l, *r;
	
	no(){}
	no(long long a, long long b) : key(a), w(b), flag(0), l(NULL), r(NULL) {}
}* No;


struct treap{
	
	No root;
	
	treap(){root=NULL;}
	
	void split(No p, No &l, No &r, long long x){
		
		l = r = NULL;
		if(!p) return;
		
		if(p->key <= x){
			split(p->r, p->r, r, x), l = p;
		}else split(p->l, l, p->l, x), r = p;
	}
	
	No merge(No l, No r){
		
		if(!l || !r) return l ? l : r;
		
		if(l->w > r->w) {
			l->r = merge(l->r, r);
		}else{
			r->l = merge(l, r->l);
		}
	}
	
	void insert(long long k, long long w){
		No l, r=l=NULL;
		split(root, l, r, k);
		root = merge(merge(l, new no(k, w)), r);
	}
	
	void erase(long long k){
		No l, aux, m, r=l=m=NULL;
		split(root, l, aux, k-1);
		split(aux, m, r, k);
		root = merge(l, r);
	}
	
	int get_lca(No p, int a, int b){
		
		if(a == p->key) return a;
		if(b == p->key) return b;
		
		if( (a < p->key) != (b < p->key) ) return p->key;
		
		if(a<p->key) return get_lca(p->l, a, b);
		else return get_lca(p->r, a, b);
	}
	
	long long busca(long long a, long long b){
		int x = get_lca(root, a, b);
		
		No A = root;
		int ans=0, flag=0;
		while(1){
			
			if(flag) ans++;
			if(A->key == x) flag=1;
			if(A->key == a) break;
			if(a < A->key) A = A->l;
			else A = A->r;
		}
		
		flag=0;
		A=root;
		while(1){
			
			if(flag) ans++;
			if(A->key == x) flag=1;
			if(A->key == b) break;
			if(b < A->key) A = A->l;
			else A = A->r;
		}
		
		return ans;
	}
};

treap T;
long long n;

int main(){
	
	
	scanf("%lld", &n);
	
	long long op, a, b;
	while(n--){
		scanf("%lld %lld", &op, &a);
		//~ printf("oi\n");
		if(!op){
			scanf("%lld", &b);
			T.insert(a, b);
		}else
		if(op == 1){
			T.erase(a);
		}else{
			scanf("%lld", &b);
			printf("%lld\n", T.busca(a, b));
		}
	}
	
	
}
