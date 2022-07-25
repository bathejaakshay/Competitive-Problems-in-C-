#### [1. K difference pairs](https://leetcode.com/problems/k-diff-pairs-in-an-array/submissions/)
```
class Solution {
public:
    int findPairs(vector<int>& nums, int k) {
        set<pair<int,int>> st;
        sort(nums.begin(),nums.end()); // To maintain the order of elements in array while inserting pairs
        unordered_map<int,int> mp;
        for(int i=0;i<nums.size(); i++){
            
            if(mp.find(nums[i]-k)!=mp.end()){   // Dont check abs-difference cuz the array is sorted and hence the paired element of current element must be seen before itself. i.e i<j  and a[j] - a[i] = k then a[i] will always be there in mp while computing for a[j].
                st.insert(pair(nums[i],nums[i]-k)); // To keep unique pairs
            }
            
            mp[nums[i]]=1;
            
        }
        
    return st.size();
    }
};
```

---

#### [2. Subarrays with given XOR](https://www.interviewbit.com/old/problems/subarray-with-given-xor/)

**Approach**
1. Same logic as prefix sum.
2. intialize xor = 0;
3. for each element compute the xor : `xor^=A[i]`
4. Now if this is equal to required Xor B then count++
5. else we find if `xor^B` exist in map i.e suppose two subarrays 0 to i whose exor is x and i+1 to j whose exor is B, Now currently we have `xor` from say o to j
6. Now if we do xor^B then exor for i+1 to j zeros out and what remains is x i.e exor 0 to i. So we increment the count by the same.

```
int Solution::solve(vector<int> &A, int B) {

    unordered_map<int,int> mp;
    int x = 0, ans=0;
    for(int i=0;i<A.size();i++){
            x^=A[i];
            
            if(x == B){
                ans++;
            }
            
            if(mp.find(x^B) != mp.end()){
                ans+=(mp[x^B]);
            }
            mp[x]++;
        }
    return ans;
    
}
    
```

---
