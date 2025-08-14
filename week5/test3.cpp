#include<bits/stdc++.h>
using namespace std;

int main(){
    int n,k;
    cin>>n>>k;
    int* nums=new int[n];
    for(int i=0;i<n;i++){
        cin>>nums[i];
    }
    deque<int> min1;
    vector<int> min2;
    for(int i=0;i<n;i++){//找最小值
        while(!min1.empty()&&min1.front()<i-k+1){
            min1.pop_front();
        }
        while(!min1.empty()&&nums[i]<=nums[min1.back()]){
            min1.pop_back();
        }
        min1.push_back(i);
        if(i>=k-1){
            min2.push_back(nums[min1.front()]);
        }
    }

    deque<int> max1;
    vector<int> max2;
    for(int i=0;i<n;i++){
        while(!max1.empty()&&max1.front()<i-k+1){
            max1.pop_front();
        }
        while(!max1.empty()&&nums[max1.back()]<=nums[i]){
            max1.pop_back();
        }
        max1.push_back(i);
        if(i>=k-1){
            max2.push_back(nums[max1.front()]);
        }
    }
    for(int i:min2){
        cout<<i<<' ';
    }
    cout<<"\n";
    for(int i:max2){
        cout<<i<<' ';
    }
}