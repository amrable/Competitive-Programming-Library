// FENWICK_TREE
#include <bits/stdc++.h>
using namespace std;

struct fenwick {
    vector<int> fn;
    int NEUTRAL; // INF, -INF, 0 ...

    fenwick(int length, int neutral) {
        fn.assign(length + 5, neutral);
        this->NEUTRAL = neutral;
    }

    int query(int i) {
        int ret = NEUTRAL;
        for (++i; i > 0; i -= i & -i)
            ret = min(ret, fn[i]);
        return ret;
    }

    void update(int i, int val) {
        for (++i; i < fn.size(); i += i & -i)
            fn[i] = min(fn[i], val);
    }
};

