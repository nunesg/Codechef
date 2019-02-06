#include <bits/stdc++.h>

using namespace std;

#define N 1010
#define ALF 130

string s;
int at;

struct no{
	
	no *nxt[ALF], *pai, *suffix_link;
	int fim, num;
	char c;
	
	no (char k, no *p){
		pai = p;
		c = k;
		for(int i=0; i<ALF; i++) nxt[i] = NULL;
		fim = 0;
		suffix_link = NULL;
		num = at++;
	}
	
	
	void insert(int i){
		
		if(i == s.size()){
			fim++;
			return;
		}
		
		if(!nxt[s[i]]) nxt[s[i]] = new no(s[i], this);
		
		nxt[s[i]]->insert(i+1);
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
	
};

string txt;
no *trie;
int dp[N][N], n, m;

no *get_nxt(no *u, char k){
	no *tmp = u;
	while(tmp && !tmp->nxt[k]) tmp = tmp->suffix_link;
	return tmp ? tmp->nxt[k] : trie;
}


int solve(int i, int p, no *pos){
	
	int &ans = dp[i][p];
	
	if(ans!=-1) return ans;
	
	if(pos->fim){
		ans = pos->fim;
	}else ans=0;
	if(i == n) return ans;
	
	no *tmp;
	
	if(txt[i]=='?'){
		
		for(int k=0; k<26; k++){
			tmp = get_nxt(pos, k+'a');
			ans = max(ans, solve(i+1, tmp->num, tmp)+pos->fim);
		}
		return ans;
	}else{
		tmp = get_nxt(pos, txt[i]);
		return ans = max(ans, solve(i+1, tmp->num, tmp)+pos->fim);
	}
	
}

void print_path(int i, int p, no *pos){
	
	if(i == n) return;
	
	no *tmp;
	
	if(txt[i]=='?'){
		
		for(int k=0; k<26; k++){
			tmp = get_nxt(pos, k+'a');
			
			if(dp[i][p] == dp[i+1][tmp->num] + pos->fim){
				cout << char(k+'a');
				print_path(i+1, tmp->num, tmp);
				return;
			}
		}
		return;
	}else{
		tmp = get_nxt(pos, txt[i]);
		cout << txt[i];
		print_path(i+1, tmp->num, tmp);
		return;
	}
	
}

int main(){
	
	int tc;
	cin >> tc;
	
	while(tc--){
		
		cin >> n >> m;
		getline(cin, s);
		getline(cin, txt);
		at = 0;
		trie = new no('$', NULL);
		
		while(m--){
			getline(cin, s);
			trie->insert(0);
		}
		
		trie->build_sf();
		
		memset(dp, -1, sizeof dp);
		cout << solve(0, 0, trie) << endl;
		print_path(0, 0, trie); cout << endl;
	}
}

