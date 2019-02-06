#include <bits/stdc++.h>

using namespace std;

#define N 5050

int n, m, dp[N][N][2], memo[N][N][2], tmp;
string s[2];

int solve(int i, int j, int op){
	if(i == n && j == m) return 0;
	
	int &ans = dp[i][j][op];
	
	if(memo[i][j][op] == tmp) return ans;
	memo[i][j][op] = tmp;
	ans = N*N;
	char last = (op == 0) ? s[op][i-1] : s[op][j-1];
	if(i<n) ans = min(ans, solve(i+1, j, 0)+ (s[0][i] != last));
	if(j<m) ans = min(ans, solve(i, j+1, 1)+ (s[1][j] != last));
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	int tc;
	cin >> tc;
	tmp=1;
	while(tc--){
		
		cin >> n >> m;
		
		
		cin >> s[0] >> s[1];
		
		//~ cout << s[0] << endl;
		//~ cout << s[1] << endl;
		
		printf("%d\n", min(solve(0, 1, 1), solve(1, 0, 0))+1);
		tmp++;
	}
	
}
