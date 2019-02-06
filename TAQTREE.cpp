#include <bits/stdc++.h>

using namespace std;

#define N 101010
#define F first
#define S second

typedef pair<int, int> ii;
typedef pair<ii, int> iii;


int n, q, sz[N], h[N], pai[N], big[N], val[N], bit[N];
int chain[N], head[N], posChain[N], cntChain, position;
vector<ii> adj[N];
iii E[N];

void update_bit(int pos, int x){
	for(; pos<=n; pos+=pos&(-pos)) bit[pos]+=x;
}

int sum_bit(int pos){
	int s=0;
	for(; pos; pos-=pos&(-pos)) s+=bit[pos];
	return s;
}

void dfs(int u, int p, int x){
	
	h[u] = h[p]+1;
	pai[u] = p;
	val[u] = x;
	sz[u]=1;
	
	big[u] = -1;
	for(ii foo : adj[u]){
		int v = foo.F, w = foo.S;
		if(v == p) continue;
		dfs(v, u, w);
		sz[u]+=sz[v];
		
		if(big[u] == -1 || sz[v] > sz[big[u]]) big[u] = v;
	}
}

void hld(int u, int p){
	
	posChain[u] = ++position;
	update_bit(position, val[u]);
	chain[u] = cntChain;
	
	if(big[u] == -1) return;
	
	hld(big[u], u);
	
	for(ii foo : adj[u]){
		int v = foo.F, w = foo.S;
		if(v == p || v == big[u]) continue;
		head[++cntChain] = v;
		hld(v, u);
	}
}


void build_hld(){
	cntChain = position = 0;
	dfs(1, 0, 0);
	hld(1, 0);
}

int update(int u, int nv){
	update_bit(posChain[u], nv-val[u]);
	val[u] = nv;
}

int query(int u, int v){
	
	int cu = chain[u], cv = chain[v];
	int ans=0;
	while(cu!=cv){
		if(h[head[cu]] < h[head[cv]]){
			swap(u, v);
			swap(cu, cv);
		}
		
		ans+= sum_bit(posChain[u]) - sum_bit(posChain[head[cu]]-1);
		u = pai[head[cu]];
		cu = chain[u];
	}
	
	if(h[u]>h[v]) swap(u, v);
	ans+= sum_bit(posChain[v]) - sum_bit(posChain[u]);
	return ans;
}



int main(){
	
	scanf("%d", &n);
	
	int a, b, c;
	for(int i=1; i<n; i++){
		scanf("%d %d %d", &a, &b, &c);
		adj[a].push_back(ii(b, c));
		adj[b].push_back(ii(a, c));
		E[i] = iii(ii(a, b), c);
	}
	
	build_hld();
	
	scanf("%d", &q);
	
	while(q--){
		scanf("%d %d %d", &c, &a, &b);
		
		if(c == 1){
			int u = E[a].F.F, v = E[a].F.S;
			if(h[u]>h[v]) swap(u, v);
			update(v, b);
		}else{
			printf("%d\n", query(a, b));
		}
	}
	
}
