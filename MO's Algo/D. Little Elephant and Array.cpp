// https://codeforces.com/problemset/problem/221/D
// JAI SHREE RAM
#pragma GCC optimize("O3,unroll-loops")
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
using namespace chrono;

#define for0(i, n) for(int i=0; i<n; i++)
#define for1(i, n) for(int i=1; i<=n; i++)
#define rfor0(i,n) for(int i=n-1; i>=0; i--)
#define rfor1(i,n) for(int i=n; i>=1; i--)
#define fast ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define vi vector<int>
#define vll vector<ll>
#define MOD 1000000007
#define MOD1 998244353
#define nline '\n'
#define ff first
#define ss second
#define pi pair<int, int>
#define pii pair<ll, ll>
#define mp make_pair
#define INF 1e18
#define pb push_back
#define ppb pop_back
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
const int N = 1e5 + 5;
int sq = 500, vec[N], ans[N], freq[N], n, k, curans = 0;
vector<pair<pi, int>>q;
void add(int ind){
  if(freq[ind] == ind) curans--;
  freq[ind]++;
  if(freq[ind] == ind) curans++;
}
void remove(int ind){
  if(freq[ind] == ind) curans--;
  freq[ind]--;
  if(freq[ind] == ind) curans++;
}
void solve(){
  cin>>n>>k;
  q.clear();
  for0(i,n) cin>>vec[i], vec[i] = min(vec[i], (int)1e5 + 2);
  for0(i,k){
    int l, r; cin>>l>>r;
    l--, r--;
    q.pb(mp(mp(l,r), i));
  }
  sort(all(q), [&](pair<pi, int>&p1, pair<pi, int>&p2){
    if(p1.ff.ff/sq != p2.ff.ff/sq){
      return p1.ff.ff/sq < p2.ff.ff/sq;
    }else{
      return p1.ss < p2.ss;
    }
  });
  int ml = 0, mr = -1;
  for0(i,k){
    int l = q[i].ff.ff, r = q[i].ff.ss, ind = q[i].ss;
    while(mr < r) mr++, add(vec[mr]);
    while(ml > l) ml--, add(vec[ml]);
        
    while(mr > r) remove(vec[mr]), mr--;
    while(ml < l) remove(vec[ml]), ml++;
    ans[ind] = curans;
  }
  for0(i,k) cout<<ans[i]<<nline;
}
signed main(){
#ifndef ONLINE_JUDGE
  freopen("Error.txt", "w", stderr);
#endif
  fast;
  int t = 1; 
  // cin>>t;
  while(t--) solve();
  return 0;
}
