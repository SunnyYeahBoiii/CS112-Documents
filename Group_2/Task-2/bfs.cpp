#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Edge {
    int v;
    ll w;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<Edge>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    ll ans = LLONG_MAX;
    queue<pair<int,ll>> q;
    vector<ll> best(n + 1, LLONG_MAX);

    q.push({1, 0});
    best[1] = 0;

    while (!q.empty()) {
        auto [u, cost] = q.front();
        q.pop();

        if (u == n) {
            ans = min(ans, cost);
        }

        for (auto e : adj[u]) {
            ll nextCost = cost + e.w;
            if (nextCost < best[e.v]) { 
                best[e.v] = nextCost;
                q.push({e.v, nextCost});
            }
        }
    }

    if (ans == LLONG_MAX) cout << -1 << "\n";
    else cout << ans << "\n";
}
