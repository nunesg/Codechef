#include <bits/stdc++.h>

using namespace std;

#define N 301010
#define K 110
#define off 101
#define mod 1000000007

int n, k, dp[K][K][K<<1], c[N][K];


int f(int i){
	
	if(i == 1) return 1;
	int ans=0;
	for(int j = 1; j<i; j++){
		if((i-j) < j) break;
		ans+= f(j)*f(i-j);
	}
	return ans;
}


int main(){
	
	c[0][0] = 1;
	for(int i=1; i<N; i++) c[i][0] = 1;
	for(int i=1; i<N; i++){
		for(int j=1; j<=min(i, K-1); j++){
			c[i][j] = (c[i-1][j-1] + c[i-1][j])%mod;
		}
	}
	
	memset(dp, -1, sizeof dp);
	scanf("%d %d", &n, &k);
	printf("%d\n", f(5));
	//~ printf("f = %d\n", f(k, k - (k%2), off));
	//~ int num = mult(f(0, k, off), c[n][k]);
	//~ int den = mult(fast_exp(2, k-1), c[n][k]);
	//~ printf("%d\n", mult(num, fast_exp(den, mod-2)));
	
}
