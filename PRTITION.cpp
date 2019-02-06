#include <bits/stdc++.h>

using namespace std;

#define N 1000001

typedef long long ll;
typedef pair<int, int> ii;

int n, x;
char vet[N];
vector<int> adj[N];

void colore(int u, int p, int c){
	
	vet[u] = c;
	
	for(int v : adj[u]){
		if(v == p) continue;
		colore(v, u, c^1);
	}
	
}

bool solve(){
	
	priority_queue<ii> pq;
	
	for(int i=1; i<=n; i++) if(i!=x) pq.push(ii(i, i));
	
	while(pq.size() > 1){
		
		ii foo = pq.top(); pq.pop();
		int x1 = foo.first, v1 = foo.second;
		foo = pq.top(); pq.pop();
		int x2 = foo.first, v2 = foo.second;
		
		int dif = x1-x2;
		
		adj[v1].push_back(v2);
		adj[v2].push_back(v1);
		
		pq.push(ii(dif, v1));
	}
	
	if(pq.top().first != 0) return false;
	if(x==1) colore(2, -1, 0);
	else colore(1, -1, 0);
	
	return true;
	
}

int main(){
	
	int t;
	scanf("%d", &t);
	while(t--){
		scanf("%d %d", &x, &n);
		for(int i=1; i<=n; i++) adj[i].clear();
		ll tot = (n*1LL*(n+1))/2;
		
		tot-=x;
		
		if(tot%2){
			printf("impossible\n");
			continue;
		}
		
		vet[x] = 2;
		
		if(!solve()){
			printf("impossible\n");
		}else{
			for(int i=1; i<=n; i++) printf("%d", vet[i]);
			printf("\n");
		}
		
	}
	
}
