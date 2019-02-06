#include <bits/stdc++.h>

using namespace std;

#define N 33

typedef long long int ll;

int n, vet[N], k, A, B, x[1<<17], aux[1<<17];
vector<int> v[N];

int nice(ll g){
	int ans = 1;
	for(ll i=2; i*i<=g; i++){
		if(g%i == 0) ans*=i;
		while(g%i == 0) g/=i;
	}
	if(g!=1) ans*=g;
	return ans;
}


ll solve(){
	ll ans = 0;
	x[0] = 0;
	for(int i=1; i<(1<< min(16, n)); i++){
		x[i] = x[i^(i&(-i))] + vet[ __builtin_ctz(i&(-i)) ];
		if(__builtin_popcount(i) <= k && x[i]>=A && x[i]<=B) ans++;
	}
	if(n<=16) return ans;
	
	reverse(vet, vet+n);
	aux[0] = 0;
	int ct;
	for(int i=1; i<(1<<(n-16)); i++){
		aux[i] = aux[i^(i&(-i))] + vet[ __builtin_ctz(i&(-i)) ];
	}
	for(int i=0; i<(1<<(n-16)); i++){
		v[__builtin_popcount(i)].push_back(aux[i]);
	}
	
	for(int i=0; i<n; i++) if(v[i].size()) sort(v[i].begin(), v[i].end());
	ans=0;
	for(int i=0; i<(1<<16); i++){
		ct = __builtin_popcount(i);
		if(ct > k) continue;
		for(int j=0; j<=k-ct; j++){
			ans+= upper_bound(v[j].begin(), v[j].end(), B-x[i]) - lower_bound(v[j].begin(), v[j].end(), A-x[i]);
		}
	}
	return ans;
	
}


int main(){
	
	cin >> n >> k >> A >> B;
	for(int i=0; i<n; i++) cin >> vet[i], vet[i] = nice(vet[i]);
	
	cout << solve() << endl;
}
