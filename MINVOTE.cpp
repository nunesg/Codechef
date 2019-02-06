#include <bits/stdc++.h>

using namespace std;

#define N 410001
#define gc getchar

void scanint(int &x)
{
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}

typedef long long ll;

int n, bit[N], v[N], answer[N];
ll acc[N];
set<ll > vet;
unordered_map<ll , int > mapa;

void update(int pos, int x){
	for(; pos<N; pos+=pos&(-pos)) bit[pos]+=x;
}
int sum(int pos){
	int s=0;
	for(; pos>0; pos-=(pos&(-pos))) s+=bit[pos];
	return s;
}


int main(){
	
	int tc;
	scanint(tc);
	
	while(tc--){
		
		scanint(n);
		mapa.clear();
		vet.clear();
		for(int i=1; i<=n; i++){
			scanint(v[i]);
			
			acc[i] = v[i]+acc[i-1];
			vet.insert(acc[i]);
			vet.insert(acc[i]+v[i]);
			answer[i] = 0;
		}
		acc[n+1] = 0;
		mapa[0] = 1;
		for(int i=n; i; i--){
			acc[i] = v[i]+acc[i+1];
			vet.insert(acc[i]);
			vet.insert(acc[i]+v[i]);
		}
		int c=2;
		for(auto x : vet){
			mapa[x] = c++;
		}
		
		for(int i=1; i<=n; i++){
			acc[i] = v[i]+acc[i-1];
			answer[i]+= i-1 - sum(mapa[acc[i-1]]-1);
			update(mapa[acc[i]+v[i]], 1);
		}
		for(int i=1; i<=n; i++){
			acc[i] = v[i]+acc[i-1];
			update(mapa[acc[i]+v[i]], -1);
		}
		
		for(int i=n; i; i--){
			acc[i] = v[i]+acc[i+1];
			answer[i]+= n-i - sum(mapa[acc[i+1]]-1);
			update(mapa[acc[i]+v[i]], 1);
		}
		for(int i=n; i; i--){
			acc[i] = v[i]+acc[i+1];
			update(mapa[acc[i]+v[i]], -1);
		}
		
		for(int i=1; i<=n; i++) printf("%d%c", answer[i], i==n?'\n':' ');
	}
}
