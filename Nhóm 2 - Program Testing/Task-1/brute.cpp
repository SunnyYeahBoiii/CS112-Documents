#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> a(n + 1);
    long long res = 0;

    for (int i = 1; i <= n; i++){
        cin >> a[i];
        res += a[i];
    }
    cout << res;
    
    return 0;
}
