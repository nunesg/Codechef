#include <bits/stdc++.h>

using namespace std;

#define N 101010
#define L 18

struct no{
	int level[L];
	no(){ memset(level, 0, sizeof level); }
}tr[N<<1];

int n, k;

void join(int a, int b, int c){
	for(int i=0; i<L; i++){
		tr[a].level[i]|= (tr[b].level[i] | tr[c].level[i]);
	}
}

void build(int p){
	
	if(p>n) return;
	int nxt = p<<1;
	build(nxt);
	build(nxt+1);
	
	join(p, nxt, nxt+1);
}

int query(int p){
	
	int l = 31-__builtin_clz(p);
	int mask = 0;
	for(int i=l; i<L; i++){
		mask|= tr[p].level[i];
		if(__builtin_popcount(mask) >= k) return i-l;
	}
	return -1;
}

int main(){
	int tc, a, u, q;
	scanf("%d", &tc);
	while(tc--){
		
		scanf("%d", &n);
		for(int i=1; i<=n; i++){
			scanf("%d", &a);
			for(int j=0; j<L; j++) tr[i].level[j] = 0;
			tr[i].level[ 31 - __builtin_clz(i) ] = (1<<a);
		}
		
		build(1);
		scanf("%d", &q);
		while(q--){
			scanf("%d %d", &u, &k);
			printf("%d\n", query(u));
		}
	}
}
