#include <bits/stdc++.h>

using namespace std;

#define N 101010
#define BLOCK 444


int n, q, v[N], blc[N], lazy[N/BLOCK+2], freq[N/BLOCK+2][N];

void add(int bl, int l, int r, int x){
	for(int i=l; i<=r; i++){
		freq[bl][v[i]]--;
		v[i] = (v[i]+x)%n;
		freq[bl][v[i]]++;
	}
}

void update(int l, int r, int x){
	
	int bl = blc[l], br = blc[r];
	
	add(bl, l, min((bl+1)*BLOCK - 1, r), x);
	if(bl == br)  return;
	add(br, br*BLOCK, r, x);
	
	for(int i=bl+1; i<br; i++) lazy[i]= (lazy[i]+x)%n;
}

int query(int l, int r, int x){
	if(r-l<=BLOCK){
		int ans=0;
		for(int i=l; i<=r; i++) ans+= (v[i]+lazy[blc[i]])%n == x;
		return ans;
	}
	int ans=0, bl = blc[l], br = blc[r];
	for(int i=l; blc[i]==bl; i++) ans+= (v[i]+lazy[bl])%n == x;
	for(int i=r; blc[i]==br; i--) ans+= (v[i]+lazy[br])%n == x;
	
	for(int i=bl+1; i<br; i++){
		ans+= freq[i][ (x-lazy[i]+n)%n ];
	}
	return ans;
}

int main(){
	
	scanf("%d %d", &n, &q);
	
	for(int i=0; i<n; i++){
		scanf("%d", &v[i]);
		blc[i] = i/BLOCK;
		freq[i/BLOCK][v[i]]++;
	}
	
	
	int t, l, r, x;
	
	for(int i=0; i<q; i++){
		scanf("%d %d %d %d", &t, &l, &r, &x);
		
		if(t == 1){
			update(l, r, x);
		}else{
			printf("%d\n", query(l, r, x));
		}
	}
	
}
