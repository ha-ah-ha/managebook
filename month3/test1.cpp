#include<bits/stdc++.h>
using namespace std;

int r,c;
int oldx,oldy;
bool is=false;
vector<string> note(1);
vector<string> ban;


void insert(){
    if(is){}
    string s;
    cin>>s;
    if(s=="Char"){
        string word;
        cin>>word;
        note[r].insert(c,word);
        c++;
    }
    if(s=="Enter"){
        string a=note[r].substr(0,c);
        string b=note[r].substr(c);
        note[r]=a;
        note.insert(note.begin()+r+1,b);
        c=0;
        r++;
    }
    if(s=="Space"){
        note[r].insert(c," ");
        c++;
    }
    if(s=="Paste"){
        if(ban.size()==0) return;
        if(ban.size()==1){
            note[r].insert(c,ban[0]);
            c+=ban[0].size();
        }
        else if(ban.size()==2){
            string a = note[r].substr(0, c) + ban[0];
			string b = ban[1] + note[r].substr(c);
			note[r] = a;
			note.insert(note.begin() + r + 1, b);
			r++; c = ban[1].size();
        }

    }
}

void print(){}

int main(){
    int n;
    cin>>n;
    while(n--){
        string str;
        cin>>str;
        if(str=="INSERT"){
            insert();
        }
        if(str=="PRINT"){

        }
    }
}
