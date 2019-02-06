#include <bits/stdc++.h>

using namespace std;

#define N 33

int n, m, tc, g[N][N], dp[N][N], aux[N*N];
string s, vet[N];


int solve(int l, int r){
	
	int &ans = dp[l][r];
	if(ans != -1) return ans;
	//~ printf("[%d , %d]\n", l, r);
	ans=0;
	if(r<l) return 0;
	
	int tam;
	for(int i=0; i<n; i++){
		tam = vet[i].length();
		
		for(int j=l; j<=r; j++){
			if(j+tam > r+1) break;
			if(s.substr(j, tam) == vet[i]){
				solve(l, j-1);
				solve(j+tam, r);
			}
		}
	}
	memset(aux, 0, sizeof aux);
	for(int i=0; i<n; i++){
		tam = vet[i].length();
		
		for(int j=l; j<=r; j++){
			if(j+tam > r+1) break;
			if(s.substr(j, tam) == vet[i]){
				aux[solve(l, j-1)^solve(j+tam, r)]=1;
			}
		}
	}
	for(int i=0; i<N*N; i++) {
		if(!aux[i]){
			ans = i;
			return ans;
		}
	}
}


int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> tc;
	
	while(tc--){
		
		cin >> s;
		m = s.length();
		s = " "+s;
		cin >> n;
		
		for(int i=0; i<n; i++){
			cin >> vet[i];
		}
		memset(dp, -1, sizeof dp);
		if(solve(1, m)) cout << "Teddy\n";
		else cout << "Tracy\n";
	}
	
}
