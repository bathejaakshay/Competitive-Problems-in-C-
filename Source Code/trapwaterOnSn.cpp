#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

long long int water_trapped(const vector <int> &v){
    int n=v.size();
    long long int tw=0;
    int left = 0,right = n-1;
    if(n<3){
        return 0;
    }
    else{
        int lmax = v[0], rmax = v[n-1];
        while(left<=right){
            if(lmax<=rmax){
                lmax = max(v[left],lmax);
                rmax = max(v[right],rmax);
                tw = tw+lmax-v[left];
                left++;
            }
            else{
                lmax = max(v[left],lmax);
                rmax = max(v[right],rmax);
                tw = tw+rmax-v[left];
                right--;
             

            }
        }
        
        return tw;  
    }
}

int main(){
    int t,n;
    cin>>t;
    while(t--){
        cin>>n;
        vector<int> v(n);
        for(int i=0;i<n;i++){
            cin>>v[i];
        }
        int st = 0,end = n-1,tw=0;
        
        // The following algo has T(n) = O(n^2) cuz of min(max(v[0...i]),max(v[i...n])) operation 

        // for(int i=st+1;i<=end-1;i++){
        //     int lm=0,rm=0,mx=0;
        //     for(int y=st;y<=i;y++){
        //         lm=max(lm,v[y]);
        //     }
        //     for(int y=i;y<=end;y++){
        //         rm=max(rm,v[y]);
        //     }
        //     mx = min(lm,rm);

        //        tw = tw+mx-v[i];

        //}
        // cout<<tw<<endl


        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        // Optimization 1. To optimize min(max(v[0...i]),max(v[i...n])) we can maintain two arrays Leftmax[0...n] and Rightmax[0...n] this will result in 
        // T(n) = O(n) and S(n) = O(n)
        
        // int leftmax[n],rightmax[n];
        // leftmax[0]=v[0]; rightmax[n-1]=v[n-1];
        // for(int i=1;i<n;i++){
        //     leftmax[i] = max(leftmax[i-1],v[i]);
        // }
        // for(int i=n-2;i>=0;i--){
        //     rightmax[i] = max(rightmax[i+1],v[i]);

        // }

        // for(int i=0;i<n;i++){
        //     tw = tw + (min(leftmax[i],rightmax[i])-v[i]);

        // }
        // cout<<tw<<endl;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        // Optimization 2. If we plot leftmax[] and rightmax[] against index i the leftmax will be a non-decresing and rightmax[] will be a non-increasing function
        // and min(leftmax,rigtmax) will be a lower envelope function which consists of a plot that firstly increases and then decreases ,
        // such question which  have min(max,max) or max(min,min) functions i.e lower envelope function can be optimized through generally using
        // 1. Two pointer approach (Mostly Used) or 2. Binary Search approach.

        // Two pointer approach:  T(n) = O(n)  , S(n)= O(1)

        long long int twater = water_trapped(v);
        cout<<twater<<endl;
    }
}