#include <bits/stdc++.h>

using namespace std;

#define N 41

long long int n, fib[N], fibmax;
int main(){
	int tc;
	fib[0] = 1; fib[1] = 2;
	for(int i=2; i<N; i++){
		fib[i] = fib[i-1] + fib[i-2];
		printf("fib[%d] = %lld\n", i, fib[i]);
		if(fib[i] > 1000000000LL) {
			fibmax = i;
			break;
		}
	}
	cout << fibmax << endl;
}
