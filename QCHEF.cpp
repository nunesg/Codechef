#include <bits/stdc++.h>
 
using namespace std;
 
#define N 101010
#define BLOCK 222

struct query{
	int l, r, id;
};
 
int n, m, q, v[N], blc[N], ini[N/BLOCK+2], answer[N], f[N], lst[N];
int ans_block[N/BLOCK+2][N], last_in_block[N/BLOCK+2][N];
vector<query> Q;


void build(){
	int ind = 1;
	for(int bl=0; ind<=n; bl++){
		ini[bl] = ind;
		int old_ind = ind;
		for(int k=0; ind<=n && k<BLOCK; k++, ind++){
			blc[ind] = bl;
			last_in_block[bl][v[ind]] = ind;
		}
		int ans=0;
		for(int i=old_ind; i<=n; i++){
			if(!f[v[i]]) f[v[i]] = i;
			ans = max(ans, i-f[v[i]]);
			ans_block[bl][i] = ans;
		}
		
		for(int i=old_ind; i<=n; i++){
			f[v[i]]=0;
		}
	}
	
}


int solve_bruta(int l, int r){
	int ans=0;
	for(int i=l; i<=r; i++){
		if(!f[v[i]]) f[v[i]] = i;
		ans = max(ans, i-f[v[i]]);
	}
	for(int i=l; i<=r; i++){
		f[v[i]]=0;
	}
	return ans;
}

void solve(){
	int pos=1, ans, bl;
	memset(lst, 0, sizeof lst);
	for(query x : Q){
		
		bl = blc[x.l]+1;
		ans= ans_block[bl][x.r];
		for(; pos<=x.r; pos++) lst[v[pos]] = pos;
		
		
		int b = blc[x.l];
		for(int i = x.l; i<=x.r && blc[i]==b; i++){
			ans = max(ans, last_in_block[b][v[i]] - i);
			ans = max(ans, lst[v[i]] - i);
		}
		answer[x.id] = ans;
	}
}

int main(){
	
	scanf("%d %d %d", &n, &m, &q);
	
	for(int i=1; i<=n; i++){
		scanf("%d", &v[i]);
	}
	
	build();
	int l, r;
	for(int i=0; i<q; i++){
		
		scanf("%d %d", &l, &r);
		
		if(r-l+1 <= BLOCK) answer[i] = solve_bruta(l, r);
		else Q.push_back({l, r, i});
	}
	
	sort(Q.begin(), Q.end(), [](query a, query b){ return a.r < b.r; });
	solve();
	for(int i=0; i<q; i++) printf("%d\n", answer[i]);
}
