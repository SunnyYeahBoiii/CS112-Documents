#include <bits/stdc++.h>
#define problem "dominating"
#define ll long long
#define pii pair<int,ll>
#define pll pair<ll,ll>
#define BIT(x,i) (((x) >> (i)) & 1)
#define MASK(i) (1LL << (i))
#define fi first
#define se second
using namespace std;
const int maxn = 6e5 + 10;
const int max_bit = 20;

int n,test;
ll a[maxn];
int cnt[maxn][max_bit];
vector<ll> value;
vector<int> pos[maxn];

void compress(){
    for (int i=1;i<= n;i++ )
        value.push_back(a[i]);
    sort(value.begin(),value.end());
    value.erase(unique(value.begin(),value.end()),value.end());
    for (int i=1;i<= n;i++ )
        a[i] = lower_bound(value.begin(),value.end(),a[i]) - value.begin() + 1;
}

void prepare(){
    for (int i=1;i<= n;i++ )
        pos[a[i]].push_back(i);
    for (int i=1;i<= n;i++ ){
        for (int j=0;j< max_bit;j++ )
            cnt[i][j] = cnt[i - 1][j] + BIT(a[i],j);
    }
}

int getCount(int l,int r,int val){
    int u = upper_bound(pos[val].begin(),pos[val].end(),r) - pos[val].begin() + 1;
    int v = lower_bound(pos[val].begin(),pos[val].end(),l) - pos[val].begin() + 1;
    return u - v;
}

long long query(int l,int r){
    int tmp = 0;
    for (int j=0;j < max_bit;j++ ){
        int mul = cnt[r][j] - cnt[l - 1][j];
        if (2*mul > r - l + 1)
            tmp |= MASK(j);
    }
    return 2*getCount(l,r,tmp) > r - l + 1 ? value[tmp - 1] : -1;
}

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);	cout.tie(NULL);
    // freopen(problem".inp","r",stdin);
    // freopen(problem".out","w",stdout);
    cin>>n>>test;
    for (int i=1;i<= n;i++ )
        cin>>a[i];
    compress();
    prepare();
    while (test-- ){
        int l,r;    cin>>l>>r;
        cout<<query(l,r)<<' ';
    }
    cout << ' ';
    cout << '\n';
}