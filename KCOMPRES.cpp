#include <bits/stdc++.h>

using namespace std;

#define N 101010
#define F first
#define S second

typedef long long ll;
typedef pair<int, int> ii;

int n, SOMA, v[N], st[N<<2], comp[N], mcomp[N];

void init(){
	for(int i=1; i<=n; i++){
		comp[i] = i;
		mcomp[i] = 0;
	}
}

int find(int i){ return i == comp[i] ? i : comp[i] = find(comp[i]); }

bool same(int i, int j){ return find(i) == find(j); }

void updcomp(int i, int val){
	int ci = find(i);
	mcomp[ci] = max(mcomp[ci], val);
}

void join(int i, int j){
	int ci = find(i), cj = find(j);
	comp[ci] = cj;
	updcomp(j, mcomp[ci]);
}

void update(int p, int l, int r, int pos, int val){
	
	if(l == r) {
		st[p] = val;
		return;
	}
	
	int mid = (l+r)>>1, nxt = p<<1;
	if(pos<=mid) update(nxt, l, mid, pos, val);
	else update(nxt+1, mid+1, r, pos, val);
	st[p] = max(st[nxt], st[nxt+1]);
}

int query(int p, int l, int r, int a,int b){
	if(r<a || l>b) return 0;
	if(a<=l && b>=r) return st[p];
	int mid = (l+r)>>1, nxt = p<<1;
	return max(query(nxt, l, mid, a, b), query(nxt+1, mid+1, r, a, b));
}



bool check(int k){
	
	ll s=0;
	vector<int> tmp, adj;
	for(int i=1; i<=n; i++) tmp.push_back(i);
	
	sort(tmp.begin(), tmp.end(), [](int a, int b){return v[a] != v[b] ? v[a]<v[b] : a<b;});
	
	init();
	memset(st, 0, sizeof st);
	
	int i, j;
	for(i=0, j=0; i<tmp.size(); ){
		
		while(j<tmp.size() && v[tmp[j]] == v[tmp[i]]){
			adj.push_back(tmp[j]);
			j++;
		}
		
		for(int x=0; x<adj.size(); x++){
			int pos = adj[x];
			int l = max(pos-k, 1), r = min(pos+k, n);
			int val = query(1, 1, n, l, r)+1;
			if(x && pos-adj[x-1] <= k) join(pos, adj[x-1]);
			updcomp(pos, val);
		}
		
		for(int x=0; x<adj.size(); x++){
			int pos = adj[x];
			update(1, 1, n, pos, mcomp[find(pos)]);
		}
		adj.clear();
		i = j;
	}
	
	for(int i=1; i<=n; i++){
		s+= mcomp[find(i)];
		if(s>SOMA) return false;
	}
	return true;
}


int solve(){
	int ini=0, fim=n, meio, ans=-1;
	
	while(ini<=fim){
		meio = (ini+fim)>>1;
		if(check(meio)){
			ans = meio;
			ini = meio+1;
		}else fim = meio-1;
	}
	
	return ans+1;
}


int main(){
	
	int tc;
	scanf("%d", &tc);
	
	while(tc--){
		
		scanf("%d %d", &n, &SOMA);
		
		for(int i=1; i<=n; i++) scanf("%d", &v[i]);
		
		printf("%d\n", solve());
	}
	
}
