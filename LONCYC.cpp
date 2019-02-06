#include <bits/stdc++.h>

using namespace std;

#define N 201010
#define M 5000010
#define F first
#define S second

typedef long long ll;
typedef pair<int, int> ii;

int n, m, szcomp[N], tam[N], sub[N], sztree[N], comp[N], low[N], in[N], seen[N], cnt;
vector<ii> adj[N];
ll ans, answer[M];
ii E[M];

void init(){
	for(int i=1; i<=n; i++) {
		comp[i] = i;
		szcomp[i]=1;
		adj[i].clear();
		seen[i]=0;
		tam[i]=0;
	}
	cnt = 1;
}

int find(int i){ return i == comp[i] ? i : comp[i] = find(comp[i]); }

bool same(int i, int j){ return find(i) == find(j); }

void join(int i, int j){
	int ci = find(i), cj = find(j);
	szcomp[cj]+=szcomp[ci];
	szcomp[ci]=0;
	comp[ci] = cj;
}


void tarjan(int u, int p){
	
	low[u] = in[u] = cnt++;
	seen[u] = 1;
	for(ii foo : adj[u]){
		int v = foo.F, id = foo.S;
		if(v == p) continue;
		
		if(!seen[v]){
			
			tarjan(v, u);
			
			if(low[v] > in[u]){
				join(u, v);
				//~ printf("join (%d, %d)\n", u, v);
			}
			low[u] = min(low[u], low[v]);
		}else{
			low[u] = min(low[u], in[v]);
		}
	}
}
void dfs(int u, int p){
	seen[u]=1;
	sztree[u] = 1;
	sub[u]=1;
	for(ii foo : adj[u]){
		int v = foo.F, id = foo.S;
		
		if(v == p && !same(u, v)) sztree[u]+=szcomp[find(v)];
		if(v == p) continue;
		
		if(!seen[v]){
			dfs(v, u);
			if(same(u, v)) {
				sztree[u]+=sztree[v];
				sub[u]+=sub[v];
			}else {
				sztree[u]+=szcomp[find(v)];
				answer[id] = szcomp[find(u)]*1LL*szcomp[find(v)];
			}
		}else{
			answer[id] = szcomp[find(u)]*1LL*szcomp[find(v)];
			sztree[u]+=szcomp[find(v)];
		}
	}
	//~ printf("sztree[%d] = %d\n", u, sztree[u]);
	int cu = find(u);
	tam[cu] = max(tam[cu], sztree[u]);
}



int main(){
	
	int tc;
	scanf("%d", &tc);
	
	while(tc--){
		scanf("%d %d", &n, &m);
		
		init();
		int a, b;
		for(int i=0; i<m; i++){
			scanf("%d %d", &a, &b);
			adj[a].push_back(ii(b, i));
			adj[b].push_back(ii(a, i));
			E[i] = ii(a, b);
		}
		
		tarjan(1, 0);
		
		ans=0;
		for(int i=1; i<=n; i++) seen[i]=0;
		dfs(1, 0);
		
		for(int i=0; i<m; i++){
			a = E[i].F, b = E[i].S;
			
			if(in[a] > in[b]) swap(a, b);
			if(!same(a, b)) continue;
			
			answer[i] = sztree[b]*1LL*(szcomp[find(a)] - sub[b]) + sub[b]*1LL*(tam[find(a)] - sztree[b]) - (sub[b]*1LL*(szcomp[find(a)]-sub[b])) ;
		}
		
		
		for(int i=0; i<m; i++){
			printf("%lld\n", answer[i]);
		}
	}
	
}
