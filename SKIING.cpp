#include <bits/stdc++.h>

using namespace std;

#define N 1010

int mat[N][N], n, m, seen[N][N], grau[N*N];
int r[]={-1, 0, 1, 0};
int c[]={0, -1, 0, 1};

bool valid(int i, int j){
	return i>=0 && i<n && j>=0 && j<m;
}


void flood(int i, int j, int cc){
	
	seen[i][j] = cc;
	
	for(int k=0; k<4; k++){
		int x = i+r[k];
		int y = j+c[k];
		if(!valid(x, y)) continue;
		
		if(mat[x][y] == mat[i][j] && !seen[x][y]){
			flood(x, y, cc);
		}
	}
	
	
}


int main(){
	
	
	int tc;
	scanf("%d", &tc);
	
	while(tc--){
		
		scanf("%d %d", &n, &m);
		memset(seen, 0, sizeof seen);
		memset(grau, 0, sizeof grau);
		for(int i=0; i<n; i++){
			for(int j=0; j<m; j++){
				scanf("%d", &mat[i][j]);
			}
		}
		int cc=1;
		for(int i=0; i<n; i++){
			for(int j=0; j<m; j++){
				if(!seen[i][j]){
					flood(i, j, cc++);
				}
			}
		}
		
		for(int i=0; i<n; i++){
			for(int j=0; j<m; j++){
				for(int k=0; k<4; k++){
					int x = i+r[k];
					int y = j+c[k];
					if(!valid(x, y)) continue;
					
					if(mat[i][j] > mat[x][y]) grau[seen[x][y]]++;
				}
			}
		}
		
		int ans=0;
		for(int i=1; i<cc; i++){
			ans+= (grau[i]==0);
		}
		printf("%d\n", ans);
	}
	
	
}
