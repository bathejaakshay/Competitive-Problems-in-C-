#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int main(){
    int t,size;
    cin>>t;
    while(t){
        cin>>size;
        int triplets =0;
        vector <int> a(size);
        for(int i=0; i<size; i++){
            cin>>a[i];
        }
        sort(a.begin(),a.end());
        int item;
        for (int i=a.size()-1;i>1;i--){
            item=a[i];
            // cout<<item<<endl;
            int left = 0, right = i-1,sum;
            while(left<right){
                // cout<<left<<' '<<right<<endl;
                sum=a[left]+a[right];
                if(sum==item){
                    triplets++;
                    left++;right--;
                }
                else if(sum<item){
                    left++;
                }
                else{right--;}
            }

        }
        if(triplets)
            cout<<triplets<<endl;
        else
        {
                cout<<-1<<endl;
        }
        
        t--;
    }
}