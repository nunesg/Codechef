#include <bits/stdc++.h>

using namespace std;

#define N 101010
#define inf 10101010101010LL

typedef long long ll;

ll n, v[N], h;

bool check(ll x){
	ll s=0;
	for(ll i=1; i<=n; i++){
		s+= v[i]/x;
		s+= (v[i]%x != 0);
		if(s>h) return false;
	}
	return true;
}

ll busca(){
	
	ll ini=1, fim=inf, meio, ans;
	
	while(ini<=fim){
		
		meio = (ini+fim)>>1;
		
		if(check(meio)){
			ans = meio;
			fim = meio-1;
		}else ini = meio+1;
	}
	return ans;
}


int main(){
	ll tc;
	scanf("%lld", &tc);
	while(tc--){
		
		scanf("%lld %lld", &n, &h);
		
		for(ll i=1; i<=n; i++) scanf("%lld", &v[i]);
		
		printf("%lld\n", busca());
	}
}
