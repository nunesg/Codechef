#include <bits/stdc++.h>

using namespace std;

#define N 10101

typedef pair<int, int> ii;

int n, in[2][N], out[2][N], cnt;
vector<int> adj[2][N];
ii E1[N], E2[N];

void dfs(int u, int p, int t){
	
	in[t][u] = cnt++;
	
	for(int v : adj[t][u]){
		if(v == p) continue;
		dfs(v, u, t);
	}
	
	out[t][u] = cnt++;
}

bool filho(int x, int u, int p){
	int a = in[p][x], b = out[p][x];
	int l = in[p][u], r = out[p][u];
	return l<=a && r>=b;
}

void solve(){
	
	for(int e1 = 0; e1<n-1; e1++){
		
		int u = E1[e1].first, v = E1[e1].second;
		
		if(in[0][u] > in[0][v]) swap(u, v);
		int cont=0;
		for(int e = 0; e<n-1; e++){
			
			
			int a = E2[e].first, b = E2[e].second;
			
			if(in[1][a] > in[1][b]) swap(a, b);
			
			
			if(filho(a, v, 0) && !filho(b, v, 0) || !filho(a, v, 0) && filho(b, v, 0)){
				if(filho(u, b, 1) && !filho(v, b, 1) || !filho(u, b, 1) && filho(v, b, 1)) cont++;
			}
		}
		printf("%d%c", cont, e1==n-2 ? '\n' : ' ');
	}
	
	
}

int main(){
	
	int tc;
	scanf("%d", &tc);
	
	while(tc--){
		
		scanf("%d", &n);
		int a, b;
		
		for(int t=0; t<2; t++){
			for(int i=0; i<=n; i++) adj[t][i].clear();
		}
		
		for(int i=1; i<n; i++){
			scanf("%d %d", &a, &b);
			if(a>b)swap(a, b);
			E1[i-1] = ii(a, b);
			adj[0][a].push_back(b);
			adj[0][b].push_back(a);
		}
		for(int i=1; i<n; i++){
			scanf("%d %d", &a, &b);
			if(a>b)swap(a, b);
			E2[i-1] = ii(a, b);
			adj[1][a].push_back(b);
			adj[1][b].push_back(a);
		}
		
		cnt = 0;
		dfs(1, 1, 0);
		cnt = 0;
		dfs(1, 1, 1);
		
		solve();
	}
	
	
}
