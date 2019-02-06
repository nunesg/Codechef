#include <bits/stdc++.h>

using namespace std;

#define N 101010
#define M 32
#define inf 10000000000000000LL
#define F first
#define S second

typedef long long int ll;

typedef pair<ll , ll > ii;

bitset<N> ph;
ll n, m, k, menor, money, val[M], cost[N], pop[N], power[M], seen[N], acc_max[(1<<16)+10];
vector<ll > adj[N];
vector<ii> vet, v1, v2;

ll dfs(ll u){
	seen[u] = 1;
	
	ll s = pop[u];
	if(ph[u]) menor = min(menor, cost[u]);
	
	for(ll v : adj[u]){
		if(seen[v]) continue;
		s+=dfs(v);
	}
	return s;
}

void build(){
	
	memset(seen, 0, sizeof seen);
	for(ll i=0; i<n; i++){
		if(!seen[i]){
			menor = inf;
			ll s = dfs(i);
			if(menor != inf) vet.push_back(ii(menor, s));
		}
	}
}

ii soma(ii a, ii b){
	return ii(a.F+b.F, a.S+b.S);
}

ll solve(){
	ll ans=0;
	v1.push_back(ii(0, 0));
	n = vet.size();
	for(ll i=1; i< (1<<min(n, 16LL)); i++){
		v1.push_back( soma( v1[i^(i&(-i))], vet[ __builtin_ctz( i&(-i) )]) );
		if(v1[i].F <= money) ans = max(ans, v1[i].S);
	}
	if(n<=16) return ans;
	
	reverse(vet.begin(), vet.end());
	
	ans=0;
	v2.push_back(ii(0, 0));
	for(ll i=1; i< (1<<(n-16)); i++){
		v2.push_back( soma(v2[i^(i&(-i))] , vet[ __builtin_ctz( i&(-i) )] ));
	}
	sort(v2.begin(), v2.end());
	acc_max[0] = v2[0].S;
	
	for(ll i=1; i<v2.size(); i++) acc_max[i] = max(acc_max[i-1], v2[i].S);
	
	for(ll i=0; i<v1.size(); i++){
		
		if(money<v1[i].F) continue;
		ll j = prev(upper_bound(v2.begin(), v2.end(), ii(money-v1[i].F, inf))) - v2.begin();
		
		ans = max(ans, v1[i].S+acc_max[j]);
	}
	return ans;
}

int main(){
	
	scanf("%lld %lld %lld", &n, &m, &k);
	ll a, b, x;
	for(ll i=0; i<m; i++){
		scanf("%lld %lld", &a, &b);
		a--; b--;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	for(ll i=0; i<n; i++){
		scanf("%lld", &pop[i]);
	}
	for(ll i=0; i<k; i++){
		scanf("%lld", &power[i]); power[i]--;
		ph[power[i]] = 1;
	}
	
	for(ll i=0; i<k; i++){
		scanf("%lld", &cost[power[i]]);
	}
	scanf("%lld %lld", &x, &money);
	for(ll i=0; i<x; i++){
		scanf("%lld", &a); a--;
		money+=cost[power[a]];
	}
	
	build();
	cout << solve() << endl;
}
