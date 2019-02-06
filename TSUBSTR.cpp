#include <bits/stdc++.h>

using namespace std;

#define N 251010
#define ALF 26

typedef long long int ll;

struct state{
	int len, link, nxt[ALF];
}stt[N<<1];

string s, alf;
int n, m, last[N<<1], sz;
ll dp[N<<1];
vector<int> adj[N];

void init(){
	stt[0] = {0, -1};
	memset(stt[0].nxt, 0, sizeof stt[0].nxt);
	sz=0;
}

int add(int last, int c){
	int p, q, clone;
	if(stt[last].nxt[c]) {
		p = last;
		q = stt[last].nxt[c];
		
		if(stt[q].len == stt[p].len+1) return q;
		
		clone = ++sz;
		
		stt[clone] = stt[q];
		stt[clone].len = stt[p].len+1;
		
		stt[q].link = clone;
		
		for(; p!=-1 && stt[p].nxt[c] == q; p = stt[p].link) stt[p].nxt[c] = clone;
		return clone;
	}
	
	int curr = ++sz;
	
	for(p = last; p!=-1 && !stt[p].nxt[c]; p = stt[p].link) stt[p].nxt[c] = curr;
	
	if(p==-1){
		stt[curr].link = 0;
	}else{
		q = stt[p].nxt[c];
		if(stt[q].len == stt[p].len+1){
			stt[curr].link = q;
		}else{
			clone = ++sz;
			
			stt[clone] = stt[q];
			stt[clone].len = stt[p].len+1;
			
			stt[q].link = stt[curr].link = clone;
			
			for(; p!=-1 && stt[p].nxt[c] == q; p = stt[p].link) stt[p].nxt[c] = clone;
		}
	}
	stt[curr].len = stt[last].len+1;
	return curr;
}

void dfs(int u, int p){
	
	last[u] = add(last[p], s[u]-'a');
	
	for(int v : adj[u]){
		if(v == p) continue;
		dfs(v, u);
	}
}

void build(int u){
	
	if(dp[u]) return;
	dp[u] = 1;
	
	for(int i=0; i<ALF; i++){
		if(!stt[u].nxt[i]) continue;
		int v = stt[u].nxt[i];
		build(v);
		dp[u]+=dp[v];
	}
}


void solve(int u, ll k){
	
	if(k<=0){
		cout << s << endl;
		return;
	}
	
	for(int i=0; i<ALF; i++){
		int c = alf[i]-'a';
		if(!stt[u].nxt[c]) continue;
		int v = stt[u].nxt[c];
		
		if(dp[v] < k) k-=dp[v];
		else{
			s.push_back(alf[i]);
			solve(v, k-1);
			return;
		}
	}
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	string aux;
	cin >> n >> m;
	cin >> aux;
	s = " "+aux;
	int a, b;
	for(int i=1; i<n; i++){
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	
	init(); last[0] = 0;
	dfs(1, 0);
	
	memset(dp, 0, sizeof dp);
	
	build(0);
	cout << dp[0] << endl;
	ll k;
	while(m--){
		s.clear();
		cin >> alf >> k;
		if(k>dp[0]) cout << -1 << endl;
		else solve(0, k-1);
	}
}
