// SEGMENT TREE
#include <bits/stdc++.h>
using namespace std;

vector<int> a;
int n, m;
vector<long long> st, lazy;

void init() {
    a.resize(n);
    st.resize(4 * n);
    lazy.resize(4 * n);
}

void build(int i, int l, int r) {
    lazy[i] = 0;
    if (l == r) {
        st[i] = a[l];
        return;
    }
    int im = 2 * i, lm = (l + r) / 2;

    build(im, l, lm), build(im + 1, lm + 1, r);
    st[i] = st[im] + st[im + 1];
}

void push(int i, int l, int r) {
    st[i] += (r - l + 1) * lazy[i];  // apply postponed updates for st[i]
    if (l != r) {                   // propagate updates to child nodes only if current node i is not leaf node
        lazy[2 * i] += lazy[i];
        lazy[2 * i + 1] += lazy[i];
    }
    lazy[i] = 0;                   // st[i] is updated ... clear the postponed updates of node i
}
long long query(int i, int l, int r, int ql, int qr) {
    push(i, l, r);
    if (ql > r || qr < l) {
        return 0;
    }
    if (l >= ql && r <= qr) {
        return st[i];
    }
    int im = 2 * i, lm = (l + r) / 2;
    return query(im, l, lm, ql, qr) + query(im + 1, lm + 1, r, ql, qr);
}

void update(int i, int l, int r, int v, int ql, int qr) {
    push(i, l, r);
    if (ql > r || qr < l) {
        return;
    } else if (l >= ql && r <= qr) {
        lazy[i] += v;
        push(i, l, r);
        return;
    }

    int im = 2 * i, lm = (l + r) / 2;
    update(im, l, lm, v, ql, qr), update(im + 1, lm + 1, r, v, ql, qr);
    st[i] = st[im] + st[im + 1];
}

long long query(int ql, int qr) {
    return query(1, 0, n - 1, ql, qr);
}
void update(int v, int ql, int qr) {
    update(1, 0, n - 1, v, ql, qr);
}

int main() {

    cin >> n >> m;

    init();

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    build(1, 0, n - 1);

    for (int i = 0; i < m; i++) {
        int type;
        cin >> type;
        int l, r;

        if (type == 0) {
            cin >> l >> r;
            int ans = query(1, 0, n - 1, l, r);
            cout << ans << endl;
        } else if (type == 1) {
            int value;
            cin >> l >> r >> value;
            update(1, 0, n - 1, value, l, r);
        }

    }
    return 0;
}
