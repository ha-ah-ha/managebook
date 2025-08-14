#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cassert>

using namespace std;

vector<string> tokens;
int pos = 0;
long long coeff[11] = {0};

void parse_statement(long long current_k, int current_e);

void parse_statement_list(long long current_k, int current_e) {
    while (pos < tokens.size() && tokens[pos] != "END") {
        parse_statement(current_k, current_e);
    }
}

void parse_statement(long long current_k, int current_e) {
    string token = tokens[pos++];
    if (token == "LOOP") {
        string param = tokens[pos++];
        long long loop_k;
        int loop_e;
        if (param == "n") {
            loop_k = 1;
            loop_e = 1;
        } else {
            loop_k = stoll(param);
            loop_e = 0;
        }
        long long new_k = current_k * loop_k;
        int new_e = current_e + loop_e;
        parse_statement_list(new_k, new_e);
        assert(tokens[pos++] == "END");
    } else if (token == "OP") {
        string num_str = tokens[pos++];
        long long val = stoll(num_str);
        coeff[current_e] += val * current_k;
    } else {
        assert(false);
    }
}

void parse_program() {
    assert(tokens[pos++] == "BEGIN");
    parse_statement_list(1, 0);
    assert(tokens[pos++] == "END");
}

int main() {
    string line;
    string input;
    while (getline(cin, line)) {
        input += line + " ";
    }
    istringstream iss(input);
    string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    pos = 0;
    parse_program();

    vector<string> terms;
    for (int e = 10; e >= 0; --e) {
        if (coeff[e] == 0) continue;
        string term;
        if (e == 0) {
            term = to_string(coeff[e]);
        } else {
            string var_part;
            if (e == 1) {
                var_part = "n";
            } else {
                var_part = "n^" + to_string(e);
            }
            if (coeff[e] == 1) {
                term = var_part;
            } else {
                term = to_string(coeff[e]) + "*" + var_part;
            }
        }
        terms.push_back(term);
    }

    if (terms.empty()) {
        cout << "Runtime = 0" << endl;
    } else {
        cout << "Runtime = ";
        for (size_t i = 0; i < terms.size(); ++i) {
            if (i != 0) {
                cout << "+";
            }
            cout << terms[i];
        }
        cout << endl;
    }

    return 0;
}