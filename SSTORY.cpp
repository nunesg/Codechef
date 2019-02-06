#include <bits/stdc++.h>

using namespace std;

#define N 500500
#define inf 10101010
#define M 20

int n, SA[N], tmpSA[N], R[N], tmpR[N], cont[N], id[N], lcp[N], inv[N], st[N<<2], lazy[N<<2], table[N][M];
string s;

void radix(int k){
	int maxi = max(300, n);
	memset(cont, 0, sizeof cont);
	
	for(int i=0; i<n; i++) {
		cont[ i+k < n ? R[i+k] : 0 ]++;
	}
	
	for(int i=1; i<maxi; i++) cont[i]+=cont[i-1];
	
	for(int i=n-1; i>=0; i--){
		tmpSA[ --cont[SA[i]+k < n ? R[SA[i]+k] : 0 ] ] = SA[i];
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
	
	//~ for(int i=0; i<n; i++){
		//~ printf("%2d: ", i); cout << s.substr(SA[i]) << endl;
	//~ }
}

void build_lcp(){
	int L=0;
	for(int i=0; i<n; i++){
		inv[SA[i]] = i;
	}
	
	for(int i=0; i<n; i++){
		if(inv[i] == 0){
			lcp[0] = 0;
			continue;
		}
		
		int prev = SA[inv[i]-1];
		while(i+L<n && prev+L<n && s[i+L] == s[prev+L]) L++;
		
		lcp[inv[i]] = L;
		L = max(L-1, 0);
	}
	//~ for(int i=0; i<n; i++){
		//~ printf("lcp[%d] = %d\n", i, lcp[i]);
	//~ }
}

void build_table(){
	for(int i=0; i<n; i++) {
		table[i][0] = lcp[i];
		//~ printf("table[%d][0] = %d\n", i, table[i][0]);
	}
	for(int j=1; j<M; j++){
		for(int i=0; i+(1<<j)<=n; i++){
			table[i][j] = min(table[i][j-1], table[i+(1<<(j-1))][j-1]);
			//~ printf("table[%d][%d] = %d\n", i, j, table[i][j]);
		}
	}
}

int query_min(int l , int r){
	int k = 31 - __builtin_clz(r-l+1);
	//~ printf("[%d, %d], log2 = %d\n", l, r, k);
	
	return min(table[l][k], table[r-(1<<k)+1][k]);
}

void build_st(int p, int l, int h){
	if(l == h){
		st[p] = -1;
		lazy[p] = -1;
		return;
	}
	
	int mid = (l+h)>>1, nxt = p<<1;
	
	build_st(nxt, l, mid);
	build_st(nxt+1, mid+1, h);
	st[p] = -1;
}

void do_lazy(int p, int l, int h){
	
	if(lazy[p] == -1) return;
	
	int nxt = p<<1;
	
	st[p] = max(st[p], lazy[p]);
	if(l!=h){
		lazy[nxt] = max(lazy[nxt], lazy[p]);
		lazy[nxt+1] = max(lazy[nxt+1], lazy[p]);
	}
	lazy[p] = -1;
}

int query(int p, int l, int h, int a){
	
	do_lazy(p, l, h);
	
	if(l == h) return st[p];
	
	int mid = (l+h)>>1, nxt = p<<1;
	
	if(a<=mid) return query(nxt, l, mid, a);
	return query(nxt+1, mid+1, h, a);
	
}

void update(int p, int l, int h, int a, int b, int v){
	
	do_lazy(p, l, h);
	
	if(h<a || l>b) return;
	if(a<=l && b>=h){
		lazy[p] = v;
		do_lazy(p, l, h);
		return;
	}
	
	int mid = (l+h)>>1, nxt = p<<1;
	update(nxt, l, mid, a, b, v);
	update(nxt+1, mid+1, h, a, b, v);
	st[p] = max(st[nxt], st[nxt+1]);
}

void solve(){
	
	cont[0] = cont[1] = 0;
	
	
	int l, r = l = 0, w=0;
	int maior = 0, aux;
	
	while(1){
		
		if(w < 2){
			if(r == n) break;
			cont[id[SA[r]]]++;
			if(cont[id[SA[r++]]] == 1) w++;
		}else{
			
			aux = query_min(l+1, r-1);
			//~ printf("[%d, %d], aux = %d, maior = %d\n", l, r, aux, maior);
			if(aux >= maior){
				maior = aux;
				update(1, 0, n-1, l-1, r-1, maior);
			}
			
			cont[id[SA[l]]]--;
			if(cont[id[SA[l++]]] == 0) w--;
		}
	}
	
	string ans;
	int ini=inf;
	if(maior == 0){
		cout << 0 << endl;
		return;
	}
	
	for(int i=0; i<n; i++){
		if(id[SA[i]] == 0) continue;
		//~ printf("i = %d, SA = %d\n", i, SA[i]);
		if(query(1, 0, n-1, i) == maior) {
			//~ printf("ini = %d, passa a ser %d\n", ini, min(ini, SA[i]));	
			ini = min(ini, SA[i]);
		}
	}
	
	ans = s.substr(ini, maior);
	cout << ans << "\n" << maior << endl;
}



int main(){
	
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	string a;
	getline(cin, a);
	s = a+"$";
	getline(cin, a);
	s+= a+"#";
	n = s.size();
	int c=0;
	for(int i=0; i<n; i++){
		id[i] = c;
		if(s[i]=='$') c++;
	}
	
	
	
	build_SA();
	build_lcp();
	build_table();
	build_st(1, 0, n-1);
	
	solve();
	
}
