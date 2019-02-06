#include <bits/stdc++.h>

using namespace std;

#define N 101010
#define block 200

int n, m, v[N], bit[block][N];
vector<int> lines[block];

void update(int type, int pos, int val){
	for(; pos<=n; pos+=pos&(-pos)) bit[type][pos]+=val;
}

int query(int type, int pos){
	int s=0;
	for(; pos; pos-=pos&(-pos)) s+= bit[type][pos];
	return s;
}

void build(){
	
	for(int a=1; a<block; a++){
		
		for(int b : lines[a]){
			update(b%a, b, 1);
		}
		
		for(int i=1; i<=n; i++){
			v[i]+= query(i%a, i);
		}
		
		for(int b : lines[a]){
			update(b%a, b, -1);
		}
	}
}

int main(){
	
	scanf("%d %d", &n, &m);
	
	int a, b;
	for(int i=0; i<m; i++){
		
		scanf("%d %d", &a, &b);
		
		if(a>=block){
			for(int x=b; x<=n; x+=a) v[x]++;
		}else lines[a].push_back(b);
	}
	
	build();
	for(int i=1; i<=n; i++) printf("%d%c", v[i], i==n ? '\n' : ' ');
}
