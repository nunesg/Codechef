#include <bits/stdc++.h>

using namespace std;


map< vector<int> , int > f;

void printa(vector<int>&v){
	for(int i=0; i<v.size(); i++) {
		if(i) printf(" ");
		printf("%d", v[i]);
	}
	printf("\n");
}

int main(){
	srand(time(NULL));
	int n;
	
	
	for(n=1; n<=17; n++){
		vector<int> v(n), aux(n);
		f.clear();
		
		for(int i=1; i<=n; i++) v[i-1] = i;
		
		for(int i=0; i< 1e6; i++){
			
			aux = v;
			//~ printf("oi i = %d\n", i);
			for(int j=0; j<n; j++){
				int x = rand()%n;
				swap(aux[j], aux[x]);
			}
			
			f[aux]++;
		}
		
		int ans=-1;
		for(auto tmp : f){
			if(tmp.second > ans){
				ans = tmp.second;
				aux = tmp.first;
			}
		}
		
		printa(aux);

		ans=1e7;
		for(auto tmp : f){
			if(tmp.second < ans){
				ans = tmp.second;
				aux = tmp.first;
			}
			if(tmp.first == v){
				next_permutation(v.begin(), v.end());
				continue;
			}else {
				aux = v;
				break;
			}
		}
		
		printa(aux);
		printf("\n");
	}
}
