#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<long long> a(n);

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    while (q--) {
        int l, r;
        cin >> l >> r;
        --l; --r;

        int len = r - l + 1;
        int need = len / 2 + 1;

        unordered_map<long long, int> freq;
        freq.reserve(len * 2);

        long long ans = -1;

        for (int i = l; i <= r; i++) {
            int &f = freq[a[i]];
            f++;
            if (f >= need) {
                ans = a[i];
                break;
            }
        }

        cout << ans;
        if (q > 0) cout << ' ';
    }
    cout << "\n";

    return 0;
}
