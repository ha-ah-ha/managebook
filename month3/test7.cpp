#include<bits/stdc++.h>
using namespace std;
int find(const string& s, const string& t) {
    int count = 0;
    size_t pos = 0;
    while ((pos = t.find(s, pos)) != string::npos) {
        count++;
        pos += s.length();
    }
    return count;
}
string print1(int n) {
    string result = "01";
    while (result.size() < n) {
        string str;
        for (char c : result) {
            str += (c == '0') ? '1' : '0';
        }
        result += str;
    }
    return result.substr(0, n);
}
int main() {
    int n;
    string T;
    cin >> n >> T;
    string s = print1(n);
    int num = find(T, s);
    cout <<num<< endl;
    return 0;
}