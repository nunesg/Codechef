#include <bits/stdc++.h>
 
using namespace std;
 
#define N 101010
#define block 555
 
typedef long long ll;
 
ll n, q, h[N], blc[N];
ll value[N], ini[N/block+2], acc[N/block+2][block], soma[N/block+2];
vector<int> vet[N/block+2];
 
void build_block(ll bl){
	
	ll ind = ini[bl];
	ll sum=0;
	vet[bl].clear();
	for(ll k=0; ind<=n && k<block; ind++, k++){
		blc[ind] = bl;
		acc[bl][k] = sum+h[ind];
		value[ind] = acc[bl][k];
		sum+=h[ind];
		
		if(!vet[bl].empty() && ind-vet[bl].back()>100) continue;
		if(vet[bl].empty() || value[vet[bl].back()] < value[ind]) vet[bl].push_back(ind);
	}
	soma[bl] = sum;
}
 
void build(){
	
	ll ind=1;
	for(ll bl=0; ind<=n; bl++){
		ini[bl] = ind;
		build_block(bl);
		ind+=block;
	}
}
 
void update(ll pos, ll x){
	h[pos]+=x;
	build_block(blc[pos]);
}
 
ll find_first(ll bl, ll val){
	ll sz = vet[bl].size();
	ll ans=-1;
	for(ll k= 31-__builtin_clz(sz); k>=0; k--){
		if(ans+(1<<k) < sz && value[vet[bl][ans+(1<<k)]]<=val) ans+=(1<<k);
	}
	return ans+1;
}
 
ll query(ll pos, ll k){
	
	ll s=0, hat=0;
	for(ll i=pos+1; blc[i]==blc[pos] && i<=n; i++){
		s+=h[i];
		
		if(i-pos>100) return pos;
		if(s>hat) {
			pos = i;
			hat = s;
			k--;
		}
		if(k == 0) return pos;
	}
	
	for(ll bl=blc[pos]+1; bl<=blc[n]; bl++){
		
		//~ ll f = find_first(bl, hat-s);
		ll f = upper_bound(vet[bl].begin(), vet[bl].end(), hat-s, [](int a ,int b){ return a < value[b]; }) - vet[bl].begin();
		if(f == vet[bl].size()) return pos;
		
		
		ll qtd = (int)vet[bl].size() - f;
		ll ind = vet[bl][f];
		if(ind-pos > 100) return pos;
		
		if(qtd>=k){
			pos = vet[bl][f+k-1];
			return pos;
		}else{
			
			k-=qtd;
			pos = vet[bl][f+qtd-1];
			hat = s+value[pos];
			s+=soma[bl];
		}
	}
	
	return pos;
}
 
int main(){
	
	scanf("%lld %lld", &n, &q);
	
	for(ll i=1; i<=n; i++){
		scanf("%lld", &h[i]);
	}
	for(ll i=n; i>0; i--) h[i] = h[i]-h[i-1];
	
	build();
	ll t, a, b, c;
	while(q--){
		scanf("%lld %lld %lld", &t, &a, &b);
		
		if(t == 1){
			printf("%lld\n", query(a, b));
		}else{
			scanf("%lld", &c);
			
			update(a, c);
			if(b<n) update(b+1, -c);
		}
	}
}
