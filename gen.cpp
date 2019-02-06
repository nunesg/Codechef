#include <bits/stdc++.h>

using namespace std;

int main(){
	for(int i=2; i<=7; i++){
		long long int sz = i*(i-1)/2, pot=1;
		for(int j=1; j<=i && pot<=100000LL; j++){
			printf("%d %d\n", i, j);
			pot*=sz;
			//~ printf("pot = %lld\n", pot);
		}
	}
}
