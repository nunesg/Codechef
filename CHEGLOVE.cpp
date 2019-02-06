#include <bits/stdc++.h>

using namespace std;

#define N 101010

int n, f[N], v[N];

bool front(){
	for(int i=1; i<=n; i++) if(f[i] > v[i]) return false;
	return true;
}
bool back(){
	for(int i=1; i<=n; i++) if(f[i] > v[n-i+1]) return false;
	return true;
}

int main(){
	
	
	int tc;
	scanf("%d", &tc);
	
	while(tc--){
		
		scanf("%d", &n);
		
		for(int i=1; i<=n; i++) scanf("%d", &f[i]);
		for(int i=1; i<=n; i++) scanf("%d", &v[i]);
		
		bool a = front();
		bool b = back();
		
		if(a && b) printf("both\n");
		else if(a) printf("front\n");
		else if(b) printf("back\n");
		else printf("none\n");
		
	}
	
	
}
