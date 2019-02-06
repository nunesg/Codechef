#include <bits/stdc++.h>

using namespace std;

#define N 303010
#define NMAX 1500100

typedef long long int ll;

int n, sz[N], bit[N<<1], block[N], peso[N];
char peso_[1500100];
bitset<1500100> bs;
ll dist[N<<1], answer;
vector<int> adj[N], prime;

void update(int pos, int v, int op){
	pos+=N;
	for(; pos<= (N<<1); pos+=(pos&(-pos))){ 
		if(!op) bit[pos]+=v;
		else dist[pos]+=v;
	}
}

ll sum(int pos, int op){
	ll s=0;
	pos+=N;
	for(; pos; pos-=(pos&(-pos))){
		if(!op) s+=bit[pos];
		else s+=dist[pos];
	}
	return s;
}

ll query(int a, int op){
	return sum(N-1, op) - sum(a-1, op);
}

void build_sz(int u, int p){
	sz[u] = 1;
	for(int v : adj[u]){
		if(v == p || block[v]) continue;
		build_sz(v, u);
		sz[u]+=sz[v];
	}
}

int find_centroid(int u, int p, int tam){
	for(int v : adj[u]){
		if(v == p || block[v]) continue;
		if(sz[v]*2 > tam) return find_centroid(v, u, tam);
	}
	return u;
}


void solve(int u, int p, int d, int deep, int d_cent){
	
	int k = (peso[u] ? 1 : -1);
	d+=k;
	if(d+d_cent>=0) answer+=(deep+1)*2;
	
	//~ printf("u=%d, d = %d, query (%d)\n", u, d, -d);
	ll q1 = query(-d, 1);
	ll q0 = query(-d, 0);
	
	answer+=  q1 + q0*(ll)deep;
	
	for(int v : adj[u]){
		if(v == p || block[v]) continue;
		solve(v, u, d, deep+1, d_cent);
	}
	
}


void dfs(int u, int p, int d, int deep, int add){
	d+= (peso[u]) ? 1 : -1;

	update(d, add, 0);
	update(d, deep*add, 1);
	for(int v : adj[u]){
		if(v == p || block[v]) continue;
		dfs(v, u, d, deep+1, add);
	}
}




void decompose(int u){
	build_sz(u, u);
	u = find_centroid(u, u, sz[u]);
	block[u] = 1;
	
	dfs(u, u, 0, 1, 1);
	int value = (peso[u] ? 1 : -1);
	update(value, -1, 0);
	update(value, -1, 1);
	
	for(int v : adj[u]){
		if(block[v]) continue;

		dfs(v, u, value, 2, -1);

		solve(v, u, 0, 1, value);

		dfs(v, u, value, 2, 1);
	}
	
	update(value, 1, 0);
	update(value, 1, 1);
	
	dfs(u, u, 0, 1, -1);
	for(int v : adj[u]){
		if(block[v]) continue;
		decompose(v);
	}
}



void crivo(){
	bs.set();
	bs[0] = bs[1] = 0;
	for(int i=2; i<NMAX; i++){
		if(bs[i]){
			for(int j=i+i; j<NMAX; j+=i) bs[j] = 0;
			prime.push_back(i);
		}
	}
}

int calc(int x){
	int k=0;
	while(x%2 == 0) x/=2;
	for(int pf = 1; prime[pf]*prime[pf]<=x; pf++){
		k=0;
		while(x%prime[pf] == 0){
			x/=prime[pf];
			k++;
		}
		if(k%2) return 0;
	}
	if(x!=1) return 0;
	return 1;
}



int main(){
	crivo();
	int a, b;
	scanf("%d", &n);
	for(int i=1; i<n; i++){
		scanf("%d %d", &a, &b);
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	answer = 0;
	
	for(int i=1; i<=n; i++){
		scanf("%d", &a);
		peso[i] = calc(a);
		//~ printf("%d ", peso[i]);
		if(peso[i]) answer+=2;
	}
	
	memset(bit, 0, sizeof bit);
	memset(dist, 0, sizeof dist);
	
	decompose(1);
	
	printf("%lld\n", answer/2);
}
