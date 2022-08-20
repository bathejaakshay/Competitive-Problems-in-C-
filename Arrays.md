#### [1. a Trapping Rain Water - **HARD**](https://leetcode.com/problems/trapping-rain-water/)
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

#### [1.b Largest rectangle in the histogram](https://leetcode.com/problems/largest-rectangle-in-histogram/)

The logic is that we need to think of each element just like in Rain water trap question.  
We will think of what is the logic for the right and left boundary for the current element to be included in the area.  
**Approaches : Brute Force**
1. for each index we find the element smaller to itself in the left and the right.
2. Now the element right after and before these left_min and right_min will create the boundary for my current rectangle.
3. The area would be (right_boundary - left_boundary + 1)*height_of_current_element.
 `TC: O(n^2)`
 
 
**Approaches:**
1. To precompute the left_min and right_min array for each element.
2. We use stack for the same. We only keep indices of increasing elements in the stack, otherwise we pop them

`TC: O(N) + O(N)`

```
int largestRectangleArea(vector<int>& heights) {
        int n=heights.size();
        stack<int> st;
        vector<int> left(n);
        vector<int> right(n);
        left[0] = 0;
        st.push(0);
        for(int i=1; i<n; i++){
            while(!st.empty() && heights[st.top()]>=heights[i]) st.pop();
            if(st.empty()){
                left[i] = 0;
                
            }
            else{
                left[i] = st.top()+1;
            }
            st.push(i);      
        }
        while(!st.empty()) st.pop();
        right[n-1] = n-1;
        st.push(n-1);
        for(int i = n-2; i>=0; i--){
            while(!st.empty() && heights[st.top()] >= heights[i]) st.pop();
            if(st.empty()){
                right[i] = n-1;
            }
            else{
                right[i] = st.top()-1;
            }
            st.push(i);
            
        }
        int ans=0;
        for(int i=0; i<n; i++){
            ans = max(ans, (right[i] - left[i]+1)*heights[i]);
        }
        return ans;
    }
```

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

#### [4. Four Sum](https://practice.geeksforgeeks.org/problems/find-all-four-sum-numbers1732/1#)

**Problem** 
Given an array of integers and another number. Find all the unique quadruple from the given array that sums up to the given number. TC shouldnt be more than O(n3)

**Approach 1 using 2 pointers**
1. Sort the vector
2. for each distinct pair (means no repetition for i and no repetition for j)(our final quadruple will always be {i,j,k,l} so make sure no repetitions  at first two locations)
3. Now find another two numbers between j+1 and n whose sum with i and j is target and append it to ans. 
4. This is done using two pointer approach we also make sure once we find such k and l then next k and l should be distinct.
5. two pointer approach: while(k<l) if(sum==target){} else if (sum>target) l-- else k++

```
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& a, int target) {
        vector<vector<int>> ans;
        sort(a.begin(),a.end());
        int sum;
        for(int i=0;i<a.size()-1;i++){
            if(i!=0&& a[i]==a[i-1]) continue; \\ To ensure no repetition for first element of quadruple
            
            for(int j=i+1;j<a.size();j++){
                if(j!=i+1 && a[j]==a[j-1]) continue; \\ To ensure no repetition for second element of quadruple
                sum = a[i]+a[j];
                int k = j+1;
                int l = a.size()-1;
                
                while(k<l){
                    
                    if(1LL+ a[k]+a[l] + sum -1LL == target){
                        ans.push_back({a[i],a[j],a[k],a[l]});  
                        while(k<a.size()-1 && a[k] == a[k+1]) k++;  \\ To ensure no repetition for third element of quadruple
                        while(l>j && a[l] == a[l-1]) l--;        \\ To ensure no repetition for fourth element of quadruple
                        k++;
                        l--;
                    }
                    else if(1LL + a[k] + a[l] +sum - 1LL> target) l--;
                    else k++;
                    
                }
                
            }
        }        
       return ans;
    }
};
```
**Approach 2 Less efficient Approach using hashmap**
1. We will use a hashmap `mp` with key k as sum and value as vector of pairs which has sum = k.
2. Now for each pair we will see if k-sum of curr pair exist in `mp`. If yes then check for all the pairs corresponding to key k-sum. 
3. 	The quadruple should have distinct indices otherwise it will mean a value from the same index is repeating. Add this quadruple into ans after sorting.
4. 	push curr pair as value to key sum of hashmap
5. Now After we have traversed all the pairs we have obtained the ans but it is not unique. So we create a set of vectors from the ans
6. Then again we convert this set to vector of vectors and return it as ans.

