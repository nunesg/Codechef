#include <bits/stdc++.h>

using namespace std;

#define N 19
#define M 9
#define inf 10101010
#define F first
#define S second

typedef pair<int, int> ii;

int n, dp[N][N][1<<M], tempo;
ii point[N];//0..n-1 = cook. n .. 2n-1 = tool
char vis[N][N][1<<M];

int dist(ii a, ii b){
	return abs(a.F-b.F)+abs(a.S-b.S);
}


int solve(int p, int tool, int mask){
	
	if((mask == (1<<n)-1) && tool == 2*n) return dist(point[p], ii(0, 0));
	
	int &ans = dp[p][tool][mask];
	if(vis[p][tool][mask] == tempo) return ans;
	vis[p][tool][mask] = tempo;
	ans = inf;
	
	if( tool == 2*n ){
		for(int i=n; i<2*n; i++){
			if(mask & (1<<(i-n))) continue;
			ans = min(ans, solve(i-n, 2*n, mask | (1<<(i-n)))+dist(point[p], point[i])+dist(point[i], point[i-n]));
			
			for(int j=n; j<2*n; j++){
				if(j == i) continue;
				if(mask & (1<<(j-n))) continue;
				ans = min(ans, 
					solve(i-n, j, mask | (1<<(i-n)))+
					dist(point[p], point[i])+dist(point[i], point[j]) + dist(point[j], point[i-n]));
			
				ans = min(ans, 
					solve(j-n, i, mask | (1<<(j-n)))+
					dist(point[p], point[i])+dist(point[i], point[j]) + dist(point[j], point[j-n]));
			}
		}
		return ans;
	}
	ans = min(ans, solve(tool-n, 2*n, mask | (1<<(tool-n)))+dist(point[p], point[tool-n]));
	for(int i=n; i<2*n; i++){
		if(mask & (1<<(i-n))) continue;
		if(i == tool) continue;
		
		ans = min(ans, 
				solve(tool-n, i, mask | (1<<(tool-n)))+
				dist(point[p], point[i])+dist(point[i], point[tool-n]));
		ans = min(ans, 
				solve(i-n, tool, mask | (1<<(i-n)))+
				dist(point[p], point[i])+dist(point[i], point[i-n]));		
	}
	return ans;
}


int main(){
	
	int tc;
	scanf("%d", &tc);
	tempo = 0;
	while(tc--){
		
		scanf("%d", &n);
		
		for(int i=0; i<n; i++){
			scanf("%d%d%d%d", &point[i].F, &point[i].S, &point[i+n].F, &point[i+n].S);
		}
		point[2*n] = ii(0, 0);
		tempo++;
		printf("%d\n", solve(2*n, 2*n, 0));
	}
}
