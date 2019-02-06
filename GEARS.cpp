#include <bits/stdc++.h>

using namespace std;

#define N 101010

int n, m, comp[N], cor[N], killed[N], A[N], sz[N];
vector<int> cmp[N];


inline long long gcd(long long a, long long b){
	if(!b) return a;
	return gcd(b, a%b);
}

inline void init(){
	for(int i=1; i<=n; i++){
		comp[i] = i;
		killed[i] = 0;
		cor[i] = 0;
		cmp[i].push_back(i);
	}
}

inline void join(int u, int v){
	
	int cu = comp[u], cv = comp[v];
	if(sz[cu] < sz[cv]) {
		swap(u, v);
		swap(cu, cv);
	}

	bool flag = cor[u]==cor[v];
	if(cu!=cv){
		for(int x : cmp[cv]){
			if(flag) cor[x]^=1;
			comp[x] = cu;
			cmp[cu].push_back(x);
		}
		sz[cu] = cmp[cu].size();
		killed[cu]|=killed[cv];
		return;
	}
	if(cor[u] == cor[v]) killed[cu] = 1;
}


int main(){
	
	scanf("%d %d", &n, &m);
	for(int i=1; i<=n; i++) scanf("%d", &A[i]);
	
	init();
	int t, a, b, c;
	long long int x, y;
	while(m--){
		scanf("%d", &t);
		if(t == 1){
			scanf("%d %d", &a, &b);
			A[a] = b;
		}else
		if(t == 2){
			scanf("%d %d", &a, &b);
			join(a, b);
		}else{
			scanf("%d %d %d", &a, &b, &c);
			if(comp[a]!=comp[b] || killed[comp[a]]) printf("0\n");
			else{
				
				x = 1LL*c*A[a];
				y = A[b];
				long long g = gcd(x, y);
				
				x/=g;
				y/=g;
				if(cor[a]!=cor[b]) printf("-");
				printf("%lld/%lld\n", x, y);
			}
		}
	}
	
	
}
