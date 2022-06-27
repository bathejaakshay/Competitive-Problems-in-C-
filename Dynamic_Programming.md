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

#### [4. Maximum Subsequence sum with no adjacent elements/ Maximum sum of non-adjacent elements](https://www.codingninjas.com/codestudio/problems/maximum-sum-of-non-adjacent-elements_843261?leftPanelTab=1)

**Problem** Find the maximum subsequence sum in an array with a condition that no two elements in a subsequence should be adjacent in the given array.
**Approach**
1. Approach is simple pick and not pick as it is a subsequence question. 
2. Now say f(n) represents the maximum subarray sum with no adjacent elements. 
3. Now if I say the subsequence includes a[n] then one possible ans has to be a[n] + f(n-2). f(n-2) 
4. Because if we have picked f(n) we cant pick f(n-1) 
5. And If I dont pick then another possible ans could be f(n-1)
6. f(n) = max(a[n] + f(n-2), f(n-1))


**Approach 1** Memoization: (Top Down)
```
int max_sum(int n, vector<int> &nums, vector<int> &dp){
    if(n==0) return nums[0];
    if(n<0) return 0;
    
    if(dp[n]!=-1) return dp[n];
    
    int left = nums[n] + max_sum(n-2, nums, dp);
    int right = max_sum(n-1,nums, dp);
    return dp[n] = max(left, right);
}
TC: O(n)
Space : O(n) + O(n) : Aux + DP_array
```

**Approach 2** Tabular 1 : Bottom up
```
int max_sum(int n, vector<int> &nums, vector<int> &dp){
    
    dp[0] = nums[0];
    int left=INT_MIN,right=INT_MIN;
    for(int i=1; i<nums.size(); i++){
        if(i>1)
            left = nums[i] + dp[i-2];
        else
            left = nums[i];
        right = dp[i-1];
        dp[i] = max(left, right);
    }
    return dp[n];
}


TC: O(n)
SC: O(n) : Dp array
```

**Approach 3** Tabular 2: Bottom up with only two variables

```
int max_sum(int n, vector<int> &nums, vector<int> &dp){
    int prev1 = nums[0], prev2 = 0, curr, left, right;
    for(int i=1; i<nums.size(); i++){
        left = nums[i] + prev2;
        right = prev1;
        curr = max(left, right);
        prev2 = prev1;
        prev1 = curr;
    }
    return prev1;
    
}
TC: O(n)
SC: O(1)
```

---

#### [5. Ninjq Training](https://www.codingninjas.com/codestudio/problems/ninja-s-training_3621003?leftPanelTab=0)
**Approach**:
1. We start with nth day and go top down. We say then on n+1th day we didn't do any training so last=3 (i.e neither 0 or 1 or 2).
2. Now we compute ,`f(n) = max(maxi,points[n][j] + f(n-1,j))` if last!=j , for each activity on day n and max_points till day n-1 with last day activity as j   
```
#// DP: Memo
int ninja(int n, vector<vector<int>> &points, int last, vector<vector<int>> &dp){
    if(n==0){
        int maxi=0;
        for(int i=0; i<3; i++){
            if(i!=last){
                maxi = max(maxi, points[0][i]);
            }
        }
        return maxi;
    }
    if(dp[n][last]!=-1) return dp[n][last];
    int maxi=0;
    for(int i=0;i<3;i++){
        
        if(i!=last){
            maxi = max(maxi, points[n][i] + ninja(n-1, points, i, dp));
        }
    }
    return dp[n][last]=maxi;
}
// DP: Tabulation1
int ninja_tab(int n, vector<vector<int>> &points, vector<vector<int>> &dp){
    dp[0][0] = max(points[0][1], points[0][2]);
    dp[0][1] = max(points[0][0], points[0][2]);
    dp[0][2] = max(points[0][0], points[0][1]);
    dp[0][3] = max(dp[0][0],points[0][0]);
    
    
    for(int i=1; i<=n; i++){ // For each day for each last training value we compute each current training value
        
        
        for(int last=0;last<4;last++){
            dp[i][last]=0;
            int maxi =0;
            for(int j=0;j<3;j++){
                if(j!=last){
                    maxi = max(maxi, points[i][j] + dp[i-1][j]);  
                  }
             
            }
            dp[i][last] = maxi; 
        }
        
    }
    return dp[n][3];
}
// DP: Tabulation Space optimization
int ninja_spc(int n, vector<vector<int>> &points){
    vector<int> prev(4,-1); // prev[i] represents the points scored on previous day when last activity was i, at any time we only want points scored on previous day for all 3 training options.
    prev[0] = max(points[0][1], points[0][2]);
    prev[1] = max(points[0][0], points[0][2]);
    prev[2] = max(points[0][0], points[0][1]);
    prev[3] = max(prev[2], points[0][2]);
    
    for(int i=1; i<=n; i++){
        vector<int> temp(4,0);
        for(int last=0; last<4; last++){
            
            int maxi =0;
           
            for(int task=0; task<3; task++){
                if(task!=last)
                    maxi = max(maxi, points[i][task] + prev[task]);       
            }
            temp[last] = maxi;
        }
        prev = temp;
    }
    return prev[3];
}

```

---
