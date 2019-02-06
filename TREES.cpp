#include <bits/stdc++.h>

using namespace std;

#define N 80

int n, dp[N][N], baixo[N][N], k, tmp[N], tmpb[N], answer;
vector<int> adj[N];


void solve(int u, int p){
	dp[u][0] = 1;
	baixo[u][0] = 1;
	
	for(int v : adj[u]){
		
		if(v == p) continue;
		
		solve(v, u);
		printf("\n");
		memset(tmp, 0, sizeof tmp);
		memset(tmpb, 0, sizeof tmpb);
		
		for(int i=1; i<=k; i++){
			tmpb[i]+= baixo[u][i]*baixo[v][i-1];
		}
		
		for(int a=0; a<=k; a++){
			for(int b=0; a+b<=k; b++){
				
				tmp[a+b+1] += baixo[u][a]*dp[v][b];
				//~ printf("tmp[%d]+= (dp[%d][%d] = %d) * (dp[%d][%d] = %d)\n", a+b+1, u, a, dp[u][a], v, b, dp[v][b]);
			}
		}
		for(int i=0; i<=k; i++) dp[u][i]+= tmp[i];
		for(int i=0; i<=k; i++) baixo[u][i]+= tmpb[i];
	}
	for(int i=0; i<=k; i++) {
		printf("dp[%d][%d] = %d\n", u, i, dp[u][i]);
		answer+=dp[u][i];
	}
}


int main(){
	
	int tc;
	scanf("%d", &tc);
	int a, b;
	while(tc--){
		memset(dp, 0, sizeof dp);
		memset(baixo, 0, sizeof baixo);
		scanf("%d %d", &n, &k);
		
		for(int i=1; i<n; i++){
			scanf("%d %d", &a, &b);
			adj[a].push_back(b);
			adj[b].push_back(a);
		}
		answer = 0;
		solve(0, -1);
		printf("%d\n", answer);
		for(int i=0; i<=n; i++) adj[i].clear();
	}
	
}
