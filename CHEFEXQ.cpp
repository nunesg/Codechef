#include <bits/stdc++.h>

using namespace std;

#define N 101010
#define block 444

int n, m, v[N], xsum[N/block+2];
int blc[N], ini[N/block+2];
unordered_map<int, int> mapa[N/block+2];

void build_block(int bl){
	int ind = ini[bl];
	int x=0;
	mapa[bl].clear();
	for(int k=0; k<block && ind<=n; k++, ind++){
		blc[ind] = bl;
		x^=v[ind];
		//~ printf("mapa[%d][%d]++\n", bl, x);
		mapa[bl][x]++;
	}
	xsum[bl] = x;
}

void build(){
	int ind = 1;
	for(int bl = 0; ind<=n; bl++){
		ini[bl] = ind;
		build_block(bl);
		ind += block;
	}
}

void update(int pos, int x){
	v[pos] = x;
	build_block(blc[pos]);
}

int query(int pos, int k){
	
	int x=0, ans=0;
	for(int bl=0; bl<blc[pos]; bl++){
		//~ printf("ans+= mapa[%d].count(%d) = %d\n", bl, x^k, (int)mapa[bl].count(x^k));
		ans+= mapa[bl].count(x^k) ? mapa[bl][x^k] : 0;
		x^=xsum[bl];
	}
	//~ printf("ans = %d\n", ans);
	for(int i=ini[blc[pos]]; i<=pos; i++){
		x^=v[i];
		if(x == k) ans++;
	}
	return ans;
}

int main(){
	
	scanf("%d %d", &n, &m);
	
	for(int i=1; i<=n; i++){
		scanf("%d", &v[i]);
	}
	build();
	int t, x, y;
	for(int i=0; i<m; i++){
		scanf("%d %d %d", &t, &x, &y);
		
		if(t == 1){
			update(x, y);
		}else{
			printf("%d\n", query(x, y));
		}
	}
	
}
