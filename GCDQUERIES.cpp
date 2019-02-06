#include <bits/stdc++.h>

using namespace std;

#define N 101010
#define M 20

int n, m, table[N][M];

int gcd(int a, int b) { return b == 0 ? a : gcd(b, a%b); }

void build(){
	
	for(int j=1; j<M; j++){
		
		for(int i=0; i + (1<<j) <=n; i++){
			table[i][j] = gcd(  table[i][j-1],  table[i+(1<<(j-1))][j-1]  );
		}
	}
}

int query(int l, int r){
	//~ if(l>r) return 1;
	int x = r-l+1, k = floor(log2(x));
	return gcd(  table[l][k],  table[l+x-(1<<k)][k]  );
}

int main(){
	
	int t;
	scanf("%d", &t);
	
	while(t--){
		scanf("%d%d", &n, &m);
		for(int i=0; i<n; i++) scanf("%d", &table[i][0]);
		
		int a, b;
		build();
		
		while(m--){
			scanf("%d %d", &a, &b);
			a--; b--;
			int l = (a) ? query(0, a-1) : -1;
			int r = (b<n-1) ? query(b+1, n-1) : -1;
			int ans = (l==-1) ? r : (r==-1) ? l : gcd(l, r);
			printf("%d\n", ans);
		}
	}
	
}
