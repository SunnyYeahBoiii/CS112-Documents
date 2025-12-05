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
const int MAX = 3*N;

struct Person{
    int l,r,v,id;
    Person (){
        l = r = v = id = 0;
    }
    void input(int index){
        cin>>l>>v>>r;
        id = index;
    }
    bool operator < (const Person &other)   const{
        return v < other.v;
    }
};

struct Event{
    int l,r,delta;
    Event (int _l = 0,int _r = 0,int _delta = 0){
        l = _l; r = _r; delta = _delta;
    }
};

int n;
Person person[N + 10];
vector<Event> event[MAX + 10];
pii maxCount[4*MAX + 10];
int lazy[4*MAX + 10];

void build(int id,int l,int r){
    if (l > r)  return;
    if (l == r){
        maxCount[id] = make_pair(0,l);
        return;
    }
    int mid = (l + r) >> 1;
    build(2*id,l,mid);
    build(2*id + 1,mid + 1,r);
    maxCount[id] = max(maxCount[2*id],maxCount[2*id + 1]);
}

void pushdown(int id){
    maxCount[2*id].fi += lazy[id];
    maxCount[2*id + 1].fi += lazy[id];
    lazy[2*id] += lazy[id];
    lazy[2*id + 1] += lazy[id];
    lazy[id] = 0;
}

void update(int id,int l,int r,int u,int v,int delta){
    if (l > r || u > v || v < l || r < u)   return;
    if (u <= l && r <= v){
        maxCount[id].first += delta;
        lazy[id] += delta;
        return;
    }
    int mid = (l + r) >> 1;
    pushdown(id);
    update(2*id,l,mid,u,v,delta);
    update(2*id + 1,mid + 1,r,u,v,delta);
    maxCount[id] = max(maxCount[2*id],maxCount[2*id + 1]);
}

pii getMax(){
    return maxCount[1];
}

void compress(){
    vector<int> value;
    for (int i=1;i<= n;i++ ){
        value.push_back(person[i].l);
        value.push_back(person[i].r);
        value.push_back(person[i].v);
    }
    sort(value.begin(),value.end());
    value.resize(unique(value.begin(),value.end()) - value.begin());

    for (int i=1;i<= n;i++ ){
        person[i].l = lower_bound(value.begin(),value.end(),person[i].l) - value.begin() + 1;
        person[i].r = lower_bound(value.begin(),value.end(),person[i].r) - value.begin() + 1;
        person[i].v = lower_bound(value.begin(),value.end(),person[i].v) - value.begin() + 1;
    }
}

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);	cout.tie(NULL);
    // freopen(problem".inp","r",stdin);
    // freopen(problem".out","w",stdout);
    cin>>n;
    for (int i=1;i<= n;i++ )
        person[i].input(i);
    compress();
    for (int i=1;i<= n;i++ ){
        int _left = person[i].l;
        int _right = person[i].v;
        int bot = person[i].v;
        int top = person[i].r;
        event[_left].push_back(Event(bot,top,1));
        event[_right + 1].push_back(Event(bot,top,-1));
    }
    
    build(1,1,3*n);
    int maxVal = 0,bestX = 0,bestY = 0;
    for (int i=1;i<= 3*n;i++ ){
        for (Event e : event[i]){
            update(1,1,3*n,e.l,e.r,e.delta);
        }
        pii Max = getMax();
        if (Max.fi > maxVal){
            maxVal = Max.fi;
            bestX = i;
            bestY = Max.se;
        }
    }
    cout<<maxVal<<'\n';
    for (int i=1;i<= n;i++ ){
        int _left = person[i].l;
        int _right = person[i].v;
        int bot = person[i].v;
        int top = person[i].r;
        if (_left <= bestX && bestX <= _right && bot <= bestY && bestY <= top)
            cout<<person[i].id<<' ';
    }
}