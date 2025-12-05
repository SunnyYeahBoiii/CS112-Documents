#include <bits/stdc++.h>
#define ll long long
#define fi first
#define se second
using namespace std;
const int N = 696969;

ll n, m;
int res;
vector<int> adj[N + 5];
int p[N + 5];
ll w[N + 5], carry[N + 5];
priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> Q;

void dfs(int u){
    for (int v : adj[u])
        dfs(v);

    for (int v: adj[u]){
        Q.push({w[v] - 1, v});
    }

    while (!Q.empty() && Q.top().fi <= carry[u]){
        ll cost = Q.top().fi;
        int v = Q.top().se;
        Q.pop();
        res++;
        w[u] += cost;
        carry[u] -= cost;
    }

    while (!Q.empty())
        Q.pop();
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);  cout.tie(NULL);
    if (fopen("input.txt", "r")){
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    }
    cin >> n >> m;
    for (int i=1;i<= n;i++ )
        cin >> w[i];
    for (int i=2;i<= n;i++ ){
        cin >> p[i];
        adj[p[i]].push_back(i);
    }

    for (int i=1;i<= n;i++ ){
        carry[i] = m - (w[i] + (int)adj[i].size());
        w[i] += (int)adj[i].size();
    }

    dfs(1);

    cout << res;
}