#include <bits/stdc++.h>

using namespace std;

#define N 202

int n, vet[N];

int main(){
	int tc;
	scanf("%d", &tc);
	
	while(tc--){
		
		scanf("%d", &n);
		
		for(int i=0; i<n; i++){
			scanf("%d", &vet[i]);
		}
		
		int max_sum = 0, qtd=0;
		for(int i=0; i<n; i++){
			for(int j=i+1; j<n; j++){
				max_sum = max(max_sum, vet[i]+vet[j]);
			}
		}
		
		for(int i=0; i<n; i++){
			for(int j=i+1; j<n; j++){
				qtd += max_sum == vet[i]+vet[j];
			}
		}
		
		double ans = ((qtd*1.0)*2.0)/(n*1.0*(n-1));
		printf("%.7lf\n", ans);
		
	}
	
}
