#include "testlib.h"

using namespace std;

const long long MIN_ANS = -1;
const long long MAX_ANS = 1000000000000000000LL; // 1e18

int n, q;

// Đọc và bỏ qua input (mảng a và các query)
void readInputHeader() {
    const int N_MAX = 600000;
    const int Q_MAX = 1250000;
    const long long A_MIN = 0;
    const long long A_MAX = 1000000000000000000LL;

    n = inf.readInt(1, N_MAX, "n");
    inf.readSpace();
    q = inf.readInt(1, Q_MAX, "q");
    inf.readEoln();

    // Bỏ qua dãy a
    for (int i = 0; i < n; ++i) {
        long long a = inf.readLong(A_MIN, A_MAX, "a_i");
        if (i + 1 < n) inf.readSpace();
        else inf.readEoln();
    }

    // Bỏ qua q query
    for (int j = 0; j < q; ++j) {
        int lj = inf.readInt(1, n, "l_j");
        inf.readSpace();
        int rj = inf.readInt(lj, n, "r_j");
        inf.readEoln();
    }
}

// readAns paradigm: dùng chung cho ouf và ans
vector<long long> read_answers(InStream &stream, const char *who) {
    vector<long long> res;
    res.reserve(q);

    for (int i = 0; i < q; ++i) {
        // Cho phép -1 hoặc [0, 1e18]
        long long x = stream.readLong(MIN_ANS, MAX_ANS, "answer");
        res.push_back(x);
    }

    // Không chấp nhận thêm dữ liệu sau q số (trừ whitespace)
    stream.skipBlanks();
    stream.quitif(!stream.seekEof(),
                  who == string("participant") ? _pe : _fail,
                  "%s output has extra data after %d numbers",
                  who, q);

    return res;
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    // Đọc input (để lấy q)
    readInputHeader();

    // Đọc output của thí sinh và của ban ra đề
    vector<long long> out = read_answers(ouf, "participant");
    vector<long long> answ = read_answers(ans, "jury");

    // So sánh từng câu hỏi
    for (int i = 0; i < q; ++i) {
        if (out[i] != answ[i]) {
            quitf(_wa,
                  "mismatch at query %d: expected %lld, found %lld",
                  i + 1, answ[i], out[i]);
        }
    }

    quitf(_ok, "all %d answers are correct", q);
}
