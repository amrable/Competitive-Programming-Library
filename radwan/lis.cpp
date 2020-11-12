// LONGEST INCREASING SUBSEQUENCE
#include<bits/stdc++.h>
using namespace std;

vector<int> a;

int lis_not_strictly_inc() {
    vector<int> lis;
    for (int i = 0; i < a.size(); i++) {
        int idx = upper_bound(lis.begin(), lis.end(), a[i]) - lis.begin();
        if (idx >= lis.size())
            lis.push_back(0);
        lis[idx] = a[i];
    }
    return lis.size();
}

int lis_strictly_inc() {
    vector<int> lis;
    for (int i = 0; i < a.size(); i++) {
        int index = lower_bound(lis.begin(), lis.end(), a[i]) - lis.begin();
        if (index >= lis.size())
            lis.push_back(0);
        lis[index] = a[i];
    }
    return lis.size();
}
