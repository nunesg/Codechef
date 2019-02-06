#include <bits/stdc++.h>

using namespace std;

#define N 101010

struct no{
	int sz, ini;
	no(){sz = ini = N;}
}st[N<<2], lazy[N<<2];

int n, SA[N], tmpSA[N], R[N], tmpR[N], lcp[N], inv[N], cont[N];
string s;

void do_lazy(int p, int l, int h){
	if(lazy[p].sz == N) return;
	
	if(st[p].sz > lazy[p].sz)
		st[p] = lazy[p];
	
	int nxt = (p<<1);
	if(l!=h){
		if(lazy[nxt].sz > lazy[p].sz) lazy[nxt] = lazy[p];
		if(lazy[nxt+1].sz > lazy[p].sz) lazy[nxt+1] = lazy[p];
	}
	lazy[p].sz = N;
}

void update(int p, int l, int h, int a, int b){
	do_lazy(p, l, h);
	
	if(h<a || l>b) return;
	
	if(a<=l && b>=h){
		lazy[p].sz = b-a+1;
		lazy[p].ini = a;
		do_lazy(p, l, h);
		return;
	}
	
	int mid = (l+h)>>1, nxt = p<<1;
	
	update(nxt, l, mid, a, b);
	update(nxt+1, mid+1, h, a, b);
	
	if(st[nxt].sz > st[p].sz) st[p] = st[nxt];
	if(st[nxt+1].sz > st[p].sz) st[p] = st[nxt+1];
}

no query(int p, int l, int h, int a){
	do_lazy(p, l, h);
	
	if(l == h)
		return st[p];
	
	int mid = (l+h)>>1, nxt = p<<1;
	
	if(a<=mid) return query(nxt, l, mid, a);
	return query(nxt+1, mid+1, h, a);
}

void radix(int k){
	int maxi = max(n, 300);
	memset(cont, 0, sizeof cont);
	
	for(int i=0; i<n; i++){
		cont[i+k < n ? R[i+k] : 0]++;
	}
	
	for(int i=1; i<maxi; i++) cont[i]+=cont[i-1];
	
	for(int i=n-1; i>=0; i--){
		tmpSA[ --cont[SA[i]+k < n ? R[SA[i]+k] : 0] ] = SA[i];
	}
	for(int i=0; i<n; i++) SA[i] = tmpSA[i];
}

void build_SA(){
	for(int i=0; i<n; i++){
		SA[i] = i;
		R[i] = s[i];
	}
	
	for(int k=1; k<n; k<<=1){
		radix(k);
		radix(0);
		
		int r = 0;
		tmpR[SA[0]] = 0;
		for(int i=1; i<n; i++){
			tmpR[SA[i]] = (R[SA[i]] == R[SA[i-1]] && R[SA[i]+k] == R[SA[i-1]+k]) ? r : ++r;
		}
		
		for(int i=0; i<n; i++) R[SA[i]] = tmpR[SA[i]];
		if(R[SA[n-1]] == n-1) break;
	}
	for(int i=0; i<n; i++){
		cout << s.substr(SA[i]) << endl;
	}
}

void build_lcp(){
	int L=0;
	for(int i=0; i<n; i++) inv[SA[i]] = i;
	for(int i=0; i<n; i++){
		if(inv[i] == 0){
			lcp[inv[i]] = 0;
			continue;
		}
		
		int prev = SA[inv[i]-1];
		
		while(i+L < n && prev+L < n && s[i+L] == s[prev+L]) L++;
		
		lcp[inv[i]] = L;
		L = max(L-1, 0);
	}
	for(int i=0; i<n; i++)
	printf("%2d: %d\n", i, lcp[i]);
}


void solve(){
	
	
	for(int i=1; i<n; i++){
		if(SA[i]+lcp[i]+1 >= n-1 || (i<n-1 && SA[i]+lcp[i+1]+1 >= n-1)) continue;
		
		
		
		int lc = max(lcp[i], i<n-1 ? lcp[i+1] : 0);
		
		printf("oi  i=%d,   [%d, %d]\n", i, SA[i], SA[i]+lc);
		
		update(1, 0, n-1, SA[i], SA[i]+lc);
	}
	
	
}

int main(){
	//~ ios_base::sync_with_stdio(0); cin.tie(0);
	getline(cin, s);
	s+="$";
	n = s.size();
	
	build_SA();
	build_lcp();
	
	solve();
	no q;
	for(int i=0; i<n-1; i++){
		q = query(1, 0, n-1, i);
		cout << q.ini+1 << " " << q.sz << endl;
		//~ cout << s.substr(SA[query(1, 0, n-1, i)], 
	}
}
