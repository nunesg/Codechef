#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll n;
map<ll, ll> freq;

int main(){
	
	ll tc, a;
	scanf("%lld", &tc);
	while(tc--){
		
		scanf("%lld", &n);
		ll ans=0;
		freq.clear();
		for(ll i=1; i<=n; i++){
			scanf("%lld", &a);
			if(freq.count(a)) ans++;
			freq[a]++;
		}
		printf("%lld\n", ans);
	}
	
	
}
