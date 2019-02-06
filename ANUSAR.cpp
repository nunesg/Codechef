#include <bits/stdc++.h>
 
using namespace std;
 
#define N 200020
#define F first
#define H second
 
typedef long long int ll;
 
typedef pair<ll , ll > ii;
 
 
ll SA[N], tmpSA[N], R[N], tmpR[N], cont[N], lcp[N], inv[N];
ll answer[N], n;
char s[N];
 
void radix(ll k){
	
	ll maxi = max(n, 300LL);
	memset(cont ,0, sizeof(ll)*maxi);
	
	for(ll i=0; i<n; i++){
		cont[i+k < n ? R[i+k] : 0]++;
	}
	
	for(ll i=1; i<maxi; i++) cont[i]+=cont[i-1];
	
	for(ll i=n-1; i>=0; i--){
		tmpSA[ --cont[SA[i]+k < n ? R[SA[i]+k] : 0] ] = SA[i];
	}
	for(ll i=0; i<n; i++) SA[i] = tmpSA[i];
}
 
void build_SA(){
 
	for(ll i=0; i<n; i++){
		SA[i] = i;
		R[i] = s[i];
	}
	
	for(ll k=1; k<n; k<<=1){
		
		radix(k);
		radix(0);
		
		
		ll r=0;
		tmpR[SA[0]] = 0;
		for(ll i=1; i<n; i++) tmpR[SA[i]] = (R[SA[i]] == R[SA[i-1]] && R[SA[i]+k] == R[SA[i-1]+k]) ? r : ++r;
		
		for(ll i=0; i<n; i++) R[SA[i]] = tmpR[SA[i]];
		if(R[SA[n-1]] == n-1) break;
	}
	//~ for(ll i=0; i<n; i++){
		//~ printf("%2d: ", i); cout << s.substr(SA[i]) << endl;
	//~ }
}
 
void build_lcp(){
	
	ll L=0;
	for(ll i=0; i<n; i++) inv[SA[i]] = i;
	for(ll i=0; i<n; i++){
		
		if(inv[i] == 0){
			lcp[inv[i]] = 0;
			continue;
		}
		
		ll prev = SA[inv[i]-1];
		while(i+L<n && prev+L<n && s[i+L] == s[prev+L]) L++;
		
		lcp[inv[i]] = L;
		L = max(L-1, 0LL);
	}
	//~ for(ll i=0; i<n; i++){
		//~ printf("lcp[%2lld]: %2lld\n", i, lcp[i]);
	//~ }
}
 
 
void solve(){
	memset(answer, 0, sizeof(ll)*n);
	vector<ii> vet;
	ii foo;
	ll l, r;
	for(ll i=1; i<n; i++){
		
		//~ printf("i=%lld\n", i);
		while(vet.size() && vet.back().H > lcp[i]){
			foo = vet.back();  vet.pop_back();
			
			l = 1; r = foo.F+1;
			
			ll value = (r*(foo.H- (vet.size()==0 ? lcp[i] : max(lcp[i],vet.back().H) ) ) );
			
			answer[r]+= value;
			
			if(vet.empty() || vet.back().H<lcp[i]){
				vet.push_back(ii(foo.F, lcp[i]));
				break;
			}
			if(vet.size()) vet.back().F+=foo.F;
			
			
		}
		
		if(lcp[i] == 0) continue;
		
		
		
		if(vet.empty() || vet.back().H<lcp[i]) {
			vet.push_back(ii(1, lcp[i]));
			continue;
		}
		
		
		if(vet.back().H == lcp[i]){
			vet.back().F++;
			continue;
		}
	}
	
	while(vet.size()){
		foo = vet.back();  vet.pop_back();
		
		l = 1; r = foo.F+1;
		
		ll value = (r*(foo.H- (vet.size()==0 ? 0 : vet.back().H ) ) );
		
		answer[r]+= value;
		
		if(vet.size()) vet.back().F+=foo.F;
	}
	
	
	ll sum=0;
	
	for(ll i=n-1; i>=0; i--){
		//~ printf("answer[%lld] = %lld, sum = %lld\n", i, answer[i], sum);
		//~ sum+=answer[i]; answer[i]=0;
		//~ answer[i]+=sum;
		answer[i]+=answer[i+1];
	}
	
}
 
int main(){
	//~ ios_base::sync_with_stdio(0); cin.tie(0);
	ll tc, q, f;
	scanf("%lld", &tc);
	while(tc--){
		scanf(" %s", s);
		n = strlen(s);
		s[n++] = '$'; s[n]='\0';
		
		build_SA();
		build_lcp();
		solve();
		
		answer[1] = (n*(n-1))/2;
		
		scanf("%lld", &q);
		
		while(q--){
			scanf("%lld", &f);
			if(f>n) printf("%lld\n", 0LL);
			else printf("%lld\n", answer[f]);
		}
		
	}
}
