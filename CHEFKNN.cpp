#include <bits/stdc++.h>

using namespace std;

#define N 2505
#define mod 163577857

int n, K, dp[N][N], soma[N][N];


int f(int, int);
int somatorio(int len, int k){
	
	if(len == 0) return 1;
	if(soma[len][k]!=-1) return soma[len][k];
	
	return soma[len][k] = ((len+1)*1LL*f(len, k) + somatorio(len-1, k))%mod;
}

int f(int len, int k){
	if(len==0) return 1;
	if(k == 0) return 1;

	if(dp[len][k]!=-1) return dp[len][k];
	int &ans = dp[len][k];
	ans = 0;

	if(k<K) ans = (ans+f(len, k-1))%mod;

	//~ for(int x=1; x<=len; x++){
		//~ ans = (ans+ x*1LL*f(x-1, k-1))%mod;
	//~ }
	ans = (ans+ somatorio(len-1, k-1))%mod;
	return ans;
}


int main(){
	
	
	int tc;
	scanf("%d", &tc);
	
	while(tc--){
		//~ while(scanf("%d %d", &n, &K)!=EOF){
		scanf("%d %d", &n, &K);
		memset(dp, -1, sizeof dp);
		memset(soma, -1, sizeof soma);
		printf("%d\n", f(n, K));
	}
	
	
	
}
