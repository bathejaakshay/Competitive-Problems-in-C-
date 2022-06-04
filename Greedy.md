#### [1. Largest Permuatation after B swtiches](https://www.interviewbit.com/old/problems/largest-permutation/)

**Problem Statement:**  
Given an integer array A of size N consisting of unique integers from 1 to N. You can swap any two integers atmost B times.  
Return the largest lexicographical value array that can be created by executing atmost B swaps.  
Problem Constraints  
1 <= N <= 10^6  
1 <= B <= 10^9  

E.g: N = [2,4,1,3] B = 2  
step 1: 4 2 1 3  
step 2: 4 3 1 2  

output: 4 3 1 2  

**Naive Approach**  
For each element Find maximum in its right array and swap places. T(n) = O(n^2)

**Smart Approach**  
1. We Check whether element at ith pos is value N-i i.e the value that should have been there. If not the swap it with N-i valued index.  
2. This can be efficiently done using unordered_map

```
vector<int> Solution::solve(vector<int> &A, int B) {
    
    unordered_map<int,int> mp;
    for(int i=0; i<A.size() ;i++){
        mp[A[i]] = i;
    }
    int n=A.size();
    for(int i=0;i<A.size() && B;i++){
        if(A[i]!=A.size()-i){
            swap(A[i],A[mp[A.size()-i]]);
            mp[A[mp[A.size()-i]]] = mp[A.size()-i];
            mp[A[i]] = i;
            B--;
        }
    }
    return A;
}

```

---

#### [2. Largest Number in an array](https://leetcode.com/problems/largest-number/)
**Problem:**  
Given a list of non-negative integers nums, arrange them such that they form the largest number and return it.  
Since the result may be very large, so you need to return a string instead of an integer.  
**Main Idea:**  
1. Sort the array in a way that concatenation two numbers is always greater

```
bool comparator(int a,int b){
    string x=to_string(a);
    string y=to_string(b);
    if(x+y > y+x) return true;
    return false;
}
class Solution {
public:
    string largestNumber(vector<int>& nums) {
        
        if(nums.size()==1){
            string ans =  to_string(nums[0]);
            return ans;
        }
        int i;
        for(i=0;i<nums.size();i++){
            if(nums[i]>0) break;
        }
        if(i==nums.size()) return "0"; \\Edge case when array contains only zeros
        sort(nums.begin(),nums.end(),comparator);
        string ans =to_string(nums[0]);
        for(i=1;i<nums.size();i++){
            string curr = to_string(nums[i]);
                ans = ans+curr;
        }
        return ans;
    }
};
```
---

