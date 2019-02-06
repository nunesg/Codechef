#include <bits/stdc++.h>

using namespace std;

#define N 202020
#define ALF 26

struct state{
	int len, link, cnt;
	map<char, int> nxt;
}stt[N<<1];


int n, sz, last, grau[N<<1];
vector<int> vet[N];

void init(){
	grau[0] = N;
	stt[0] = {0, -1, 0};
	stt[0].nxt.clear();
	last = sz = 0;
}


void add(char c){
	
	int curr = ++sz, p, q, clone;
	
	for(p = last; p!=-1 && !stt[p].nxt.count(c); p = stt[p].link) stt[p].nxt[c] = curr;
	
	if(p == -1){
		stt[curr].link = 0;
	}else{
		q = stt[p].nxt[c];
		
		if(stt[p].len + 1 == stt[q].len){
			stt[curr].link = q;
		}else{
			clone = ++sz;
			stt[clone] = stt[q];
			stt[clone].len = stt[p].len+1;
			
			stt[q].link = stt[curr].link = clone;
			
			++grau[clone];
			
			for(; p!=-1 && stt[p].nxt[c] == q; p = stt[p].link) stt[p].nxt[c] = clone;
		}
	}
	stt[curr].cnt = 1;
	stt[curr].len = stt[last].len+1;
	
	++grau[stt[curr].link];
	last = curr;
}


void build(){
	for(int i=0; i<s.size(); i++) add(s[i]);
	queue<int> q;
	for(int i=1; i<=sz; i++) if(!grau[i]) q.push(i);
	
	while(q.size()){
		int u = q.front(); q.pop();
		
		
		vet[stt[u].cnt].push_back(stt[u].len);
		stt[stt[u].link].cnt += stt[u].cnt;
		
		
		if(!(--grau[stt[u].link])){
			q.push(stt[u].link);
		}
	}
	
	
}




int main(){
	
}
