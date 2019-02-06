#include <bits/stdc++.h>

using namespace std;

#define N 101010
#define mod 1000000007

int f[N];

int main(){
	
	int tc, n, m, sa, sb, a;
	
	scanf("%d", &tc);
	while(tc--){
		
		scanf("%d %d", &m, &n);
		sa = sb= 0;
		for(int i=0; i<m; i++){
			scanf("%d", &a);
			sa = (sa + m*1LL*a)%mod;
		}
		for(int i=0; i<m; i++){
			scanf("%d", &a);
			sb = (sb + m*1LL*a)%mod;
		}
		
		f[1] = sa;
		f[2] = sb;
		for(int i=3; i<=n; i++) f[i] = (f[i-1]+f[i-2])%mod;
		printf("%d\n", f[n]);
	}
	
}
