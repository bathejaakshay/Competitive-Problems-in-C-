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


#### [2. Minimum Cost to Make Array Equal](https://leetcode.com/problems/minimum-cost-to-make-array-equal/description/)  
You are given two 0-indexed arrays nums and cost consisting each of n positive integers.  

You can do the following operation any number of times:  

Increase or decrease any element of the array nums by 1.  
The cost of doing one operation on the ith element is `cost[i]`.  

Return the minimum total cost such that all the elements of the array nums become equal.  

**Approach** 
- pre-req minCost to make array equal when cost of each element is 1. In this case our cost is minimum/ coverges at median of the array e.g `[1,5,7,8,10]` : min is cost when we do `[7,7,7,7,7]`
- Similarly here we have been given cost of each element. We can simply observe that we can reduce the current problem into the above one by finding "weighted median" i.e replace the num[i] which `cost[i]` times `nums[i]` and then find median of the whole array
- E.g `[1,5,7,8,10]` cost: `[2,3,1,4,1]` :-> updated array A: `[1,1,5,5,5,7,8,8,8,8,10]` Now we find medain of A and calculate the number of operations.

