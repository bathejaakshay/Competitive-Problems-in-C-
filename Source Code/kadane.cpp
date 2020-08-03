#include<iostream>
#include<vector>
#include<algorithm>
#include<limits>

using namespace std;
int kadane(vector<int> &v,int n, int &max){
    int item,current,x;
    
    if(n==1){
        max = max>v[0]?max:v[0];
        return v[0];
    }
    else{
        current = v.back();
        v.pop_back();
        item = kadane(v,n-1,max);
        x = current+item;
        if(x>current){
            max = max>x?max:x;  
            return x;

        }
        else{
            max = max>current?max:current;
            return current;
        }
        
        
            }
}

int main(){

int t,n,max;
cin>>t;
while(t--){
max =  -(numeric_limits<int>::max()); 
cin>>n;
vector <int>v(n);
for(int i=0;i<n;i++){
    cin>>v[i];
}

int item = kadane(v,n,max);
cout<<max<<endl;
}

}