#include <bits/stdc++.h>

using namespace std;

#define N (1<<19)
#define block 909
#define MASK ((1<<17)-1)

typedef long long ll;

struct query{
	ll x, y;
}Q[N];

ll n, m, dp[N], h[N], ans[N];

int main(){
	ll a, b;
	
	scanf("%lld", &n);
	for(ll i=0; i<n; i++) scanf("%lld", &h[i]);
	
	scanf("%lld", &m);
	
	for(ll i=0; i<m; i++){
		scanf("%lld %lld", &a, &b);
		a&= MASK;
		Q[i] = {a, b};
	}
	ll qtd_blocks = m/block + 1, idx=0;
	for(ll b=0; idx < m && b<qtd_blocks; b++){
		
		memset(dp, 0, sizeof dp);
		
		ll ind = idx;
		
		for(ll i=0; i<block && idx<m; i++, idx++){
			dp[Q[idx].x] += Q[idx].y;
		}
		
		for(ll BIT = 0; BIT<18; BIT++){
			for(ll mask=MASK; mask>=0; mask--){
				if(mask&(1<<BIT)) dp[mask^(1<<BIT)]+=dp[mask];
			}
		}
		
		for(ll i=0; i<n; i++){
			if(h[i]<=0) continue;
			
			if(h[i]-dp[i]<=0){
				
				for(ll j=ind; j<idx; j++){
					
					if((i&(Q[j].x)) == i){
						h[i]-=Q[j].y;
						if(h[i]<=0){
							ans[j]++;
							break;
						}
					}
				}
			}else h[i]-=dp[i];
		}
	}
	ll qtd=n;
	for(ll i=0; i<m; i++){
		qtd-=ans[i];
		printf("%lld\n", qtd);
	}
}
