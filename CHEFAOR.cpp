#include <bits/stdc++.h>

using namespace std;


#define N 5050
#define M 14
#define gc getchar

typedef long long int ll;

void scanint(ll &x)
{
    register ll c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}




ll n, K;
ll dp[2][N];
ll vet[N];



inline void func(ll at, ll k, ll l, ll r, ll optL, ll optR){
	if(r<l) return;
	ll mid = (l+r)/2;
	ll opt = 1;
	ll best = -1;
	
	ll ant = at^1;
	
	
	ll lim = min(mid-1, optR);
	
	ll c = 0;
	for(ll i=lim+1; i<=mid; i++) c|=vet[i];
	
	
	for(ll i=lim; i>=optL; i--){
		
		
		if(best < dp[ant][i]+c){
			best = dp[ant][i]+c;
			opt = i;
		}
		c|=vet[i];
	}
	
	dp[at][mid] = best;

	func(at, k, l, mid-1, optL, opt);
	func(at, k, mid+1, r, opt, optR);
}



int main(){
	
	ll t;
	
	scanint(t);
	while(t--){	
		scanint(n);scanint(K);
		
		for(ll i=1; i<=n; i++) scanint(vet[i]);
		
		ll at = 0;
		for(ll i=1; i<=n; i++) dp[1][i] = dp[1][i-1]|vet[i];
		
		for(ll k=2; k<=K; k++){
			func(at, k, 1, n, 1, n);
			at^=1;
		}
		
		printf("%lld\n", dp[at^1][n]);
	}
}
