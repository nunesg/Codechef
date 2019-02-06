#include <bits/stdc++.h>

using namespace std;

#define N 100010
#define block 317

typedef long long ll;

int n, q, cnt, c[N], blc[N], state[N], vet[N], in[N], sz[N], v[N], lazy[N/block+2];
ll val[N/block+2][N];
vector<int> adj[N];


void dfs(int u, int p){
	in[u] = cnt;
	vet[cnt++] = u;
	
	sz[u] = 1;
	for(int v : adj[u]){
		if(v == p) continue;
		
		dfs(v, u);
		sz[u]+=sz[v];
	}
}

void build(){
	for(int b=0, i=0; i<n; b++){
		for(int k=0; k<block && i<n; k++, i++){
			blc[i] = b;
		}
	}
	for(int i=0; i<n; i++){
		val[blc[i]][0]+=c[vet[i]];
	}
}

void update(int l, int r, int x){
	
	int bl = blc[l], br = blc[r];
	if(bl == br){
		for(int i=l; i<=r; i++) {
			val[bl][v[i]]-=c[vet[i]];
			v[i]+=x;
			val[bl][v[i]]+=c[vet[i]];
		}
		return;
	}
	
	for(int i=l; blc[i] == bl; i++){
		val[bl][v[i]]-=c[vet[i]];
		v[i]+=x;
		val[bl][v[i]]+=c[vet[i]];
	}
	for(int i=r; blc[i] == br; i--){
		val[br][v[i]]-=c[vet[i]];
		v[i]+=x;
		val[br][v[i]]+=c[vet[i]];
	}
	
	for(int b = bl+1; b<br; b++) lazy[b]+=x;
}

ll query(int l, int r, int x){
	
	int bl = blc[l], br = blc[r];
	ll ans=0;
	if(bl == br){
		for(int i=l; i<=r; i++){
			if(v[i]+lazy[bl] == x) ans+=c[vet[i]];
		}
		return ans;
	}
	
	for(int i=l; blc[i] == bl; i++){
		if(v[i]+lazy[bl] == x) ans+=c[vet[i]];
	}
	for(int i=r; blc[i] == br; i--){
		if(v[i]+lazy[br] == x) ans+=c[vet[i]];
	}
	
	for(int b = bl+1; b<br; b++){
		if(x<lazy[b]) continue;
		ans+= val[b][x-lazy[b]];
	}
	return ans;
}

int main(){
	
	scanf("%d", &n);
	
	for(int i=1; i<=n; i++) scanf("%d", &c[i]);

	int t,a, b;

	for(int i=1; i<n; i++){
		scanf("%d %d", &a, &b);
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	
	
	dfs(1, 0);
	build();
	
	
	scanf("%d", &q);
	
	while(q--){
		scanf("%d %d", &t, &a);
		if(t == 1){
			update(in[a], in[a]+sz[a]-1, state[a] ? -1 : 1);
			state[a]^=1;
		}else{
			
			int pos = in[a];
			int x = v[pos]+lazy[blc[pos]];
			
			if(state[a]) printf("0\n");
			else printf("%lld\n", query(pos, pos+sz[a]-1, x));
		}
	}
	
}
