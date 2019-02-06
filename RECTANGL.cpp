#include <bits/stdc++.h>

using namespace std;

int main(){
	long long vet[4];
	
	int tc;
	cin >> tc;
	while(tc--){
	
		for(int i=0; i<4; i++) cin >> vet[i];
		sort(vet, vet+4);
		
		if(vet[0] == vet[1] && vet[2] == vet[3]) cout << "YES\n";
		else cout << "NO\n";
	}
}
