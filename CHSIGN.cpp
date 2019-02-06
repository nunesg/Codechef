#include <bits/stdc++.h>

using namespace std;

#define N 101010

typedef long long ll;

ll n, v[N], dp[N], acc[N], opt[N];
vector<int> vet;

ll get_sum(ll l, ll r){
	return acc[r]- acc[l-1];
}

void solve(){
	
	dp[1] = -v[1];
	dp[0] = 0;
	v[0] = 0;
	for(ll i=2; i<=n; i++){
		ll ult = lower_bound(vet.begin(), vet.end(), i) - vet.begin() - 1;
		dp[i] = dp[vet[ult]]+acc[i]-acc[vet[ult]];
		if(v[i] >= v[i-1]) continue;
		
		//~ printf("\ni = %d, ult = %d\n", i, vet[ult]);
		
		ll ini = 0, fim = ult, ans=-1;
		
		while(ini<=fim){
			ll meio = (ini+fim)>>1;
			//~ printf("meio = %d\n", vet[meio]);
			if(get_sum(vet[meio]+1, i-1) > v[vet[meio]] + v[i]){
				ans = meio;
				ini = meio+1;
			}else fim = meio-1;
		}
		//~ printf("ans = %d\n", vet[ans]);
		if(ans == -1) continue;
		
		dp[i] = min(dp[i], dp[vet[ans]]+get_sum(vet[ans]+1, i-1) - v[i]);
	}
}

void build(){
	for(ll i=n; i>0; ){
		//~ printf("i = %d\n", i);
		if(i == 1){
			v[i]*=-1;
			return;
		}
		ll ult = lower_bound(vet.begin(), vet.end(), i) - vet.begin() - 1;
		if(dp[i] == dp[vet[ult]]+acc[i]-acc[vet[ult]]){
			i = vet[ult];
			continue;
		}
		
		ll ini = 0, fim = ult, ans=-1;
		while(ini<=fim){
			ll meio = (ini+fim)>>1;
			if(get_sum(vet[meio]+1, i-1) > v[vet[meio]] + v[i]){
				ans = meio;
				ini = meio+1;
			}else fim = meio-1;
		}
		
		v[i]*=-1;
		i = vet[ans];
	}
}

int main(){
	
	ll tc;
	
	scanf("%lld", &tc);
	
	while(tc--){
		scanf("%lld", &n);
		vet.clear();
		for(ll i=1; i<=n; i++) {
			scanf("%lld", &v[i]), acc[i] = acc[i-1]+v[i];
			if(v[i] > v[i-1]) vet.push_back(i-1);
		}
		
		solve();
		build();
		//~ printf("%lld\n", dp[n]);
		for(ll i=1; i<=n; i++) printf("%lld%c", v[i], i==n?'\n':' ');
		
	}
	
	
}
