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
