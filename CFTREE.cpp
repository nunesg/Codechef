#include <bits/stdc++.h>

using namespace std;

#define N 301010
#define mod 1000000007
#define block 333
#define F first
#define S second

typedef long long ll;
typedef pair<int, int> ii;

int n, m, val[N], h[N], in[N], out[N], aux[N], aux2[N], pai[N], f[N], curr;
vector<int> adj[N];

void dfs(int u, int p){
	pai[u] = p;
	h[u] = h[p]+1;
	in[u] = curr++;
	if(u>1){
		aux[u] = ((ll)aux[u] + (ll)aux[pai[u]] + (ll)aux[pai[pai[u]]] + (ll)aux2[pai[u]])%mod;
	}
	val[u] = (val[u] + aux[u])%mod;
	//~ printf("aux[%d] = %d\n", u, aux[u]);
	for(int v : adj[u]){
		if(v == p) continue;
		dfs(v, u);
	}
	
	out[u] = curr++;
}



int main(){
	
	f[0] = 0;
	f[1] = f[2] = 1;
	for(int i=3; i<N; i++) f[i] = (f[i-1]+f[i-2])%mod;
	
	
	scanf("%d %d", &n, &m);
	int a, b;
	for(int i=2; i<=n; i++){
		scanf("%d", &a);
		adj[a].push_back(i);
	}
	
	vector<ii> upd;
	char op;
	for(int i=0; i<m; ){
		curr = 0;
		//~ printf("\n");
		dfs(1, 0);
		upd.clear();
		for(int k=0; k<block && i<m; i++, k++){
			
			scanf(" %c %d", &op, &a);
			//~ printf("a = %d\n", a);
			if(op == 'U'){
				scanf("%d", &b);
				upd.push_back(ii(a, b));
			}else{
				
				int ans=val[a];
				//~ printf("h[%d] = %d\n", a, h[a]);
				for(ii foo : upd){
					int u = foo.F, w = foo.S;
					//~ printf("u = %d, h[%d] = %d\n", u, u, h[u]);
					if(in[u]<=in[a] && out[u]>=out[a]){
						ans = (ans+f[h[a]-h[u]+w])%mod;
					}
				}
				printf("%d\n", ans);
			}
			
		}
	
		memset(aux, 0, sizeof aux);
		memset(aux2, 0, sizeof aux2);
		for(ii foo : upd){
			int u = foo.F, w = foo.S;
			aux[u] = (aux[u] + f[w])%mod;
			//~ printf("aux[%d] += %d,  aux2[%d] += %d\n", u, f[w], pai[u], f[w-1]);
			aux2[u] = (aux2[u] + f[w-1])%mod;
		}
	}
	
}
