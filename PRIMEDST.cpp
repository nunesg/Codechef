#include <bits/stdc++.h>

using namespace std;

#define N 50500

typedef long long int ll;

int sz[N], dist[N], block[N];
ll n, answer;
vector<int> adj[N], prime;
bitset<N> bs;


void crivo(){
	bs.set();
	bs[0] = 0;
	bs[1] = 0;
	for(int i=2; i<N; i++){
		if(bs[i]){
			for(int j=i+i; j<N; j+=i) bs[j] = 0;
			prime.push_back(i);
		}
	}
}


void build_sz(int u, int p){
	sz[u] = 1;
	for(int v : adj[u]){
		if(v == p || block[v]) continue;
		build_sz(v, u); sz[u]+=sz[v];
	}
}

int find_centroid(int u, int p, int tam){
	for(int v : adj[u]){
		if(v == p || block[v]) continue;
		if(sz[v]*2 > tam) return find_centroid(v, u, tam);
	}
	return u;
}

void dfs(int u, int p, int d, int add){
	dist[d]+=add;
	for(int v : adj[u]){
		if(v == p || block[v]) continue;
		dfs(v, u, d+1, add);
	}
}

void solve(int u, int p, int d){
	
	for(int i=0; i<prime.size(); i++){
		if(prime[i] < d) continue;
		if(!dist[prime[i]-d]) break;
		if(prime[i] == d) answer+= 2*dist[0];
		else answer+= dist[prime[i]-d];
	}
	
	for(int v : adj[u]){
		if(v == p || block[v]) continue;
		solve(v, u, d+1);
	}
}

void decompose(int u){
	
	build_sz(u, u);
	u = find_centroid(u, u, sz[u]);
	block[u] = 1;
	dfs(u, u, 0, 1);
	
	for(int v: adj[u]){
		if(block[v]) continue;
		dfs(v, u, 1, -1);
		solve(v, u, 1);
		dfs(v, u, 1, 1);
	}
	dfs(u, u, 0, -1);
	for(int v : adj[u]){
		if(block[v]) continue;
		decompose(v);
	}
}


int main(){
	int a, b;
	crivo();
	scanf("%lld", &n);
	for(int i=1; i<n; i++){
		scanf("%d %d", &a, &b);
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	
	answer = 0;
	decompose(1);
	double den = n*(n-1)*1.0000000;
	printf("%.10lf\n", answer/den);
}
