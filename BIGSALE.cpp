#include <bits/stdc++.h>

#define N 101010

using namespace std;

int n, qtd[N], p[N], d[N];
double tot, after;

double percent(double p, double x){
	return (p*x)/100.0;
}

int main(){
	
	
	int tc;
	scanf("%d", &tc);
	
	while(tc--){
		
		scanf("%d", &n);
		tot=0.0, after=0.0;
		for(int i=1; i<=n; i++){
			scanf("%d %d %d", &p[i], &qtd[i], &d[i]);
			tot+= qtd[i]*p[i];
			
			double novo = (p[i]+percent(p[i], d[i]));
			after+= (novo - percent(novo, d[i]))*qtd[i];
		}
		
		printf("%.12lf\n", tot-after);
	}
	
	
}
