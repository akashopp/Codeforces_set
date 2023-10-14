// https://codeforces.com/contest/1881/problem/F
//......There'll be a day where I'll be loved, I'll be admired and they'll respect me......
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define for0(i, n) for(int i=0; i<n; i++)
#define for1(i, n) for(int i=1; i<=n; i++)
#define rfor0(i,n) for(int i=n-1; i>=0; i--)
#define rfor1(i,n) for(int i=n; i>=1; i--)
#define fast ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define vi vector<int>
#define vll vector<long long>
#define MOD 1000000007
#define nline '\n'
#define ff first
#define ss second
#define pi pair<int, int>
#define INF 1e18
#define pb push_back
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update > pbds; // find_by_order, order_of_key
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;
int dx[4] = {0, 0, -1, 1}, dy[4] = {1, -1, 0, 0};
int XX[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
int YY[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

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

/*---------------------------------------------------------------------------------------------------------------------------*/
ll gcd(ll a, ll b) {if (b > a) {return gcd(b, a);} if (b == 0) {return a;} return gcd(b, a % b);}
ll expo(ll a, ll b, ll mod) {ll res = 1; while (b > 0) {if (b & 1)res = (res * a) % mod; a = (a * a) % mod; b = b >> 1;} return res;}
ll mod_add(ll a, ll b, ll m) {a = a % m; b = b % m; return (((a + b) % m) + m) % m;}
ll mod_mul(ll a, ll b, ll m) {a = a % m; b = b % m; return (((a * b) % m) + m) % m;}
ll mod_sub(ll a, ll b, ll m) {a = a % m; b = b % m; return (((a - b) % m) + m) % m;}
ll mminvprime(ll a, ll b) {return expo(a, b - 2, b);}
ll mod_div(ll a, ll b, ll m) {a = a % m; b = b % m; return (mod_mul(a, mminvprime(b, m), m) + m) % m;}  //only for prime m
/*---------------------------------------------------------------------------------------------------------------------------*/
/* 
  auto j = upper_bound(begin(e) + i, end(e), e[i][1], 
    [](int t, const vector<int> &v) {return v[0] > t;}) - begin(e); */
/*  
NOTES: 
  -> min no of bits to change a to b ==> a ^ b 
    ex a = 11, b = 15, a = 1011, b = 1111, a^b = 0100
  -> To remove the last set bit ==> n & (n-1) 
    ex a = 13, 1101, a & (a-1), 1101 & 1100 = 1100
  -> To get first set bit y = x&(~(x-1))
*/
vi marked, depth;
int ans = 1e9;
vector<vi>adj;
void dfs(int u, int p){
  if(marked[u]) depth[u] = 0;
  else depth[u] = -1e9;
  for(auto v: adj[u]){
    if(v == p) continue;
    dfs(v, u);
    depth[u] = max(depth[u], 1 + depth[v]);
  }
}
void dfs1(int u, int p, int par_ans){
  if(marked[u]) par_ans = max(par_ans, 0);
  ans = min(ans, max(par_ans, depth[u]));
  vector<pi>distance;
  for(auto v: adj[u]){
    if(v == p) continue;
    distance.pb({depth[v]+1, v});
  }
  sort(all(distance));
  for(auto v: adj[u]){
    if(v == p) continue;
    if(sz(distance) && distance.back().ss == v){
      if(sz(distance) > 1){
        int pos = sz(distance)-2;
        dfs1(v, u, max(par_ans, distance[pos].ff)+1);
      }else{
        dfs1(v, u, par_ans+1);
      }
    }else{
      if(sz(distance)){
        dfs1(v, u, max(par_ans, distance.back().ff)+1);
      }else{
        dfs1(v, u, par_ans+1);
      }
    }
  }
}
void solve(){
  int n, k; cin>>n>>k;
  adj.clear(), marked.clear(), depth.clear();
  marked.resize(n, 0), adj.resize(n), depth.resize(n);
  for0(i,k){
    int x; cin>>x;
    marked[x-1] = 1;
  }
  for0(i,n-1){
    int u, v; cin>>u>>v;
    u--, v--;
    adj[u].pb(v), adj[v].pb(u);
  }
  ans = 1e9;
  dfs(0, -1);
  dfs1(0, -1, -1e9);
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
