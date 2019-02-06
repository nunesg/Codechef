#include <bits/stdc++.h>

using namespace std;


#define N 5050
#define mod 1000000007


int n, k, v[N], c[N][N];

int mult(int a, int b){
	return (1LL*a*b)%mod;
}

int fast_exp(int base, int exp){
	if(!exp) return 1;
	int u = fast_exp(base, exp/2);
	u = mult(u, u);
	if(exp%2) u = mult(u, base);
	return u;
}


int main(){
	
	c[0][0] = 1;
	for(int i=1; i<N; i++) c[i][0] = 1;
	for(int i=1; i<N; i++){
		for(int j=1; j<=i; j++){
			c[i][j] = (c[i-1][j] + c[i-1][j-1])%(mod-1);
		}
	}
	
	int tc;
	scanf("%d", &tc);
	while(tc--){
		scanf("%d %d", &n, &k);
		for(int i=1; i<=n; i++) scanf("%d", &v[i]);
		sort(v+1, v+n+1);
		
		int num=1, den=1;
		
		for(int i=1; i<=n; i++){
			num = mult(num, fast_exp(v[i], c[n-1][k-1]));
			
			if(n-i>=k-1) den = mult(den, fast_exp(v[i], c[n-i][k-1]));
			if(i-1>=k-1) den = mult(den, fast_exp(v[i], c[i-1][k-1]));
		}
		
		int ans = mult(num, fast_exp(den, mod-2));
		printf("%d\n", ans);
	}
}
