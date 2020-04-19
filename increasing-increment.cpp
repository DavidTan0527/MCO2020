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

void setIO(string s) {
  ios_base::sync_with_stdio(0); cin.tie(0);
  freopen((s+".in").c_str(),"r",stdin);
  freopen((s+".out").c_str(),"w",stdout);
}

int main() { _
  int n, q; cin >> n >> q;
  vector<ll> base(n+1, 0), acc(n+1, 0), dec(n+1, 0), decc(n+1, 0);
  while (q--) {
    ll l, r, x, y; cin >> l >> r >> x >> y;
    base[l] += x; base[r+1] += -x;
    acc[l] += y; dec[r+1] += (r-l+2)*y;
    decc[r+2] += y;
  }
  vector<ll> ans(n, 0);
  ll dmg = 0, accd = 0, accc = 0, decam = 0, decacc = 0;
  for (ll i = 0; i < n; i++) {
    dmg += base[i];
    decacc += decc[i];
    decam += decacc + dec[i];
    accc += acc[i];
    accd += accc;
    ans[i] = dmg+accd-decam;
  }
  for (ll i : ans) cout << i << " ";
  return 0;
}