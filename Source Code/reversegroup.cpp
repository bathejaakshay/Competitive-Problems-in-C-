#include<iostream>
#include<queue>
#include<vector>

#include<algorithm>
#include<stack>
using namespace std;
int main(){
    int t,n,k,item,nog;
    cin>>t;
    while(t--){
        cin>>n>>k;
        queue<int> v;
        stack<int> s;
        vector <int> vec;
        for(int i =0;i<n;i++){
            cin>>item;
            v.push(item);
        }
        if(k>=n){
            while(!v.empty()){s.push(v.front());v.pop();}
            while(!s.empty()){cout<<s.top()<<' ';s.pop();}
            cout<<'\n';continue;
        }
        else{
            while(!v.empty()){
                if(v.size()>k){
                    int z=k;
                    while(z--){
                        s.push(v.front());
                        v.pop();
                        
                    }
                    while(!s.empty()){
                        vec.push_back(s.top());
                        s.pop();
                    }


                }
                else{
                    while(!v.empty()){
                        s.push(v.front());
                        v.pop();
                    }
                    while(!s.empty()){
                        vec.push_back(s.top());
                        s.pop();
                    }
                    
                }
            }

        }
        for(int i = 0; i<vec.size();i++){
            cout<<vec[i]<<' ';
        }
        cout<<'\n';
 
    }
}