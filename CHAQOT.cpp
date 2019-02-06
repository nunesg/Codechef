#include <bits/stdc++.h>

using namespace std;

#define N 101010
#define M 20
#define inf 1010101010
#define F first
#define S second

typedef pair<int, int> ii;


struct no{
	int sum;
	no *left, *right;
	no() : sum(0), left(NULL), right(NULL) {}
};


int n, q, val[N], h[N], lca[N][M];
vector<int> adj[N], aux;
no *root[N];

no * update(no *p, int l, int r, int pos){
	
	no *ans;
	ans = new no();
	
	if(p) *ans = *p;
	ans->sum++;
	
	if(l == r) return ans;
	
	int mid = (l+r)>>1;
	
	if(mid>=pos) ans->left = update(p ? p->left : NULL, l, mid, pos);
	else ans->right = update(p ? p->right : NULL, mid+1, r, pos);
	
	return ans;
}


void destroy(no *p){
	if(!p) return;
	destroy(p->left);
	destroy(p->right);
	delete p;
	p = NULL;
}

int get(no *p){ return p ? p->sum : 0; }

int menores(no *u, no *p, int l, int r, int x){
	if(l == r) return 0;
	
	int mid = (l+r)>>1;
	int a = get(u ? u->left : NULL), b = get(p ? p->left : NULL);
	int s = a-b;
	if(x<=mid) return menores(u ? u->left : NULL, p ? p->left : NULL, l, mid, x);
	else return s + menores(u ? u->right : NULL, p ? p->right : NULL, mid+1, r, x);
}


void dfs(int u, int p){
	root[u] = update(root[p], -inf, inf, val[u]);
	h[u] = h[p]+1;
	lca[u][0] = p;
	for(int i=1; i<M; i++) lca[u][i] = lca[lca[u][i-1]][i-1];
	
	for(int v : adj[u]){
		if(v == p) continue;
		dfs(v, u);
	}
}

int get_lca(int u, int v){
	if(h[u]<h[v]) swap(u, v);
	int d = h[u]-h[v];
	
	for(int i=0; i<M; i++) if(d&(1<<i)) u = lca[u][i];
	if(v == u) return u;
	for(int i=M-1; i>=0; i--){
		if(lca[u][i] != lca[v][i]){
			u = lca[u][i];
			v = lca[v][i];
		}
	}
	return lca[u][0];
}

int get_menores(int p, int x){//qts vertices tem valor < x
	int m=0;
	for(int u : aux){
		m+= menores(root[u], root[p], -inf, inf, x);
	}
	m+= val[p]<x;
	return m;
}

int get_kth(no *no1, vector<no*> &vet, int l, int r, int p, int k){
	
	if(l == r) return l;
	int s=0, mid = (l+r)>>1;
	
	for(int i=0; i<vet.size(); i++){
		s+= get(vet[i] ? vet[i]->left : NULL) - get(no1 ? no1->left : NULL);
	}
	
	s+= val[p]<=mid;
	printf("s = %d, k = %d\n", s, k);
	
	if(s>=k) {
		for(int i=0; i<vet.size(); i++) vet[i] = vet[i] ? vet[i]->left : NULL;
		return get_kth(no1 ? no1->left : NULL, vet, l, mid, p, k);
	}else{
		for(int i=0; i<vet.size(); i++) vet[i] = vet[i] ? vet[i]->right : NULL;
		return get_kth(no1 ? no1->right : NULL, vet, mid+1, r, p, k-s);
	}
	
}

int solve(int p, int r){
	int a = get_menores(p, r+1);
	vector<no*> vet;
	for(int u : aux) vet.push_back(root[u]);
	int low = get_kth(root[p], vet, -inf, inf, p, a);

	vet.clear();
	for(int u : aux) vet.push_back(root[u]);
	int high = get_kth(root[p], vet, -inf, inf, p, a+1);
	printf("low = %d, high = %d\n", low, high);
	return min(abs(r-low), abs(r-high));
}

int main(){
	
	int tc, a, b;
	
	scanf("%d", &tc);
	
	while(tc--){
		
		scanf("%d %d", &n, &q);
		
		for(int i=1; i<=n; i++) {
			scanf("%d", &val[i]);
			adj[i].clear();
			for(int j=0; j<M; j++) lca[i][j] = 0;
			//~ destroy(root[i]);
		}
		
		for(int i=1; i<n; i++){
			scanf("%d %d", &a, &b);
			adj[a].push_back(b);
			adj[b].push_back(a);
		}
		
		root[0] = new no();
		dfs(1, 0);
		
		int last=0, r, k, p;
		
		while(q--){
			
			scanf("%d %d", &r, &k);
			r^=last;
			aux.clear();
			for(int i=0; i<k; i++){
				scanf("%d", &a);
				a^=last;
				if(!i) p = a;
				else p = get_lca(p, a);
				aux.push_back(a);
			}
			
			printf("%d\n", (last = solve(p, r)));
		}
		
		
	}
	
}
