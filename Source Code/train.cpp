#include<iostream>
#include<vector>
#include<algorithm>
#include<map>
#include<iterator>
#include<utility>

using namespace std;

int main(){
    int t,n;
    cin>>t;
    while(t--){
        cin>>n;
        vector<int> arr(n);
        vector<int> dept(n);
        multimap<int,char> map;
        int item;
        for(int i=0;i<n;i++){
            cin>>item;
            map.insert(pair<int,char>(item,'a'));
        }
        for(int i=0;i<n;i++){
            cin>>item;
            map.insert(pair<int,char>(item,'d'));
        }
        int tand = 0,max_plat=0,plt=0;
        for(auto it=map.begin();it!=map.end();it++){
            if((*it).second == 'a'){
                tand++;
            }
            else{tand--;}
            if(tand>=1){plt = tand;
            if(plt>max_plat){
                max_plat = plt;
            }
                

            }
        }
        cout<<max_plat<<endl;

        
    }
}