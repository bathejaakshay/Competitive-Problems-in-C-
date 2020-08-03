#include<iostream>
#include<vector>
#include<map>
#include<deque>
#include<utility>

using namespace std;
int main(){
    int t,n,k;
    cin>>t;
    while(t--){
        cin>>n>>k;
        vector<int> v(n);
        deque<int> q;
        for(int i=0;i<n;i++){
            cin>>v[i];
        }
        int item;
        for(int i=0;i<k;i++){
            if(q.empty()){q.push_back(i);}
            else{
                
                while(!(q.empty()) && v[i]>v[q.back()])
                {
                    q.pop_back();
            }
            q.push_back(i);
            }
            
        }
        item = q.front();
        cout<<v[item]<<' ';
        for(int i = k ;i<n;i++){
            // cout<<"i = "<<i<<endl;
            // // for(int j=i;j<i+k&&j<n;j++){
            //     hmap.insert(pair<int,int>(v[j],j));
            // }
        
        if(q.empty()){
            q.push_back(i);
        }
        
        else{
            if(q.front()<(i-k+1)){
            q.pop_front();
            }
            while(!(q.empty()) && v[i]>v[q.back()])
                {
                    q.pop_back();
            }
            q.push_back(i);
            
        
        }
        
        cout<<v[q.front()]<<' ';
    }
    cout<<endl;

}
}