TC: For each pair we go through candidate pairs of quadruples: O(n3)

```
class Solution{
    public:
    // arr[] : int input array of integers
    // k : the quadruple sum required
    vector<vector<int> > fourSum(vector<int> &a, int k) {
        // Your code goes here
        unordered_map<int,vector<pair<int,int>>> mp;
        vector<vector<int>> ans;
        for(int i=0;i<a.size();i++){
            for(int j=i+1;j<a.size();j++){
                if(mp.find(k-a[i]-a[j])!=mp.end()){
                    vector<pair<int,int>> q = mp[k-a[i]-a[j]];
                    for(int x=0;x<q.size();x++){
                        if(i!=q[x].first&& i!=q[x].second && j!=q[x].first && j!=q[x].second){
                            vector<int> pr = {a[i],a[j],a[q[x].first],a[q[x].second]};
                            sort(pr.begin(),pr.end());
                                ans.push_back(pr);
                        }
                    }
                }
                
                mp[(a[i]+a[j])].push_back(make_pair(i,j));
            }
        }
        set<vector<int>> st;
        for(int i=0; i<ans.size();i++){
            st.insert(ans[i]);
        }
        ans = vector<vector<int>>(st.begin(),st.end());
        return ans;
    }
};

```

---

#### [5. Next Permutation](https://leetcode.com/problems/next-permutation/)
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

#### [6.Binary Search in Rotated Sorted Array](https://leetcode.com/problems/search-in-rotated-sorted-array/)
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

#### [7. Finding the Duplicate number in linear (nlogn) time with O(1) space complexity](https://leetcode.com/problems/find-the-duplicate-number/)
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

#### [8. Merge two sorted arrays without extra space in O((n+m)log(n+m) time](https://practice.geeksforgeeks.org/problems/merge-two-sorted-arrays5135/1#)   

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

#### [9 (i). Counting Inversions in an array in O(nlongn) time](https://practice.geeksforgeeks.org/problems/inversion-of-array-1587115620/1#)
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

#### [9.(ii) Count Reverse pairs with extra condition](https://leetcode.com/problems/reverse-pairs/submissions/)
A pair is called reverse is `i < j` and `a[i] >  2* a[j]`

**Approach**  
1. We use the same merge sort method with a modification that in merge operation. We first count the inversion pairs in o(m+n) time and then run extra loop for actual merging in O(n)

`TC: O((n)log(n))`

```
int merge(vector<int> &nums, int i, int mid, int j){
    int first_size = mid-i+1;
    int second_size = j - mid;
    int ans=0;
    vector<int> first(first_size, 0);
    vector<int> second(second_size, 0);
    for(int x = 0; x<first_size; x++){
        first[x] = nums[i+x];
    }
    for(int x = 0; x<second_size; x++){
        second[x] = nums[mid+x+1];
    }
    // We divide the merging and counting inversion pairs into two separate tasks
    int a=0,b=0;
    while(a<first_size && b<second_size){
        long long cond = (long long)2*(long long)second[b];
        
        if(first[a] <= cond){
            a++; // if first[a] is <= 2*second[b] then first [a] will also be lesser than 2* all second[m], where m>=b
            
        }
        else{
            ans+=(first_size - a);
            b++;
        }
    }
    
    int x=0,y=0;
    int k=i;
    
    
    while(x<first_size && y<second_size){
        if(first[x] <= second[y]){
            nums[k] = first[x];
            x++;
            k++;
        }
        else{
            nums[k] = second[y];
            y++;
            k++;
        }
    }
    while(x<first_size){
        nums[k] = first[x];
        x++;
        k++;
    }
    while(y<second_size){
        nums[k] = second[y];
        k++;
        y++;
    }
    return ans;
    
}
```

---

