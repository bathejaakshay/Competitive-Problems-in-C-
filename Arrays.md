#### [1. Trapping Rain Water - **HARD**](https://leetcode.com/problems/trapping-rain-water/)
##### Q. Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it can trap after raining.

![Image](https://assets.leetcode.com/uploads/2018/10/22/rainwatertrap.png)

**height: [0,1,0,2,1,0,1,3,2,1,2,1]**

**Main Idea**: 
1. We need to remember for each index in the array how much water can be stored. 
2. For this we need to find for each index the maximum height in left array and right array respectively, say it is a and b respt.
3. Now the water that can be stored on the top of index i is **min(a,b) - height[i]** (if this value is less than zero than store 0)

Naive Approach : O(n^2)  
Two loops : for each index we compute max in its left and right;

**Best : O(n)**  
We can instead do some preprocessing:
Create two arrays left and right to store the left_max and right_max for an index i
i.e left[i] represent left_max of i and right[i] is right_max of i (This can be done in O(n))
After that iterate over height array and compute water trapped on each index : **min(left[i],right[i]) - height[i]**

---
#### 2. Left Rotating Array by k pos.
Naive Intuitive: Time- O(n) , space O(k) 
keep first k numbers in a temp[k] array left rotate the rest of the array k places and copying temp[k] after k indices.

**Best Approach: Time - O(n) , Space: O(1)**
1. reverse first k numbers (inplace)  
2. reverse remaining n-k numbers (inplace)  
3. now reverse the whole obtained array (inplace)  

```
A=[2,3,1,4,5]
k=2
1. [3,2,1,4,5] // reverse first k numbers
2. [3,2,5,4,1] // reverse remaining n-k numbers
3. [1,4,5,2,3] // reverse the whole array

```

*PS*: To rotate right just perform step 3 first then 1 and 2 respt.

---

#### 3. [3 Sum.](https://leetcode.com/problems/3sum/submissions/)  
**Problem:** Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]] such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == 0.

Notice that the solution set must not contain duplicate triplets.

**Main Idea**
There exist multiple approaches:
1. Naive: Fix i, j, k and find sum: O(n^3) 
2. Intermediate: Fix i and apply two sum using hashmap : O(n^2 + nlogn), space: O(n)
3. Best: Fix i and computw two sum using two pointer approach. O(n^2 + nlogn), space : O(1) 

```
vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> ans;
        if(nums.size() < 3){
            return {};
        }
        sort(nums.begin(),nums.end()); // We sort the array to make it easier to only keep unique vectors
        for(int i=0; i < nums.size()-2; i++){
            if(i==0 || nums[i]!=nums[i-1]){   // We dont want to compute for the same values of "a" again as it will bring duplicates
                int j=i+1, k=nums.size()-1;
                    while(j<k){   // Two pointer approach
                    if(j==i+1 || nums[j]!= nums[j-1]){ // We dont want to compute for the same values of "b" again as it will bring duplicates
                        int sum = nums[j] + nums[k] + nums[i];
                        if(sum == 0){
                            ans.push_back({nums[i],nums[j],nums[k]});
                            j++;
                            k--;
                        }
                        else if(sum > 0) {
                            k--;
                        }
                        else{
                            j++;
                        }
                    }
                        else{
                                j++;                          
                        }
                        
                    }
            }
        }
        return ans;
    }
};
```

---


