#include <bits/stdc++.h>

using namespace std;

#define N 101010
#define M 55

typedef long long ll;

vector<int> st[N<<2];

int n, q, v[N];
vector<int> aux;


void build(int p, int l, int r){
	if(l == r){
		st[p].push_back(v[l]);
		return;
	}
	
	int mid = (l+r)>>1, nxt = p<<1;
	
	build(nxt, l, mid);
	build(nxt+1, mid+1, r);
	
	st[p].resize(st[nxt].size()+st[nxt+1].size());
	merge(st[nxt].begin(), st[nxt].end(), st[nxt+1].begin(), st[nxt+1].end(), st[p].begin(), greater<int>());
	if(st[p].size() > M) st[p].resize(M);
}

void update(int p, int l, int r, int a, int b){
	
	if(l == r){
		st[p].clear();
		st[p].push_back(b);
		return;
	}
	int mid = (l+r)>>1, nxt = p<<1;
	
	if(a<=mid) update(nxt, l, mid, a, b);
	else update(nxt+1, mid+1, r, a, b);
	
	st[p].resize(st[nxt].size()+st[nxt+1].size());
	merge(st[nxt].begin(), st[nxt].end(), st[nxt+1].begin(), st[nxt+1].end(), st[p].begin(), greater<int>());
	if(st[p].size() > M) st[p].resize(M);
}

void join(vector<int> &x){
	vector<int> o(aux.size()+x.size());
	merge(aux.begin(), aux.end(), x.begin(), x.end(), o.begin(), greater<int>());
	aux = o;
}


void query(int p, int l, int r, int a, int b){
	if(r<a || l>b) return;
	if(a<=l && b>=r){
		join(st[p]);
		return;
	}
	
	int mid = (l+r)>>1, nxt = p<<1;
	query(nxt, l, mid, a, b);
	query(nxt+1, mid+1, r, a, b);
}


int main(){
	
	
	scanf("%d %d", &n, &q);
	
	for(int i=1; i<=n; i++) scanf("%d", &v[i]);
	
	build(1, 1, n);
	
	int op, l, r;
	while(q--){
		
		scanf("%d %d %d", &op, &l, &r);
		
		if(op == 1){
			update(1, 1, n, l, r);
		}else{
			aux.clear();
			query(1, 1, n, l, r);
			ll ans=0;
			for(int i=0; i+2 < aux.size(); i++){
				if(aux[i] < aux[i+1] + aux[i+2]) {
					ans = aux[i]+aux[i+1]+(ll)aux[i+2];
					break;
				}
			}
			printf("%lld\n", ans);
		}
	}
}
