#include <bits/stdc++.h>

using namespace std;

#define N 20


int n, m, vet[N];


int main(){
	
	int tc;
	scanf("%d", &tc);
	while(tc--){
		
		scanf("%d %d", &n, &m);
		
		for(int i=0; i<n; i++) scanf("%d", &vet[i]);
		int sum, ans=0;
		for(int mask=0; mask<(1<<n) && ans==0; mask++){
			sum=0;
			for(int x = mask; x; x-=(x&(-x))){
				int i = __builtin_ctz(x&(-x));
				
				sum+=vet[i];
				if(sum > m) break;
			}
			if(sum == m){
				ans = 1;
				break;
			}
		}
		
		printf(ans ? "Yes\n" : "No\n");
		
	}
	
}
