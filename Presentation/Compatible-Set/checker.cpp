#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct Triple {
    long long l, v, r;
};

int n;
vector<Triple> a;

/* =====================================================
   Read contestant or jury answer using "readAns paradigm"
   ===================================================== */

vector<int> read_answer(InStream& in, const char* who) {
    // đọc số lượng k
    int k = in.readInt(0, n, string(who) + string("_k"));
    vector<int> ids;
    ids.reserve(k);

    for (int i = 0; i < k; ++i) {
        // chỉ số từ 1..n
        int id = in.readInt(1, n, string(who) + string("_id"));
        ids.push_back(id);
    }

    // không cho phép thêm rác sau phần output (chỉ whitespace + EOF)
    in.skipBlanks();
    in.readEof();
    return ids;
}

/* =====================================================
   Check validity of a chosen set of indices
   ===================================================== */

bool is_valid_set(const vector<int>& ids) {
    if (ids.empty()) return true;

    // có thể kiểm tra trùng chỉ số (không bắt buộc, nhưng chặt chẽ hơn)
    {
        vector<int> tmp = ids;
        sort(tmp.begin(), tmp.end());
        if (unique(tmp.begin(), tmp.end()) != tmp.end()) {
            return false; // có chỉ số trùng
        }
    }

    long long min_v = LLONG_MAX;
    long long max_v = LLONG_MIN;

    // Tính min_v và max_v
    for (int id : ids) {
        const long long v = a[id - 1].v;
        min_v = min(min_v, v);
        max_v = max(max_v, v);
    }

    // Check mutual compatibility:
    // min_v và max_v phải nằm trong mọi [l_i, r_i]
    for (int id : ids) {
        const Triple& t = a[id - 1];
        if (!(t.l <= min_v && min_v <= t.r)) return false;
        if (!(t.l <= max_v && max_v <= t.r)) return false;
    }

    return true;
}

int main(int argc, char** argv) {
    registerTestlibCmd(argc, argv);

    // --- đọc input từ inf ---
    n = inf.readInt();
    a.resize(n);

    for (int i = 0; i < n; ++i) {
        a[i].l = inf.readLong();
        a[i].v = inf.readLong();
        a[i].r = inf.readLong();
    }

    // --- đọc output của thí sinh và của ban ra đề ---
    vector<int> out_ids = read_answer(ouf, "out");
    vector<int> ans_ids = read_answer(ans, "ans");

    int out_k = (int)out_ids.size();
    int ans_k = (int)ans_ids.size();

    // nếu jury answer không hợp lệ -> lỗi của đề
    if (!is_valid_set(ans_ids)) {
        quitf(_fail, "Jury answer is not a valid beautiful set");
    }

    // nếu số lượng khác nhau => WA
    if (out_k != ans_k) {
        quitf(_wa, "Wrong size: expected %d, found %d", ans_k, out_k);
    }

    // kiểm tra tập của thí sinh có hợp lệ không
    if (!is_valid_set(out_ids)) {
        quitf(_wa, "Contestant output is not a valid beautiful set");
    }

    // mọi thứ OK
    quitf(_ok, "Correct: k = %d", out_k);
}
