#### [1. Frequency of the Most Frequent Element](https://leetcode.com/problems/frequency-of-the-most-frequent-element/)
The frequency of an element is the number of times it occurs in an array.  

You are given an integer array nums and an integer k. In one operation, you can choose an index of nums and increment the element at that index by 1.  

Return the maximum possible frequency of an element after performing at most k operations.  

 
```
Example 1:

Input: nums = [1,2,4], k = 5
Output: 3
Explanation: Increment the first element three times and the second element two times to make nums = [4,4,4].
4 has a frequency of 3.
```

**Approach: Sliding Window**
1.  Sort the array
2.  We maintain a window w of elements which gives us the frequency of the max element in that window.
3.  We maintain simple `sum` of the current window and check if adding the next element `j+1` in this window is possible by checking `sum + k >= (i-j+1)*nums[j+1]` 
4.  i.e `currsum + k >= curr_windsize*new_max_frequent_element`
5.  To keep things simple we always maintain sum, or (in case of bits manipulation) of the window to keep essence of each element and to remove esssence of elements at head we do `sum-=num[i]` or `sum^num[i]`     
6.  So if the condition mentioned in point 3 doesnot satisfy then we compress the window till it satisfy by doing `sum-=nums[i++]`
7.  After that if the condition satisfy then we update our ans `res = max(res, j-i+1 + 1)` we added 1 to the current window because we are checking if we can accomodate next element in the current window

```
    int maxFrequency(vector<int>& nums, int k) {
      int i=0;
      int curr_k=k;
      int res=1;
      sort(nums.begin(), nums.end());
        long long sum=0;
      for(int j=0; j<nums.size()-1; j++){
          sum+=(long long)nums[j];
          while(i<j && sum + k  < (long long)nums[j+1]* (long long)(j-i+1)){
              sum-=nums[i];
              i++;
          }
          if((long long)nums[j+1]*(j-i+1) <= ((long long)curr_k + sum)){
            res = max(res, j-i+2);  
          }
          else{
              sum=0; 
              i++;
          }
          
         
      }
        
        return res;
    }

```

---

#### [2. Longest Nice Subarray](https://leetcode.com/contest/weekly-contest-309/problems/longest-nice-subarray/)

You are given an array nums consisting of positive integers.  

We call a subarray of nums nice if the bitwise AND of every pair of elements that are in different positions in the subarray is equal to 0.  

Return the length of the longest nice subarray.  

A subarray is a contiguous part of an array.  

Note that subarrays of length 1 are always considered nice.  

 
```
Example 1:

Input: nums = [1,3,8,48,10]
Output: 3
Explanation: The longest nice subarray is [3,8,48]. This subarray satisfies the conditions:
- 3 AND 8 = 0.
- 3 AND 48 = 0.
- 8 AND 48 = 0.
It can be proven that no longer nice subarray can be obtained, so we return 3.
```

**Approach : Sliding Window O(N)**  
1. Things to remember: longest subarray say x1, x2, x3 has pairwise `&` equal to zero if `x1&x2&x3 = 0` simply, do not complicate.
2. maintain a window from i to j which is currently nice. Now how do we maintain the windows bits?. By using `wind |= nums[j]` i.e collecting all the bits of all the nums in the window.( Just for future me Remember 6|6 is 6 and not 12, sum is different than bitwise or :P)
3. Also we are not using xor to collect bits of wind because 1 ^ 1 is 0 and it wont collect all the ones as we want that the next nice number should have 0 at that bit.
4. Now once we encounter an new element which doent make the window nice anymore that is `wind | new num != 0` then we compress the window till we do not get the nice window with new element  i.e `wind | new num == 0`. How do we compress?
5. This is something to remember the most. In the collection `wind (|) ` of bits of all nums in the window we remove the contribution of head elements (i.e elements at index i) of the window by exoring them i.e `wind^=nums[i]`. The concept is `(A | B ^ A) = B`. **Remember this**

```
class Solution {
public:
    int longestNiceSubarray(vector<int>& nums) {

        int wind=nums[0];
        int res=1;
        int i=0;
        for(int j=1; j<nums.size(); j++){
                while(i<j && ( (wind & nums[j]) != 0)){
                    wind^=nums[i];
                    i++;
                }
            
                wind|=nums[j];
            res = max(res, j-i+1 );
        }
        return res;
    
    }
};
```

---

#### [3. Find All Lonely Numbers in the Array](https://leetcode.com/problems/find-all-lonely-numbers-in-the-array/)
**Approach: Sliding Window O(n), O(1)**
1. We maintain a window of equal and strictly increasing sequence with common diff 1.
2. Once we encounter a new element which doest fit in the seq then we check if the window size is just one we append it to our ans and contiue doing the same for next elements.

```
vector<int> find(vector<int> &nums){
    // maintain a window of increasing and equal elements
    
    sort(nums.begin(), nums.end());
    if(nums.size() == 1) return nums;
    if(nums.size() == 2){
        if(nums[0]+1 < nums[1]) return nums;
        return {};
    } 
    int i=0,j=0;
    vector<int> ans;
    for(;j<nums.size()-1; ){
        while(j<nums.size()-1 && nums[j]+1 >= nums[j+1]) j++;
        if(j<nums.size()-1 && nums[j] + 1 < nums[j+1]){
            if(i==j) {
                ans.push_back(nums[i]);
                
            }
                j++;
                i=j;
            
        }
        else j++;
    }
    if(j==nums.size()-1 && nums[j-1] + 1 < nums[j]) ans.push_back(nums[j]);
    return ans;
}
```

**Approach: Unordered_map O(n), O(n)**  
1. Put all elements in the unordered map
2. Now check for each element if occurence is 1 and occurence of previous and next element is 0 then append it to our ans;

```
vector<int> findLonely(vector<int>& nums) {
    unordered_map<int, int> m;
    vector<int> res;
    for (int n : nums)
        ++m[n];
    for (const auto [n, cnt] : m)
        if (cnt == 1 && m.count(n + 1) == 0 && m.count(n - 1) == 0)
            res.push_back(n);
    return res;
}
```
---
