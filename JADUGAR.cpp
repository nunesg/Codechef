#include <bits/stdc++.h>

using namespace std;

#define N 1010100
#define mod 1000000007


int n, k, a, b, dp[N];

int main(){
	
	cin >> n >> k >> a >> b;
	
	dp[1] = 1;
	
	for(int i=2; i<=n; i++){
		
		int x = (b*1LL*k)%mod;
		int y = ((i/2)*1LL*x)%mod;
		dp[i] = a*dp[i-1];
		if(i%2) (i/2)*b*k*dp[i-1];
		printf("dp[%d] = %d\n", i, dp[i]);
	}
	
	cout << dp[n] << "\n";
}
