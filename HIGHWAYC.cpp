#include <bits/stdc++.h>

using namespace std;

#define N 101
#define eps 0.000001

struct car{
	long double pos, v, len;
	int dir;
	void operator *= (long double k){
		pos = pos+(v*k);
	}
}vet[N];


int n;
long double f, s, y;

long double tempo(int id, long double t){
	car c = vet[id];
	c*=t;
	if(c.pos - c.len >= eps) return 0.0;
	return (c.len - c.pos)/c.v;
}

bool can(int it, long double t){
	car c = vet[it];
	c*=t;
	
	if(c.pos - c.len >= eps) return true;
	if(c.pos >= eps) return false;
	return (-c.pos/c.v) >= f+eps;
}

long double solve(int it, long double t){
	if(it == n) return t;
	if(can(it, t)) return min(solve(it+1, t+f), solve(it+1, t+f + tempo(it, t)));
	else return solve(it+1, t+f+tempo(it, t));;
}


int main(){
	
	int tc;
	cin >> tc;
	
	while(tc--){
		
		cin >> n >> s >> y;
		
		f = y/s;
		
		for(int i=0; i<n; i++){
			cin >> vet[i].v;
		}
		for(int i=0; i<n; i++){
			cin >> vet[i].dir;
			if(!vet[i].dir) vet[i].dir = -1;
		}
		for(int i=0; i<n; i++){
			cin >> vet[i].pos;
			vet[i].pos*=vet[i].dir;
		}
		for(int i=0; i<n; i++){
			cin >> vet[i].len;
		}
		
		cout << fixed << setprecision(20) << solve(0, 0.0) << "\n";
	}
	
	
}
