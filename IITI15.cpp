//Sherlock and inversions

#include <bits/stdc++.h>

using namespace std;

#define N 20101
//~ #define BLOCK 200

struct query{
	int l, r, id;
}q[N];

int n, m, bit[N], cor[N], vet[N], soma[N], answer[N], ans, BLOCK;

bool comp(query a, query b){
	
	if(a.l / BLOCK != b.l / BLOCK){
		return a.l / BLOCK < b.l / BLOCK;
	}
	return a.r < b.r;
}

void update(int pos, int val){ for(; pos<N; pos+= (pos&(-pos))) bit[pos]+=val; }

int sum(int pos){
	int ans=0;
	for(; pos; pos-= (pos&(-pos))) ans+=bit[pos];
	return ans;
}

void addR(int i){
	
	int c = cor[i];
	
	int tot = sum(n+10);
	int bf = sum(c);
	int inv = tot-bf;
	
	ans+=inv;
	
	update(c, 1);
}

void addL(int i){
	
	int c = cor[i];
	
	int inv = sum(c-1);
	
	ans+=inv;
	update(c, 1);
}

void removeR(int i){
	
	int c =cor[i];
	
	int tot = sum(n+10);
	int bf = sum(c);
	int inv = tot-bf;
	
	ans-=inv;
	update(c, -1);
}

void removeL(int i){
	
	int c =cor[i];
	
	int inv = sum(c-1);
	
	ans-=inv;
	update(c, -1);
}

int main(){
	
	set<int> aux;
	map<int, int> mapa;
	
	while(scanf("%d", &n)!=EOF){
		
		BLOCK = sqrt(n)+1;
		mapa.clear();
		aux.clear();
		memset(soma, 0, sizeof soma);
		memset(bit, 0, sizeof bit);
		
		int cont=1, a, b;
		for(int i=0; i<n; i++){
			scanf("%d", &cor[i]);
			aux.insert(cor[i]);
		}
		
		for(set<int>::iterator it = aux.begin(); it != aux.end(); it++){
			mapa[*it] = cont++;
		}
		
		for(int i=0; i<n; i++){
			cor[i] = mapa[cor[i]];
			//~ printf("cor[%d] = %d\n", i, cor[i]);
		}
		
		scanf("%d", &m);
		
		for(int i=0; i<m; i++){
			scanf("%d %d", &a, &b); a--; b--;
			
			q[i].l = a;
			q[i].r = b;
			q[i].id = i;
		}
		
		sort(q, q+m, comp);
		
		//~ for(int i=0; i<m; i++){
			//~ printf("%d %d, id=%d\n", q[i].l+1, q[i].r+1, q[i].id);
		//~ }
		
		int i, j=i=0; ans=0;
		
		for(int k=0; k<m; k++){
			query p = q[k];
			
			while(j <= p.r)  addR(j++);
			while(i > p.l)  addL(--i);
			while(j > p.r+1)  removeR(--j);
			while(i < p.l)  removeL(i++);
			
			answer[p.id] = ans;
		}
		for(int i=0; i<m; i++) printf("%d\n", answer[i]);
	}
	
}
