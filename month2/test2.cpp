#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
vector<string> tokens;
int pos=0;
ll coeff[11]={0};
void parse(ll currentk,int currente);
void parse_list(long long current_k, int current_e) {
    while (pos < tokens.size() && tokens[pos] != "END") {
        parse(current_k, current_e);
    }
}
void parse(ll currentk,int currente){
    string token1=tokens[pos++];
    if(token1=="LOOP"){
        string parm=tokens[pos++];
        ll loopk;
        int loope;
        if(parm=="n"){
            loopk=1;
            loope=1;
        }
        else{
            loopk=stoll(parm);
            loope=0;
        }
        ll newk=currentk*loopk;
        int newe=currente+loope;
        parse_list(newk,newe);
        assert(tokens[pos++]=="END");
    }
    else if(token1=="OP"){
        string numstr=tokens[pos++];
        long long val=stoll(numstr);
        coeff[currente]+=val*currentk;
    }
    else{
        assert(false);
    }
}

int main(){
    string line;
    string input;
    while(getline(cin,line)){
        input+=line+" ";
    }
    istringstream iss(input);
    string token;
    while(iss>>token){
        tokens.push_back(token);
    }
    pos=0;
    assert(tokens[pos++]=="BEGIN");
    parse_list(1,0);
    assert(tokens[pos++]=="END");
    vector<string> terms;
    for(int i=10;i>=0;--i){
        if(coeff[i]==0){
            continue;
        }
        string term;
        if(i==0){
            term=to_string(coeff[i]);
        }
        else{
            string var;
            if(i==1){
                var="n";
            }
            else{
                var="n^"+to_string(i);
            }
            if(coeff[i]==1){
                term=var;
            }
            else{
                term=to_string(coeff[i])+"*"+var;
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