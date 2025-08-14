#include<bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size();
    if (n < 6) {
        cout<<0;
        return 0;
    }
    int strength = 0;
    char pre = '\0';
    for (char c : s) {
        char cur;
        if (isdigit(c)) {
            cur = 'd';
        } else if (islower(c)) {
            cur = 'l';
        } else if (isupper(c)) {
            cur = 'u';
        } else {
            continue;
        }
        if (pre != cur) {
            strength++;
            pre = cur;
        }
    }
    cout <<strength;
    return 0;
}