#include <bits/stdc++.h>

using namespace std;

#define N 18

int n, m, k, vet[N], freq[N<<1];
int add[N];

int maior(int l, int r){
	int ans=-1;
	for(int i=l; i<=r; i++) ans = max(ans, vet[i]+add[i]);
	return ans;
}

bool can(int mask){
	
	for(int i=0; i<N; i++) add[i] = (mask & (1<<i)) ? 1 : 0;
	memset(freq, 0, sizeof freq);
	
	int l=0, r;
	for(r=0; r<k; r++) freq[vet[r]+add[r]]++;
	if(freq[maior(l, r-1)]>=m) return false;
	
	while(r<n){
		freq[vet[r]+add[r++]]++;
		freq[vet[l]+add[l++]]--;
		if(freq[maior(l, r-1)]>=m) return false;
	}
	return true;
}

int main(){
	int tc;
	cin >> tc;
	while(tc--){
		
		cin >> n >> k >> m;
		
		for(int i=0; i<n; i++) cin >> vet[i];
		int ans = 1000;
		for(int mask = 0; mask<(1<<n); mask++){
			if(can(mask)) ans = min(ans, __builtin_popcount(mask));
		}
		
		if(ans == 1000) cout << -1 << endl;
		else cout << ans << endl;
	}
}
