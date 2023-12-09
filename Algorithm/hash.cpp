#include <bits/stdc++.h>

using namespace std;

int main() {
    freopen("in.txt", "r", stdin);

    string text, pattern;
    cin >> text >> pattern;

    cout << "[..HASHING]\n\n";

    /// O(n)
    const int BASE = 28;
    const int MOD = 1e9 + 7;

    /// pattern hash koto?
    long long pattern_hash = 0;
    for (int i = 0; i < pattern.size(); ++i) {
        int new_char = pattern[i] - 'a' + 1;
        pattern_hash = (pattern_hash * BASE + new_char) % MOD;
    }

    long long text_window_hash = 0;
    for (int i = 0; i < pattern.size(); ++i) {
        int new_char = text[i] - 'a' + 1;
        text_window_hash = (text_window_hash * BASE + new_char) % MOD;
    }

    /// power = BASE^(|pattern|-1)
    long long power = 1;
    for (int i = 0; i < (int) pattern.size() - 1; ++i) {
        power = power * BASE % MOD;
    }

    /// text er surur 3 size window ase
    for (int i = 0, j = (int) pattern.size() - 1; j < text.size(); ++i, ++j) {
        if (text_window_hash == pattern_hash) {
            cout << "Match found at position " << i << '\n';
        }

        /// leftmost char ta baad dite hobe
        int out_char = text[i] - 'a' + 1;
        /// here power = BASE^(|pattern|-1)
        text_window_hash = (text_window_hash - out_char * power) % MOD;
        if (text_window_hash < 0) text_window_hash += MOD;

        text_window_hash = text_window_hash * BASE % MOD;

        if (j + 1 < text.size()) {
            int in_char = text[j + 1] - 'a' + 1;
            text_window_hash = (text_window_hash + in_char) % MOD;
        }
    }
    return 0;
}



