#include<iostream>
using namespace std;
int main(){
    char * a=new char[4];
    cin.getline(a,4);
    //bool isequal=true;
    for(int i=0;i<3;i++){
        for(int j=i+1;j<3;j++){
            if(a[i]!=a[j])
            {
                delete[] a;
                cout<<"Lost";
                return 0;
            }
        }
    }
    delete[] a;
    cout<<"Won";
    return 0;
}