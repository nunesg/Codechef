#include <bits/stdc++.h>

using namespace std;

#define N 101010
#define block 250
#define div Div

int n, m, v[N], freq[N/block+2][N], blc[N], compress[N], sinal[N];
vector<int> div[N];

void build(){
	
	for(int i=1; i<N; i++){
		
		int x= i;
		int ans=1, cnt=0;
		
		for(int j=2; j*j<=x; j++){
			if(x%j) continue;
			ans*=j;
			cnt++;
			while(x%j == 0) x/=j;
		}
		ans*=x;
		cnt+= x>1;
		compress[i] = ans;
		sinal[i] = (cnt%2) ? 1 : -1;
		//~ if(i<20) printf("sinal[%d] = %d\n", i, sinal[i]);
		x= compress[i];
		for(int j=1; j*j<=x; j++){
			if(x%j) continue;
			if(j>1) div[i].push_back(j);
			if(j*j!=x){
				div[i].push_back(x/j);
			}
		}
	}
	
	
	for(int i=1; i<=n; i++){
		for(int x : div[v[i]]) freq[blc[i]][x]++;
	}
}


void update(int pos, int val){
	for(int x : div[v[pos]]) freq[blc[pos]][x]--;
	v[pos] = val;
	for(int x : div[v[pos]]) freq[blc[pos]][x]++;
}




int query(int l, int r, int val){
	
	if(blc[l] == blc[r]){
		int ans=0;
		while(l<=r) ans+= __gcd(v[l++], val) == 1;
		return ans;
	}
	
	int ans=0;
	for(int x : div[val]){
		for(int i=l; blc[i] == blc[l]; i++) ans+= (v[i]%x == 0)*sinal[x];
		for(int i=r; blc[i] == blc[r]; i--) ans+= (v[i]%x == 0)*sinal[x];
		
		for(int b = blc[l]+1; b<blc[r]; b++) ans+= freq[b][x]*sinal[x];
	}
	return (r-l+1)-ans;
}

int main(){
	
	scanf("%d", &n);
	
	for(int b=0, i=1; i<=n; b++){
		for(int k=0; k<block && i<=n; k++, i++){
			scanf("%d", &v[i]);
			blc[i] = b;
		}
	}
	
	
	build();
	
	int op, l, r, x, y;
	
	scanf("%d", &m);
	
	for(int i=0; i<m; i++){
		
		scanf("%d", &op);
		if(op == 1){
			scanf("%d %d", &x, &y);
			update(x, y);
		}else{
			scanf("%d %d %d", &l, &r, &x);
			printf("%d\n", query(l, r, x));
		}
	}
	
	
}
