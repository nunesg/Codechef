#include <bits/stdc++.h>

using namespace std;

#define N 21

typedef long long ll;

ll k, n, dp[N][2];
string s, str;

ll solve(ll i, ll last){
	
	if(i == n+2) return last == 0;
	
	if(dp[i][last]!=-1) return dp[i][last];
	
	ll &ans = dp[i][last];
	ans=0;
	
	ll c = str[i]-'0';
	if(last!= c) ans = solve(i+1, c);
	ans+= solve(i+1, last);
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	ll tc;
	cin >> tc;
	while(tc--){
		cin >> s;
		n= (int)s.size()-2;
		
		cin >> k;
		ll c, sum, ans=n, flag=0;
		
		str.resize(n+2);
		for(ll mask=0; n>=0 && mask<(1<<n); mask++){
			str = s;
			
			for(ll i=0; i<n; i++){
				if(mask&(1<<i)) str[i+1] = ((str[i+1]-'0')^1)+'0';
			}
			//~ cout << str << endl;
			memset(dp, -1, sizeof dp);
			sum = solve(0, 0)-1;
			//~ cout << "sum = " << sum << endl;
			
			if(sum == k){
				ans = min(ans, __builtin_popcountll(mask)*1LL);
				flag=1;
			}
		}
		
		if(flag){
			cout << "YES\n" << ans << "\n";
		}else cout << "NO\n";
	}
	
}
