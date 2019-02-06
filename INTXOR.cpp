#include <bits/stdc++.h>

using namespace std;

#define N 201010

int main(){
	
	int a1a2a3, a1a2a4, a1a3a4, a2a3a4, v[N];
	
	int t, n;
	scanf("%d", &t);
	
	while(t--){
		
		scanf("%d", &n);
		
		printf("1 1 2 4\n"); fflush(stdout);
		scanf("%d", &a1a2a4);
		printf("1 1 3 4\n"); fflush(stdout);
		scanf("%d", &a1a3a4);
		printf("1 2 3 4\n"); fflush(stdout);
		scanf("%d", &a2a3a4);
		
		v[4] = a1a2a4 ^ a1a3a4 ^ a2a3a4;
		v[3] = a1a2a3 ^ a1a2a4 ^ v[4];
		v[2] = a1a2a3 ^ a1a3a4 ^ v[4];
		v[1] = a1a2a3 ^ a2a3a4 ^ v[4];
		
		int aux;
		for(int i=5; i<=n; i++){
			printf("1 %d %d %d\n", i-2, i-1, i); fflush(stdout);
			scanf("%d", &aux);
			v[i] = v[i-1]^v[i-2]^aux;
		}
		printf("2");
		for(int i=1; i<=n; i++) {
			printf(" %d", v[i]);
		}
		printf("\n");
		fflush(stdout);
		
		scanf("%d", &aux);
		if(aux == -1) return 0;
	}
	
	
	
}
