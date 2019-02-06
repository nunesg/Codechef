#include <bits/stdc++.h>

using namespace std;

#define N 333333

typedef pair<int, int> ii;

struct query{
	char op;
	int p, len;
	string str;
};

int q, bit[N], pos[N], num[N], ans[N];
string aux;
query Q[N];

void update(int pos, int val){
	for(; pos<N; pos+=pos&(-pos)) bit[pos]+=val;
}

int kth(int k){
	
	int ans=0;
	for(int j=20; j>=0; j--){
		if(ans+(1<<j)>=N) continue;
		if(bit[ans+(1<<j)]<k){
			ans+=(1<<j);
			k-=bit[ans];
		}
	}
	return ans+1;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> q;
	int a, b;
	char op;
	int sum=0;
	for(int i=0; i<q; i++){
		cin >> Q[i].op >> Q[i].p;
		aux.clear();
		if(Q[i].op == '+') {
			cin >> aux;
			Q[i].str = aux;
		}else cin >> Q[i].len;
		sum+=aux.size();
	}
	
	set<int> v;
	for(int i=1; i<=sum; i++) v.insert(i);

	int qtd=0;
	for(int i=q-1; i>=0; i--){
		
		if(Q[i].op == '?') continue;
		
		for(int j=0; j<Q[i].str.length(); j++){
			
			int id = *v.lower_bound(Q[i].p+j+1);
			ans[id] = Q[i].str[j];
			update(id, 1);
			pos[sum-qtd-j] = id;
			v.erase(id);
		}
		qtd+=Q[i].str.size();
	}
	
	stack<string> pilha;
	//~ printf("oi\n");
	for(int i=q-1; i>=0; i--){
		aux.clear();
		if(Q[i].op == '?'){
			for(int j=0; j<Q[i].len; j++){
				aux.push_back((char)ans[kth(Q[i].p+j)]);
			}
			pilha.push(aux);
			continue;
		}
		
		for(int j=0; j<Q[i].str.size(); j++){
			//~ printf("oi\n");
			update(pos[sum], -1);
			sum--;
		}
	}
	while(pilha.size()){
		cout << pilha.top() << "\n";
		pilha.pop();
	}
}
