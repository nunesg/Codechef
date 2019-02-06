#include <bits/stdc++.h>

using namespace std;


#define N 101010
#define M 31

int n, m, acc[N][M];


int main(){
	
	
	scanf("%d %d", &n, &m);
	int a;
	for(int i=1; i<=n; i++){
		scanf("%d", &a);
		for(int j=0; j<M; j++) acc[i][j] = ((a&(1<<j)) != 0)+acc[i-1][j];
	}
	
	int l, r;
	
	while(m--){
		scanf("%d %d", &l, &r);
		
		int ans=0, sz=r-l+1;
		
		for(int i=M-1; i>=0; i--){
			
			int qtd = acc[r][i] - acc[l-1][i];
			
			if(qtd*2<sz) ans+=(1<<i);
		}
		printf("%d\n", ans);
	}
	
	
}
