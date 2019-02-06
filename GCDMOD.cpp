#include <bits/stdc++.h>

using namespace std;

#define N 101010
#define MOD 1000000007

typedef long long ll;

ll n;

ll gcd(ll a, ll b){
	return !b ? a : gcd(b, a%b);
}

ll fpow(ll base, ll exp, ll mod){
	if(!exp) return 1LL;
	
	ll u = fpow(base, exp/2, mod);
	u = (u*u)%mod;
	if(exp%2) u = (u*base)%mod;
	return u;
}


bool check(ll A, ll B, ll mod){
	ll sum = (fpow(A, n, mod) + fpow(B, n, mod))%mod;
	return sum == 0;
}


int main(){
	
	
	int t;
	scanf("%d", &t);
	ll a, b;
	vector<ll> aux;
	while(t--){
		
		scanf("%lld %lld %lld", &a, &b, &n);
		
		if(a == b){
			printf("%lld\n", (fpow(a, n, MOD)+fpow(b, n, MOD))%MOD);
			continue;
		}
		
		
		ll diff = max(a,b)-min(a,b);
		
		for(ll x=1; x*x<=diff; x++){
			if((diff%x)!=0) continue;
			if(x*x != diff) aux.push_back(diff/x);
			aux.push_back(x);
		}
		
		ll ans = 1;
		
		
		for(ll x : aux){
			if(check(a, b, x)) ans = max(ans, x);
		}
		printf("%lld\n", ans%MOD);
		aux.clear();
	}
	
	
	
}
