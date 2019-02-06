#include <bits/stdc++.h>

using namespace std;

#define N 101010
#define M 9
#define block 333

typedef long long ll;

ll n, q, sum[N/block+2][M], v[N][M], lazy[N/block+2], ini[N/block+2], blc[N];

void build_block(ll bl, ll l, ll r){
	
	memset(sum[bl], 0, sizeof sum[bl]);
	
	for(ll i=l; i<=r; i++){
		for(ll j=0; j<M; j++){
			sum[bl][j] += v[i][j]*v[i][j];
		}
	}
}

void build(){
	ll ind=1;
	for(ll bl=0; ind<=n; bl++){
		build_block(bl, ind, min(ind+block-1, n));
		ind+=block;
	}
}

void rotate(ll bl, ll vet[], ll qtd){
	ll aux[M];
	for(ll i=0; i<M; i++){
		aux[i] = vet[(i+qtd)%M];
	}
	for(ll i=0; i<M; i++){
		sum[bl][i]-= vet[i]*vet[i];
		vet[i] = aux[i];
		sum[bl][i]+= vet[i]*vet[i];
	}
}

void update(ll l, ll r){
	
	ll bl = blc[l], br = blc[r];
	ll aux[M];
	if(bl == br){
		for(ll i=l; i<=r; i++){
			rotate(bl, v[i], 1);
		}
		return;
	}
	
	for(ll i=l; blc[i]==bl; i++){
		rotate(bl, v[i], 1);
	}
	for(ll i=r; blc[i] == br; i--){
		rotate(br, v[i], 1);
	}
	
	for(ll b=bl+1; b<br; b++) lazy[b] = (lazy[b]+1)%M;
}

ll query(ll l, ll r){
	
	ll bl = blc[l], br = blc[r];
	
	if(bl == br){
		ll ans=0;
		for(ll i=l; i<=r; i++){
			ans+= v[i][lazy[bl]]*v[i][lazy[bl]];
		}
		return ans;
	}
	ll ans=0;
	for(ll i=l; blc[i] == bl; i++) ans+= v[i][lazy[bl]]*v[i][lazy[bl]];
	for(ll i=r; blc[i] == br; i--) ans+= v[i][lazy[br]]*v[i][lazy[br]];
	
	for(ll b=bl+1; b<br; b++) ans+= sum[b][lazy[b]];
	return ans;
	
}


int main(){
	
	scanf("%lld %lld", &n, &q);
	
	
	ll i=1;
	
	for(ll bl=0; i<=n; bl++){
		ini[bl] = i;
		for(ll k=0; k<block && i<=n; k++, i++){
			blc[i] = bl;
			scanf("%lld", &v[i][0]);
			
			ll qtd = 0, a = v[i][0];
			
			while(a%2 == 0){ a/=2; qtd++; }
			
			for(ll j=1; j<M; j++){
				if(i%2){
					v[i][j] = a*( 1<<((qtd-j+M)%M) );
				}else{
					v[i][j] = a*( 1<<((qtd+j)%M) );
				}
			}
		}
	}
	
	build();
	ll t, l, r;
	while(q--){
		scanf("%lld %lld %lld", &t, &l, &r);
		if(t){
			printf("%lld\n", query(l, r));
		}else{
			update(l, r);
		}
	}
}
