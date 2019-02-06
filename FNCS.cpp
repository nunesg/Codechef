#include <bits/stdc++.h>

using namespace std;

#define N 101010
#define block 200
#define F first
#define S second

typedef pair<int, int> ii;
typedef unsigned long long ll;

struct no{
	int val, l, r;
}st[10101010];



int n, q, v[N], root[N], cnt, seen[N];
ll accv[N], accf[N];
ii f[N];
vector<ii> upd;

int update(int no1, int l, int r, int pos, int x){
	int no2 = cnt++;
	
	st[no2] = st[no1];
	
	if(l == r){
		st[no2].val+=x;
		return no2;
	}
	
	int mid = (l+r)>>1;
	if(pos<=mid) st[no2].l = update(st[no1].l, l, mid, pos, x);
	else st[no2].r = update(st[no1].r, mid+1, r, pos, x);
	
	st[no2].val = st[st[no2].l].val + st[st[no2].r].val;
	return no2;
}

int query_persistent(int no1, int l, int r, int a){
	if(l>a) return 0;
	if(r<=a) return st[no1].val;
	
	
	int mid = (l+r)>>1;
	return query_persistent(st[no1].l, l, mid, a) + query_persistent(st[no1].r, mid+1, r, a);
}


void build(){
	
	for(int i=1; i<=n; i++) accv[i] = accv[i-1]+v[i];
	for(int i=1; i<=n; i++){
		accf[i] = accf[i-1] + accv[f[i].S] - accv[f[i].F-1];
	}
}

int main(){
	
	
	scanf("%d", &n);
	
	for(int i=1; i<=n; i++){
		scanf("%d", &v[i]);
	}
	
	for(int i=1; i<=n; i++){
		scanf("%d %d", &f[i].F, &f[i].S);
	}
	
	
	root[0] = cnt++;
	
	for(int i=1; i<=n; i++){
		if(f[i].S<n) root[i] = update(update(root[i-1], 1, n, f[i].F, 1), 1, n, f[i].S+1, -1);
		else root[i] = update(root[i-1], 1, n, f[i].F, 1);
	}
	
	
	
	
	scanf("%d", &q);
	
	int ind = 1, type, x, y, u, h;
	
	for(int b=0; ind<=q; b++){
		
		build();
		upd.clear();
		
		for(int k=0; k<block && ind<=q; k++, ind++){
			
			scanf("%d %d %d", &type, &x, &y);
			
			if(type == 1) upd.push_back(ii(x, y));
			else{
				ll ans = accf[y] - accf[x-1];
				for(int i=(int)upd.size()-1; i>=0; i--){
					ii foo = upd[i];
					u = foo.F, h = foo.S;
					if(seen[u]) continue;
					seen[u]=1;
					int qtd = query_persistent(root[y], 1, n, u) - query_persistent(root[x-1], 1, n, u);
					ans-= qtd*1LL*v[u];
					ans+= qtd*1LL*h;
				}
				for(int i=(int)upd.size()-1; i>=0; i--){
					ii foo = upd[i];
					u = foo.F, h = foo.S;
					seen[u]=0;
				}
				printf("%llu\n", ans);
			}
		}
		
		for(ii foo : upd){
			v[foo.F] = foo.S;
		}
	}
}
