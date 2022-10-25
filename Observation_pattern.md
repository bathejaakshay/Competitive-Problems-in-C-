#### [1. Minimum Number of Operations to Make Arrays Similar](https://leetcode.com/contest/weekly-contest-316/problems/minimum-number-of-operations-to-make-arrays-similar/)  
You are given two positive integer arrays nums and target, of the same length.  

In one operation, you can choose any two distinct indices i and j where 0 <= i, j < nums.length and:  
```
set nums[i] = nums[i] + 2 and  
set nums[j] = nums[j] - 2.  
```
Two arrays are considered to be similar if the frequency of each element is the same.  

Return the minimum number of operations required to make nums similar to target. The test cases are generated such that nums can always be similar to target.  

**Approach**
 -Two  things to observe is that odd terms in nums will match to odd terms in target
 - second is the matching will always be in sorted order. i.e a1 < b1 in nums_odd and a'1<b'1 in target_odd then a1 should always be converted to a'1 and b1 to b'1
 - The total cost will be abs_diff of all nums_odd and target_odd , nums_even and target even in sorted order
 - The total operations both + and - : total_cost/2
 - Min operations i.e just + is total_operations/2

```
 long long makeSimilar(vector<int>& nums, vector<int>& target) {
        sort(nums.begin(), nums.end());
        sort(target.begin(), target.end());
        vector<int> oddn, oddt;
        vector<int> evenn, event;
        for(int i=0; i<nums.size(); i++){
            if(nums[i]%2==0) evenn.push_back(nums[i]);
            else{
                oddn.push_back(nums[i]);
            }
            if(target[i]%2==0) event.push_back(target[i]);
            else oddt.push_back(target[i]);
        }
        
     long long op=0;
     for(int i=0; i<evenn.size(); i++){
         op = op + abs(evenn[i] - event[i]);
     }
     for(int i=0; i<oddn.size(); i++){
         op = op + abs(oddn[i] - oddt[i]);
     }
        return op/4;
    }
```
---
