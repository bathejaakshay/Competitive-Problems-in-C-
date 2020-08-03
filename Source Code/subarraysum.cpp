#include<iostream>
using namespace std;

int main(){
    int t,size,target,sum;
    
    cout<<"Hello World"<<endl;
    cin>>t;
    while(t){
        cin>>size>>target;
        int a[size];
        for(int i=0;i<size;i++){
            cin>>a[i];
        }
        for(int i=0;i<size;i++){
            sum=a[i];
            if(sum==target){
                cout<<i+1<<' '<<i+1<<endl;
                break;
            }
            else{
                for(int j=i+1; j<size;j++){
                  sum += a[j];
                  if(sum==target){
                      cout<<i+1<<' '<<j+1<<endl;
                      break;
                  }
                  else if(sum>target){
                      break;
                  }
                      
                   
                }
            }
            if(sum==target){break;}
        }
        if(sum!=target){
            cout<<-1<<endl;
        }
        t--;
    }
}