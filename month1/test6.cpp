#include<bits/stdc++.h>
using namespace std;

bool isPowerOfK(long long i, long long k) {
    if (i == 1) 
    {
        return true;
    }
    while (i > 1) {
        if (i % k != 0) 
        {
            return false;
        }  
        i /= k;  
    }
    return i == 1;  
}

int main() {
    long long l, r, k;
    cin >> l >> r >> k;
    
    if (k <= 1) {
        cout << -1;
        return 0;
    }
    bool is = false;
    for (long long i = l; i <= r; i++) {
        if (isPowerOfK(i, k)) {
            cout << i << " ";
            is = true;
        }
    }
    
    if (!is) {
        cout << -1;
    }

    return 0;
}
