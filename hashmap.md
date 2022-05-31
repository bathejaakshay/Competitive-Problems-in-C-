#### [1. K difference pairs](https://leetcode.com/problems/k-diff-pairs-in-an-array/submissions/)
```
class Solution {
public:
    int findPairs(vector<int>& nums, int k) {
        set<pair<int,int>> st;
        sort(nums.begin(),nums.end());
        unordered_map<int,int> mp;
        int count=0;
        
        for(int i=0;i<nums.size(); i++){
            
            if(mp.find(nums[i]-k)!=mp.end()){
                st.insert(pair(nums[i],nums[i]-k));
            }
            
            mp[nums[i]]=1;
            
        }
        for(auto it=st.begin(); it!=st.end(); it++){
            count++;
        }
    return count;
    }
    
};
```
