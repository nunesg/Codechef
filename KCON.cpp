#include <bits/stdc++.h>

using namespace std;

#define N 101010

typedef long long ll;

ll n, k, vet[N], pref, suf, tot, maior, kadane;


int main(){
	
	int t;
	scanf("%d", &t);
	while(t--){
		
		scanf("%lld %lld", &n, &k);
		
		for(int i=1; i<=n; i++) scanf("%lld", &vet[i]);
		
		pref = suf = tot = 0;
		maior = LLONG_MIN;
		
		ll sum=0;
		for(int i=1; i<=n; i++){
			sum+=vet[i];
			pref = max(sum, pref);
			maior = max(maior, vet[i]);
		}
		tot = sum;
		sum=0;
		for(int i=n; i>=1; i--){
			sum+=vet[i];
			suf = max(sum, suf);
		}
		
		
		sum = 0;
		kadane = 0;
		for(int i=1; i<=n; i++){
			sum+=vet[i];
			if(sum<0) sum=0;
			kadane = max(kadane, sum);
		}
		
		//~ printf("pref = %lld, suf = %lld, tot = %lld, maior = %lld, kadane = %lld\n", pref, suf, tot, maior, kadane);
		
		if(maior < 0) {
			printf("%lld\n", maior);
			continue;
		}
		
		if(k == 1){
			printf("%lld\n", kadane);
			continue;
		}
		
		printf("%lld\n", max(kadane, max((k-2)*tot + pref+suf, pref+suf)));
	}
	
}
