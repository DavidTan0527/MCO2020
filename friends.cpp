#include <iostream>
#include <algorithm>
#include <cmath>
#include <queue>
#include <set>
#include <map>
#include <vector>
#include <string>
using namespace std;

#pragma GCC optimize("O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
//(UNCOMMENT WHEN HAVING LOTS OF RECURSIONS)
#pragma comment(linker, "/stack:200000000")
//(UNCOMMENT WHEN TRYING TO BRUTEFORCE WITH A LOT OF LOOPS)
#pragma GCC optimize("unroll-loops")

#define DEBUG(x) cout << ">> " << #x << ": " << x << endl;
#define _ ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define f first
#define s second

const int MOD = 1000000007;
typedef long long ll;
typedef long double ld;

ll n;
vector<ll> happy;
vector<vector<ll> > tree;
vector<vector<ll> > dp;

void dfs(ll u, ll p) {
  for (ll v : tree[u]) {
    if (v == p) continue;
    dfs(v, u);
    dp[u][0] += max(dp[v][1], dp[v][0]);
  }
  for (ll v : tree[u]) {
    if (v == p) continue;
    dp[u][1] = max(dp[u][1], dp[u][0] + happy[u]*happy[v] + dp[v][0] - max(dp[v][0], dp[v][1]));
  }
}

int main() { _
  cin >> n;
  tree.resize(n);
  dp.resize(n, vector<ll>(2, 0));
  happy.resize(n);
  for (ll i = 0; i < n; i++) {
    cin >> happy[i];
  }
  for (ll i = 0; i < n-1; i++) {
    ll u,v; cin >> u >> v;
    u--; v--;
    tree[u].push_back(v);
    tree[v].push_back(u);
  }
  dfs(0, -1);
  cout << max(dp[0][1], dp[0][0]) << endl;
  return 0;
}