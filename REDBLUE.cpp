#include <bits/stdc++.h>

using namespace std;

#define N 2020

struct pv{
	
	int x, y, c;
	
	pv(){}
	pv(int i, int j) : x(i), y(j), c(0) {}
	pv(int i, int j, int k) : x(i), y(j), c(k) {}
	
	pv operator - (pv g){
		return pv(x-g.x, y-g.y, c);
	}
	
	long long operator ^ (pv g){
		return x*1LL*g.y - y*1LL*g.x;
	}
	
	int q(){
		if(x>0 && y>=0) return 1;
		if(x<=0 && y> 0) return 2;
		if(x<0 && y<=0) return 3;
		if(x>=0 && y<0) return 4;
		if(x == 0 && y == 0) return 0;
	}
};


pv pivo, vet[N], v[N];
vector<pv> up, down;
int n, R, B, c[3];

bool comp(pv a, pv b){
	a = a-pivo;
	b = b-pivo;
	if(a.q() != b.q()) return a.q() < b.q();
	return (a^b) > 0;
}

void build(){
	up.clear();
	down.clear();
	c[1] = c[2] = 0;
	for(int i=0; i<n; i++){
		v[i] = v[i]-pivo;
		if(!i) continue;
		if(v[i].q() <= 2) {
			up.push_back(v[i]);
			c[v[i].c]++;
		}else down.push_back(v[i]);
	}
}

void add(pv a){
	c[a.c]++;
}
void remove(pv a){
	c[a.c]--;
}

int calc(){
	int red = c[1], blue = c[2];
	//~ printf("red = %d, blue = %d\n", red, blue);
	return min(R-red + blue, B-blue + red);
}



int solve(){
	
	int ans = INT_MAX;
	
	for(int i=0; i<n; i++){
		pivo = vet[i];
		for(int j=0; j<n; j++) v[j] = vet[j];
		sort(v, v+n, comp);
		
		//~ printf("\npivo = (%d, %d)\n\n", pivo.x, pivo.y);
		//~ for(int i=0; i<n; i++){
			//~ printf("v[%d] = (%d, %d)\n", i, v[i].x, v[i].y);
		//~ }
		build();
		
		
		
		int a, b = a = 0;
		ans = min(ans, calc());
		while(a<up.size() && b<down.size()){
			
			pv p = up[a], q = down[b];
			
			if((p^q) > 0){
				add(q);
				b++;
			}else {
				remove(p);
				a++;
			}
			ans = min(ans, calc());
		}
		
		while(a<up.size()){
			remove(up[a++]);
			ans = min(ans, calc());
		}
		while(b<down.size()){
			add(down[b++]);
			ans = min(ans, calc());
		}
	}
	return ans;
}



int main(){
	int tc;
	scanf("%d", &tc);
	
	while(tc--){
		
		scanf("%d %d", &R, &B);
		n = R+B;
		c[1] = c[2] = 0;
		int x, y;
		for(int i=0; i<R; i++){
			scanf("%d %d", &x, &y);
			vet[i] = pv(x, y, 1);
			v[i] = vet[i];
		}
		for(int i=0; i<B; i++){
			scanf("%d %d", &x, &y);
			vet[i+R] = pv(x, y, 2);
			v[i+R] = vet[i+R];
		}
		
		printf("%d\n", solve());
		
	}
	
	
}



