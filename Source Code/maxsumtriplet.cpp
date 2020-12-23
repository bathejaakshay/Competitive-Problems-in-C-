#include<iostream>
#include <vector>
#include <bits/stdc++.h> 
using namespace std;

int main(){
    int n,item;
    cin>>n;
    vector <int> v;
    //scanning the vector
    for (int i=0;i<n;i++){
        cin>>item;
        v.push_back(item);
    }

    n = v.size();
    vector <int> right(n,0);

    //calculating maximum suffix of array
    for(int i = n-2; i>=0; i--){
        int mx = max(right[i+1],v[i+1]);
        if(mx > v[i]){
            right[i] = mx;
        }
    }
    int sum=0;
    set <int> s;
    //sorting and binary searching max at left of element which is smaller than that element
    s.insert(v[0]);
    for(int i=1;i<n-1;i++){
        s.insert(v[i]);
        if(right[i]!=0){
            auto itr = s.find(v[i]);
            if(itr!=s.begin()){
                
                sum = max(sum, ((*(--itr)) + v[i] + right[i]));
                
            }
        }
    }
    cout<<sum<<endl;



}
