#include <bits/stdc++.h>

using namespace std;

#define N 1010
#define inf 1010101010

typedef long long ll;
typedef pair<ll , ll > ii;
typedef pair< ll , ii > iii;


ll n, comp[N], d[N][N], answer;
vector<ii> adj[N];
vector<iii> edges;

void init(){ for(ll i=0; i<=n; i++) comp[i] = i; }

ll find(ll i){ return i == comp[i] ? i : comp[i] = find(comp[i]); }

bool same(ll i, ll j){ return find(i) == find(j); }

void join(ll i, ll j){ comp[find(i)] = find(j); }

void build_MST(){
	init();
	sort(edges.rbegin(), edges.rend());
	
	for(iii foo : edges){
		ll u = foo.second.first, v = foo.second.second, w = foo.first;
		if(same(u, v)) continue;
		
		join(u, v);
		//~ printf("add (%lld, %lld, %lld)\n", u, v, w);
		adj[u].push_back(ii(v, w));
		adj[v].push_back(ii(u, w));
	}
}


void solve(ll u, ll pai, ll ini, ll mincut){
	
	if(u != ini) answer+= mincut-d[ini][u];
	//~ printf("ini = %lld, u = %lld, mincut = %lld\n", ini, u, mincut);
	for(ii foo : adj[u]){
		ll v = foo.first, w = foo.second;
		if(v == pai) continue;
		solve(v, u, ini, min(mincut, w));
	}
}


int main(){
	
	ll tc;
	scanf("%lld", &tc);
	
	while(tc--){
		scanf("%lld", &n);
		
		edges.clear();
		memset(d, 0, sizeof d);
		
		for(ll i=1; i<=n; i++){
			adj[i].clear();
			for(ll j=1; j<=n; j++){
				scanf("%lld", &d[i][j]);
				edges.push_back(iii(d[i][j], ii(i, j)));
			}
		}
		
		build_MST();
		
		answer=0;
		for(ll i=1; i<=n; i++){
			solve(i, 0, i, inf);
		}
		
		printf("%lld\n", answer);
	}
	
	
}
