#include "testlib.h"

using namespace std;

int main() {
    registerValidation();

    const int N_MAX = 600000;          // 6 * 10^5
    const int Q_MAX = 1250000;         // 125 * 10^4
    const long long A_MIN = 0;
    const long long A_MAX = 1000000000000000000LL; // 1e18

    int n = inf.readInt(1, N_MAX, "n");
    inf.readSpace();
    int q = inf.readInt(1, Q_MAX, "q");
    inf.readEoln();

    // Dòng 2: n số a_i
    for (int i = 0; i < n; ++i) {
        long long a = inf.readLong(A_MIN, A_MAX, "a_i");
        if (i + 1 < n) inf.readSpace();
        else inf.readEoln();
    }

    // q dòng query: l_j, r_j
    for (int j = 0; j < q; ++j) {
        int lj = inf.readInt(1, n, "l_j");
        inf.readSpace();
        int rj = inf.readInt(lj, n, "r_j"); // r_j >= l_j
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