#### [10.1a Subarray with sum 0 in O(N) space and time](https://practice.geeksforgeeks.org/problems/subarray-with-0-sum-1587115621/1)
**Prefix Sum property is used IMP** 
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
####[10. 1b Longest Subarray with sum 0](https://practice.geeksforgeeks.org/problems/largest-subarray-with-0-sum/1)
**Approach**
1. We use unordered_map to keep record of the prefix sum and its min index
2. initially, `mp[0]=-1`, This is because intially without array the sum was 0. This helps in case when sum of 0 to ith element is 0, otherwise it wont consider this case.
3. Then we maintain sum for each element in the array and search if `sum-0` has already appeared before i.e does it exist in the hashmap, if yes then we calculate the length of current subarray with sum 0 and update our ans.
4. else we set `mp[sum] = current index`
---

#### [10.2 No of subarrays with sum K](https://leetcode.com/problems/subarray-sum-equals-k/)
**Approach: Naive : O(n^2)**
**Appriach : Prefix sum : O(n)**
1. The crux of prefix sum concept is that for each index i we store the sum from index 0 till i.
2. Now To find if there exists a subarray whose sum is k. Then for each index i we have current sum `si`  we check if `si-k` exists in the prefix sum unordered map.
3. The simple concept behind this is that if this sum `si-k` exists say for jth index i.e `a[0]+a[i] .... a[j]` is `si-k` and we also know that `a[0] + a[1] + .. a[i]` is `si`, hence subtracting both gives : `a[j+1] + a[j+2] + .. a[i] = si-si + k = k` hence subarray i+1 till j has sum k.
4. Now for this particular question we mantain a frequency map of prefix sums.
5. so `mp[si-k]` will give us the number of subarrays ending at i which sums up to k.

```
int subarraySum(vector<int>& nums, int k) {
       
       unordered_map<int,int> mp;
       int sum=0;
        int count=0;
        mp[sum]=1;
        for(int i=0; i<nums.size(); i++){
            sum+=(nums[i]);
            if(mp.find(sum-k)!=mp.end()) {
                count+=(mp[sum-k]);
            }
            mp[sum]++;
        }
        return count;
    }
```

---
#### [10.3 No of subarrays whose sum is divisible by k](https://leetcode.com/problems/subarray-sums-divisible-by-k/submissions/)
**Approach**:
1. Key idea is that given sum `si` from `ind 0 to i` and sum `sj` from `ind 0 to j`.
2. If `si%k == sj%k` then the sum of subarray i to j is divisble by k
3. Proof: `si = kn1 + x`, `sj = kn2 + x`, then `sj-si = k(n2-n1)`, hence sum `sj-si` is divisible by k.
4. Now we use the PrefixSum using unordered_map mp key, val
5. `key` represents the `(subarraysum%k)` and `val` represents its current frequency.
6. Now we iterate over the array and find if the current subarraysum%k exists in the map, if it does then how many. We simply increment our ans by that frequency
7. Finally we increment frequency of current remainder in the map for future.
8. For negative remainders we do the same process by updating the current remainder as : k + negative_remainder. (This is because 7n - 5 and 7n' + 2 is equivalent where 7 is the k and n' = n-1)  


```
int subarraysDivByK(vector<int>& nums, int k) {
        int ans=0;
        int sum=0;
        unordered_map<int,int> mp;
        mp[0]=1; 
        for(int i=0; i<nums.size(); i++){
            sum+=(nums[i]);
            int rem =sum%k;
            if(rem < 0){
                rem = k + rem;
            }
            if(mp.find(rem)!=mp.end()){
                ans+=(mp[rem]);
            }
            mp[rem]++;
        }
        return ans;
    }
```
---

####[10.4 Minimum size subarray with sum atleast K](https://leetcode.com/problems/minimum-size-subarray-sum/)
Given an array of size N with all positive values and a value K, find a minimum length subarray whose sum is atleast K.
**Approach : Brute Force : O(n^2)** : Go over all possible subarrays and check sum
**Approach : Sliding Window with Two pointer O(n)** (This approach is only possible when the array doesnt consist negative numbers and the accumulative relation is monotonic)
1. In this approach we create two pointers at the starting and start maintaining sum using the j pointer.
2. We keep on moving j in the right direction until sum becomes >= target.
3. Once it does we know that j-i+1 is the size of subarray with sum atleast target. But is it the shortest?
4. So we start shrinking this subarray by moving i pointer to the right direction.
5. We keep on shrinking the subarray till the sum is still >= target. Once it fails we update our `ans = min(ans, j-i+2)` (+1 extra because we come one point ahead after completing the loop)


