#include<bits/stdc++.h>
using namespace std;

int number(const string& str,int& i){
    int num=0;
    while(i<str.size()&&isdigit(str[i])){
        num=num*10+(str[i]-'0');
        i++;
    }
    return num;
}

struct element
{
    string elem;
    int num;
    element(string str="",int num1=0){
        elem=str;
        num=num1;
    }
};


void calculate(string str,map<string,int>& map1){
    stringstream ss(str);
    string item;
    
    while(getline(ss,item,'+')){
        int facter=1;
        int i=0;
        vector<element> elements;
        if(!item.empty()&&isdigit(item[0])) facter=number(item,i);
        while(i<item.size()){
            if(isdigit(item[i])){
                int num=number(item,i);
                if(elements[elements.size()-1].elem==")"){
                    int j=elements.size()-1;
                    elements[j].elem="/";
                    //j--;
                    while(!elements.empty()&&elements[--j].elem!="("){
                        elements[j].num*=num;
                      //  j--;
                    }
                    if(j>=0){
                        elements[j].elem="/";
                    }
                }
                else if (!elements.empty()){
                    elements[elements.size()-1].num*=num;
                }
            }
            else if(item[i]==')'){
                elements.push_back(element(")",0));
                if(i+1==item.size()||!isdigit(item[i+1])){
                    item.insert(i+1,"1");
                    i++;
                }
                i++;
            }
            else if(item[i]=='('){
                elements.push_back(element("(",0));
                i++;
            }
            else if(isupper(item[i])){
                string str1="";
                str1+=item[i];
                i++;
                if(islower(item[i])){
                    str1+=item[i];
                    i++;
                }
                elements.push_back(element(str1,1));
            }
            else{
                i++;
            }
        }
        for(const auto& t:elements){
            //if(t.elem == "/") {continue;}
            
            if(t.elem!="/"&&t.elem!="("&&t.elem!=")")
            {
                map1[t.elem]+=t.num*facter;
            }
        }
    }
}

bool issame(map<string,int>& map1,map<string,int>& map2){
    if(map1.size()!=map2.size()) return false;
    for(const auto& t:map1){
        if(t.second!=map2[t.first]){
            return false;
        }
    }
    return true;
}

int main(){
    
    int n;
    cin>>n;
    
    while(n--){
        string str,leftstr,rightstr;
        cin>>str;
        stringstream ss(str);
        getline(ss,leftstr,'=');
        getline(ss,rightstr);
        map<string,int> left,right;
        calculate(leftstr,left);
        calculate(rightstr,right);
        if(issame(right,left)){
            cout<<"Y"<<"\n";
        }
        else{
            cout<<"N"<<"\n";
        }
    }
}