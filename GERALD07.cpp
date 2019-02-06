#include <bits/stdc++.h>

using namespace std;

#define N 201010
#define block 450
#define F first
#define S second

typedef pair<int, int> ii;

struct dsu{
	
	vector<int> comp;
	int n;
	
	void resize(int sz){
		comp.resize(sz+1);
		n= sz+1;
		for(int i=1; i<=sz; i++) comp[i] = i;
	}
	
	int find(int i){ return comp[i] == i ? i : comp[i] = find(comp[i]); }
	
	void join(int i, int j){ comp[find(i)] = find(j); }
	
	bool same(int i, int j){ return find(i) == find(j); }
};


struct query{
	int l, r, id;
};

int n, m, q, ini[N], blc[N], answer[N], mapa[N], seen[N];
dsu ds, daux;
ii E[N];
vector<query> Q[N];

int solve_bruta(int l, int r){
	
	int ans=n;
	for(int i=l; i<=r; i++){
		int u = E[i].F, v = E[i].S;
		if(!ds.same(u, v)) {
			ds.join(u, v);
			ans--;
		}
	}
	for(int i=l; i<=r; i++){
		int u = E[i].F, v = E[i].S;
		ds.comp[u] = u;
		ds.comp[v] = v;
	}
	return ans;
}


int solve_left(int l, int r){
	int cnt=1;
	for(int i=l; i<=r; i++){
		int u = ds.find(E[i].F), v = ds.find(E[i].S);
		if(!seen[u]) mapa[u] = cnt++, seen[u]=1;
		if(!seen[v]) mapa[v] = cnt++, seen[v]=1;
	}
	cnt--;
	daux.resize(cnt);
	int ans=0;
	for(int i=l; i<=r; i++){
		int u = mapa[ds.find(E[i].F)], v = mapa[ds.find(E[i].S)];
		if(!daux.same(u, v)){
			daux.join(u, v);
			ans++;
		}
	}
	for(int i=l; i<=r; i++){
		int u = ds.find(E[i].F), v = ds.find(E[i].S);
		seen[u] = 0; seen[v] = 0;
	}
	return ans;
}

void solve(){
	
	for(int b=0; b<=blc[m]; b++){
		
		ds.resize(n);
		sort(Q[b].begin(), Q[b].end(), [](query a, query b){ return a.r < b.r; });
		int ind = ini[b], qtd=n;
		
		for(query x : Q[b]){
			while(ind<=x.r){
				int u = E[ind].F, v = E[ind++].S;
				if(!ds.same(u, v)){
					ds.join(u, v);
					qtd--;
				}
			}
			
			answer[x.id] = qtd - solve_left(x.l, ini[b]-1);
		}
	}
}

int main(){
	
	
	int tc;
	scanf("%d", &tc);
	while(tc--){
		
		scanf("%d %d %d", &n, &m, &q);
		
		ds.resize(n+1);
		
		for(int i=1; i<=m; i++) Q[i].clear();
		
		for(int i=1; i<=m; i++){
			scanf("%d %d", &E[i].F, &E[i].S);
		}
		
		for(int ind=1, b=0; ind<=m; b++){
			ini[b] = ind;
			for(int k=0; k<block && ind<=m; k++, ind++){
				blc[ind] = b;
			}
		}
		
		
		int l, r;
		for(int i=0; i<q; i++){
			scanf("%d %d", &l, &r);
			
			if(r-l+1 <= block) answer[i] = solve_bruta(l, r);
			else{
				Q[blc[l]+1].push_back({l, r, i});
			}
		}
		
		solve();
		
		
		for(int i=0; i<q; i++) printf("%d\n", answer[i]);
	}
}
