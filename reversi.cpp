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
int rs = 1e9, cs = 1e9;
vector<ll> dsu;

ll parent(ll ind) {
  if (dsu[ind] < 0) return ind;
  return (dsu[ind] = parent(dsu[ind]));
}

void merge(ll a, ll b) {
  a = parent(a); b = parent(b);
  if (a == b) return ;
  if (dsu[a] < dsu[b]) swap(a, b);
  dsu[b] += dsu[a];
  dsu[a] = b;
}

ll si(ll r, ll c) {
  return r+c;
}

ll di(ll row, ll col) {
  return (row-col)+(ll)(3*1e9);
}

int main() { _
  cin >> n;
  dsu.resize(3*n, -1);
  ll pos = 0;
  map<ll, ll> mapp;
  vector<ll> edge;
  for (ll i = 0; i < n; i++) {
    ll r, c; cin >> r >> c;
    if (mapp.find(si(r,c)) == mapp.end()) mapp[si(r,c)] = pos++;
    if (mapp.find(di(r,c)) == mapp.end()) mapp[di(r,c)] = pos++;
    edge.push_back(si(r,c));
    merge(mapp[si(r,c)], mapp[di(r,c)]);
  }
  set<ll> grp;
  for (ll p : edge) {
    grp.insert(parent(mapp[p]));
  }
  cout << grp.size() << endl;
  return 0;
}