```
 int minSubArrayLen(int target, vector<int>& nums) {
        int ans = INT_MAX;
        
        int i = 0, j = 0;
        int sum = 0;
        
        while(i<nums.size() && j<nums.size()){
            sum+=(nums[j]);
            
            if(sum>=target){
                while(i<nums.size() && sum >= target){
                  sum-=nums[i];
                  i++;
                } 
                // i--;
                // sum+=(nums[i]);
                ans = min(ans, j-i+2);
                
            }
            j++;
        }
        if(ans == INT_MAX) return 0;
        return ans;
    }
```
---
####[10.5 Shortest Subarray with Sum at Least K HARD](https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/)
Same as previous ques but this time the array can consist negative elements so we can use the 2 pointer approach
**Approach: Deque**
1. We use the same fundamentals for expanding and shrinking. We just need to maintain a deque of monotonically increasing sums.
2. We create a deque of `pair<int,int>`. 
3. for each index we add it to sum and check if this sum>=K if yes then check the ans = min(ans, i+1)
4. Then we check if popping the initial elements of deque increases the sum to match >=k. We keep on doing this till its valid. This is shrinking and allows us get the smaller size subarray with sum atleast K. We are doing this at each step no matter if total sum was >=k because if the intial elements were negative then it can increase the current sum by popping them out of the subarray. (We use prefix sum property).
5. Then we again calculate the updated ans. 
6. Then finally at the time of inserting the sum we check if the element at rear of deque has sum keyword < current sum, if not we pop_back. (This is to maintain monotonic dequeue)
7. finally we insert {sum,i} to the deque.

```
#include<bits/stdc++.h>
class Solution {
public:
    int shortestSubarray(vector<int>& nums, int k) {
        deque<pair<long long,int>> dq;
        
        long long sum=0;
        int ans=INT_MAX;
        
        for(int i=0; i<nums.size(); i++){
            // Think it as a form of prefix array
            sum +=(nums[i]);
            if(sum >= k){
                ans = min(ans, i+1);
            }
             pair<long long, int> curr = {INT_MIN, INT_MIN};
               // using prefix sum property to find if the subarray sum >=k
                while(!dq.empty() && sum-dq.front().first>=k){
                    curr = dq.front();
                    dq.pop_front();
                    
                }
            if(curr.second!=INT_MIN)
                ans = min(ans, i-curr.second);
            while(!dq.empty() && sum < dq.back().first){
                dq.pop_back();
            }
            dq.push_back(make_pair(sum, i));
        }
        
        return ans==INT_MAX?-1:ans;
    
    }
};
```
---
#### [10.6 (Trick Prefix) Count Number of Bad Pairs](https://leetcode.com/contest/biweekly-contest-84/problems/count-number-of-bad-pairs/)
You are given a 0-indexed integer array nums. A pair of indices `(i, j)` is a `bad pair` if `i < j` and `j - i != nums[j] - nums[i]`.   

Return the total number of bad pairs in nums  


**Approach : Using prefix property unordered map**
1. Try playing with the equations.
2. Bad pairs = Total pairs - Good Pairs
3. Good pairs are ones where `i<j` and `j-i == nums[j] - nums[i]`.
4. Now using prefix this equation is not possible to handle and is not intuitive. So lets modify the equation
5. We can change the equation to good pair are ones where `i<j` and `nums[j] - j == nums[i] - i`.
6. Now this is intuitive and simple to calculate.
7. Starting from index i = 0, we count number of indices k < i where `nums[i] - i == nums[k] - k` by using unordered_map.
8. Increment` mp[nums[i]-i]` by 1 at each iteration.
9. Finally we substract this count from total pairs `(n*(n-1))/2` to get final bad pairs.

```
long long countBadPairs(vector<int>& nums) {
        unordered_map<long long, long long> mp;
        
        long long tot = ((long long )nums.size() * (long long) (nums.size()-1))>>1;
        
        long long valid=0;
        for(int i=0; i<nums.size(); i++){
            if(mp.find(nums[i] - i)!=mp.end()){
                valid+=(mp[nums[i]-i]);
                
            }
            mp[nums[i]-i]++;
        }
        
        return tot - valid;
    }
```
---

####[11. Minimum jumps to reach end of the array](https://practice.geeksforgeeks.org/problems/minimum-number-of-jumps-1587115620/1#)
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

