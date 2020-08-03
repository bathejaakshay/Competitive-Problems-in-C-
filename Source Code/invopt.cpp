#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

long long int merge(int v[],int left, int right, int q, long long inv){
    int n1 = q-left+1, n2=right-q; 
    int a[n1],b[n2];

    for(int i = 0, x=0;i<n1;i++){
        a[i] = v[left+i];
    }
    for(int i = 0,x=0;i<n2;i++){
        b[i] = v[q+i+1];
    }
    // cout<<"left right q "<<left<<' '<<right<<' '<<q<<endl;
    int i = 0, j=0, p = left;
    while(i<n1 && j<n2){
        if(a[i] <= b[j]){
            v[p] = a[i];
            p++;i++;
            
        }
        else{
            v[p] = b[j];
            p++;j++;
            inv = inv + n1 - i;
        }
    }
    while(i<n1){
        v[p]=a[i];
        p++;i++;
    }
    while(j<n2){
        v[p] = b[j];
        p++;j++;
    }
    return inv;
    
}
long long int merge_sort(int v[],int left,int right, long long int inv){
    long long x,y;
    if(left<right){
    int q = (left+right)/2;
    // cout<< "left right q ="<<left<<' '<<right<<' '<<q<<endl;
   x= merge_sort(v,left,q, inv);
   y= merge_sort(v,q+1,right,inv);
    inv= x + y +merge(v,left,right,q,inv);
    return inv;
    }
    else if(left == right){
        return inv;
    }
}
int main(){
    int t,n;
    cin>>t;
    while(t--){
        cin>>n;
        // vector<int> x(n);
        int x[n];
        // vector<int> y(n);
        long long int inv = 0;
        for(int i=0;i<n;i++){
            cin>>x[i];
        }

        inv = merge_sort(x,0,n-1,inv);

        for(int i=0;i<n;i++){
            cout<<x[i]<<' ';
        }
        cout<<endl;
        cout<<inv<<endl;
    }
}