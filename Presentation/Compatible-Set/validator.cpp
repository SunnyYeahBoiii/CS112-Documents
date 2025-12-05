#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char** argv) {
    registerValidation(argc, argv);

    // Constraints
    const int N_MIN = 1;
    const int N_MAX = 100'000;

    const long long V_MIN = 1LL;
    const long long V_MAX = 2'000'000'000LL; // 2e9
    const long long LRI_MIN = 1LL;
    const long long LRI_MAX = 2'000'000'000LL; // 2e9

    // ---- Read n ----
    int n = inf.readInt(N_MIN, N_MAX, "n");
    inf.readEoln();

    // ---- Read n triplets (l_i, v_i, r_i) ----
    for (int i = 0; i < n; i++) {
        long long li = inf.readLong(LRI_MIN, LRI_MAX, "l_i");
        inf.readSpace();

        long long vi = inf.readLong(V_MIN, V_MAX, "v_i");
        inf.readSpace();

        long long ri = inf.readLong(LRI_MIN, LRI_MAX, "r_i");
        inf.readEoln();

        // Check constraint l_i ≤ v_i ≤ r_i
        if (!(li <= vi && vi <= ri)) {
            quitf(_fail, "Condition l_i <= v_i <= r_i violated at line %d", i + 2);
        }
    }

    // ---- No extra characters ----
    inf.readEof();
    return 0;
}