#### [12. Rotating an NXN matrix](https://leetcode.com/problems/rotate-image/submissions/)
**Main Idea:**  
1. Reverse the matrix
2. Swap ij to ji for each row i starting with zero and j starting with i;

![first](https://github.com/bathejaakshay/Competitive-Problems-in-C-/blob/master/Images/first.png?raw=true)

![second](https://github.com/bathejaakshay/Competitive-Problems-in-C-/blob/master/Images/second.png?raw=true)


#### [13. Spiral Matrix](https://practice.geeksforgeeks.org/problems/spirally-traversing-a-matrix-1587115621/1)
**Main Idea:**  
1. Traverse the 2D matrix in spiral form

```
vector<int> spirallyTraverse(vector<vector<int> > matrix, int r, int c) 
    {
        // code here 
        int rows;
        if(r%2==0) rows =  r/2; 
        else rows = r/2+1; //If rows are odd then we need to traverse one extra row 
        vector<int> ans;
        for(int i=0;i<rows;i++){
            //left to right
            for(int j=i; j<c-i;j++){
                if(ans.size() == r*c) return ans;
                ans.push_back(matrix[i][j]);
                    
            }
            // up to down
            for(int j=i+1;j<r-i;j++){
                if(ans.size() == r*c) return ans;
                ans.push_back(matrix[j][c-i-1]);
            }
            // right to left
            for(int j=c-i-2 ; j>=i;j--){
                if(ans.size() == r*c) return ans;
                ans.push_back(matrix[r-i-1][j]);
            }
            // down to up
            for(int j=r-i-2; j>=i+1;j--){
                // cout<<"i,j = "<<i<<","<<j<<endl;
                if(ans.size() == r*c) return ans;
                ans.push_back(matrix[j][i]);
            }
            
        }
            
        return ans;
    }
```

---

#### [14 Number of Subsequences That Satisfy the Given Sum Condition](https://leetcode.com/problems/number-of-subsequences-that-satisfy-the-given-sum-condition/)
Constraints are very tight so we will learn new tech to compute pow.
**Approach**
1. Sort array
2. Apply 2 sum to find for each num x in array , the largest corresponding y in array st x+y<=target.
3. now we can compute for each such pairs the number of subsequences: from ind(x)+1 till ind(y) we have 2^(y-x) subseq.
4. We precompute the power values as the constraint is too tight.

```
class Solution {
public:
    int numSubseq(vector<int>& nums, int target) {
     // Apply 2 sum first st for each element a[i] we find max a[j] such that a[i] + a[j]<=target
    
        sort(nums.begin(), nums.end());
        // vector<pair<int,int>> v;
        int i=0, j=nums.size()-1;
        int res=0;
        vector<int> pow(nums.size());
        pow[0]=1;
        for(int i=1; i<nums.size(); i++){
            pow[i] = (pow[i-1]*2)%1000000007;
        }
        while(i<=j){
            if(nums[i] + nums[j]<=target){
                
                res = (res + pow[j-i])%1000000007;
                i++;
            }
            else{
                j--;
            }
        }
        
        
        return res;
    }
};
```
---

#### 15. Find an element in row wise and column wise sorted matrix  
**Approach : O(n)**
1. Start from the top right element and compare the element to the item.
2. If the element is equal then return 
3. if element is greater than item then that means all other elements in that column is greater than that element hence we drop the column by doing `j--`.
4. If the element is lesser than item then that means all the other elements in that row is smaller to that item hence we drop that row by doing `i++`.

```
pair<int,int> search(vector<vector<int>> &mat, int item){
	int i=0, j=mat[0].size()-1;
	while(i<mat.size() && j>=0){
		if(mat[i][j] == item){
			return make_pair(i,j);

		}
		if(mat[i][j] >  item){
			j--; // eliminate column
		}
		else{
			i++;
		}
	}

	return make_pair(-1,-1); 
}

```
---
#### [16. Kth permutation sequence - HARD](https://leetcode.com/problems/permutation-sequence/)  
Given N numbers `[1..N]` find the k th permutation  
**Approach**
1. Create a vector of 1 to N and simultaneously cal (n-1)!
2. We firstly find the first number in the kth permutation (following 0 based indexing if k=4 then we find k=3 i.e k-1), `k/(n-1)!`, this gives us the index of the first number in the array. 
3. We also remove the selected element of vector. i.e erase(k/(n-1)!)
3. Then we find the required k in the subgroup selected i.e k = k%(n-1)!
4. Now we find the second element in the similar way.. till the vector is not empty

`TC : O(n^2)`

```
class Solution {
public:
    string getPermutation(int n, int k) {
        vector<int> num;
        int fact=1;
        int i;
        for(i=1;i<n;i++){
            fact*=i;
            // The only trick is to maintain the array
            num.push_back(i);
        }
        num.push_back(i);
        k = k-1;  // To set 0th index : 3rd permutation is at 2nd ind
        string ans="";
        i--;
        while(true){
                
            ans+=to_string(num[k/fact]); 
            
            /* we find the first element by diving the sequences into the groups e.g for n=3
           
           1 2 3   (two permutations start with 1)
           1 3 2    
           
           2 1 3   (two permutations start with 2)
           2 3 1
           
(2! in each group)

           3 1 2    (two permutations start with 3)
           3 2 1
           
         We now find in which group does kth permutation belong say k=3.
         so 3rd permutation will have index=2 in this list.
         so 2/2 = 1 so it must lie in 1th group i.e 213 or 231.
         we are sure that it starts with 2. and now we need to find k%2 i.e 2%2 = 0th indexed permutation in the group starting with 2.
         
         Now do the same thing for
         1 3 (1 permutation start with 1)

(1! in each group)

         3 1 (1 permutation start with 3)
         
         so we divide  0/1 = 0
         so it is the 0%1 = 0th permutation in 1st group i.e 1 3
         so second number is 1 for sure.
         
         now we remain with
         3  (1 permutation start with 3)
         so 0/1 = 0
         so it is the 0%1 = 0 th permutation in the 1st group i.e 3
         so third number is 3.
         Now the list is empty hence the ans is "213". 3rd permutation in 3!. 
         
        */
            cout<<"ans= "<<ans<<" fact = "<<fact<<" k/fact = "<<(k/fact)<<" k%fact = "<<(k%fact)<<endl; 
            num.erase(num.begin() + k/fact);
            if(num.empty()) break;
            k=k%fact;
            fact/=i;
            i--;
        }
        
        return ans;
    }
};
```

---

#### [17. Maximum points to obtain from the cards](https://leetcode.com/problems/maximum-points-you-can-obtain-from-cards/)
In an operation we can either take pop and take first element or the right element and add it to our ans;
Given an array do k such operations such that we have maximum ans. 

**Approach: Sliding window approach**:
1. Precompte the total lsum till k from left;
2. Now for each from right till n-k we maintain rsum and obtain lsum for the corresponding window and update our ans.
```
public int maxScore(int[] cardPoints, int k) {
        int n = cardPoints.length, lSum = 0;
        for(int i = 0; i < k; ++i){
            lSum += cardPoints[i];
        }
        int max = lSum;
        for(int rSum = 0, i = 0; i < k; ++i){
            rSum += cardPoints[n-1-i];
            lSum -= cardPoints[k-1-i];
            max = Math.max(max,lSum+rSum);
        }
        return max;
    }
```

---
## Beautiful Tricky Concepts

### [1. Shifting Letters II](https://leetcode.com/contest/biweekly-contest-85/problems/shifting-letters-ii/)
`Variation of Prefix Sum`  

Q. ou are given a string s of lowercase English letters and a 2D integer array shifts where `shifts[i] = [start_i, end_i, direction_i]`. For every i, shift the characters in s from the index starti to the index endi (inclusive) forward if directioni = 1, or shift the characters backward if `direction_i = 0`.  

Shifting a character forward means replacing it with the next letter in the alphabet (wrapping around so that 'z' becomes 'a'). Similarly, shifting a character backward means replacing it with the previous letter in the alphabet (wrapping around so that 'a' becomes 'z').

Return the final string after all such shifts to s are applied.


**Approach : Brute Force**  
1. For each shift operation perform the operation from start_i to end_i 
2. Takes `O(N*K)` where k is the size of shift array. But it will give TLE
3. Now We cannot compromise on K as we have to Traverse K but we have to reduce the shifting operation from start_i till end_i. Hence Follow the next approach

![wes](https://github.com/bathejaakshay/Competitive-Problems-in-C-/blob/master/Images/shifting%20letters%202.png?raw=True)

**Approach : Prefix sum**
1. Given start and end index for the shifting how can you do it in O(1)
2. Ans is by accumulating all the required operations on a particular index and performing the update only once 
3. For e.g as in the above fig. if we want to increment all the chars by 1 from index 3 to index 6, there are two ways
4. Either we mark all the elements from 3 to 6 as 1 and finally while traversing for each index we will have the offset or final increment or decrement value. 
5. But to mark all the elements we would have to traverse all elements between 3 and 6 so it will take O(N) time and TC remains O(N\*K)
6. Another efficient way is to mark only the beginning index i.e 3 by +1 (because we need increment from index 3 onwards) and ending + 1 (because we dont want this increment from index 7 onwards) index i.e 7 by -1. 
7. So instead of marking all the indices we just mark the start and end+1 to keep record for future.
8. Now while computing offset value for index i in string s we will keep a prefix sum till i which will represent its offset value.
9. Now the algo is simple:
	- Initialize an array `arr` of the size of String A + 1.
	- Now for each query in shift array, increment the `arr[start_ind]` and decrement `arr[end_ind+1]` if `shift[2] = 1` else decrement the `arr[start_ind]` and increment ` arr[end_ind+1]`.
	- Initialize count=0
	- Now for each idx i in string A 
	- do `count+=arr[i]` //Prefix sum till i
	- if count is negative then we need to bring it to positive by adding 26 till it becomes positive
	- e.g if count = -5 and char at i is a representing 0 so if we move `5 backward` or `(26-5 = 21 forward) = ` we will get the same char.
	- while(count<0) count+=26 (its like taking a mod for the negative numbers and bringing them to positive, same cycle concept add the total cycle size and it will end up at the same location)
	- Now we add this count to our char at i and take mod 26 to obtain final char at i
	- `s[i] = 'a' + (s[i] -'a'+ count)%26`

`TC : O(N+K)`
```
string shiftingLetters(string s, vector<vector<int>>& shifts) {
        vector<int> dp(s.length()+1,0);
        for(auto vec: shifts){
            int x = vec[2]==0?-1:1;
            dp[vec[0]] +=(x);
            dp[vec[1]+1] -=(x); 
       }
        
        int count=0;
       for(int i=0; i<s.length(); i++){
           
           count+=dp[i];
            
           while(count<0) count+=26;
           
           s[i] = 'a' + (s[i] -'a'+ count)%26;
       }   
        return s;
    }
```

---
#### [18. Maximum Triplet Sum](https://www.interviewbit.com/old/problems/maximum-sum-triplet/)  
We need to find a triplet ai, aj ,ak such that ai<aj<ak and i<j<k and their sum is max   
								  
**Approach-Brute Force**  
								  
1. 3 For loops

`TC: O(n^3)`

**Approach-LIS**  
								  
1. We find Increasing seq of size 3 with max sum using DP
`TC : O(n^2)`

**Approach-Non intuitive**  
1. We consider each element to be the middle element of the triplet and try to find the just smaller and the greatest element to the left and right side of it respectively.
2. For each element if we iteratively look at left and right elements of it then it will give us O(n^2) sol
								  
**Approach-Sorting and Binary Search**  
1. This is a little non ituitive approach.
2. We precompute the max suffix array namely `right`.
3. Each element `right[i]` denotes the max element in arr `A` to the right of i i.e i+1 till end.
4. Now we create a set `s`, we keep on inserting each element in A[i] if `right[i]!=0` (meaning it has element greater than itself).
5. Right after insert we binary searh the element just smaller than A[i] in s and compute max sum : A[i] + element smaller than A[i] + right[i]

`TC: O(nlogn)`
								  
```
int Solution::solve(vector<int> &A) {

int n = A.size();
vector<int> right(n, 0);
for(int i=A.size()-2; i>=0; i--){
    int mx = max(right[i+1], A[i+1]);
    if(mx > A[i]) right[i] = mx; // This is important we cant have right[i] = A[i] as we need exactly one element after A[i] which is greater than A[i].
}

set<int> s;
int maxi  = 0;
s.insert(A[0]);
for(int i=1; i<A.size()-1; i++){
    s.insert(A[i]);
    if(right[i]!=0){
        auto itr = s.find(A[i]);
        if(itr!=s.begin()){
            maxi = max(maxi , A[i] + (*(--itr)) + right[i]);
        }
    }
}

return maxi;
}
			 
```
