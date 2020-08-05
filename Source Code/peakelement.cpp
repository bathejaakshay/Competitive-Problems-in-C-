#include<iostream>
#include<vector>
using namespace std;
int bsearch(const vector<int> &v,int left,int right){
    
    if(left<=right){
        int q = (left+right)/2;
        if(q>0&&q<v.size()-1&&v[q]>=v[q-1]&&v[q]>=v[q+1]){
        
            return q;
        }
        else if(q==0){
            if(v[q]>=v[q+1]){
            return q;}
            else{
                if(v[q]<v[q+1])
                return bsearch(v,q+1,right);}
        }
        else if(q==v.size()-1){ 
            if(v[q]>v[q-1]){return q;
            }
            else{ if(v[q]<v[q-1]) return bsearch(v,left,q-1);
                }
        }
        else{
            if(v[q-1]>v[q]){
             return  bsearch(v,left,q-1);
             
             }

            else if(v[q]<v[q+1]){
                return bsearch(v,q+1,right);
            }
            else return -1;             
              
        }
    }
    
}
int main(){
    int t,n;
    cin>>t;
    while(t--){
        cin>>n;
        vector <int> v(n);
        for(int i= 0;i<n;i++){
            cin>>v[i];
        }
        int ind = bsearch(v,0,n-1);
        cout<<ind<<endl;
    }
}