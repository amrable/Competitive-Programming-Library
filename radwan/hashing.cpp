// HASHING
#include<bits/stdc++.h>

using namespace std;

const int P = 53, MOD = 1e9 + 7;
vector<int> power, prefix;

void fill_power(int n) {
    power.push_back(1);
    for (int i = 1; i <= n; i++)
        power.push_back((1LL * P * power[i - 1]) % MOD);
}

void prefix_order_hash(const string &s) {
    prefix.push_back(0);
    for (int i = 1; i <= s.size(); i++)
        prefix.push_back((1LL * prefix[i - 1] + 1LL * power[i - 1] * (s[i - 1] - 'a' + 1)) % MOD);
}

int string_order_hash(const string &s) {
    int ret = 0;
    for (int i = 0; i < s.size(); i++)
        (ret += ((1LL * power[i] * (s[i] - 'a' + 1)) % MOD)) %= MOD;
    return ret;
}

int string_no_order_hash(const string &s, const int &x, const int &MOD) {
    int ret = 0;
    for (char c: s)
        (ret += power[c - 'a' + 1]) %= MOD;
    return ret;
}

int query(int i, int j) {
    return (prefix[j + 1] - prefix[i] + MOD) % MOD;
}

int normalize(int start_index, int hash_value) {
    return (1LL * hash_value * power[power.size() - start_index - 1]) % MOD;
}

