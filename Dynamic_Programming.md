#### DP Shortcut
Identification: If the question asks to count something or find minimum or maximum from all the ways possible then its recursion.

Steps:
1. Try to represent the problems in terms of index.
2. Do all possible stuff on the index according to the problem.
3. For count all the ways -> sum up all the stuff
4. If mini of all the ways -> find minimum of all stuff. Same for maximum

#### 1. kth Fibbonacci number

**Approach 1** Memoization: (Top Down)
```
int fibbo(n){
  if(n<=1) return 1;
  if(dp[n]!=-1) return dp[n];
  
  dp[n] = dp[n-1] + dp[n-2];
  return dp[n];
  
}

TC: O(n)
Space : O(n) + O(n) : Aux + DP_array
```

**Approach 2** Tabular 1 : Bottom up
```
dp[0] = 0, dp[1] = 1
for(i : 2 to n):
  dp[n] = dp[n-1] + dp[n-2];


TC: O(n)
SC: O(n) : Dp array
```

**Approach 3** Tabular 2: Bottom up with only two variables

```
prev2 = 0, prev1 = 1

for(i :2 to n):
  curr_i = prev1+prev2;
  prev2=prev1;
  prev1 = curr_i;
  
ans: prev1

TC: O(n)
SC: O(1)
```

---

#### [2. Climbing Stairs](https://leetcode.com/problems/climbing-stairs/)
**Approach**
1. Given n stairs we can represent in index from 1 to n where 0 means floor and 1 to n are stairs.
2. Secondly we need to find all the ways so we return 1 in base case.
3. Now we add left and right to compute all.

```
climbst(int n)
{
  if(n<=1) return 1;
  
  int left = f(n-1);
  int right = f(n-2);
  return left+right;
}
```
The recurrsion seems like fibonacci hence we can use the same.

---

#### [3. Frog Jump](https://www.codingninjas.com/codestudio/problems/frog-jump_3621012?leftPanelTab=1)
**Problem** Given stairs 1 to N and heights of each stair. The energy consumed to jump from stair 1 to 2 is abs(heights[1] - heights[2]). Now we want to reach the stair n from stair 1 with minimum energy  consumption.
**Approach**
1. The recursive way is: say f(n) is the minimum energy consumed to reach n from 1
2. So we can write f(n) = min(f(n-1) + abs(heights[n] - heights[n-1]), f(n-2) + abs(heights[n] - heights[n-2]))
3. Just take care of additional corner case for n=1 the above will fail so we handle it.
4. The tabu and spcopt is similar to above mentioned problems.

```
#include<bits/stdc++.h>
int f_approach_memo(int n,vector<int> &heights, vector<int> &dp)
{
    if(n==0) return 0;// frogjump(n) is the energy consumed to reach n from 0 
    if(dp[n]!=-1) return dp[n];
    int left = f_approach_memo(n-1, heights, dp) + abs(heights[n] - heights[n-1]);
    int right = INT_MAX;
    if (n > 1)
         right = f_approach_memo(n-2, heights, dp) + abs(heights[n] - heights[n-2]);
    dp[n]=min(left, right);
    return dp[n];
}

int f_approach_tabu(int n, vector<int> &heights, vector<int> &dp){
    dp[0] = 0;
    int left,right;
    for(int i=1;i<=n;i++){
        left = dp[i-1] + abs(heights[i] - heights[i-1]);
        right = INT_MAX;
        if(i>1)
            right=dp[i-2] + abs(heights[i] - heights[i-2]);
        dp[i] = min(left,right);
    }
    return dp[n];
}
int f_approach_spcop(int n, vector<int> &heights){
    int prev2, prev1=0,curr;
    for(int i=1; i<=n ;i++){
        curr = prev1 + abs(heights[i] - heights[i-1]);
        if(i>1)
            curr = min(curr, prev2 + abs(heights[i] - heights[i-2]));
        
        prev2 = prev1;
        prev1 = curr;
    }
    return prev1;
        
}
int frogJump(int n, vector<int> &heights)
{
    // Write your code here.
    vector<int> dp(n+1,-1);
//     int ans = f_approach_memo(n-1, heights, dp);
//     int ans = f_approach_tabu(n-1, heights, dp);
    int ans = f_approach_spcop(n-1, heights);
    return ans;
    
}

```

---

  
