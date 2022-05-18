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
#### [3. Next Permutation](https://leetcode.com/problems/next-permutation/)
**Problem Statement:** A permutation of an array of integers is an arrangement of its members into a sequence or linear order.  
For example, for arr = [1,2,3], the following are considered permutations of arr: [1,2,3], [1,3,2], [3,1,2], [2,3,1].  
The next permutation of an array of integers is the next lexicographically greater permutation of its integer. More formally, if all the permutations of the array are sorted in one container according to their lexicographical order, then the next permutation of that array is the permutation that follows it in the sorted container. If such arrangement is not possible, the array must be rearranged as the lowest possible order (i.e., sorted in ascending order).

**Main Idea:**  
1. Find if there exist an increasing pair starting from the end pos. i.e a[i] < a[i+1]. Call i as index1
2. If there does not exist such increasing pair then the array is in decreasing order hence just reverse it and return.
3. If there exist index1 then again find index2 starting from end s.t a[index1] < a[index2]. (This is done because we want first element just greater then index 1, so we find from end). e.g: [1,3,2]: index1 = 0.. now we cant take index2 =1 as it will lead to ans [3,2,1]. We take index2 = 2. So ans= [2,1,3]
4. Once index1 and index2 are obtained, swap them and reverse array from index1+1 till end. reverse(nums.begin()+index1+1, nums.end()). **RETURN**

```
  void nextPermutation(vector<int>& nums) {
        if(nums.size()<=1){return;}
        int index1=-1,index2=-1;
        for(int i=nums.size()-1; i>=1;i--){
            if(nums[i-1]<nums[i]){
                index1=i-1;
                // index2=i;
                break;
            }
        } 
        if(index1==-1){
            reverse(nums.begin(), nums.end());
        }
        else{
            for(int i = nums.size()-1; i>index1; i--){
                if(nums[i]>nums[index1]) {
                    index2 = i;
                    break;
                }
            }
            swap(nums[index1], nums[index2]);
            reverse(nums.begin()+index1+1,nums.end());
            
        }
        return;
        
    }
```
***PS Shortcut:*** next_permutation(nums.begin(),nums.end())  
***MAIN LEARNING:*** In such ques to find next lexicographical order or next permutation, always start finding  increasing from last instead of finding last increasing pair from the start.

---

#### [4.Binary Search in Rotated Sorted Array](https://leetcode.com/problems/search-in-rotated-sorted-array/)
**Main Idea:**
1. Find the pivot element first (around which the array is rotated i.e a decreasing pair, a[pivot] > a[pivot+1])
2. Apply binary search in left or right side of pivot element as per its value. i.e if 0<=item<=pivot then serach in left else in right.

```
 \\ To apply binary search
 int b_search(vector<int>& nums, int i, int j, int item){
        if(i > j) return -1; 
        int mid = (i+j)/2;
        if(nums[mid] == item) return mid;
            if(nums[mid]<item){
                return b_search(nums, mid+1, j, item);
            }
            else{
                return b_search(nums, i, mid-1, item);
            }
        
    }
    //To get pivot element
    int get_pivot(vector<int> &nums, int i, int j, int item){
        if(i>j) return -1;
        int mid = (i+j)/2;
        if(mid == nums.size()-1){
            return -1;
        }
        if(nums[mid] > nums[mid+1]){
            return mid; 
        }
        else{
            if(nums[mid] < nums[nums.size()-1]){
                return get_pivot(nums, i, mid-1, item);
            }
            else{
                return get_pivot(nums, mid+1, j, item);
            }
        }
            
    }
    \\Driver Function
    int search(vector<int>& nums, int target) {
        if(nums.size()==1){
            if(nums[0]==target) return 0;
            else return -1;
        }
        int pivot = get_pivot(nums, 0, nums.size()-1, target);
        if (pivot==-1){
            return b_search(nums, 0, nums.size()-1,target);
        }
        else{
             if(target<=nums[pivot] && target>=nums[0]){
                return b_search(nums,0,pivot, target);
            }
            else{
                return b_search(nums, pivot+1,nums.size()-1,target);
            }
        }
    }
```


