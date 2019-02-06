#include <bits/stdc++.h>

using namespace std;

#define N 101010

int n, m, q;
vector< vector<int> > mat;
char sa[N], sb[N];

int main(){
	
	int tc;
	scanf("%d", &tc);
	
	while(tc--){
		scanf(" %s", sb);
		scanf(" %s", sa);
		
		n = strlen(sa), m = strlen(sb);
		mat.resize(n+1);
		for(int i=0; i<=n; i++){
			if(i<7) mat[i].resize(m+1);
			else mat[i].resize(7);
		}
		
		for(int i=1; i<=n; i++){
			mat[i][0] = sa[i-1]-'0';
		}
		
		for(int i=1; i<=m; i++){
			mat[0][i] = sb[i-1]-'0';
		}
		
		for(int i=1; i<=n; i++){
			for(int j=1; j<mat[i].size(); j++){
				mat[i][j] = !(mat[i-1][j] & mat[i][j-1]);
			}
		}
		scanf("%d", &q);
		int x, y;
		while(q--){
			
			scanf("%d %d", &x, &y);
			
			if(x<7 || y<7){
				printf("%d", mat[x][y]);
			}else{
				
				int ini = mat[5][5];
				int sum = x-5+y-5;
				if(sum%2) ini^=1;
				printf("%d", ini);
			}
		}
		printf("\n");
	}
}
