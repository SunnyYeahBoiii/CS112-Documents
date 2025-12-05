#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    if (n == 1) {
        cout << 1 << '\n';
        return 0;
    }

    vector<int> adjMask(n, 0);
    for (int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v;
        --u; --v;
        adjMask[u] |= (1 << v);
        adjMask[v] |= (1 << u);
    }

    int FULL = (1 << n) - 1;
    vector<vector<char>> dp(1 << n, vector<char>(n, 0));
    vector<vector<int>> parent(1 << n, vector<int>(n, -1));

    for (int v = 0; v < n; ++v) dp[1 << v][v] = 1;

    for (int mask = 1; mask <= FULL; ++mask) {
        for (int v = 0; v < n; ++v) if (dp[mask][v]) {
            int can = adjMask[v] & (~mask);
            while (can) {
                int w = __builtin_ctz(can);
                can &= can - 1;
                int nmask = mask | (1 << w);
                if (!dp[nmask][w]) {
                    dp[nmask][w] = 1;
                    parent[nmask][w] = v;
                }
            }
        }
    }

    int endV = -1;
    for (int v = 0; v < n; ++v) if (dp[FULL][v]) { endV = v; break; }

    if (endV == -1) {
        cout << -1 << '\n';
        return 0;
    }

    vector<int> path;
    int mask = FULL, v = endV;
    while (v != -1) {
        path.push_back(v);
        int pv = parent[mask][v];
        if (pv == -1) break;
        mask ^= (1 << v);
        v = pv;
    }
    reverse(path.begin(), path.end());

    for (int i = 0; i < n; ++i) {
        cout << (path[i] + 1) << (i + 1 == n ? '\n' : ' ');
    }
    return 0;
}
