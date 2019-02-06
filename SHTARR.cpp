#include <bits/stdc++.h>

using namespace std;

#define N 1000100
#define BLOCK 1000
#define gc getchar

void scanint(int &x)
{
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}



int n, q, v[N], blc[N], ini[N/BLOCK+2], maior[N/BLOCK+2], qtd[N/BLOCK+2][N/BLOCK+2];
vector<int> vblock[N/BLOCK+2];

void build_block(int b, int l, int r, bool isbuild){
	
	vblock[b].clear();
	maior[b] = 0;
	for(int i=l; i<=r; i++){
		maior[b] = max(maior[b], v[i]);
		if(!vblock[b].size() || v[i] > vblock[b].back()) {
			vblock[b].push_back(v[i]);
		}
	}
	
	for(int i=b-1; i>=1; i--){
		qtd[b][i] = vblock[b].end() - upper_bound(vblock[b].begin(), vblock[b].end(), maior[i]);
	}
	
	if(!isbuild){
		for(int i=blc[n]; i>b; i--){
			qtd[i][b] = vblock[i].end() - upper_bound(vblock[i].begin(), vblock[i].end(), maior[b]);
		}
	}
}


int query(int p, int l, int r){
	
	int b = blc[p];
	
	int ans = 0, h=l;
	
	
	int lst=n;
	for(int i=p; blc[i] == b; i++){
		if(v[i]>=h){
			h = v[i]+1;
			ans++;
			lst = blc[i];
		}
		if(h>r) return ans;
	}
	for(b = b+1; b<=blc[n]; b++) {
		if(maior[b]>=h) {
			lst = b;
			break;
		}
	}
	if(lst == n) return ans;
	
	for(int i = ini[lst]; blc[i]==lst; i++){
		if(v[i]>=h){
			h = v[i]+1;
			ans++;
		}
		if(h>r) return ans;
	}
	
	for(b = lst+1; b<=blc[n]; b++){
		if(maior[b] < h) continue;
		if(maior[b] >= r) break;
		
		ans+= qtd[b][lst];
		h = maior[b]+1;
		lst = b;
	}
	
	if(b == blc[n]+1) return ans;
	
	for(int i=ini[b]; blc[i] == b; i++){
		if(v[i]>=h){
			h = v[i]+1;
			ans++;
		}
		if(h>r) return ans;
	}
	return ans;
}


int main(){
	
	int tc;
	scanint(tc);
	while(tc--){
		
		scanint(n);scanint(q);
		
		for(int i=1, b=1; i<=n; b++){
			ini[b] = i;
			for(int k=0; k<BLOCK && i<=n; i++, k++){
				scanint(v[i]);
				blc[i] = b;
			}
		}
		
		for(int b=1; b<=blc[n]; b++) build_block(b, ini[b], min(ini[b]+BLOCK-1, n), true);
		
		char op;
		int p, x, l, r;
		
		while(q--){
			scanf(" %c", &op);
			scanint(p);
			if(op == '?'){
				scanint(l);scanint(r);
				
				printf("%d\n", query(p, l, r));
				
			}else{
				scanint(x);
				v[p]+=x;
				build_block(blc[p], ini[blc[p]], min(ini[blc[p]]+BLOCK-1, n), false);
			}
		}
		
	}
}
