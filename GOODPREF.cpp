#include <bits/stdc++.h>

using namespace std;

#define N 5010
#define ERR 2500

typedef long long ll;

ll n, tota, totb, k, v[N];
string s;

void build(){
	
	tota = totb = 0;
	memset(v, 0, sizeof v);
	
	for(ll i=0; i<n; i++){
		if(s[i] == 'a') tota++;
		else totb++;
		v[tota-totb+ERR]++;
	}
	
	for(ll i=N-2; i>=0; i--) v[i]+=v[i+1];
}





ll solve(){
	
	ll dif=0, ans=0;
	ll a, b = a = 0;
	if(tota == totb) return v[1+ERR]*k;
	for(ll f=0; f<k; f++){
		//~ printf("f=%d\n", f);
		dif = a-b;
		//~ printf("a = %d, b = %d, ans+= %d\n", a, b, v[-dif+1+ERR]);
		ans+= v[-dif+1+ERR];
		a+=tota;
		b+=totb;
		
		if(a-b >= n){
			ans+= n*(k-f-1);
			break;
		}
		if(b-a >= n){
			break;
		}
	}
	return ans;
}

int main(){
	//~ ios_base::sync_with_stdio(0); cin.tie(0);
	ll tc;
	cin >> tc;
	while(tc--){
		cin >> s >> k;
		
		n = s.length();
		
		build();
		cout << solve() << "\n";
	}
}
