// all binary strings of given length

#include <iostream>
#include <vector>
#include <cstdio>

void print_binary(size_t bits_count) {
    int bits = bits_count;
    for (int i = 0; i < (1 << bits); ++i) {
        for (int j = bits - 1; j >= 0; --j) {
            printf("%d", (((1 << j) & i) > 0));
        }
        std::cout << '\n';
    }
}

using namespace std;

int main() {
    int n;
    cin >> n;
    print_binary(n);
}


// all binary strings of length n with k ones

#include <iostream>
#include <vector>
#include <cstdio>
#include <string>

using namespace std;

void generate(int n, int k) {
    vector<int> bits(n, 0);
    for (int i = 0; i < k; ++i) {
        bits[n - 1 - i] = 1;
    }
    do {
        for (auto elem : bits) {
            cout << elem;
        }
        cout << '\n';
    } while (next_permutation(bits.begin(), bits.end()));
}


int main() {
    int n, k;
    cin >> n >> k;
    generate(n, k);
}


// all increasing sequences of length k from first n natural numbers

#include <iostream>
#include <vector>
#include <cstdio>
#include <string>

using namespace std;

bool next_c(vector<int>& bits, int n) {
    int k = bits.size();
    for (int i = k - 1; i >= 0; --i) {
        if (bits[i] < n - k + 1 + i) {
            ++bits[i];
            for (int j = i + 1; j < k; ++j) {
                bits[j] = bits[j - 1] + 1;
            }
            return true;
        }
    }
    return false;
}

void generate(int n, int k) {
    vector<int> bits(k);
    for (int i = 0; i < k; ++i) {
        bits[i] = i + 1;
    }
    do {
        for (auto elem : bits) {
            cout << elem << ' ';
        }
        cout << '\n';
    } while (next_c(bits, n));
}


int main() {
    int n, k;
    cin >> n >> k;
    generate(n, k);
}


// all ways to write n as sum of non-increasing numbers in lexicographical order

#include <iostream>
#include <vector>
#include <cstdio>
#include <string>

using namespace std;

void print_sums(size_t n) {
    vector<vector<int>> ans;
    vector<int> partition(n);
    partition[0] = n;
    int last_elem = 0;
    while (true) {
        ans.emplace_back();
        for (int i = 0; i <= last_elem; ++i) {
            ans[ans.size() - 1].push_back(partition[i]);
        }
        int remaining = 0;
        while (last_elem >= 0 && partition[last_elem] == 1) {
            remaining += partition[last_elem];
            --last_elem;
        }
        if (last_elem < 0)
            break;
        --partition[last_elem];
        ++remaining;
        while (remaining > partition[last_elem]) {
            partition[last_elem + 1] = partition[last_elem];
            remaining = remaining - partition[last_elem];
            ++last_elem;
        }
        partition[last_elem + 1] = remaining;
        ++last_elem;
    }
    for (int i = ans.size() - 1; i >= 0; --i) {
        for (auto elem : ans[i]) {
            cout << elem << ' ';
        }
        cout << '\n';
    }
}



int main() {
    int n;
    cin >> n;
    print_sums(n);
}


//find permutation by its number in lexicographic order

#include <iostream>
#include <vector>
#include <cstdio>
#include <string>

using namespace std;
vector<int> factorial;


void print_permutation(int n, int k) {
    --k;
    vector<bool> used(n + 1, false);
    int pref;
    for (int i = 1; i <= n; ++i) {
        pref = k / factorial[n - i];
        k %= factorial[n - i];
        int remaining = 0;
        for (int j = 1; j <= n; ++j) {
            if (!used[j]) {
                ++remaining;
                if (remaining == pref + 1) {
                    cout << j << ' ';
                    used[j] = true;
                }
            }
        }
    }
    cout << '\n';

}

int main() {
    int n, k;
    cin >> n >> k;
    factorial.push_back(1);
    for (int i = 1; i <= n; ++i) {
        factorial.push_back(factorial.back() * i);
    }
    print_permutation(n, k);
}
