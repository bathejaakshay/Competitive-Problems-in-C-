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

---

#### [5. Couting bits](https://leetcode.com/problems/counting-bits/description/)
**Approach : O(n) dp **

1. Observe the pattern that after every power of two one 1 bit is is fixed and the remaining number of ones can be computed from the previous number e.g
2. 8 : 1000 : 1 + dp[0], 10 : 1010 = 1 + dp[2] , ... 15 : 1 + dp[7] i.e dp[i] = 1 + dp[i- offset]  where offset is the bit that is currently fixed.
3. Offset changes once offset * 2 becomes equal to current i.

```
vector<int> countBits(int n) {
        vector<int> dp;
        int offset = 1;
        dp.push_back(0);
        for(int i=1; i<=n; i++){
            if(offset*2 == i){
                offset = i;
            }
            dp.push_back(1 + dp[i-offset]); 

        }
        return dp;
    }
```

---

#### [6. Reverse bits](https://leetcode.com/problems/reverse-bits/description/)
**Approach**
- start with the Most significant bit and check if it is one, if it is then add its value as per the new LSB in the reverse order.
- We take start variable which is set to MSB i.e `2^31`. ans `j=0` representing the position of bit in the reverse number.
- Now check if start&number == start, if it is then add pow(2,j) in the ans.
- other wise do j++ and start/=2;
```
uint32_t reverseBits(uint32_t n) {
        uint32_t ans=0;
        uint32_t start = pow(2,31);
        int j=0;
        while(start>0){
            if((n&start) == start){
                ans += pow(2,j);
            }
            j++;
            start/=2;
        }
        return ans;

    }

```

#### [7. Missing number](https://leetcode.com/problems/missing-number/description/)
Given an array nums containing n distinct numbers in the range `[0, n]`, return the only number in the range that is missing from the array.
```
int missing(vector<int> &nums){
// take exor of 0 to n elements then exor the ans with the exor of all elements of nums , all the equal elements element will cancel out and give us the ans which appeared only once.

int s = 0;
for(int i=0;i<=nums.size();i++){
    s^=i;
}

for(int i=0; i<nums.size(); i++){
     s^=(nums[i]);
    }
    return s;
}

```
