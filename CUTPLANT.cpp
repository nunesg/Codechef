#include <bits/stdc++.h>

using namespace std;

#define N 201010
#define M 20

int n, v[N], b[N], table[2][N][M];
vector<int> vet[N], aux;

void build_table(){
	for(int i=0; i<n; i++) {
		table[0][i][0] = b[i];
		table[1][i][0] = v[i];
	}
	for(int j=1; j<M; j++){
		for(int i=0; i+(1<<j)<=n; i++){
			table[0][i][j] = max(table[0][i][j-1], table[0][i+(1<<(j-1))][j-1]);
			table[1][i][j] = min(table[1][i][j-1], table[1][i+(1<<(j-1))][j-1]);
		}
	}
}

int get_max(int l, int r){
	int k = 31 - __builtin_clz(r-l+1);
	return max(table[0][l][k], table[0][r-(1<<k)+1][k]);
}
int get_min(int l, int r){
	int k = 31 - __builtin_clz(r-l+1);
	return min(table[1][l][k], table[1][r-(1<<k)+1][k]);
}

int solve(){
	int answer=0;
	for(int i=1; i<=2*n; i++){
		
		if(!vet[i].size()) continue;
		//~ printf("i = %d: ", i);
		int last = vet[i][0], ans=1;
		for(int j=1; j<vet[i].size(); j++){
			if(get_max(last, vet[i][j]) <= i && get_min(last, vet[i][j]) >= i) continue;
			//~ printf("%d, ", vet[i][j]);
			ans++;
			last = vet[i][j];
		}
		//~ printf("\n");
		answer+=ans;
	}
	
	return answer;
}

int main(){
	
	int tc;
	scanf("%d", &tc);
	
	while(tc--){
		scanf("%d", &n);
		aux.clear();
		for(int i=0; i<N; i++) vet[i].clear();
		
		for(int i=0; i<n; i++){
			scanf("%d", &v[i]);
			aux.push_back(v[i]);
		}
		
		int a;
		bool flag=true;
		for(int i=0; i<n; i++){
			scanf("%d", &b[i]);
			aux.push_back(b[i]);
			if(b[i] > v[i]) {
				flag = false;
			}
		}
	
		sort(aux.begin(), aux.end());
	
		if(!flag){
			printf("-1\n");
			continue;
		}
		aux.resize(distance(aux.begin(), unique(aux.begin(), aux.end())));
		for(int i=0; i<n; i++){
			v[i] = lower_bound(aux.begin(), aux.end(), v[i]) - aux.begin() + 1;
			b[i] = lower_bound(aux.begin(), aux.end(), b[i]) - aux.begin() + 1;
			
			if(b[i]!=v[i]) vet[b[i]].push_back(i);
		}
		
		build_table();
		printf("%d\n", solve());
	}
	
	
}
