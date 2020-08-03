#include<iostream>
#include<vector>
#include<limits>
using namespace std;
int global_max;
int max_seq(vector<int> &v, int n){
int max= v[0];
for(int i=1;i<=n;i++){
    
    if(v[i]+max>max && v[i]+max>v[i]){
        max = v[i]+max;
    }
    else if(v[i]+max<v[i] && v[i] > max){
        max = v[i];
    }
    
}
return max;
}


int max_sub(vector<int> &v, int n){
int local_max = 0;
int sum;
if(n==0){
    if(global_max<v[n]){
        global_max = v[n];
    }
    return v[n];
}
else{
    sum = max_sub(v,n-1);
    if(sum+v[n]>v[n]){
        if(sum+v[n]>global_max){
            global_max = sum+v[n];
        }
        return sum+v[n];
    }
    else{
        if(v[n]>global_max){
            global_max = v[n];
        }
        return v[n];
    }
}

}

int main(){
    int t,n;
    cin>>t;
    while(t--){
        global_max = -(numeric_limits<int>::max());;
        cin>>n;
        vector<int> v(n);
        for(int i=0;i<n;i++){
            cin>>v[i];
        }
        int sum,mus ;
        sum = max_sub(v,n-1);
        mus = max_seq(v,n-1);
        cout<<global_max<<' '<<mus<<endl;
    }
}