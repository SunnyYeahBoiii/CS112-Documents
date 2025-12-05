#include <bits/stdc++.h>
#define problem "teams"
#define ll long long
#define pii pair<int,ll>
#define pll pair<ll,ll>
#define fi first
#define se second
#define BIT(x,i) (((x) >> (i)) & 1)
#define MASK(i) (1LL << (i))
using namespace std;
const int N = 4e5;

struct Person{
    int l,r,v,id;
    Person(){
        l = r = v = id = 0;
    }
    void input(int index){
        cin>>l>>v>>r;   id = index;
    }
    bool operator < (const Person &other)   const{
        return v < other.v;
    }
};

int n;
Person a[N + 1];
int idByR[N + 1];
bool used[N + 1];
int bestLeft,bestRight,bestCount;

bool maximize(int &x,int y){
    if (x < y){
        x = y;  return true;
    }
    return false;
}

bool check(int u,int v){
    return (a[u].l <= a[v].v && a[v].v <= a[u].r);
}

bool compR(int u,int v){
    return a[u].r < a[v].r;
}

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);	cout.tie(NULL);
    // freopen(problem".inp","r",stdin);
    // freopen(problem".out","w",stdout);
    cin>>n;
    for (int i=1;i<= n;i++ )
        a[i].input(i);
    sort(a + 1,a + n + 1);
    for (int i=1;i<= n;i++ )
        idByR[i] = i;
    sort(idByR + 1,idByR + n + 1,compR);
    bestLeft = bestRight = bestCount = 1;
    for (int i=1;i<= n;i++ ){
        memset(used,false,sizeof(used));
        int numOK = 0;
        int pos = 1;
        for (int j=i + 1;j<= n;j++ ){
            if (j - 1 > i && check(j - 1,i) && check(j - 1,j)){
                numOK++;
                used[j - 1] = true;
            }

            while (pos <= n && a[idByR[pos]].r < a[j].v){
                if (used[idByR[pos]])   numOK--;
                used[idByR[pos]] = false;
                pos++;
            }

            if (check(i,j) && check(j,i) && maximize(bestCount,numOK + 2)){
                bestLeft = i;
                bestRight = j;
            }
        }
    }


    cout<<bestCount<<'\n';
    for (int i=bestLeft;i<= bestRight;i++ )
        if (check(i,bestLeft) && check(i,bestRight))
            cout<<a[i].id<<' ';
}