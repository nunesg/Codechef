#include <bits/stdc++.h>

using namespace std;

#define N 30000001

typedef long long ll;

vector<int> quad, nquad;
bitset<N>aux;
int n, q[N];

void build(){
	
	for(int i=2; i*i<N; i++) {
		quad.push_back(i*i);
		q[i*i] = 1;
		aux[i*i] = 1;
		for(int j=i*i; j<N; j+=(i*i)) aux[j] = 1;
	}
	for(int i=1; i<N; i++) if(!aux[i]) nquad.push_back(i);
	
}

int go(int x){
	int ans=0;
	for(int i=0; i<quad.size(); i++){
		
		int el = quad[i];
		
		ans += upper_bound(nquad.begin(), nquad.end(), x/el) - nquad.begin(); 
	}
	return ans;
}

int solve(){
	
	int ini = 2, fim = N*10, meio, ans;
	
	while(ini<=fim){
		
		meio = (ini+fim)>>1;
		
		int qtd = go(meio);
		
		if(qtd>=n){
			ans = meio;
			fim = meio-1;
		}else ini = meio+1;
	}
	return ans;
	
}


int main(){
	build();
	cin >> n;
	
	printf("%d\n", solve());
}
