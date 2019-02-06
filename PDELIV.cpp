#include <bits/stdc++.h>

using namespace std;

#define N 201010
#define inf 3010000010000010000LL

typedef long long ll;

struct line{
	
	ll a, b, s, p;
	int id;
	
	line(){}
	line(ll x, ll y, int c) : s(x), p(y), id(c), a(-2*x), b(x*x + y) {}
	
	ll eval(ll x){ return a*x + b; }
};


struct cht{
	
	vector<line> ch;
	
	cht(){}
	
	bool can(line ant, line top, line L){
		return (L.b - top.b)*(ant.a - L.a) <= (top.a - L.a)*(L.b - ant.b);
	}
	
	void add(line L){
		
		int n = ch.size();
		while(n > 1 && can(ch[n-2], ch[n-1], L)){
			ch.pop_back();
			n--;
		}
		
		ch.push_back(L);
		n++;
	}
	
	ll query(ll x){
		//~ printf("entrou\n");
		int ans = -1;
		int n = ch.size();
		for(int k=20; k>=0; k--){
			if(ans+(1<<k) >=n-1) continue;
			if(ch[ans+(1<<k)].eval(x) > ch[ans+(1<<k)+1].eval(x)) ans+=(1<<k);
		}
		//~ printf("saiu\n");
		ans++;
		return ch[ans].eval(x);
	}
};


int n, m, mapa[N];
line vet[N];
cht st[N<<2];

void build(int p, int l, int r){
	
	for(int i=l; i<=r; i++) st[p].add(vet[i]);
	
	if(l == r) return;
	int mid = (l+r)>>1, nxt = p<<1;
	build(nxt, l, mid);
	build(nxt+1, mid+1, r);
}

ll query(int p, int l, int r, int a, int b, ll x){
	if(r<a || l>b) return inf;
	if(a<=l && b>=r) return st[p].query(x) + x*x;
	
	int mid = (l+r)>>1, nxt = p<<1;
	return min(query(nxt, l, mid, a, b, x), query(nxt+1, mid+1, r, a, b, x));
}

int main(){
	
	scanf("%d %d", &n, &m);
	int a, b;
	for(int i=1; i<=n; i++){
		scanf("%d %d", &a, &b);
		vet[i] = line(a, b, i);
	}
	
	sort(vet+1, vet+n+1, [](line a, line b) { return a.s < b.s; });
	
	for(int i=1; i<=n; i++){
		mapa[vet[i].id] = i;
	}
	
	build(1, 1, n);
	
	int k, x;
	vector<int> aux;
	while(m--){
		scanf("%d %d", &x, &k);
		aux.clear();
		for(int i=0; i<k; i++){
			scanf("%d", &a);
			aux.push_back(mapa[a]);
		}
		sort(aux.begin(), aux.end());
		ll ans = inf;
		if(k>0){
			a = aux[0];
			//~ printf("oi\n");
			if(a > 1) ans = min(ans, query(1, 1, n, 1, a-1, x));
			a = aux.back();
			if(a < n) ans = min(ans, query(1, 1, n, a+1, n, x));
			
			for(int i=1; i<aux.size(); i++){
				if(aux[i] == aux[i-1]+1) continue;
				ans = min(ans, query(1, 1, n, aux[i-1]+1, aux[i]-1, x));
			}
		}else ans = query(1, 1, n, 1, n, x);
		printf("%lld\n", ans);
	}
	
	
}
