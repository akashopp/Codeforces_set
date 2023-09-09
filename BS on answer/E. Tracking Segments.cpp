// https://codeforces.com/problemset/problem/1843/E
//Practice is the only shortcut to improve
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define for0(i, n) for(int i=0; i<n; i++)
#define for1(i, n) for(int i=1; i<=n; i++)
#define fast ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define vi vector<int>
#define MOD 1000000007
#define nline '\n'
#define ff first
#define ss second
#define pi pair<int, int>
#define INF 1e18
#define pb push_back
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update > pbds; // find_by_order, order_of_key
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;
int dx[4] = {0, 0, -1, 1}, dy[4] = {1, -1, 0, 0};

#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x <<" "; _print(x); cerr << endl;
#else
#define debug(x)
#endif

void _print(ll t) {cerr << t;}
void _print(int t) {cerr << t;}
void _print(string t) {cerr << t;}
void _print(char t) {cerr << t;}
void _print(lld t) {cerr << t;}
void _print(double t) {cerr << t;}
void _print(ull t) {cerr << t;}

template <class T, class V> void _print(pair <T, V> p);
template <class T> void _print(vector <T> v);
template <class T> void _print(set <T> v);
template <class T, class V> void _print(map <T, V> v);
template <class T> void _print(multiset <T> v);
template <class T, class V> void _print(pair <T, V> p) {cerr << "{"; _print(p.ff); cerr << ","; _print(p.ss); cerr << "}";}
template <class T> void _print(vector <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(set <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(multiset <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T, class V> void _print(map <T, V> v) {cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";}

//graph
int findParent(int node,vector<int>& par){if(par[node]==node) return node; return par[node]=findParent(par[node],par);}
void Union(int u,int v,vector<int>& par,vector<int>& size){int pu=findParent(u,par);int pv=findParent(v,par);if(pu==pv) return;if(size[pu]>=size[pv]){par[pv]=pu;size[pu]++;}else{par[pu]=pv;size[pv]++;}} 

/*---------------------------------------------------------------------------------------------------------------------------*/
ll gcd(ll a, ll b) {if (b > a) {return gcd(b, a);} if (b == 0) {return a;} return gcd(b, a % b);}
ll expo(ll a, ll b, ll mod) {ll res = 1; while (b > 0) {if (b & 1)res = (res * a) % mod; a = (a * a) % mod; b = b >> 1;} return res;}
ll mod_add(ll a, ll b, ll m) {a = a % m; b = b % m; return (((a + b) % m) + m) % m;}
ll mod_mul(ll a, ll b, ll m) {a = a % m; b = b % m; return (((a * b) % m) + m) % m;}
ll mod_sub(ll a, ll b, ll m) {a = a % m; b = b % m; return (((a - b) % m) + m) % m;}
ll mminvprime(ll a, ll b) {return expo(a, b - 2, b);}
ll mod_div(ll a, ll b, ll m) {a = a % m; b = b % m; return (mod_mul(a, mminvprime(b, m), m) + m) % m;}  //only for prime m
vector<ll> sieve(int n) {int*arr = new int[n + 1](); vector<ll> vect; for (int i = 2; i <= n; i++)if (arr[i] == 0) {vect.push_back(i); for (int j = 2 * i; j <= n; j += i)arr[j] = 1;} return vect;}
/*---------------------------------------------------------------------------------------------------------------------------*/
/* 
  auto j = upper_bound(begin(e) + i, end(e), e[i][1], 
    [](int t, const vector<int> &v) {return v[0] > t;}) - begin(e); */
/*  
NOTES: 
  -> a << n = a * pow(2, n)
  -> a >> n = a / pow(2, n)
  -> if(n&1) odd else even
  -> min no of bits to change a to b ==> a ^ b 
    ex a = 11, b = 15, a = 1011, b = 1111, a^b = 0100
  -> Count the set bits ==> while(n){ cnt += (n&1), n = n >> 1}
  -> To remove the last set bit ==> n & (n-1) 
    ex a = 13, 1101, a & (a-1), 1101 & 1100 = 1100
  -> To extract the ith bit we use mask ==> x = n & (1 << i)
    ex n = 13, 1101, i = 2, so 1 << 2 = 0100, so we get 4
  -> Changing the ith bit ==> n | (1 << i)
    ex n = 13, i = 2, 1101 | (1<<2), 1101|0010 = 1111
  -> Clearing the ith bit ==> n & (~(1<<i)) 
    ex n = 13, i = 2, 1101 & (~(1<<i)), 1101 & (1011) = 1001
  -> To get first set bit y = x&(~(x-1))
  -> 
*/
bool f(int mid, vector<pi>&query, vi &vec, int q, int n){
  vi pref(n);
  for0(i,mid+1) pref[vec[i]-1]++;
  for1(i,n-1) pref[i] += pref[i-1];
  for0(i,q){
    int l = query[i].ff-1, r = query[i].ss-1;
    int cnt = pref[r];
    if(l > 0) cnt -= pref[l-1];
    if(cnt > (r-l+1)/2) return 1;
  }
  return 0;
}
void solve(){
  int n, q; cin>>n>>q;
  vector<pi>query(q);
  for0(i,q) cin>>query[i].ff>>query[i].ss;
  int m; cin>>m;
  vi vec(m);
  for0(i,m) cin>>vec[i];
  int cnt = 0, low = 0, high = m-1, ans = -1;
  while(low <= high){
    cnt++;
    int mid = low+(high-low)/2;
    if(f(mid, query, vec, q, n)) ans = mid+1, high=mid-1;
    else low=mid+1;
  }
  cout<<ans<<nline;
}
signed main(){
#ifndef ONLINE_JUDGE
  freopen("Error.txt", "w", stderr);
#endif
  fast;
  int t = 1; 
  cin>>t;
  while(t--) solve();
  return 0;
}

