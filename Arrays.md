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

#### [5. Finding the Duplicate number in linear (nlogn) time with O(1) space complexity](https://leetcode.com/problems/find-the-duplicate-number/)
**Problem:** Given an array of integers nums containing n + 1 integers where each integer is in the range [1, n] inclusive.  
There is only one repeated number in nums, return this repeated number.  
You must solve the problem without modifying the array nums and uses only constant extra space.  
**Main Idea:**  
1. It is quite clear that for linear time we need to use binary search.
2. Idea is find the mid of values i.e (1+n)/2 , now count numbers in whole array which are <= mid. (This will show if before mid exists duplicate causing mid+1 numbers)
3. if count<=mid then we need to search between mid+1 and high
4. If count>mid then we need to search between low and mid-1
5. return low  
O(nlogn)

```
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
       /*
       Trick: Binary Search
       */
        int i=1, j = nums.size()-1;
        int mid; 
        int count=0;
        while(i<=j){
            mid = i + (j-i)/2;
            count=0;
            for(int &a:nums){
                if(a<=mid){
                    count++;
                }
            }
                if(count<=mid){
                    i = mid+1;
                }
                else{
                    j=mid-1;
                }
            }
        
        return i;
    }
};
```

---

#### [6. Merge two sorted arrays without extra space in O((n+m)log(n+m) time](https://practice.geeksforgeeks.org/problems/merge-two-sorted-arrays5135/1#)   

![mwes](https://github.com/bathejaakshay/Competitive-Problems-in-C-/blob/master/Images/mwes.png?raw=True)   
**Main Idea:**  
1. In both arr1 and arr2 we traverse from left to right.
2. We find the first element in arr1 which is greater than first element arr2.
3. When we find such element we swap the smaller element in arr2[] with last pos in arr1. (This is because we know one element has to be inserted in arr1 so atleast the greatest of this array arr1 has to leave). we increase pointer in arr2
4. Now we find first element in arr2 which is greater than the second element in arr2.
5. & so on..
6. finally after obtain both arrays we sort them.

```
class Solution{
public:
    
    void merge(int arr1[], int arr2[], int n, int m) {
	    // code here
	    int i=0,j=0,k=n-1;
	    
	    while(i<=k && j<=m-1){
	        if(arr1[i]<=arr2[j]){
	            i++;
	        }
	        else{
	            swap(arr1[k],arr2[j]);
	            k--;
	            j++;
	        }
	    }
	    sort(arr1, arr1+n);
	    sort(arr2, arr2+m);
	}
};
```

---

#### [7. Counting Inversions in an array in O(nlongn) time](https://practice.geeksforgeeks.org/problems/inversion-of-array-1587115620/1#)
**Main Idea**  
1. Modify merge sort in a way that you count all inversion pairs while merging.

```
  long long int merge(vector<long long int> &arr, int left, int right, int mid){
      long long int subleft = mid-left+1;
      long long int subright = right-mid;
      
    //   int arr1[subleft], arr2[subright];
    long long *arr1 = new long long int[subleft], *arr2= new long long int[subright];
    
      for(long long int i=0; i<subleft;i++) arr1[i] = arr[left+i];
      for(long long int i=0; i<subright;i++) arr2[i] = arr[mid + 1 + i];
      
      long long int l=0, h=0,i=left;
      long long int ans=0;
      while(l<subleft && h<subright){
          if(arr1[l] <= arr2[h]) {
              arr[i] = arr1[l];
              l++;
          }
          else{
              arr[i] = arr2[h];
            //   cout<<((subright-h))<<endl;
            //   ans += ((subright-h)*(subleft-l));
              ans+=(subleft-l);
              h++;
              
          }
          i++;
      }
      while(l<subleft) {
          arr[i] = arr1[l];
          l++;i++;
          
      }
      while(h<subright){
          arr[i] = arr2[h];
          h++;i++;
      }
      return ans;
      
  }
 long long int mergeSort(vector<long long int> &arr, int low, int high){
      if(low>=high) return 0;
      int mid = (low+high)/2;
      long long int ans=0;
      ans+=mergeSort(arr, low, mid);
      ans+=mergeSort(arr, mid+1, high);
      ans+= merge(arr, low, high, mid);
      return ans;
      
  }
```

---

#### [8. Subarray with sum 0 in O(N) space and time](https://practice.geeksforgeeks.org/problems/subarray-with-0-sum-1587115621/1)

**Main idea:**  
1. In a single loop maintain a sum , if sum==0 return true  
2. else if sum is present in the hash then return true :( This means if this sum has been seen in previous subarrays then simply substracting them will give ans without actually substracting them. e.d 4 2 -3 1 6 .. at index = 3 sum = 4 now 4 exists in hash representing there exist a prior subarray with sum 4 which can be removed to simply turn the sum to zero.)  
3. else insert sum in hash  

```
bool subArrayExists(int arr[], int n)
    {
    	unordered_set<int> s;
        int sum=0;
        for(int i=0;i<n;i++){
            sum+=(arr[i]);
            if(sum==0) return true;
            if(s.find(sum)!=s.end()) return true;
            else s.insert(sum);
        }
        return false;
    }
```

---

#### [9. Minimum jumps to reach end of the array](https://practice.geeksforgeeks.org/problems/minimum-number-of-jumps-1587115620/1#)
**Main Idea:**  
Two solutions exists: greedy and DP. DP takes O(n) time and O(n) space while greedy takes O(n) time and O(1) space
But greedy is not intuitive and a little smart approach:

```
int minJumps(int arr[], int n){
        // Your code here
     int mx=0,halt=0,jump=0;
       if(n==1 and arr[0]==0)
       return 0;
       if(arr[0]==0)
       return -1;
       for(int i=0;i<n-1;i++)
       {
           mx=max(mx,i+arr[i]); \\ we find maximum reach till now 
           if(mx>=n-1)          \\ If curr max reach reaches end then increment jump and return
           {
               jump++;
               return jump;
           }
           if(i==halt)         \\we put max reach in halt and increment jump i.e jump is the min jump to reach i now we need to find same till new reach
           {
               halt=mx;
               jump++;
           }
       }
       if(halt>=n-1)
       return jump;
       else 
       return -1;
    }
```

---

#### [10. Rotating an NXN matrix](https://leetcode.com/problems/rotate-image/submissions/)
**Main Idea:**  
1. Reverse the matrix
2. Swap ij to ji for each row i starting with zero and j starting with i;

![first](https://github.com/bathejaakshay/Competitive-Problems-in-C-/blob/master/Images/first.png?raw=true)

![second](https://github.com/bathejaakshay/Competitive-Problems-in-C-/blob/master/Images/second.png?raw=true)
