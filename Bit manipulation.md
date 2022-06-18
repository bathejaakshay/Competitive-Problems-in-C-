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
