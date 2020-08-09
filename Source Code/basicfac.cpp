#include<iostream>
#include<cmath>

using namespace std;
double fact_x(int x){
    if(x==1){
        return log10(1); 
    }
    else{
        return (log10(x) + fact_x(x-1));
    }
}
int main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        int y = floor(fact_x(n));
        cout<<y+1<<endl;
    }
}