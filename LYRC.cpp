#include <bits/stdc++.h>

using namespace std;

#define ALF 130
#define N 550

string s;


struct no{
	
	no *nxt[ALF], *pai, *suffix_link;
	int fim, ans;
	char c;
	
	no (char k, no *p){
		c = k;
		pai = p;
		for(int i=0; i<ALF; i++) nxt[i] = NULL;
		suffix_link = NULL;
		fim = 0;
		ans = 0;
	}
	
	no *insert(int i){
		
		if(i == s.size()) {
			fim++;
			return this;
		}
		
		if(!nxt[s[i]]) nxt[s[i]] = new no(s[i], this);
		return nxt[s[i]]->insert(i+1);
	}
	
	
	void build_sf(){
		
		no *root = this;
		queue<no*> q;
		
		for(int i=0; i<ALF; i++) if(nxt[i]) q.push(nxt[i]);
		
		while(q.size()){
			
			no *u = q.front(); q.pop();
			no *tmp = u->pai->suffix_link;
			
			char letra = u->c;
			
			while(tmp && !tmp->nxt[letra]) tmp = tmp->suffix_link;
			
			u->suffix_link = tmp ? tmp->nxt[letra] : root;
			
			u->fim += u->suffix_link->fim;
			
			for(int i=0; i<ALF; i++) if(u->nxt[i]) q.push(u->nxt[i]);
		}
	}
	
	void bfs(){
		no *root = this;
		queue<no*> q;
		
		for(int i=0; i<ALF; i++) if(nxt[i]) q.push(nxt[i]);
		
		while(q.size()){
			
			no *u = q.front(); q.pop();
			
			no *tmp = u->suffix_link;
			while(tmp){
				tmp->ans+= u->ans;
				tmp = tmp->suffix_link;
			}
			
			for(int i=0; i<ALF; i++) if(u->nxt[i]) q.push(u->nxt[i]);
		}
	}
	
};


no *trie, *no_[N];

no *get_nxt(no *u, char letra){
	no *tmp = u;
	while(tmp && !tmp->nxt[letra]) tmp = tmp->suffix_link;
	return tmp ? tmp->nxt[letra] : trie;
}

void query(int u, no *pos){
	
	if(pos->fim){
		pos->ans++;
	}
	
	if(u == s.size()) return;
	
	no *tmp = get_nxt(pos, s[u]);
	query(u+1, tmp);
}


int main(){
	
	int n, m;
	cin >> n; cin.ignore();
	
	trie = new no('$', NULL);
	
	for(int i=0; i<n; i++){
		cin >> s; cin.ignore();
		no_[i] = trie->insert(0);
	}
	
	trie->build_sf();
	cin >> m; cin.ignore();
	while(m--){
		cin >> s; cin.ignore();
		query(0, trie);
	}
	trie->bfs();
	
	for(int i=0; i<n; i++) cout << no_[i]->ans << endl;
	
}
