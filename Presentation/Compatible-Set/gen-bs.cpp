#ifdef _MSC_VER
#pragma warning(disable : 4459)
#endif

#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Node {
    ll l, v, r;
};

ll randRange(ll L, ll R) {
    return rnd.next(L, R);
}

/*
    ========================
      CÁC MODE SINH TEST
    ========================
*/

// Mode 1: Sinh ngẫu nhiên hoàn toàn
void buildRandom(vector<Node>& a) {
    int n = a.size();
    for (int i = 0; i < n; ++i) {
        ll l = randRange(1, (ll)1e9);
        ll r = randRange(l, min(2000000000LL, l + rnd.next(0LL, 2000000000LL - l)));
        ll v = randRange(l, r);
        a[i] = {l, v, r};
    }
}

// Mode 2: Một cụm lớn (beautiful set lớn)
void buildCluster(vector<Node>& a) {
    int n = a.size();
    ll coreL = randRange(1, (ll)1e9);
    ll coreR = coreL + randRange(100, 200000);

    int big = n * 7 / 10; // 70% intervals bao core

    for (int i = 0; i < big; ++i) {
        ll l = randRange(max(1LL, coreL - 200000), coreL);
        ll r = randRange(coreR, min(2000000000LL, coreR + 200000));
        ll v = randRange(l, r);
        a[i] = {l, v, r};
    }

    // Phần còn lại random
    for (int i = big; i < n; ++i) {
        ll l = randRange(1, (ll)1e9);
        ll r = randRange(l, min(2000000000LL, l + rnd.next(0LL, 2000000000LL - l)));
        ll v = randRange(l, r);
        a[i] = {l, v, r};
    }
}

// Mode 3: Chuỗi giao tại 1 điểm (chain-overlap)
void buildChain(vector<Node>& a) {
    int n = a.size();
    ll X = randRange(1, (ll)1500000000);

    for (int i = 0; i < n; ++i) {
        ll l = randRange(max(1LL, X - 2000000LL), X);
        ll r = randRange(X, min(2000000000LL, X + 2000000LL));
        ll v = X; // giao tại một điểm
        a[i] = {l, v, r};
    }
}

// Mode 4: Tất cả bao cùng đoạn core (all-cover → beautiful = n)
void buildAllCover(vector<Node>& a) {
    int n = a.size();
    ll L = randRange(1, (ll)1e9);
    ll R = L + randRange(1000, 200000);

    for (int i = 0; i < n; ++i) {
        ll l = randRange(max(1LL, L - 200000), L);
        ll r = randRange(R, min(2000000000LL, R + 200000));
        ll v = randRange(l, r);
        a[i] = {l, v, r};
    }
}

// Mode 5: Nhiều cluster (multi cluster)
void buildMultiCluster(vector<Node>& a) {
    int n = a.size();
    int c1 = n / 3;
    int c2 = n / 3;
    int c3 = n - c1 - c2;

    ll base = randRange(1, (ll)500000000);

    auto gen = [&](int L, int R, ll X) {
        for (int i = L; i < R; ++i) {
            ll l = randRange(max(1LL, X - 200000), X + 200000);
            ll r = randRange(l, min(2000000000LL, l + 200000));
            if (l > r) swap(l, r);
            ll v = randRange(l, r);
            a[i] = {l, v, r};
        }
    };

    gen(0, c1, base);
    gen(c1, c1 + c2, base + 400000);
    gen(c1 + c2, n, base + 800000);
}

// Mode 6: Adversarial mix
void buildAdversarial(vector<Node>& a) {
    int n = a.size();
    for (int i = 0; i < n; ++i) {
        int t = rnd.next(0, 2);
        if (t == 0) {
            // Điểm
            ll x = randRange(1, (ll)2e9);
            a[i] = {x, x, x};
        } else if (t == 1) {
            // Nested
            ll L = randRange(1, (ll)1e9);
            ll R = L + randRange(10, 100000);
            ll v = randRange(L, R);
            a[i] = {L, v, R};
        } else {
            // Random
            ll l = randRange(1, (ll)1e9);
            ll r = randRange(l, min(2000000000LL, l + rnd.next(0LL, 2000000000LL - l)));
            ll v = randRange(l, r);
            a[i] = {l, v, r};
        }
    }
}

/*
    ===========================
        MAIN GENERATOR
    ===========================
*/

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);

    // Đọc options theo chuẩn Polygon
    int n = opt<int>("n");
    string mode = opt<string>("mode", "random");

    vector<Node> a(n);

    if (mode == "random") buildRandom(a);
    else if (mode == "cluster") buildCluster(a);
    else if (mode == "chain") buildChain(a);
    else if (mode == "allcover") buildAllCover(a);
    else if (mode == "multi") buildMultiCluster(a);
    else if (mode == "adversarial") buildAdversarial(a);
    else
        quitf(_fail, "Unknown mode: %s", mode.c_str());

    // Xuất
    println(n);
    for (int i = 0; i < n; ++i) {
        println(a[i].l, a[i].v, a[i].r);
    }

    return 0;
}
