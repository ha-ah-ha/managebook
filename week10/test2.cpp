#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
    }
    sort(nums.begin(), nums.end());
    
    int max_val = nums.back();
    int min_val = nums[0];
    double median;
    if (n % 2 == 1) {
        median = nums[n / 2];
        printf("%d %d %d", max_val, (int)median, min_val);
    } else {
        int a = nums[n/2 - 1];
        int b = nums[n/2];
        int sum = a + b;
        if (sum % 2 == 0) {
            median = sum / 2;
            printf("%d %d %d", max_val, (int)median, min_val);
        } else {
            median = sum / 2.0;
            printf("%d %.1f %d", max_val, median, min_val);
        }
    }
    return 0;
}