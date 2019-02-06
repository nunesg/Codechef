#include <bits/stdc++.h>

using namespace std;

#define N 100
#define base 33

typedef unsigned long long int ull;

ull pot[N], hash_[2][N];
string s;
int k, n;

void calc_hash(int op){
	hash_[op][0] = s[0];
	for(int i=1; i<n; i++) hash_[op][i] = hash_[op][i-1] + s[i]*pot[i];
}

bool is_palindrome(int l, int h){
	
	int x = h-l+1;
	ull h1 = pot[n-h-1]*(hash_[0][h] - (l ? hash_[0][l-1] : 0LL) );
	
	h = n-l-1;
	l = h-x+1;
	
	ull h2 = pot[n-h-1]*(hash_[1][h] - (l ? hash_[1][l-1] : 0LL) );
	
	return h1 == h2;
}

int solve(){	
	int ans = 0;
	
	for(int l=0, r=k-1; r<n; l++, r++){
		ans+= is_palindrome(l, r);
	}
	return ans;
}


int main(){
	
	int tc;
	cin >> tc;
	
	pot[0] = 1;
	for(int i=1; i<N; i++) pot[i] = pot[i-1]*base;
	
	while(tc--){
		
		cin >> k;
		
		getline(cin, s);
		getline(cin, s);
		
		n = s.size();
		
		calc_hash(0);
		reverse(s.begin(), s.end());
		calc_hash(1);
		
		
		printf("%d\n", solve());
		
	}
}
