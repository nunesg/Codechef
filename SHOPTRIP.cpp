#include <bits/stdc++.h>

using namespace std;

#define N 38
#define M 14
#define inf 10101010


int n, k, x[N], y[N], vet[N], tempo;
string s;
double dp[N][1<<M];
char vis[N][1<<M];

double dist(int i, int j){
	return hypot(x[i]-x[j], y[i]-y[j]);
}


double solve(int p, int mask){
	
	if(mask == ((1<<k)-1)) return dist(p, 0);
	
	double &ans = dp[p][mask];
	if(vis[p][mask]==tempo) return ans;
	vis[p][mask] = tempo;
	
	ans = inf;
	
	for(int i=1; i<=n; i++){
		if( (vet[i] & mask) == vet[i]) continue;
		
		ans = min(ans, solve(i, mask|vet[i])+dist(p, i));
	}
	return ans;
}


int main(){
	int tc;
	cin >> tc;
	tempo=0;
	while(tc--){
		
		cin >> n >> k;
		x[0] = y[0] = 0;
		for(int i=1; i<=n; i++){
			cin >> x[i] >> y[i];
		}
		vet[0] = 0;
		for(int i=1; i<=n; i++){
			cin >> s;
			int mask = 0;
			for(int i=0; i<s.size(); i++){
				if(s[i]-'0' == 1) mask|=(1<<i);
			}
			vet[i] = mask;
		}
		tempo++;

		cout << fixed << setprecision(10);
		double ans = solve(0, 0);
		if(ans == inf) cout << "-1\n";
		else cout << ans << "\n";
	}
}
