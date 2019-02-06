#include <bits/stdc++.h>

using namespace std;

#define N 40020
#define block 222
#define M 20
#define BLACK 1

struct qry{
	char op;
	int u, v, id;
};


int n, q, cor[N], vet[N], h[N], lca[N][M], bup[N], answer[N], min_dist;
vector<int> adj[N], black;
multiset<int> Ms, Diffs, maux, daux;
vector<qry> Q[N], qvtx[N];

int dfs(int u, int p){
	h[u] = h[p]+1;
	lca[u][0] = p;
	
	for(int i=1; i<M; i++) lca[u][i] = lca[lca[u][i-1]][i-1];
	
	int maxh=0;
	for(int v : adj[u]){
		if(v == p) continue;
		dfs(v, u);
		maxh = max(maxh, dfs(v, u)+1);
	}
	
	if(maxh>=block || u==1) {
		cor[u] = BLACK;
		black.push_back(u);
		return 0;
	}
	return maxh;
}

void build_up(){
	for(int i=1; i<=n; i++){
		int x = i;
		while(!cor[x]) {
			x = lca[x][0];
		}
		
		bup[i] = x;
		//~ printf("bup[%d] = %d\n", i, bup[i]);
	}
}

int get_lca(int u, int v){
	if(h[u]<h[v]) swap(u, v);
	int d = h[u]-h[v];
	
	for(int i=0; i<M; i++) if(d&(1<<i)) u = lca[u][i];
	if(u == v) return u;
	for(int i = M-1; i>=0; i--){
		if(lca[u][i] != lca[v][i]){
			u = lca[u][i];
			v = lca[v][i];
		}
	}
	return lca[u][0];
}

int get_dist(int u, int v){
	return h[u] + h[v] - 2*h[get_lca(u, v)];
}

void add(int u, multiset<int> &ms, multiset<int> &diffs){
	int val = vet[u];
	if(ms.empty()) {
		ms.insert(val);
		return;
	}
	
	auto ub = ms.upper_bound(val);
	
	if(ub == ms.end()) diffs.insert(val-*ms.rbegin());//insere no final
	else if(ub == ms.begin()) diffs.insert(*ms.begin() - val);//insere no inicio
	else{
		auto lb = prev(ms.upper_bound(val));
		diffs.erase(diffs.find(*ub - *lb));
		diffs.insert(val - *lb);
		diffs.insert(*ub - val);
	}
	ms.insert(val);
}

void remove(int u, multiset<int> &ms, multiset<int> &diffs){
	int val = vet[u];
	if(ms.size() == 1) {
		ms.clear();
		return;
	}
	
	auto ub = ms.upper_bound(val);
	
	ms.erase(ms.find(val));
	
	if(ub == ms.end()) diffs.erase(diffs.find(val-*ms.rbegin()));//tava no final
	else if(ub == ms.begin()) diffs.erase(diffs.find(*ms.begin() - val));//tava no inicio
	else{
		auto lb = prev(ms.upper_bound(val));
		diffs.erase(diffs.find(val - *lb));
		diffs.erase(diffs.find(*ub - val));
		diffs.insert(*ub - *lb);
	}
}


int solve_bruta(int u, int v, char op){
	
	int lc = get_lca(u, v);
	
	
	Diffs.clear();
	Ms.clear();
	
	if(h[u]<h[v]) swap(u, v);
	while(h[u]>h[v]) {
		add(u, Ms, Diffs);
		u = lca[u][0];
	}
	while(u != v){
		add(u, Ms, Diffs);
		add(v, Ms, Diffs);
		u = lca[u][0];  v = lca[v][0];
	}
	
	add(u, Ms, Diffs);
	
	if(op == 'C'){
		return *Diffs.begin();
	}else	return *Ms.rbegin() - *Ms.begin();
	
	
}

void sobe(int u, int id, char op){
	maux.clear();
	daux.clear();
	
	int mdist = INT_MAX;
	while(!cor[u]){
		add(u, maux, daux);
		
		
		auto ub = Ms.upper_bound(vet[u]);
		if(ub == Ms.end()){
			mdist = min(mdist, vet[u] - *Ms.rbegin());
		}else
		if(ub == Ms.begin()){
			mdist = min(mdist, *Ms.begin() - vet[u]);
		}else{
			auto lb = prev(ub);
			mdist = min(mdist, *ub - vet[u]);
			mdist = min(mdist, vet[u] - *lb);
		}
		
		u = lca[u][0];
	}
	
	if(op == 'C'){
		answer[id] = min(answer[id], min(mdist, (daux.size() ? *daux.begin() : INT_MAX)));
	}else{
		answer[id] = max(answer[id], max(*maux.rbegin() - *maux.begin(), max(*Ms.rbegin() - *maux.begin(), *maux.rbegin() - *Ms.begin())));
	}
}

void go(int u, int p){
	add(vet[u], Ms, Diffs);
	for(qry x : qvtx[u]){
		
		int v = x.u;
		
		if(x.op == 'C') answer[x.id] = (Diffs.size() ? *Diffs.begin() : INT_MAX);
		else answer[x.id] = *Ms.rbegin() - *Ms.begin();
		
		sobe(v, x.id, x.op);
	}
	
	for(int v : adj[u]){
		if(v == p) continue;
		go(v, u);
	}
	
	remove(vet[u], Ms, Diffs);
}	
	
void solve(){
	
	
	for(int b : black){
		
		Ms.clear();
		Diffs.clear();
		for( qry x : Q[b]){
			qvtx[x.v].push_back(x);
		}
		
		go(b, b);
		
		for( qry x : Q[b]){
			qvtx[x.v].pop_back();
		}
	}
}


int main(){
	
	scanf("%d", &n);
	
	for(int i=1; i<=n; i++) scanf("%d", &vet[i]);
	int a, b;
	for(int i=1; i<n; i++){
		scanf("%d %d", &a, &b);
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	
	dfs(1, 1);
	//~ printf("oi\n");
	build_up();
	
	char op;
	int u, v;
	
	scanf("%d", &q);
	
	for(int i=0; i<q; i++){
		scanf(" %c %d %d", &op, &u, &v);
		
		if(get_dist(u, v)<=2*block){
			answer[i] = solve_bruta(u, v, op);
			continue;
		}
		
		if(h[u]<h[v]) swap(u, v);
		
		Q[bup[u]].push_back({op, u, v, i});
	}
	
	solve();
	
	for(int i=0; i<q; i++){
		printf("%d\n", answer[i]);
	}
	
}
