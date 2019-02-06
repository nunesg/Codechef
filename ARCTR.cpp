#include <bits/stdc++.h>

using namespace std;

#define N 201010
#define M 20
#define F first
#define S second
#define inf 1e18


typedef long long ll;
typedef pair<ll, ll> ii;

struct line{
	long double a, b;
	line(){}
	line(long double A, long double B) : a(A), b(B) {}
	long double eval(long double x){ return a*x+b; }
	bool operator == (line g){
		return a == g.a && b == g.b;
	}
};

bool comp(line a, line b){
	if(a.a != b.a) return a.a > b.a;
	else return a.b < b.b;
}

struct cht{
	
	vector<line> ch, vet;
	
	cht(){}
	
	void push(line a){ vet.push_back(a); }
	
	bool can(line ant, line top, line L){
		return (L.b-top.b)*(top.a - ant.a) <= (ant.b - top.b)*(top.a-L.a);
	}
	
	void add(line L){
		while(ch.size()>1 && can(ch[(int)ch.size()-2], ch.back(), L)){
			ch.pop_back();
		}
		ch.push_back(L);
	}
	
	
	
	void build(){
		sort(vet.begin(), vet.end(), comp);
		for(ll i=0; i<vet.size(); i++){
			if(i && vet[i] == vet[i-1]) continue;
			add(vet[i]);
		}
	}
	
	long double query(long double x){
		
		ll sz = ch.size(), ans = -1;
		if(!sz) return inf;
		
		for(ll k=20; k>=0; k--){
			if(ans+(1<<k) >= sz-1) continue;
			ll pos = ans+(1<<k);
			if(ch[pos].eval(x) >= ch[pos+1].eval(x)) ans+=(1<<k);
		}
		//~ printf("sz = %lld, ans = %lld, line = (%.5lf, %.5lf)\n", sz, ans, ch[ans+1].a, ch[ans+1].b);
		return ch[ans+1].eval(x);
	}
	
	void clear(){
		vet.clear();
		ch.clear();
	}
	
};

ll n, m, sz[N], h[N], dist[N], big[N], pai[N];
ll chain[N], posChain[N], head[N], position, cntChain;
cht st[N<<2];
vector<ii> adj[N];


void dfs(ll u, ll p){
	sz[u]=1;
	h[u] = h[p]+1;
	big[u] = -1;
	pai[u]=p;
	for(ii foo : adj[u]){
		ll v = foo.F, w = foo.S;
		if(v == p) continue;
		dist[v] = dist[u]+w;
		dfs(v, u);
		sz[u]+=sz[v];
		if(big[u] == -1 || sz[v]>sz[big[u]]) big[u] = v;
	}
}

void hld(ll u, ll p){
	posChain[u] = ++position;
	chain[u] = cntChain;
	if(big[u] == -1) return;
	
	hld(big[u], u);
	
	for(ii foo : adj[u]){
		ll v = foo.F;
		if(v == p || v == big[u]) continue;
		head[++cntChain] = v;
		hld(v, u);
	}
}

void build_st(ll p, ll l, ll r, ll op){
	if(op == 0) st[p].clear();
	else st[p].build();
	
	if(l == r) return;
	
	ll mid = (l+r)>>1, nxt = p<<1;
	build_st(nxt, l, mid, op);
	build_st(nxt+1, mid+1, r, op);
}

void build_hld(){
	position = cntChain = 0;
	dist[1] = 0;
	dfs(1, 0);
	hld(1, 0);
	build_st(1, 1, n, 0);//limpa segtree
}

ll get_lca(ll u, ll v){
	ll cu = chain[u], cv = chain[v];
	while(cu!=cv){
		if(h[head[cu]]<h[head[cv]]){
			swap(u, v); swap(cu, cv);
		}
		u = pai[head[cu]];
		cu = chain[u];
	}
	if(h[u]>h[v])swap(u, v);
	return u;
	
}

void update_st(ll p, ll l, ll r, ll a, ll b, line L){
	if(a>r || b<l) return;
	if(a<=l && b>=r){
		st[p].push(L);
		return;
	}
	
	ll mid = (l+r)>>1, nxt = p<<1;
	update_st(nxt, l, mid, a, b, L);
	update_st(nxt+1, mid+1, r, a, b, L);
}

long double query_st(ll p, ll l, ll r, ll pos, ll x){
	long double ans = inf;
	ans = min(ans, st[p].query(x));
	//~ printf("ans = %.10lf\n", ans);
	if(l == r) return ans;
	ll mid = (l+r)>>1, nxt = p<<1;
	if(pos<=mid) return min(query_st(nxt, l, mid, pos, x), ans);
	else return min(query_st(nxt+1, mid+1, r, pos, x), ans);
}

void update_hld(ll u, ll v, line L){
	ll cu = chain[u], cv = chain[v];
	//~ printf("u = %lld, v = %lld\n", u, v);
	while(cu!=cv){
		if(h[head[cu]]<h[head[cv]]){
			swap(u, v);
			swap(cu, cv);
		}
		ll l = posChain[head[cu]], r = posChain[u];
		//~ printf("u = %lld\n", u);
		update_st(1, 1, n, l, r, L);
		u = pai[head[cu]];
		cu = chain[u];
	}
	if(h[u]>h[v]) swap(u,v);
	update_st(1, 1, n, posChain[u], posChain[v], L);
}

void solve(){
	for(ll i=1; i<=n; i++){
		long double val = query_st(1, 1, n, posChain[i], dist[i]);
		if(val == inf) printf("-1\n");
		else cout << fixed << setprecision(10) << val << "\n";
	}
}

void clear(){
	for(int i=1; i<=n; i++){
		adj[i].clear();
	}
	build_st(1, 1, n, 0);
}


int main(){
	
	ll tc, a, b, c, t;
	
	scanf("%lld", &tc);
	while(tc--){
		
		scanf("%lld", &n);
		
		clear();
		
		for(ll i=1; i<n; i++){
			scanf("%lld %lld %lld", &a, &b, &c);
			adj[a].push_back(ii(b, c));
			adj[b].push_back(ii(a, c));
		}
		
		build_hld();
		
		scanf("%lld", &m);
		
		while(m--){
			
			scanf("%lld %lld %lld %lld", &a, &b, &t, &c);
			
			ll lc = get_lca(a, b);
			//~ printf("lc = %lld, a = %lld, b = %lld\n", lc, a, b);
			long double tx = (dist[a]-dist[lc])*1.0/c;
			//~ printf("add lines (%.5lf, %.5lf), (%.5lf, %.5lf)\n", 1.0/c, dist[a]*1.0/c + t, 1.0/c, -dist[lc]*1.0/c + tx + t);
			update_hld(a, lc, line(-1.0/c, dist[a]*1.0/c + t));
			update_hld(b, lc, line(1.0/c, -dist[lc]*1.0/c + tx + t));
		}
		
		build_st(1, 1, n, 1);
		
		solve();
	}
}
