#include <bits/stdc++.h>

using namespace std;

#define N 101010
#define M 19

typedef long long ll;

struct qry{
	int l, r, id;
};

int n, q, v[N], table[N][M];
ll st[N<<2], lazy[N<<2];
ll answer[N*5];
vector<int> val[N];
unordered_map<int, int> sq;
qry Q[N*5];

void build_val(){
	for(int i=1; i<=n; i++){
		val[i].clear();
		val[i].push_back(v[i]);
		if(i==1) continue;
		
		for(int x : val[i-1]){
			val[i].push_back(x&v[i]);
		}
		
		sort(val[i].begin(), val[i].end());
		val[i].resize(distance(val[i].begin(), unique(val[i].begin(), val[i].end())));
	}
}

void build_table(){
	for(int i=1; i<=n; i++) table[i][0] = v[i];
	
	for(int j=1; j<M; j++){
		for(int i=1; i+(1<<j)<=n+1; i++){
			table[i][j] = table[i][j-1] & table[i+(1<<(j-1))][j-1];
		}
	}
}

int get_and(int l, int r){
	int k = 31 - __builtin_clz(r-l+1);
	return table[l][k] & table[r-(1<<k)+1][k];
}

void build_st(int p, int l, int r){
	if(l == r){
		st[p] = lazy[p] = 0;
		return;
	}
	
	int mid = (l+r)>>1, nxt = p<<1;
	build_st(nxt, l, mid);
	build_st(nxt+1, mid+1, r);
	st[p]=lazy[p] = 0;
}

void push(int p, int l, int r){
	if(!lazy[p]) return;
	
	int nxt = p<<1;
	st[p]+= (r-l+1LL)*lazy[p];
	if(l!=r){
		lazy[nxt]+=lazy[p];
		lazy[nxt+1]+=lazy[p];
	}
	lazy[p]=0;
}

void update(int p, int l, int r, int a, int b, int x){
	push(p, l, r);
	
	if(r<a || l>b) return;
	if(a<=l && b>=r){
		lazy[p] = x;
		push(p, l, r);
		return;
	}
	
	int mid = (l+r)>>1, nxt = p<<1;
	update(nxt, l, mid, a, b, x);
	update(nxt+1, mid+1, r, a, b, x);
	st[p] = st[nxt]+st[nxt+1];
}

ll query(int p, int l, int r, int a, int b){
	push(p, l, r);
	if(r<a || l>b) return 0;
	if(a<=l && b>=r) return st[p];
	
	int mid = (l+r)>>1, nxt = p<<1;
	return query(nxt, l, mid, a, b) + query(nxt+1, mid+1, r, a, b);
}


void go(int x, int p){
	
	int l=0, r=0;
	if(sq.count(x) == 0) return;
	
	for(int j=M-1; j>=0; j--){
		if(l+(1<<j)>p) continue;
		if(get_and(l+(1<<j), p) < x) l+=(1<<j);
	}
	l++;
	
	for(int j=M-1; j>=0; j--){
		if(r+(1<<j)>p) continue;
		if(get_and(r+(1<<j), p) <= x) r+=(1<<j);
	}
	update(1, 1, n, l, r, 1);
}

void add(int p){
	
	for(int x : val[p]){
		go(x, p);
	}
}

void solve(){
	
	int id=0;
	build_st(1, 1, n);
	
	for(int i=1; id<q; ){
		
		while(i<=Q[id].r) {
			add(i++);
		}
		
		answer[Q[id].id] = query(1, 1, n, Q[id].l, Q[id].r);
		id++;
	}
}


int main(){
	
	int tc;
	for(int i=0; i*1LL*i<=(1LL<<30); i++) sq[i*i] = 1;
	
	scanf("%d", &tc);
	
	while(tc--){
		
		scanf("%d %d", &n, &q);
		
		for(int i=1; i<=n; i++){
			scanf("%d", &v[i]);
		}
		
		build_val();
		build_table();
		
		for(int i=0; i<q; i++){
			scanf("%d %d", &Q[i].l, &Q[i].r);
			Q[i].id = i;
		}
		
		sort(Q, Q+q, [](qry a, qry b){
			return a.r<b.r;
		});
		
		solve();
		for(int i=0; i<q; i++) printf("%lld\n", answer[i]);
		
	}
}
