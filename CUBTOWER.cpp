#include <bits/stdc++.h>

using namespace std;

#define N 201010
#define F first
#define S second
#define block 444
#define base1 499
#define base2 1009
#define mod1 1000000009
#define mod2 1000000007

typedef long long ll;

typedef pair<ll ,ll > ii;

struct pair_hash{
	ll operator () (ii p) const {
		ll ans = ((p.first) << 31LL)+p.second;
		return ans;
	}
};

struct query{
	
	ll type;
	ll l, r, id;
	query(){ l=type=r=id=0; }
	query(ll t, ll a, ll b, ll c){
		type = t;
		l = a;
		r = b;
		id = c;
	}
};

string s;
ll n, m, q, blc[N], ini[N/block+2], v[N], somab[N/block + 2],  occb[N/block + 2], answer[N];
ii hashes[N], pot[N];
vector<ii> hstack[N];
unordered_map< ii , int, pair_hash> mapa;
vector<ll> sizes;
vector<query> Q[N];

void build_blc(){
	ll ind=1;
	for(ll b=0; ind<=n; b++){
		ini[b] = ind;
		for(ll k=0; k<block && ind<=n; k++, ind++){
			blc[ind] = b;
		}
	}
}

ii multiplica(ii a, ii b){
	return ii( (a.F * b.F)%mod1,  (a.S * b.S)%mod2);
}

ii soma(ii a, ii b){
	return ii( (a.F + b.F)%mod1,  (a.S + b.S)%mod2);
}

ii subtrai(ii a, ii b){
	return ii( (a.F - b.F + mod1)%mod1,  (a.S - b.S + mod2)%mod2);
}

void build_pot(){
	pot[0] = ii(1, 1);
	for(ll i=1; i<N; i++) {
		pot[i] = multiplica(pot[i-1], ii(base1, base2));
		//~ if(i<10) printf("pot[%lld] = (%lld, %lld)\n", i, pot[i].F, pot[i].S);
	}
}

ii get_hash(string &str){
	ii ans = ii(0, 0);
	for(ll i=0; i<str.size(); i++){
		ans = soma( ans, multiplica(pot[i], ii(s[i], s[i]) ) );
	}
	//~ printf("ans = (%lld, %lld)\n", ans.F, ans.S);
	return ans;
}



void add_caracter(ll p, char c, ll id){
	
	ii htop = (hstack[p].size() ? hstack[p].back() : ii(0, 0));
	
	htop = soma( multiplica(htop, ii(base1, base2)), ii(c, c));
	hstack[p].push_back(htop);
	//~ printf("htop = (%lld, %lld),   push caracter %c\n", htop.F, htop.S, c);
	ll len = (int)hstack[p].size();
	ii h;
	for(ll sz : sizes){
		
		if(sz > len) continue;
		
		if(sz == len){
			h = htop;
		}else{
			h = subtrai( htop,  multiplica(hstack[p][len-sz-1], pot[sz]) );
		}
		
		//~ printf("sz = %lld,   h = (%lld, %lld),  id = %lld, p = %lld\n", sz, h.F, h.S, id, p);
		
		if(!mapa.count(h)) continue;
		
		ll x = mapa[h];
		//~ printf("match com a string %lld\n\n", x);
		Q[x].push_back( query(0, p, 0, id) );
	}
}


void update(ll pos, ll val){
	ll b = blc[pos];
	
	v[pos]+=val;
	somab[b]+=val;
	if(v[pos] == 1 && val == 1) occb[b]++;
	if(v[pos] == 0 && val == -1) occb[b]--;
}

ll varre(ll b, ll l, ll r, ll type){
	ll ans=0;
	for(ll i=l; i<=r; i++){
		if(type == 1){
			ans+= (v[i]>0);
		}else ans+=v[i];
	}
	return ans;
}

ll ans_query(ll l, ll r, ll type){
	
	ll bl = blc[l], br = blc[r];
	
	if(bl == br) return varre(bl, l, r, type);
	
	ll ans=0;
	ans+= varre(bl, l, ini[bl+1]-1, type);
	ans+= varre(br, ini[br], r, type);
	
	for(ll b=bl+1; b<br; b++){
		if(type == 1) ans+= occb[b];
		else ans+= somab[b];
	}
	return ans;
}

void solve(){
	//~ printf("\n");
	for(ll p = 1; p<=m; p++){
		//~ printf("\nstring %lld:\n", p);
		for(query x : Q[p]){
			
			
			
			if(x.type == 0){
				update(x.l, 1);
				
				//~ printf("type 0, pos = %lld\n", x.l);
			}else{
				//~ printf("type %lld, [%lld,  %lld]\n", x.type, x.l, x.r);
				answer[x.id] = ans_query(x.l, x.r, x.type);
			}
		}
		for(query x : Q[p]){
			if(x.type == 0){
				update(x.l, -1);
			}
		}
	}
	
}




int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	build_pot();
	
	cin >> n >> m >> q;
	
	for(ll i=1; i<=m; i++){
		
		cin >> s;
		
		sizes.push_back((int)s.size());
		ii h = get_hash(s);
		
		hashes[i] = h;
		mapa[h] = i;
	}
	
	sort(sizes.begin(), sizes.end());
	sizes.resize( distance( sizes.begin(),  unique( sizes.begin(), sizes.end() )  ) );
	
	memset(answer, -1, sizeof answer);
	
	build_blc();
	
	
	
	ll type, l, r, p;
	char c;
	
	for(ll i=0; i<q; i++){
		
		cin >> type;
		
		if(type == 0){
			cin >> p >> c;
			
			add_caracter(p, c, i);
		}else
		if(type == 1){
			cin >> l >> r >> p;
			Q[p].push_back(query(type, l, r, i));
		}else{
			cin >> l >> r >> p;
			Q[p].push_back(query(type, l, r, i));
		}
	}
	
	solve();
	
	for(ll i=0; i<q; i++){
		if(answer[i] == -1) continue;
		cout << answer[i] << "\n";
	}
	
}
