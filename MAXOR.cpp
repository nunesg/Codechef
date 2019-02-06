#include <bits/stdc++.h>

using namespace std;

#define N 1000100
#define M 20

typedef long long int ll;

int n, vet[N], freq[N], ant[N];
ll dp[1<<M];


int main(){
	
	int tc;
	scanf("%d", &tc);
	
	while(tc--){
		
		scanf("%d", &n);
		memset(dp, 0, sizeof dp);
		memset(freq, 0, sizeof freq);
		memset(ant, 0, sizeof ant);
		
		for(int i=0; i<n; i++){
			scanf("%d", &vet[i]);
			dp[vet[i]]++;
			ant[i] = freq[vet[i]]++;
		}
		
		
		
		for(int i=1; i<=M; i++){
			for(int mask = 0; mask<(1<<M); mask++){
				if(mask & (1<<(i-1))) dp[mask]+=dp[mask^(1<<(i-1))];
			}
		}
		ll ans = 0;
		for(int i=0; i<n; i++){
			ans+= dp[vet[i]] - (freq[vet[i]] - ant[i]);
		}
		printf("%lld\n", ans);
		
	}
	
}
