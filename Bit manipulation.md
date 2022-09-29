#### [1.Largest Combination With Bitwise AND Greater Than Zero](https://leetcode.com/contest/weekly-contest-293/problems/largest-combination-with-bitwise-and-greater-than-zero/)
Given an array of size n, find a maximum sized combination whose and is non zero. 
![BM1](https://github.com/bathejaakshay/Competitive-Problems-in-C-/blob/master/Images/bm1.png?raw=true)

**Main Idea**:
1. For each bit in all the numbers find the count of set bit.
2. The ans will be the maximum number of set bits for any bit place.

```
int largestCombination(vector<int>& cs) {
    int res = 0, max_e = *max_element(begin(cs), end(cs)); \\ Maximum element will decide the maximum number of bits
    for (int b = 1; b <= max_e; b <<= 1) { 
        int cnt = 0;
        for (auto n : cs)
            cnt += (n & b) > 0; \\ We are setting a bit one by one in log(max_element) bit integer and taking its **and** with all the numbers.
        res = max(res, cnt);
    }
    return res;
}
```
---

#### 2. Powerset or all subsequences of strings Brute Force using Bit Manipulation
**Approach**:
1. Given a string : abc, we need to find all of its subsequences.
2. Our approach is to take 1 to 2^(n)-1 represent all the subsequences in binary format
3. 1: 001 i.e take only first char , 3: 011 take first and second char.
4. Now For all these numbers we find what all bits are set at which index and we append char at that index to our candidate subseq string.

```
void subseq(string &s, vector<string> &ans){

	int x = pow(2, s.length())-1;

	for(int i=0; i<=x; i++){  // Iterating 0 to 2^(s.length()) -1

		string cand="";
		for(int j=0; j<s.length(); j++){	// Iterating 0 to s.length() -1 to compare check set bits
			if(i&(1<<j)){   // Most important, check if jth bit is set in i.
				cand+=(s[j]);
			}
		}
		ans.push_back(cand);

	}

	return;

}
```
**TC**=O((2^n)*n)

---


#### [3. Longest Nice Subarray](https://leetcode.com/contest/weekly-contest-309/problems/longest-nice-subarray/)

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

#### [4.  Longest Subarray With Maximum Bitwise AND](https://leetcode.com/contest/weekly-contest-312/problems/longest-subarray-with-maximum-bitwise-and/)
**Approach**
- The only thing to remember here is that bitwise and of two different numbers is strictly lesser than the maximum of those two numbers.
- By this logic the maximum bitwise `x`  possible is actually the max of the array.
- And the subarray with maximum contigous elements equal to `x` is our ans. Because different number gives bitwise and lesser than max.

```
  int longestSubarray(vector<int>& nums) {
        // Lets first find max bitwise and
       int maxi = *max_element(nums.begin(), nums.end());
       int max_win=1;
       int win=1;
       for(int i=1; i<nums.size(); i++){
           if(nums[i] == nums[i-1] && nums[i] == maxi){
               win++;
               max_win = max(max_win, win);
           } 
           else{
               win=1;
               
           }
       } 
       return max_win;
    }
```
