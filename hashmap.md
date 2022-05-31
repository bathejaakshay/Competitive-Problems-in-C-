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
