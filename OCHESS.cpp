#include <bits/stdc++.h>

using namespace std;

#define N 202


struct player{
	int rating, t, l, r, rated, color;
}vet[N];

int n, seen[N];

bool can_match(int i, int j){
	bool cor = (vet[i].color == 1 && vet[j].color == 0 ||
		   vet[i].color == 0 && vet[j].color == 1 ||
		   vet[i].color == 2 && vet[j].color == 2);
	
	bool ans = (vet[i].rated == vet[j].rated && vet[i].t == vet[j].t && cor && 
		(vet[j].rating>=vet[i].l && vet[j].rating<=vet[i].r) && 
		(vet[i].rating>=vet[j].l && vet[i].rating<=vet[j].r));
	return ans;
}


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	string a, b;
	int tc;
	cin >> tc;
	while(tc--){
		
		memset(seen, 0, sizeof seen);
		
		cin >> n;
		
		for(int i=1; i<=n; i++){
			
			cin >> vet[i].rating >> vet[i].l >> vet[i].r >> vet[i].t >> a >> b;
			
			vet[i].rated = (a == "rated");
			vet[i].color = ((b == "white") ? 0 : (b=="black" ? 1 : 2) );
			
			int match = -1;
			for(int j=1; j<i; j++){
				if(seen[j]) continue;
				
				if(can_match(i, j)) {
					match = j;
					seen[j] = 1;
					break;
				}
			}
			if(match!=-1) {
				cout << match << endl;
				seen[i] = 1;
			}else cout << "wait\n";
		}
		
	}
	
	
}
