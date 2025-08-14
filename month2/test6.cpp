#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    int min_val = INT_MAX, max_val = INT_MIN;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        min_val = min(min_val, a[i]);
        max_val = max(max_val, a[i]);
    }
    int best_avg = 0, best_len = 0;
    for (int avg = min_val; avg <= max_val; ++avg) {
        long long sum = 0, min_prefix = 0;
        int len = 0;
        vector<long long> prefix(n + 1, 0);

        for (int i = 0; i < n; ++i) {
            prefix[i + 1] = prefix[i] + (a[i] - avg);
        }

        for (int j = 1; j <= n; ++j) {
            for (int i = 0; i < j; ++i) {
                long long seg_sum = prefix[j] - prefix[i];
                int seg_len = j - i;
                if (seg_sum >= 0) {
                    if (avg > best_avg || (avg == best_avg && seg_len > best_len)) {
                        best_avg = avg;
                        best_len = seg_len;
                    }
                }
            }
        }
    }

    cout << best_avg << " " << best_len << endl;
    return 0;
}
