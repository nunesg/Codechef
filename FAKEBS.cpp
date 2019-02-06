#include <bits/stdc++.h>

using namespace std;

#define N 101010

int n, q, v[N], pos[N], query[N], aux[N], cnt[N], okL, okR;
vector<int> tmp, Left, Right;

void busca(int x){
	
	int low = 1;
	int high = n;
	int mid;
	Left.clear();
	Right.clear();
	okL=okR=0;
	while(low<=high){
		
		mid = (low+high)/2;
		//~ printf("mid = %d, pos = %d\n", mid, pos[x]);
		if(mid == pos[x]) break;
		if(mid < pos[x]){
			if(v[mid] > x) Left.push_back(v[mid]);
			else okL++;
			low = mid+1;
		}else{
			if(v[mid] < x) Right.push_back(v[mid]);
			else okR++;
			high = mid-1;
		}
	}
}

void solve(){
	
	for(int i=1; i<=q; i++){
		busca(query[i]);
		
		//~ printf("query[%d] = %d\n", i, query[i]);
		//~ for(int x : Left) printf("%d  ", x);
		//~ printf("\n");
		//~ for(int x : Right) printf("%d  ", x);
		//~ printf("\n");
		
		int menores = cnt[query[i]-1];
		int maiores = n - menores - 1;
		
		
		
		if(maiores < Right.size()+okR || menores < Left.size()+okL) printf("-1\n");
		else{
			int a = max(Right.size(), Left.size());
			printf("%d\n", a);
		}
		
	}
	
	
}


int main(){
	
	int tc;
	scanf("%d", &tc);
	
	while(tc--){
		scanf("%d %d", &n, &q);
		tmp.clear();
		for(int i=1; i<=n; i++){
			scanf("%d", &v[i]);
			tmp.push_back(v[i]);
		}
		
		sort(tmp.begin(), tmp.end());
		for(int i=1; i<=n; i++){
			v[i] = lower_bound(tmp.begin(), tmp.end(), v[i]) - tmp.begin()+1;
			pos[v[i]] = i;
		}
		
		for(int i=1; i<=q; i++){
			scanf("%d", &query[i]);
			query[i] = lower_bound(tmp.begin(), tmp.end(), query[i]) - tmp.begin()+1;
		}
		
		memset(cnt, 0, sizeof cnt);
		for(int i=1; i<=n; i++){
			cnt[v[i]]++;
		}
		for(int i=1; i<=n; i++) cnt[i]+=cnt[i-1];
		
		
		solve();
		
	}
	
	
}
