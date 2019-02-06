#include <bits/stdc++.h>

using namespace std;

#define N 101010
#define BLOCK 777
#define F first
#define S second


int n, m, v[N], aux[N], blc[N], seen[N];
vector<int> vet[N/BLOCK+2];
vector<int> upd;

void build(){
	for(int b=0; b<=blc[n]; b++) vet[b].clear();
	for(int i=1; i<=n; i++){
		if(aux[i]) v[i] = aux[i];
		
		vet[blc[i]].push_back(v[i]);
	}
	for(int b=0; b<=blc[n]; b++) sort(vet[b].begin(), vet[b].end());
}

int query(int l, int r, int x){
	int ans=0;
	if(r-l+1 <= BLOCK){
		for(int i=l; i<=r; i++){
			if(v[i]<=x) ans++;
		}
		return ans;
	}
	int bl = blc[l], br = blc[r];
	for(int i=l; blc[i] == bl; i++) ans+= v[i]<=x;
	for(int i=r; blc[i] == br; i--) ans+= v[i]<=x;
	
	for(int b=bl+1; b<br; b++) ans+= upper_bound(vet[b].begin(), vet[b].end(), x) - vet[b].begin();
	return ans;
}


int main(){
	
	scanf("%d %d", &n, &m);

	int ind=1;
	for(int b=0; ind<=n; b++){	
		for(int k=0; ind<=n && k<BLOCK; ind++, k++){
			blc[ind] = b;
			scanf("%d", &v[ind]);
		}
	}
	
	
	int t, a, b, c;
	
	ind = 1;
	for(int bl=0; ind<=m; bl++){
		
		int old_ind = ind;
		build();
		upd.clear();
		memset(aux, 0, sizeof aux);
		for(int k=0; k<BLOCK && ind<=m; k++, ind++){
			scanf("%d", &t);
			if(t == 1){
				scanf("%d %d", &a, &b);
				upd.push_back(a);
				aux[a] = b;
			}else{
				scanf("%d %d %d", &a, &b, &c);
				
				int ans = query(a, b, c);
				//~ printf("[%d, %d] x=%d, ans = %d\n", a, b, c, ans);
				for(int pos : upd){
					if(!seen[pos] && v[pos] <= c && aux[pos] > c && a<=pos && b>=pos) ans--;
					if(!seen[pos] && v[pos] > c && aux[pos] <= c && a<=pos && b>=pos) ans++;
					seen[pos] = 1;
				}
				for(int pos : upd){
					seen[pos] = 0;
				}
				printf("%d\n", ans);
			}
		}
	}
	
}
