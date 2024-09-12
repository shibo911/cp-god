#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int mod = 1e9+7;

ll n, x;
vector<ll> a;
vector<ll> dp;

ll recursiveDP(ll sum) {
    if (sum == 0) return 1; // Base case: 1 way to make sum 0 (no coins)
    if (dp[sum] != -1) return dp[sum]; // Use cached result

    dp[sum] = 0;
    for (ll i = 0; i < n; ++i) {
        if (sum - a[i] >= 0) {
            dp[sum] = (dp[sum] + recursiveDP(sum - a[i])) % mod;
        }
    }
    
    return dp[sum];
}

void solve() {
    cin >> n >> x;
    a.resize(n);
    dp.assign(x + 1, -1);  // Initialize dp array with -1 indicating uncomputed states

    for (ll i = 0; i < n; ++i) {
        cin >> a[i];
    }

    cout << recursiveDP(x) << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}
