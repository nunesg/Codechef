#include <bits/stdc++.h>

using namespace std;

#define N 301010
#define M 505
#define block 202
#define F first
#define S second

typedef pair<int, int> ii;

struct query{
	char op;
	int x, y;
}input[N];

int m, ini[N], fim[N], inib[N], fimb[N], bit[N], seen[M][M], menor;
unordered_set<ii> active;
vector<ii> v;
map<ii, int> mapa;

void update(int pos, int val){
	for(; pos<N; pos+=pos&(-pos)) bit[pos]+=val;
}

int sum(int pos){
	int s=0;
	for(; pos; pos-=pos&(-pos)) s+=bit[pos];
	return s;
}

void build(int b){
	
	menor = inf;
	v.clear();
	memset(mat, 0, sizeof mat);//O(2e5)
	for(int i=1; i<inib[b]; i++) {//O(Q)
		if(fim[i] > fimb[b]) {
			v.push_back(ii(input[i].x, input[i].y));
			mat[input[i].x][input[i].y]++;
		}
	}
	
	for(int i=0; i<v.zize(); i++){//O(2e5)
		for(int j=i+1; j<v.size(); j++) menor = min(menor, dist(v[i], v[j]));
	}
	
}

int dist(ii a, ii b){
	return (a.F-b.F)*(a.F-b.F) + (a.S-b.S)*(a.S-b.S) + 
}

bool valid(int i, int j){
	return (i>0 && j>0 && i<M && j<M && !seen[i][j]);
}

void flood(int i, int j){
	seen[i][j] = 0;
	for(int k=0; k<4; k++){
		int x = i+dr[k], y = j+dc[k];
		if(seen[x][y]) flood(x, y);
	}
}

int bfs(int inix, int iniy){
	
	queue<ii> q;
	
	q.push_back(ii(inix, iniy));
	seen[inix][iniy] = 1;
	int ans=menor;
	while(q.size()){
		ii foo = q.front(); q.pop();
		
		int x = foo.F, y = foo.S, d = dist(ii(inix, iniy), foo);
		
		if(mat[x][y]) ans = min(ans, d);
		
		for(int k=0; k<4; k++){
			int ux = x+dr[k], uy = y+dc[k];
			if(!valid(ux, uy)) continue;
			int aux = dist(ii(inix, iniy), ii(ux, uy));
			if(aux > ans) continue;
			seen[ux][uy] = 1;
			q.push(ii(ux, uy));
		}
	}
	flood(inix, iniy);
	return ans;
}


int main(){
	
	
	scanf("%d", &q);
	int a, b;
	char op;
	for(int b=0, i=1; i<=m; b++){
		inib[b] = i
		for(int k=0; k<block && i<=m; k++, i++){
			scanf(" %c %d %d", &op, &a, &b);
			if(op == '+') {
				ini[i] = i; fim[i] = m+1;
				mapa[ii(a, b)] = i;
			}else{
				fim[i] = i;
				ini[i] = mapa[ii(a, b)];
				fim[ini[i]] = i;
			}
			input[i] = {op, a, b};
		}
		fimb[b] = i-1;
	}
	
	
	for(int b=0, i=1; i<=m; b++){
		
		build(b);
		active.clear();
		for(int k=0; k<block && i<=m; k++, i++){
			int ans=menor;
			ii ponto = ii(input[i].x, input[i].y);
			if(op[i] == '+'){
				
				for(auto foo : active) {
					int d = dist(foo, ponto);
					update(d, 1);
				}
				ans = min(ans, menor_bit());
				
				if(v.size() < block){
					for(auto foo : v) ans = min(ans, dist(foo, ponto));
				}else{
					ans = min(ans, bfs(input[i].x, input[i].y));
				}
				active.insert(ponto);
			}else{
				
				active.erase(ponto);
				
				for(auto foo : active) {
					int d = dist(foo, ponto);
					update(d, -1);
				}
				
				ans = min(ans, menor_bit());
			}
			printf("%d\n", ans);
		}
		
	}
	
	
	
	
	
}
