#### 1. Trapping Rain Water - **HARD**
##### Q.Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it can trap after raining.
![Image](https://assets.leetcode.com/uploads/2018/10/22/rainwatertrap.png)
Height: [0,1,0,2,1,0,1,3,2,1,2,1]

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
