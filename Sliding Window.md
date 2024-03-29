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

#### [Uber = Min length substring with subsequences](https://leetcode.com/discuss/interview-question/1845128/Uber-Software-Engineer-India-(University)-2022-Graduates-Coding-Test)  
You are given a binary string of length n.
You have to find a minimum length substring of the above given string such that the count of subsequences of this substring which equal "01" is atleast k.
Your solution will return the length of the minimum length substring. If no such string exists then return -1.
**Approach : Sliding window**
Pattern: Min length substring in O(n) time with some computation.
We using sliding window with window shrinkage i.e whenever we encounter sum of subseq >= k then we start shrinking our window. Simple.

```
#include<bits/stdc++.h>
using namespace std;

int solve(string q, int k){

    int i=0,l=0;
    while(i<q.length() && q[i] == '1') i++;
    if(i == q.length()) return 0;
    int c_z=0,c_o=0;
    int count=0;
    int ans = INT_MAX;
    int j=i;
    while(j<q.length()){
        if(i==j && q[j] == '1') {
            i++; j++;
        }
        if(q[j] == '0') c_z++;
        else if(q[j] == '1'){
            c_o++;
            count+=(c_z);
        }
        if(count >= k){
            ans = min(ans, j-i+1);
            while(i<=j && count>=k){
                ans = min(ans, j-i+1);
                if(q[i] == '0'){
                    count-=(c_o);
                    c_z--;
                    

                }
                else c_o--;
                i++;
            }
            while(i<=j && q[i] == '1') {
                i++;
                c_o--;
            }
        }
        j++;

    }
    return (ans==INT_MAX)?-1:ans;
}

int main(){
    string q;
    cin>>q;

    int k;
    cin>>k;

    cout<<solve(q,k);
}
```
**Approach 2: Modified Binary Search**
- Range min len =0 , max_len = n
- Now mid gives us wind size. We have to check max 01 subseq in win size mid in O(n) time.
- if count satisfies k then high = mid-1 else low = mid+1

---

#### [Count Subarrays With Fixed Bounds - Good](https://leetcode.com/contest/weekly-contest-315/problems/count-subarrays-with-fixed-bounds/)  
You are given an integer array nums and two integers minK and maxK.  

A fixed-bound subarray of nums is a subarray that satisfies the following conditions:  

The minimum value in the subarray is equal to minK.  
The maximum value in the subarray is equal to maxK.  
Return the number of fixed-bound subarrays.  

A subarray is a contiguous part of an array.  

**Approach**
1. we will use sliding window approach.
2. intially i=0,j=0 and iterate j till end
3. we also mantain two pointers mi and mj representing latest index when `num[j] == minK` , `num[j] == maxK respt`.
4. Now at every step, we find x = min(mi,mj) now we know we cant have any subarray from x till j that have both minK and maxk  and our starting index is `i`, so Number of subarrays ending at j from i that have mini = minK and maxi = maxK are min(mi,mj) - i + 1 (i.e we can start with any element in [i, min(mi,mj)] and end at j).

```
class Solution {
public:
    long long countSubarrays(vector<int>& nums, int minK, int maxK) {
        long long count=0;
        
        int i=0;
        int mini=INT_MAX, maxi=INT_MIN;
        int flag=0;
        long long mi=-1,mj=-1;
        
        for(int j=0; j<nums.size(); j++){
            if(nums[j] < minK || nums[j] > maxK){
                mi=-1; mj=-1;
                i=j+1;
            } 
            if(nums[j] == minK) mi=j;
            if(nums[j] == maxK) mj=j;
            count+=( max((long long)0, (long long)min(mi,mj) -i + 1));
        }
        return count;
    }
};
```

 
