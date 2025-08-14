    #include<iostream>
    #include<vector>
    #include<string>
    using namespace std; 
    int n,k;
    int num;
    vector<int> b;
    char** q=new char*[n];
    int options;
    void fun(int cow,int* a){
        if(num==k){
            options++;
            return;
        }
        if(cow>=n){
            return;
        }
        
        for(int i=0;i<n;i++){
            if(q[cow][i]=='#'&&a[i]==-1){
                num++;
                a[i]=1;
                fun(cow+1,a);
                num--;
                a[i]=-1;
            }
        }
        fun(cow+1,a);
    }



    int main(){
        
        while(true){
        cin>>n>>k;
        if(n==-1&&k==-1){
            break;
        }
        options=0;
        int* a=new int[n];
        num=0;
        for(int i=0;i<n;i++){
            a[i]=-1;
            
        }
        for(int i=0;i<n;i++){
            q[i]=new char[n];
        }
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                cin>>q[i][j];
            }
        }
        fun(0,a);
        b.push_back(options);
    }
    for(int i=0;i<b.size();i++){
        cout<<b[i]<<"\n";
    }
    return 0;
    }