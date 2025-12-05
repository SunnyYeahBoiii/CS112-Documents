#ifdef _MSC_VER
// Tắt warning C4459 bên trong testlib khi compile bằng MSVC trên Polygon
#pragma warning(disable : 4459)
#endif

#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// Sinh mảng random hoàn toàn
void buildRandomArray(vector<ll> &a, ll maxA) {
    const int n = static_cast<int>(a.size());
    for (int i = 0; i < n; ++i) {
        a[i] = rnd.next(0LL, maxA);
    }
}

// Sinh mảng constant (tất cả phần tử giống nhau)
void buildConstantArray(vector<ll> &a, ll maxA) {
    const int n = static_cast<int>(a.size());
    const ll v = rnd.next(0LL, maxA);
    for (int i = 0; i < n; ++i) {
        a[i] = v;
    }
}

// Tạo các điểm bắt đầu của block [0 = start, n = end]
void buildBlockStarts(int n, int numBlocks, vector<int> &blockStart) {
    blockStart.clear();
    blockStart.reserve(numBlocks + 1);
    blockStart.push_back(0);
    for (int i = 1; i < numBlocks; ++i) {
        const ll posLL = 1LL * i * n / numBlocks;
        const int pos = static_cast<int>(posLL);
        blockStart.push_back(pos);
    }
    blockStart.push_back(n);
}

// Sinh mảng “block-majority”
void buildBlockMajorityArray(vector<ll> &a,
                             ll maxA,
                             int numBlocks,
                             int majRatioPercent,
                             vector<int> &blockStart) {
    const int n = static_cast<int>(a.size());
    buildBlockStarts(n, numBlocks, blockStart);

    for (int b = 0; b < numBlocks; ++b) {
        const int L = blockStart[b];
        const int R = blockStart[b + 1];
        const int len = R - L;

        if (len <= 0) {
            continue;
        }

        const ll majorityValue = rnd.next(0LL, maxA);

        // Số phần tử majority trong block
        int majorityCount =
            static_cast<int>((1LL * len * majRatioPercent) / 100);

        // Đảm bảo thật sự là "majority": > len / 2
        const int requiredMajority = len / 2 + 1;
        if (majorityCount < requiredMajority) {
            majorityCount = requiredMajority;
        }
        if (majorityCount > len) {
            majorityCount = len;
        }

        vector<ll> tmp;
        tmp.reserve(len);

        // majorityValue xuất hiện majorityCount lần
        for (int i = 0; i < majorityCount; ++i) {
            tmp.push_back(majorityValue);
        }
        // Phần còn lại là giá trị khác majorityValue
        for (int i = majorityCount; i < len; ++i) {
            ll x;
            do {
                x = rnd.next(0LL, maxA);
            } while (x == majorityValue);
            tmp.push_back(x);
        }

        // Trộn ngẫu nhiên các phần tử trong block
        shuffle(tmp.begin(), tmp.end(), mt19937(rnd.next(0, INT_MAX)));

        for (int i = 0; i < len; ++i) {
            a[L + i] = tmp[i];
        }
    }
}

// Sinh q query bất kì trên [1..n]
void generateRandomQueries(int n, int q) {
    for (int i = 0; i < q; ++i) {
        const int l = rnd.next(0, n - 1);
        const int r = rnd.next(l, n - 1);
        println(l + 1, r + 1);
    }
}

// Sinh q query khi mảng được chia block (in-block / cross-block / random)
void generateBlockQueries(int n,
                          int q,
                          int numBlocks,
                          const vector<int> &blockStart) {
    for (int i = 0; i < q; ++i) {
        const int typeQ = rnd.next(0, 2);  // 0,1,2

        // 0: query nằm gọn trong một block
        if (typeQ == 0) {
            const int b = rnd.next(0, numBlocks - 1);
            const int L = blockStart[b];
            const int R = blockStart[b + 1] - 1;
            const int l = rnd.next(L, R);
            const int r = rnd.next(l, R);
            println(l + 1, r + 1);
        }
        // 1: query cắt qua 2 block liên tiếp (cross-block)
        else if (typeQ == 1 && numBlocks >= 2) {
            const int b = rnd.next(0, numBlocks - 2);
            const int L1 = blockStart[b];
            const int R1 = blockStart[b + 1] - 1;
            const int L2 = blockStart[b + 1];
            const int R2 = blockStart[b + 2] - 1;

            const int leftIndex = rnd.next(L1, R1);
            const int rightIndex = rnd.next(L2, R2);

            int l = leftIndex;
            int r = rightIndex;
            if (l > r) {
                std::swap(l, r);
            }
            println(l + 1, r + 1);
        }
        // 2 (hoặc fallback): query random toàn mảng
        else {
            const int l = rnd.next(0, n - 1);
            const int r = rnd.next(l, n - 1);
            println(l + 1, r + 1);
        }
    }
}

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);

    // ===== Đọc tham số =====
    const int n = opt<int>("n");
    const int q = opt<int>("q");
    const ll maxA =
        opt<ll>("max-a", 1'000'000'000'000'000'000LL);  // mặc định 1e18
    const string type = opt<string>("type", "random");

    int numBlocks = opt<int>("blocks", 10);
    int majRatio = opt<int>("maj-ratio", 70);  // %

    // Giới hạn hợp lý
    numBlocks = max(1, min(numBlocks, n));
    majRatio = max(1, min(majRatio, 99));

    vector<ll> a(static_cast<size_t>(n));
    vector<int> blockStart;  // chỉ dùng nếu type == "blocks"

    // ===== Sinh mảng a =====
    if (type == "random") {
        buildRandomArray(a, maxA);
    } else if (type == "constant") {
        buildConstantArray(a, maxA);
    } else if (type == "blocks") {
        buildBlockMajorityArray(a, maxA, numBlocks, majRatio, blockStart);
    } else {
        quitf(_fail, "Unknown type: %s", type.c_str());
    }

    // ===== In n, q và dãy a =====
    println(n, q);
    println(a);

    // ===== Sinh q query =====
    if (type == "blocks") {
        // blockStart đã được build trong buildBlockMajorityArray
        generateBlockQueries(n, q, numBlocks, blockStart);
    } else {
        generateRandomQueries(n, q);
    }

    return 0;
}
