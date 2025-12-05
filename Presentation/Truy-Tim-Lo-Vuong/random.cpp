#include <bits/stdc++.h>
using namespace std;

static const int K = 30;   // số lần thử random

// Random engine — nhanh + an toàn + không bias
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

inline int randInt(int l, int r) {
    uniform_int_distribution<int> dist(l, r);
    return dist(rng);
}

// getCount(v, l, r): số lần xuất hiện v trong [l..r]
inline int getCount(const vector<int> &pos, int l, int r) {
    auto itL = lower_bound(pos.begin(), pos.end(), l);
    auto itR = upper_bound(pos.begin(), pos.end(), r);
    return int(itR - itL);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<long long> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];

    // Nén giá trị
    vector<long long> vals = a;
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    int m = vals.size();

    vector<int> b(n);
    for (int i = 0; i < n; i++)
        b[i] = int(lower_bound(vals.begin(), vals.end(), a[i]) - vals.begin());

    // pos[id] = các chỉ số xuất hiện (1-indexed)
    vector<vector<int>> pos(m);
    for (int i = 0; i < n; i++)
        pos[b[i]].push_back(i + 1);

    while (q--) {
        int l, r;
        cin >> l >> r;

        int len = r - l + 1;
        int need = len / 2 + 1;
        long long answer = -1;

        // Thử random K lần
        for (int t = 0; t < K; t++) {
            int p = randInt(l, r);   // chọn vị trí random
            int id = b[p - 1];       // id sau nén

            if (getCount(pos[id], l, r) >= need) {
                answer = vals[id];
                break;
            }
        }

        cout << answer << "\n";
    }

    return 0;
}
