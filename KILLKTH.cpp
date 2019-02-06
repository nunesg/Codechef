#include <bits/stdc++.h>
 
using namespace std;
 
#define N 2020
#define ALF 27
 
string s;
char answer;
 
struct no{
	
	no *nxt[ALF];
	int h, sum, cont;
	char letra;
	
	no(char c, int d){
		letra = c;
		memset(nxt, 0, sizeof nxt);
		h = d;
		sum = cont = 0;
	}
	
	void insert(int i){
		cont++;
		if(i == s.size()) return;
		
		int c = s[i]-'a';
		
		if(!nxt[c]) nxt[c] = new no(c+'a', h+1);
		nxt[c]->insert(i+1);
	}
	
	void build(){
		//~ printf("letra = %c, h = %d, cont = %d\n", letra, h, cont);
		sum = h*cont;
		for(int i=0; i<ALF; i++){
			if(!nxt[i]) continue;
			nxt[i]->build();
			sum+=nxt[i]->sum;
		}
		
		//~ printf("letra %c, sum = %d\n", letra, sum);
	}
	
	int query(int k){
		//~ printf("k antes = %d\n", k);
		int aux = h*cont;
		
		//~ printf("k depois = %d\n", k);
		//~ printf("aux = %d\n", aux);
		if(aux>=k){
			k%=h;
			//~ printf("k = %d\n", k);
			if(k == 0) answer = letra;
			else k=(k-h);
			return k+1;
		}
		
		k -=aux;
		
		for(int i=0; i<ALF; i++){
			if(!nxt[i]) continue;
			
			if(nxt[i]->sum >= k){
				int x = nxt[i]->query(k);
				if(x==0) answer = letra;
				return x+1;
			}else k-=nxt[i]->sum;
		}
	}
};
 
 
 
int n, q;
string str;
 
no *root;
 
 
 
int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> str;
	root = new no('$', 0);
	for(int i=0; i<str.size(); i++){
		s = str.substr(i);
		root->insert(0);
	}
	root->build();
	
	
	
	cin >> q;
	long long k, g=0, p, m;
	while(q--){
		cin >> p >> m;
		k = (p*g)%m + 1;
		//~ cin >> k;
		root->query(k);
		//~ cout << "k = " << k << endl;
		g+=answer;
		cout << answer << endl;
	}
	
}
