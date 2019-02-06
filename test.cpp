#include <bits/stdc++.h>

using namespace std;

#define N 1010

int main(){
	srand(time(NULL));
	printf("32\n");
	for(int mask=0; mask<(1<<5); mask++){
		for(int k=0; k<5; k++){
			if(mask&(1<<k)) printf("b");
			else printf("a");
		}
		printf(" %d\n", rand()%10 + 1);
	}
	
}
