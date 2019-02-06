#include <bits/stdc++.h>

using namespace std;

#define N 707
#define inf 1010101010101010LL

typedef long long ll;

ll n, mat[N][N], dp[N][N];


int main(){
	
	int tc;
	scanf("%d", &tc);
	
	while(tc--){
		
		scanf("%lld", &n);
		for(int i=1; i<=n; i++){
			for(int j=1; j<=n; j++) scanf("%lld", &mat[i][j]);
			sort(mat[i]+1, mat[i]+1+n);
			dp[i][0] = -inf;
		}
		
		
		for(int i=1; i<=n; i++){
			int prev = 1;
			for(int j=1; j<=n; j++){
				while(prev<=n && mat[i-1][prev] < mat[i][j]) prev++;
				dp[i][j] = dp[i-1][prev-1]+mat[i][j];
				dp[i][j] = max(dp[i][j], dp[i][j-1]);
			}
		}
		
		printf("%lld\n", max(dp[n][n], -1LL));
		
	}
	
	
}
