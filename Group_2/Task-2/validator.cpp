#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(0, 200000, "m");
    inf.readEoln();

    for (int i=1;i<= m;i++ ){
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readSpace();
        int w = inf.readInt(1, (int)1e9, "w");
        inf.readEoln();
    }

    inf.readEof();
}
