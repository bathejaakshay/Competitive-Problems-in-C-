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

#### [5. Ninja Training](https://www.codingninjas.com/codestudio/problems/ninja-s-training_3621003?leftPanelTab=0)
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

### DP on GRIDS

#### [6. No of ways to reach a destination in `M*N` grid/ Unique paths](https://www.codingninjas.com/codestudio/problems/total-unique-paths_1081470?leftPanelTab=1)

**Approach**
1. Representing problem in terms of index: f(i,j) represents number of unique paths from point(m,n) to point (i,j).
2. Doing all stuff on indices: as we are doing top down hence we start from m,n and we can move left or up. So we find f(m-1,n) and f(m,n-1)
3. Sum up all paths: f(m,n) = f(m-1,n) + f(m,n-1)
4. As there are a lot of overlapping subproblems, hence we can use DP

**Memoization**
```
int up_f(int m, int n, vector<vector<int>> &dp){
    if(m==0 && n==0) return 1;
    if(m<0 || n<0) return 0;
    
    if(dp[m][n]!=-1) return dp[m][n];
    
    int left = up_f(m, n-1, dp);
    int up = up_f(m-1, n, dp);
    return dp[m][n] = left+up;
}
```
`TC: O(m*n) : Total no of states`
`SC : O(((m-1) + (n-1)) + O(m*n)) : (aux space longest valid path length from m,n to 0,0) + (DP)`

**Tabulation**
```
int up_tab(int m, int n, vector<vector<int>> &dp){
    dp[0][0] = 1;
    for(int i=0; i<=m; i++){
        for(int j=0; j<=n; j++){
            if(dp[i][j]==-1){
                int up=0,left=0;
                if(i>0){
                    up = dp[i-1][j];
                }
                if(j>0){
                    left = dp[i][j-1];
                }
                dp[i][j] = up+left;
            }
        }
    }
    
    return dp[m][n];
}

SC: O(M*N)
```
**Space Optimization**
Golden Rule: Whenever we refer to previous row and col we can always space optimize.
1. How to see? : In for loops we are traversing grid from left to right and for each element we require `[i][j-1]` of the same row and `[i-1][j]` of the previous row. So we can make 2 arrays 1 dp (consists prev row) and another temp(consist curr row) to do this.

```
int up_spc(int m, int n){
     vector<int> dp(n+1,0);
    for(int i=0; i<=m; i++){
        vector<int> temp(n+1,0);
        for(int j=0; j<=n; j++){
            int up=0, left=0;
            if(i==0 && j==0){
                temp[0]=1;
                continue;
            }
            
            up = dp[j];
                
            if(j>0){
                    left = temp[j-1];
                }
            
            else left=0;
            temp[j]=up+left;
        }
        dp = temp;
    }
    return dp[n];
}

```
`SC: O(2*N)`

---

#### [7. Minimum Path Cost in a Grid](https://leetcode.com/contest/weekly-contest-297/problems/minimum-path-cost-in-a-grid/)
Also known as variable starting and variable ending point.
**Approach**
1. f(i,j) is the min path cost from first row
2. we find min path for each column j in last row. by adding the required costs.
3. For each j we pull a the following recurrsion
4. For each j in previous row find min path to current column.

```
int minpath(vector<vector<int>> &grid, vector<vector<int>> &moveCost, int m, int n, vector<vector<int>> &dp){
    
 if(m==0){
     return grid[0][n];
 }   
    if(dp[m][n]!=-1) return dp[m][n];
    int mini=INT_MAX;
 for(int j=0; j<grid[0].size(); j++){
     mini = min(mini, grid[m][n] + moveCost[grid[m-1][j]][n] + minpath(grid, moveCost, m-1, j, dp));
 }   
    return dp[m][n] = mini;
}

class Solution {
public:
    int minPathCost(vector<vector<int>>& grid, vector<vector<int>>& moveCost) {
    vector<vector<int>> dp(grid.size(), vector<int>(grid[0].size(),-1));
        int ans=INT_MAX;
        for(int j=0; j<grid[0].size(); j++){
            ans = min(ans,minpath(grid, moveCost, grid.size()-1, j, dp));
        }
        
    return ans;
    }
};


// Bottom Up: Just do opposite of Top Down
int minpath_b(vector<vector<int>> &grid, vector<vector<int>> &moveCost, int a, int b, vector<vector<int>> &dp){
    
    int m = grid.size();
    int n = grid[0].size();
    
    //Base case 
    for(int j=0; j<n; j++){
        dp[0][j] = grid[0][j];
    }
    
    // In TopDown we have variables i and j which went from m,n to 0,0 here it will be opposite: 2 for loops- i: 1 -> m and j 0->n;
    
    for(int i=1; i<m; i++){
        for(int j=0; j<n; j++){
            int mini = INT_MAX;
            for(int x=0; x<n; x++){
                mini = min(mini, grid[i][j] + moveCost[grid[i-1][x]][j] + dp[i-1][x]);
            }
            dp[i][j] = mini;
        }
    }
    return dp[a][b];
}

// Space optimization:
int minpath_spc(vector<vector<int>> &grid, vector<vector<int>>&moveCost, int a, int b){
    int m= grid.size();
    int n= grid[0].size();
    
    vector<int> dp(n, -1);
    
    for(int j=0; j<n; j++) dp[j]=grid[0][j];
    
    for(int i=1; i<m; i++){
        vector<int> temp(n, -1);
         for(int j=0; j<n; j++){
            int mini=INT_MAX;
             for(int x=0; x<n; x++){
                 mini = min(mini, grid[i][j] + moveCost[grid[i-1][x]][j] + dp[x]);
                 
                                }
             temp[j] = mini;
         }
        dp = temp;
    }
    return dp[b];
}

```
`TC: O(M*(n^2))`
---

#### [8. Minimum path cost on a Triangle Grid](https://leetcode.com/problems/triangle/)
**Approach**
1. In this we approach recurrsion in a little different way.
2. Instead of starting with m-1,n-1 going to 0,0 , we go from 0,0 to last row. Because if we start from last then we can have n different recurrsions of which we would need to take min of.
3. But here f(i,j) will represent the min path cost from last row.

```
f(i,j){
  if(j==m-1) // last row
    return cost[i][j]
    
 int down = cost[i][j] + f(i+1,j);
 int diag = cost[i][j] + f(i+1, j+1);
 
 return min(down, diag);
}
```

`Its bottom up is also iteresting, as we do opposite of top down`


**Top Down: Memo**
```
 
int minTot(vector<vector<int>> &triangle, int i, int j, vector<vector<int>> &dp){
    
    if(i==triangle.size()-1){
        return triangle[i][j];
    }
    if(dp[i][j]!=-1) return dp[i][j];
    int down = triangle[i][j] + minTot(triangle,i+1,j, dp);
    int diag = triangle[i][j] + minTot(triangle,i+1,j+1, dp);
    
    return dp[i][j] = min(down, diag);
}
```
**Bottom up**
```
int minTot_b(vector<vector<int>> & triangle, int i , int j, vector<vector<int>> &dp){
    int m = triangle.size();
    int n = triangle[m-1].size();
    
    for(int x=0; x<n; x++){
        dp[m-1][x] = triangle[m-1][x]; 
    }
    
    //Just opposite the top down approach: in top down we go from 0,0 to last row, here we from last row to 0,0. Also we computed dp for the last row so we start from the second last row. Also no of columns in nth row is n 
    int down, diag;
    for(int row=m-2; row>=0; row--){
        for(int col=row; col>=0; col--){
            down = triangle[row][col] + dp[row+1][col];
            diag = triangle[row][col] + dp[row+1][col+1];
            dp[row][col] = min(down,diag);
        }
    }
    return dp[0][0];
}

```
**Bottom up space optimization**
```
int minTot_spc(vector<vector<int>> &triangle){
    int m = triangle.size();
    int n = triangle[m-1].size();
    vector<int> dp(n,-1);
    
    for(int x=0; x<n; x++){
        dp[x] = triangle[m-1][x]; 
    }
    
    int down, diag;
    for(int row=m-2; row>=0; row--){
        vector<int>temp(n,0);
        for(int col=row; col>=0; col--){
            down = triangle[row][col] + dp[col];
            diag = triangle[row][col] + dp[col+1];
            temp[col] = min(down,diag);
        }
        dp = temp;
    }
    return dp[0];
}

```
`TC : O(m*n)`

---

#### [9. Cherry Pickup 2 - 3D DP](https://leetcode.com/problems/cherry-pickup-ii/)
In this problem we are provided with a grid of `M*N` with cherries in each cell. Given two robots at 0,0 and 0,n-1.  
Find the maximum no of cherries that can be collected by the robots if they can move to next row in left diag, straight down, and right diag. 
If both robots are at same cell then only one can collect the cherries.
**Approach**
1. We move them simultaneously.
2. One thing to notice is that is a fixed to variable dp on grids, hence we start from starting and move down.
3. We are moving both robots together so that they both be at the end row together.
4. There can be 9 move combs. for each movement of first robot the second robot can move in three ways.

`TC without Memo : O(3^n * 3^n) like a tree with order 3`  
**Top Down: Memo**
```
int cherrypick(vector<vector<int>> &grid, int i, int j, int i2, int j2, vector<vector<vector<int>>> &dp){
    
    //out of bounds return -1e8 and not INT_MIN as there could be int overflow error if we add negative to INT_MIN
    if(j<0 || j>grid[0].size()-1 || j2<0 || j2>grid[0].size()-1){
        return -1e8;
    }    
    // In fixed to variable point dp on grid we start from fixed instead of end. We are moving both robots together so that they both be at the end row together
    
    if(i==grid.size()-1 && i2==grid.size()-1){
        if(j==j2){
            return grid[i][j];
        }
        else return grid[i][j] + grid[i2][j2];
    }
    if(dp[i][j][j2]!=-1) return dp[i][j][j2];
    // For each transition of robot1 we have 3 transition of robot2
    
    // int dir[] = {-1,0,1};
    int maxi = 0;
    for(int x=-1;x<=1;x++){
        for(int y=-1; y<=1; y++){
            if(j == j2){
                maxi = max(maxi, grid[i][j] + cherrypick(grid, i+1, j+x, i2+1, j2+y, dp));
            }
            else{
                maxi = max(maxi, grid[i][j] + grid[i2][j2]+ cherrypick(grid, i+1, j+x, i2+1, j2+y, dp));    
            }
            
        }
    }
    return dp[i][j][j2]=maxi;
    
}
```
`TC: O(M*N*N) No of distinct function calls`

**Bottom up: Tabulation with space optimization**
```
int cherrypick_spc(vector<vector<int>> &grid, int m, int n){
    vector<vector<int>> dp(n,vector<int>(n,0));
    // Base case of Memo
    for(int i=0; i<n; i++){
        for(int j=0; j<n ;j++){
            if(i==j){
                dp[i][j] = grid[m-1][i];
            }
            else dp[i][j] = grid[m-1][i] + grid[m-1][j];
                
        }
    }
    
    // Doing all stuff for i:m-2->0
    
    for(int i=m-2; i>=0; i--){
        vector<vector<int>> curr(n, vector<int>(n,0));
        for(int j1=0; j1<n; j1++){
            for(int j2=0; j2<n; j2++){
                int maxi=-1e8;
                for(int dj1=-1; dj1<=1; dj1++)
                    for(int dj2=-1; dj2<=1; dj2++){
                        if(j1==j2){
                           if(j1+dj1>=0 && j1+dj1<n && j2+dj2>=0 && j2+dj2<n) 
                           maxi =  max(maxi,grid[i][j1] + dp[j1+dj1][j2+dj2]);
                        }
                        else{
                            if(j1+dj1>=0 && j1+dj1<n && j2+dj2>=0 && j2+dj2<n)
                         maxi =  max(maxi,grid[i][j1] + grid[i][j2] + dp[j1+dj1][j2+dj2]);   
                        }
                    }
                    curr[j1][j2] = maxi;   
            }
        }
        dp =curr;
    }
    
    return dp[0][n-1];
}
```
---


## DP on Subsequences

#### [10. Subset sum equal to k](https://www.codingninjas.com/codestudio/problems/subset-sum-equal-to-k_1550954?leftPanelTab=1)
**Approach**
1. We follow pick and not pick approach.
2. For each element in the array we have an option to pick and not pick and the target changes accordingly.
3. we get TC of 2^n using this.
4. We use `dp[n][target+1]`, here `dp[i][j] = true` signifies that subset  sum is equal to j is possible with subsequence inS
5.  0 to i-1 elements 
6. Base Cases are important.
**TopDown: Memo** 
```
bool subset(vector<int> &nums, int i, int target, vector<vector<int>> &dp){
    if(target==0) return true;
    if(i==0){
        if(target == nums[i]) return true;
        else return false;
    }
    
    if(dp[i][target]!=-1) return dp[i][target];
    //pick
    bool left=false, right=false;
    if(target>=nums[i])
        left = subset(nums, i-1, target - nums[i], dp);
    
    //not pick
    right = subset(nums, i-1, target, dp);
    
    return dp[i][target] = left|right;
    
}
```
**Bottom Up : Tabulation**
```
bool subset_bt(vector<int> &nums, int i, int target, vector<vector<bool>> &dp){
    
        for(int x=0; x<nums.size(); x++){
            dp[x][0] = true;
            dp[x][nums[x]] = true;
        }
        
        for(int a=1; a<nums.size();a++){
            for(int b=1; b<=target; b++){
                //pick
                bool left=false, right=false;
                if(b>=nums[a])
                    left = dp[a-1][b-nums[a]];
                //not pick
                right = dp[a-1][b];
                dp[a][b] = left|right;
            }
        }
    return dp[nums.size()-1][target];
    
}

```
**Space Optimization**
```
bool subset_bt_spc(vector<int> &nums, int i, int target){
    
        vector<bool> dp(target+1,false);
        dp[0] = true;
        for(int x=0; x<nums.size(); x++){
            dp[nums[x]] = true;
        }
        
        
        vector<bool> curr(target+1, false);
        curr[0]=true;
        for(int a=1; a<nums.size();a++){
            for(int b=1; b<=target; b++){
                //pick
                bool left=false, right=false;
                if(b>=nums[a])
                    left = dp[b-nums[a]];
                //not pick
                right = dp[b];
                curr[b] = left|right;
            }
            dp=curr;
        }
    return dp[target];
    
}

```

---
#### 11. Partition of an array into two subsets such that their sum is equal and total sum is target
**Approach**
1. Intuitively two subsets of same size hence target should be even. If not then return -1
2. Now sum of both the sequences individually should be target/2.
3. Now each element will have to options to be considered in first or second.
4. Now it boils down to previous problem where we want to compute subsequence sum equal to target/2.

---

#### 12. Partition A Set Into Two Subsets With Minimum Absolute Sum Difference 
We need to partition A set into subsets such that their sums have minimum absolute difference.
**Approach**
1. We know the total sum of set say S. Now if the sum of first subset is s1 then sum of second one has to be S-s1.
2. So we need to find all the possible subsets s1 with sum 0 to S. and then we will compute S-s1 and find min abs diff.
3. But wait didnt we do that earlier?
4. In ques 10. `DP[n-1][0..target]` i.e the last row of the tabulation method represents if the subset sum with value `xE[0,target]` is possible or not.
5. So we first apply ques 10 to build dp table for subset sum with target value S.
6. Then we apply following algo:

```
int minSubsetSumDifference(vector<int>& arr, int n)
{
    int sum=0;
    for(int &a:arr) sum+=a;
    vector<vector<bool>> dp(n, vector<bool>(sum+1));
    subset_bt(arr,0, sum,dp);
  
    int mini=1e8;
    for(int j=0; j<=sum/2; j++){
        if(dp[n-1][j]){
            int s1 = j;
            int s2 = sum-j;
            mini = min(mini, abs(s1-s2));
        }
    }
    return mini;
}
```
---

#### [13. Count number of subsets in an array with sum target VIMP](https://www.codingninjas.com/codestudio/problems/number-of-subsets_3952532?source=youtube&campaign=striver_dp_videos&utm_source=youtube&utm_medium=affiliate&utm_campaign=striver_dp_videos&leftPanelTab=1)
Many problems are adaptations of this problem.
**Approach**
1. Use pick and not pick approach and return 1 if target is zero. Count pick and not pick and add them finally.
2. Very important edge cases when array is allowed 0 valued elements. see top down.

**Top Down: Memo**
```
int ways(vector<int> &num, int tar, int n,vector<vector<int>>& dp)
{ 
    //ways(n,tar) represents number of subsets till n whose sum is tar.
    // Edges cases are more when 0 valued element exists in the array
    //Very Important 
    if(n==0){
        if(num[0]==0 && tar==0) return 2; // two ways to pick 0 as first element if tgt is 0 , One is by picking 0 and other is by not
        if(tar==0 || num[0] == tar) return 1; // if either tgt has become zero or last element is tar then there is one way.
        return 0; // else return 0;
    }
    if(dp[n][tar]!=-1) return dp[n][tar];
    int pi=0,npi=0;
    if(tar >= num[n])
        pi = ways(num, tar-num[n], n-1, dp);
    npi = ways(num, tar, n-1, dp);
    return dp[n][tar]=pi+npi;
}
```
**Bottom up: Tabulation**
```
int ways_bt(vector<int> num,int n, int tgt){
    vector<vector<int>> dp(n, vector<int>(tgt+1,0));
    for(int i=0; i<n; i++){
        if(i==0 && num[0]==0) dp[i][0] = 2;
        else dp[i][0]=1;
    }
    if(num[0]!=0 && num[0]<=tgt) dp[0][num[0]] = 1;
    for(int i=1; i<n; i++){
        for(int x=0; x<=tgt; x++){
             int pi=0,npi=0;
             if(x >= num[i])
                 pi = dp[i-1][x-num[i]];
             npi = dp[i-1][x];
             dp[i][x]=pi+npi;
        }
    }
    return dp[n-1][tgt];
}
```
**Space Optimization**
```
int ways_spc(vector<int> num,int n, int tgt){
    vector<int> prev(tgt+1,0);
    if(num[0]==0) prev[0]=2;
    else prev[0]=1;
    if(num[0]!=0 && num[0]<=tgt) prev[num[0]] = 1;
    vector<int> curr(tgt+1,0);
    for(int i=1; i<n; i++){
        for(int x=0; x<=tgt; x++){
             int pi=0,npi=0;
             if(x >= num[i])
                 pi = prev[x-num[i]];
             npi = prev[x];
             curr[x]=pi+npi;
        }
        prev = curr;
    }
    return prev[tgt];
}
```

---
#### [14. 0/1 Knapsack Problem](https://www.codingninjas.com/codestudio/problems/0-1-knapsack_920542?source=youtube&campaign=striver_dp_videos&utm_source=youtube&utm_medium=affiliate&utm_campaign=striver_dp_videos&leftPanelTab=1)
**Approach**
1. Simple Pick / Not Pick problem

```
//Top Down
int sack(vector<int> &w, vector<int> &val, int n, int W,vector<vector<int>> & dp){
    if(W==0) return 0;
    if(n==0){
        if(W>=w[n]) return  val[n];
        else return 0;
    }
    if(dp[n][W] != -1) return dp[n][W];
    // pick
    int pi = INT_MIN;
    if(w[n] <= W)
        pi = val[n] + sack(w, val, n-1, W-w[n], dp);
    // not pick 
    int npi = sack(w, val, n-1, W, dp);
    
    return dp[n][W] = max(pi,npi);
    
}

//Bottom up
int ks(vector<int> &w, vector<int> &val, int n, int W){
    vector<vector<int>> dp(n, vector<int>(W+1,0));
    
    for(int x=w[0]; x<=W; x++) dp[0][x]=val[0];
    
    for(int i=1; i<n; i++){
        for(int wi=0; wi<=W; wi++){
            int pi=INT_MIN,npi;
            if(wi>=w[i]) pi = val[i] + dp[i-1][wi-w[i]];
            npi = dp[i-1][wi];
            dp[i][wi] = max(pi, npi);
        }
    }
    return dp[n-1][W];
}

//Bottom up : spc
int ks_spc(vector<int> &w, vector<int> &val, int n, int W){
    vector<int> dp(W+1,0);
    vector<int> curr(W+1,0);
    for(int x=w[0]; x<=W; x++) dp[x]=val[0];
    
    for(int i=1; i<n; i++){
        for(int wi=0; wi<=W; wi++){
            int pi=INT_MIN,npi;
            if(wi>=w[i]) pi = val[i] + dp[wi-w[i]];
            npi = dp[wi];
            curr[wi] = max(pi, npi);
        }
        dp=curr;
    }
    return dp[W];
}
```

---

#### [15. Coin Change](https://leetcode.com/problems/coin-change/)
1. Given denominations of infinite number of coins and a target we need to find the minimum number of coins that sum up to target.
2. Similar as 0/1 knapsack
3. pick is different, after every pick we have an option of picking the same element up again if possible.
4. This problem is interesting becuase we are counting number of coins and not the ways or anything else.

```
int coin(int n,vector<int> &coins, int amount, vector<vector<int>> &dp){
    
    if(n==0){
        if(amount%coins[0]==0) return amount/coins[0];
        else return 1e9;
    }
    if(dp[n][amount]!=-1) return dp[n][amount];
    //pick
    int pi = INT_MAX,npi;
    if(coins[n]<=amount){
        pi = 1 + coin(n, coins, amount-coins[n], dp);
        
    }
    npi = coin(n-1, coins, amount, dp);
   return dp[n][amount] = min(pi,npi);
    
}
//Bottom Up
int coin_bt(int n,vector<int> &coins, int amount){
    vector<vector<int>> dp(n, vector<int>(amount+1,0));
    for(int T=0; T<=amount; T++){
        if(T%coins[0]==0) dp[0][T] = T/coins[0];
        else dp[0][T]=1e9;
    }
    for(int i=1; i<n; i++){
        for(int j=0; j<=amount; j++){
            int pi = INT_MAX,npi;
    
            if(j>=coins[i]){
                pi = 1 + dp[i][j-coins[i]]; // we are counting number of coins hence we add 1

            }
            npi = dp[i-1][j];
            dp[i][j]=min(pi,npi);        
        }
    }
    
    return dp[n-1][amount];
    
}
//Bottom Up_spc
int coin_bt_spc(int n,vector<int> &coins, int amount){
    vector<int> dp(amount+1,0);
    vector<int> curr(amount+1,0);
    for(int T=0; T<=amount; T++){
        if(T%coins[0]==0) dp[T] = T/coins[0];
        else dp[T]=1e9;
    }
    for(int i=1; i<n; i++){
        for(int j=0; j<=amount; j++){
            int pi = INT_MAX,npi;
    
            if(j>=coins[i]){
                pi = 1 + curr[j-coins[i]]; // we are using curr as we want to stay at the same ith value instead of going to prev row.

            }
            npi = dp[j];
            curr[j]=min(pi,npi);        
        }
        dp=curr;
    }
    
    return dp[n-1][amount];
    
}

```
---

#### [16. Assign +,- to array to get Target Sum](https://www.codingninjas.com/codestudio/problems/target-sum_4127362?source=youtube&campaign=striver_dp_videos&utm_source=youtube&utm_medium=affiliate&utm_campaign=striver_dp_videos)
**Approach**
1. One of the approaches is that each element has to options to pick as + or in -.
2. Another approach is to reduce this problem to partitioning array into two subsets whose sum's diff is D.
3. Now we can see that the whole array will be partition into two groups one is positive and another negative such that S1 - S2 = Target
4. we can deduce it to subset sum with target `(totsum-Target)/2` or `(totsum+Target)/2`, but the latter will take more space.
5. Now we can apply 13th sol.
---
#### [17. Coin Change 2](https://www.codingninjas.com/codestudio/problems/ways-to-make-coin-change_630471?source=youtube&campaign=striver_dp_videos&utm_source=youtube&utm_medium=affiliate&utm_campaign=striver_dp_videos&leftPanelTab=1)
Given a denomination array with infinite coins supply. Return number of ways to make a change of `target`.

**Approach**
1. Simple count number of ways problem
2. return 1 and 0 depending on the base case
3. sum up pick and not pick
4. just remember after picking we can pick the same coin again

```
// Top Down
long long countways(int *denominations, int n, int value, vector<vector<long long>> &dp){
    if(value == 0) return 1;
    if(value<0) return 0;
    if(n==0) {
        if(value%denominations[0]==0) return 1;
        else return 0;
    }
    if(dp[n][value]!=-1) return dp[n][value];
    //pick/notpick
    long long pi=0, npi=0;
    if(value>=denominations[n])
        pi = countways(denominations, n, value-denominations[n], dp);
    npi = countways(denominations, n-1, value, dp);
    return dp[n][value] = pi+npi;
}

```
---
#### [18. Unbounded 0/1 Knapsack](https://www.codingninjas.com/codestudio/problems/unbounded-knapsack_1215029?source=youtube&campaign=striver_dp_videos&utm_source=youtube&utm_medium=affiliate&utm_campaign=striver_dp_videos&leftPanelTab=1)
Similar to 0/1 Knapsack with a difference that we have infinite bags with weight w and value v.
**Note**: In case of infinite supply ques the base cases are different and important

```
//Top Down
int ks(int n, int W, vector<int> &val, vector<int> &w, vector<vector<int>> &dp){
    if(W == 0) return 0;
    if(n==0){
        if(w[0] <= W) return (W/w[0])*val[0]; // Base cases in case of infinite supply is important and different.
        return 0;
    }
    if(dp[n][W]!=-1) return dp[n][W];
    int pi=INT_MIN;
    int npi;
    if(W>=w[n]) 
        pi = val[n] + ks(n, W-w[n], val, w, dp);
    npi = ks(n-1, W, val, w, dp);
    
    return dp[n][W] = max(npi, pi);
}
```
`TC : O(N*W)`
`SC : O(W) + O(N*W) : aux stack space and dp`

---

#### [19. Rod Cutting problem](https://www.codingninjas.com/codestudio/problems/rod-cutting-problem_800284?source=youtube&campaign=striver_dp_videos&utm_source=youtube&utm_medium=affiliate&utm_campaign=striver_dp_videos&leftPanelTab=0)
Given a rod of length l and profit length array representing profit of each cut_length `(ind+1)`. e.g l=5
`profit_len = [2,1,4]` this means cut of length 1 has profit of 2, length 2 has profit of 1 and length 3 has profit of 4.  
now we can cut rod of length five as: (1,1,1,1,1) Profit: 10
or (2,2,1) Profit:4 ... etc.
Similar to Unbounded 0/1 knapsack.

**Top Down: Memo**  
`TC : O(n*target)`
`SC : O(target + n*target)`


```
int cut(vector<int> &price, int target, int n, vector<vector<int>> &dp){
    if(target==0) return 0;
    if(n==0){
        if(target>=n+1) return (target/(n+1))*price[n];
        return 0;
    }
    if(dp[n][target]!=-1) return dp[n][target];
    int pi=INT_MIN;
    int npi;
    
    if(target>=n+1) pi = price[n] + cut(price, target-(n+1), n, dp);
    npi = cut(price, target, n-1, dp);
    return dp[n][target] = max(pi,npi);
    

```

**Bottom up**
`TC: O(n*target)`
`SC: O(n*target)`
```
int coin_bt(int n,vector<int> &coins, int amount){
    vector<vector<int>> dp(n, vector<int>(amount+1,0));
    for(int T=0; T<=amount; T++){
        if(T%coins[0]==0) dp[0][T] = T/coins[0];
        else dp[0][T]=1e9;
    }
    for(int i=1; i<n; i++){
        for(int j=0; j<=amount; j++){
            int pi = INT_MAX,npi;
    
            if(j>=coins[i]){
                pi = 1 + dp[i][j-coins[i]];

            }
            npi = dp[i-1][j];
            dp[i][j]=min(pi,npi);        
        }
    }
```

**Space Optimization**
`TC: O(n*target)`
`SC : O(target+1)`
```
int cur_bt_spc(vector<int> &price, int target, int n){
    vector<int> prev(target+1, 0);
    vector<int> curr(target+1, 0);
    
    //base cases
    for(int i=1; i<=target; i++){
        prev[i] = i*price[0];
    }
    
   for(int i=1; i<n; i++){
       for(int j = 0; j<=target; j++){
           int pi=INT_MIN;
           int npi;
           if(j>=i+1) pi = price[i] + curr[j-(i+1)];
           npi = prev[j];
           curr[j] = max(pi,npi);
       }
       prev=curr;
   }
    return curr[target];
    
    
}
```

---

## DP on Strings

#### [20. Length of longest common subsequence](https://www.codingninjas.com/codestudio/problems/longest-common-subsequence_624879?source=youtube&campaign=striver_dp_videos&utm_source=youtube&utm_medium=affiliate&utm_campaign=striver_dp_videos&leftPanelTab=1)

**Approaches**
1. Express the recurrsion in form of (ind1, ind2) of string s and t. Here f(ind1, ind2) represents the length of longest common subsequence for string s[0..ind1] and t[0..ind2]
2. Explore everything on indices
3. Take the best among them.

**Top down : Memo**  
`TC: O(n*m)  SC : O((n+m) + (n*m))`

``` 
int longcs(int i, int j, string s, string t, vector<vector<int>> &dp){
    if(i<0 || j<0) return 0;
    if(dp[i][j]!=-1) return dp[i][j];
    if(s[i] == t[j]) return dp[i][j] = 1 + longcs(i-1, j-1, s, t, dp);
    
    return dp[i][j] = max(longcs(i,j-1,s,t, dp), longcs(i-1,j,s,t, dp));
    
}
```

**Bottom Up:  Tabulation**
`TC: O((n+1)*(m+1))`  `SC : O((n+1)*(m+1))` (Tricky : requires index shifting)  
**Approach**
1. The indices originally traverese from -1 to n-1 & -1 to m-1, so we shift it to 0 to n & 0 to m as we cant express -1 in array index
```
int longcs_bt(string s, string t){
    int n = s.length();
    int m = t.length();
    vector<vector<int>> dp (n+1, vector<int>(m+1, 0)); //the indices originally travels from -1 to n-1 & -1 to m-1, so we shift it to 0 to n & 0 to m as we cant express -1 in array index
    
    // Base case handled for index -1 i.e 0
    
    for(int a = 1; a<=n; a++){
        for(int b = 1; b<=m; b++){
            if(s[a-1] == t[b-1]) dp[a][b] = 1 + dp[a-1][b-1];
            else dp[a][b] = max(dp[a-1][b], dp[a][b-1]);
        }
    }
    return dp[n][m]; 
}

```
**Bottom Space Optimization**
`TC : O((n+1)*(m+1))` `SC: O(m+1)`
```
int longcs_spc(string s, string t){
    int n = s.length();
    int m = t.length();
    vector<int> prev (m+1, 0);
    vector<int> curr (m+1, 0);
    // Base case handled for index -1 i.e 0
    
    for(int a = 1; a<=n; a++){
        for(int b = 1; b<=m; b++){
            if(s[a-1] == t[b-1]) curr[b] = 1 + prev[b-1];
            else curr[b] = max(prev[b], curr[b-1]);
        }
        prev = curr;
    }
    return prev[m];
}
```
---

#### 21. Printing LCS
**Approach**
1. Scan through DP table formed in tabulation.
```
string ans = "";
    int x = s.length(), y= t.length();
    while(x>0 && y>0){
    	if(s[x-1] == t[y-1]){
    		ans = s[x-1] + ans;
    		x--;
    		y--;
    	}
    	else{
    		if(dp[x][y-1] > dp[x-1][y]){
    			y--;
    		}
    		else{
    			x--;
    		}
    	}
    }
```
---

#### 22. Longest Palindromic Subsequence 
**Approach**
1. Given a string we can easily find longest palindromic subsequence using DP 
2. We take the string and its reverse and find the longest common subsequence. 
3. It will automatically give us the longest palindrome subsequence.

#### 23. Minimum insertions to make string palindrome 
**Approach**
1. Its idea is related to longest common palindrome subsequence 
2. We first find the longest palindrome subsequence.
3. The remaining chars that are not in longest palindrome subsequence are the number of insertions required to make the string palindrome.

#### 24. Minimum insertions/ deletions to convert string A to B 
**Approach**
1. we first find LCS of two strings. 
2. Sum of the length of two strings - 2* LCS length 

#### [25. Subsequence Counting](https://www.codingninjas.com/codestudio/problems/subsequence-counting_3755256?source=youtube&campaign=striver_dp_videos&utm_source=youtube&utm_medium=affiliate&utm_campaign=striver_dp_videos&leftPanelTab=0)
Given a string  T and a  string S, find all the subsquences in T that matches S.
**Approach**
1. Represent the problem in terms of indices. f(i,j) represents the number of subsequences in string `T[0..i]` that matches `S[0..j]`.
2. Do all stuff on the indices. Here we perform pick and not pick logic and as we are doing the counting problem we will just return 0 or 1. 
3. if the last char `T[i]` and `S[j]` matches then there are two options, either to include it in the count or to find another occurence of the same character S[j].
4. if they dont match then we shrink the T string by length one.
5. Finally we return the sum of two ways mentioned above. 
```
int subseqcount(int i, int j, string &t, string s, vector<vector<int>> &dp){
    if(j<0){
        return 1;
    }
    if(i<0) return 0;
    if(dp[i][j]!=-1) return dp[i][j];
    
    if(t[i] == s[j]){
        return dp[i][j] = (subseqcount(i-1, j-1, t, s, dp) + subseqcount(i-1,j,t,s, dp))%(1000000007);
    }
    else {
        return dp[i][j] = (subseqcount(i-1, j, t, s, dp))%(1000000007);
    }
}
int subseqcount_bt(int i, int j, string &t, string s){
    vector<vector<int>> dp (i+1, vector<int>(j+1,0));
    for(int x=0;x<i; x++){
        dp[x][0] = 1;
    } 
    for(int x=1; x<=i; x++){
        for(int y=1; y<=j; y++){
            if(t[x-1] == s[y-1]){
                dp[x][y] = (dp[x-1][y-1] + dp[x-1][y])%1000000007;
            }
            else{
                dp[x][y] = dp[x-1][y];
            }
        }
    }
   return dp[i][j];
}
int subseqcount_spc(int i, int j, string &t, string s){
    vector<int> prev (j+1,0);
    vector<int> curr (j+1,0);    
    prev[0]=1;
    curr[0]=1;
    for(int x=1; x<=i; x++){
        for(int y=1; y<=j; y++){
            if(t[x-1] == s[y-1]){
                curr[y] = (prev[y-1] + prev[y])%1000000007;
            }
            else{
                curr[y] = prev[y];
            }
        }
        prev = curr;
    }
   return curr[j];
}

int subsequenceCounting(string &t, string &s, int lt, int ls) {
    // Write your code here.
//     vector<vector<int>> dp(t.length(), vector<int>(s.length(), -1));
//     return subseqcount(t.length()-1,s.length()-1,t,s, dp);
//     return subseqcount_bt(t.length(),s.length(),t,s);
    return subseqcount_spc(t.length(),s.length(),t,s);

} 
```

#### [26. Edit Distance](https://www.codingninjas.com/codestudio/problems/edit-distance_630420?leftPanelTab=1)
**Approach**
1. we start scanning from the end of the two strings s and t
2. if the chars at two strings matches then no penalty and move backward. i.e `s[i-1] == t[j-1]`
3. if they donot match then we have three  options for the `s[i-1]` char to make it same  as `t[j-1]`
4. Either insert, replace or delete. we need to find minimum of them all. 
5. insertion 1 + f(i,j-1) 
6. replace 1 + f(i-1,j-1)
7. deletion 1 + f(i-1, j)
8. we dont actually perform insertion, replacement or deletion, instead we do recursion.

**Top Down**
```
int ed(int i, int j, string &s, string &t, vector<vector<int>> &dp){
    // base case 
    if(i==0){
        return j;
    }
    if(j==0){
        return i;
    }
     if(dp[i][j]!=-1)  return dp[i][j];  
    /*if the chars matches then we dont have to do anything, no penalty just move back*/
    
    if(s[i-1] == t[j-1]){
        return dp[i][j] = ed(i-1,j-1,s,t, dp);
    }
    /* If they dont match then we have three options, 
       1. We can insert the char and move jth one back and keep the ith same, 1 Penalty
       2. We can replace the char with the required char of t and move both indices back. 1 penalty
       3. We can delete that char, for this we 1 as penalty and move ith back */
    return dp[i][j] = 1 + min(ed(i-1,j, s, t, dp), min(ed(i, j-1, s, t, dp), ed(i-1, j-1 , s, t, dp)));
}
 ```
  
**Bottom-up:Tabulation**
 We need to be careful while writing base cases.
  
 ```
  int ed_bt(int i, int j, string &s, string &t){
    int m = s.length();
    int n = t.length();
    vector<vector<int>> dp(m+1, vector<int>(n+1,0));
    /* base case */
    for(int x=0; x<=m; x++){
        dp[x][0] = x; 
    }
    for(int x=0; x<=n; x++){
        dp[0][x] = x;
    }

    for(int x=1; x<=m; x++){
        for(int y=1; y<=n; y++){
            if(s[x-1] == t[y-1]){
            dp[x][y] = dp[x-1][y-1];
            }
            else
               dp[x][y] = 1 + min(dp[x-1][y], min(dp[x][y-1], dp[x-1][y-1]));        
        }
    }
    
    return dp[m][n];
}
  
 ```
  
 **Bottom up - Space optimization**
 ```
  int ed_spc(int i, int j, string &s, string &t){
    int m = s.length();
    int n = t.length();
    vector<int> dp(n+1,0);
   vector<int> curr(n+1,0);
    /* base case */
    for(int x=0; x<=n; x++){
        dp[x] = x;
    }

    for(int x=1; x<=m; x++){
        curr[0] = x;
        for(int y=1; y<=n; y++){
            
            if(s[x-1] == t[y-1]){
            curr[y] = dp[y-1];
            }
            else
               curr[y] = 1 + min(dp[y], min(curr[y-1], dp[y-1]));        
        }
        dp = curr;
    }
    
    return dp[n];
}
                          
 ```
---
 
#### [27. Wildcard pattern matching](https://www.codingninjas.com/codestudio/problems/wildcard-pattern-matching_701650?source=youtube&campaign=striver_dp_videos&utm_source=youtube&utm_medium=affiliate&utm_campaign=striver_dp_videos&leftPanelTab=1)  
`Wild cards :  '*' , '?'`  
**Approach**
1. Given a pattern p and string s find if pattern matches s. '*' means 0 or more matches , '?' means 1 char matches
2. Representing it in f(i,j) which implies that pattern `p[0..i]` matches string `t[0..j]`.
3. We compare last chars if they matches or pattern's char is `'?'` then we move both i and j backward 
4. Else if pattern's char is `'*'` then we have two options, Either consider  `'*'` maps to nothing i.e f(i-1,j) or it maps to t's char i.e `f(i,j-1)`. See doing this we will again have two options in future for the `'*'`. 
5. Else return false

**Top Down**
`TC: O(n*m)` `SC: O(n+m) + O(n*m)`

```
bool match(int i, int j, string &p, string &t, vector<vector<int>> &dp){
    //base cases
    if(i==0 && j==0) return true;
    if(i==0) return false;
    if(j==0){
        while(i>0){
            if(p[i-1]!='*') return false;
            i--;
        }
        return true;
    }
    if(dp[i][j]!=-1) return dp[i][j];
    if(p[i-1] == t[j-1] || p[i-1] == '?'){
        return dp[i][j] = match(i-1, j-1, p, t, dp);
    }
    else if(p[i-1]=='*'){
        return dp[i][j] = (match(i-1, j, p, t, dp) | match(i, j-1, p, t, dp));
    }
    return dp[i][j] = false;
}
```

**Bottom Up**
```
bool match_bt(string &p, string &t){
    int n= p.length(), m=t.length();
    vector<vector<bool>> dp(n+1, vector<bool>(m+1, false));
    // base cases
    dp[0][0] = true;
    for(int j=1; j<=m; j++){
        dp[0][j] = false;
    }
    for(int i=1; i<=n; i++){
        int x = i;
        int flag=0;
        while(x>0){
            if(p[x-1]!='*'){
                flag=1;
                break;
            }
            x--;
        }
      if(flag==0){
          dp[i][0] = true;
      }  
    }
    
    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            if(p[i-1] == t[j-1] || p[i-1] == '?'){
                dp[i][j] = dp[i-1][j-1];
            }
            else if(p[i-1]=='*'){
                dp[i][j] = (dp[i-1][j] | dp[i][j-1]);
            }
            else dp[i][j] = false;

        }
     }
    return dp[n][m];
}

```

**Space Optimization**
```
bool match_bt_spc(string &p, string &t){
    int n= p.length(), m=t.length();
    vector<bool> dp(m+1, false);
    vector<bool> curr(m+1, false);
    // base cases
    dp[0] = true;
    for(int j=1; j<=m; j++){
        dp[j] = false;
    }
    for(int i=1; i<=n; i++){
        int x=i;
        int flag=0;
        while(x>0){
            if(p[x-1]!='*'){
                flag=1;
                break;
            }
            x--;
        }
        if(flag==0){
            curr[0] = true; 
        }
        for(int j=1; j<=m; j++){
            if(p[i-1] == t[j-1] || p[i-1] == '?'){
                curr[j] = dp[j-1];
            }
            else if(p[i-1]=='*'){
                curr[j] = (dp[j] | curr[j-1]);
            }
            else curr[j] = false;

        }
        dp = curr;
     }
    return dp[m];
}

```
---

## DP on Stocks

**Intuition for recursion**  
If you are selling a stock on ith day then you must buy it at a minimum price from 1st to i-1th day.


#### [28. Best time to Buy and Sell stock II](https://www.codingninjas.com/codestudio/problems/selling-stock_630282?source=youtube&campaign=striver_dp_videos&utm_source=youtube&utm_medium=affiliate&utm_campaign=striver_dp_videos&leftPanelTab=1)
**Problem Statement**  
Given an array with the value of stock prices at each day from 1 to N, find the max profit if you are allowed to buy and sell stocks infinite times.  
A buy should always be followed by a sell.  
**Approach : Top Down**  
1. Lets first represent the problem in terms of indices. f(i, buy) represents the maxprofit obtained from day ith till last day given we perform buy or sell or nothing based on the keyword 'buy'.
2. for the first index buy is always possible i.e we call f(0,1)
3. so if buy is possible we do buy or not buy i.e  max(buying at day i i.e `- val[i] + f(i+1,0)` //once bought we cant buy again, not buying at day i i.e `0 + f(i+1,1)` // maxprof from i+1 to n if buying is allowed. 
4. if(buying is not allowed i.e buy==0) then we do sell or not sell:  max(selling at day i i.e `val[i] + f(i+1,1)` //once sold we can buy the next shares, not selling at day i i.e `0 + f(i+1,0)`.

```
long maxprof(int i, int buy, long *val, int n, vector<vector<long>> &dp){
    //base case
    if(i==n){
        return 0;
    }
    if(dp[i][buy]!=-1) return dp[i][buy];
    long profit = 0;
    if(buy){
        profit = max(maxprof(i+1, 0, val, n, dp) - val[i], maxprof(i+1, 1, val, n, dp));
        
    }
    else{
        profit = max(maxprof(i+1, 1, val, n, dp) + val[i], maxprof(i+1, 0, val, n, dp));
    
    }
    return dp[i][buy] = profit; 
}
```
`TC:O(n*2) SC:O(n*2 + (n+2))`  
**Bottom up**
```
long maxprof_bt(long *val, int n){
    vector<vector<long>> dp(n+1, vector<long>(2,0));
    // base case already handled
     for(int i=n-1; i>=0; i--){         
        for(int buy=0; buy<=1; buy++){
            long profit = 0;
            if(buy){
                profit = max(dp[i+1][0] - val[i], dp[i+1][1]);
            }
            else{
                profit = max(dp[i+1][1] + val[i], dp[i+1][0]);
            }
            dp[i][buy] = profit;
        }    
    }
    
    return dp[0][1];
}
```
`TC:O(n*2) SC:O(n*2)` 

**Space Optimization**
```
long maxprof_bt_spc(long *val, int n){
    vector<vector<long>> dp(n+1, vector<long>(2,0));
    vector<long> next(2,0);
    vector<long> curr(2,0);
    // base case already handled
     for(int i=n-1; i>=0; i--){         
        for(int buy=0; buy<=1; buy++){
            long profit = 0;
            if(buy){
                profit = max(next[0] - val[i], next[1]);
            }
            else{
                profit = max(next[1] + val[i], next[0]);
            }
            curr[buy] = profit;
        }
         next = curr;
    }
    
    return next[1];
}
```

`TC:O(n*2) SC:O(2)`  

---

####[29. Best time to buy and sell a stock III](https://www.codingninjas.com/codestudio/problems/buy-and-sell-stock_1071012?source=youtube&campaign=striver_dp_videos&utm_source=youtube&utm_medium=affiliate&utm_campaign=striver_dp_videos&leftPanelTab=1)  
The problem is similar to the previous but here we can buy and sell the stocks only 2 times.

**Approach**
1. In this case we will have one more parameter `allow` which will tell us if we are allowed the buy or sell the stocks on the particular day.
2. We call f(0,1,2) initially which means maxprof from 0 till n if we are allowed to buy 2 times.
3. we update the value of allow only when we sell the stock 
4. So if allowed and if buy = 1 we can either buy `f(i+1, 0, allow) - val[i]` or not buy `f(i+1, 1, allow)`
5. if buy=0 the we can either sell `f(i+1, 1 , allow-1) + val[i]` or not sell `f(i+1, 0, allow)`.

```
int maxprof(int i, int buy, int allow, vector<int> &prices, int n, vector<vector<vector<int>>> &dp){
    //base case
    if(i==n){
        return 0;
    }
    
    if(dp[i][buy][allow]!=-1) return dp[i][buy][allow];
    //main
    int profit = 0;
    if(allow){
        
        if(buy){
            profit = max( maxprof(i+1, 0, allow, prices, n, dp) - prices[i], maxprof(i+1, 1, allow, prices, n, dp));    
        }
        else{
            profit = max(maxprof(i+1, 1, allow-1, prices, n, dp) + prices[i], maxprof(i+1, 0, allow, prices, n, dp));
        }
    }
    return dp[i][buy][allow]  = profit;
}
```

---

#### [29. Length of the LIS](https://www.codingninjas.com/codestudio/problems/longest-increasing-subsequence_630459?source=youtube&campaign=striver_dp_videos&utm_source=youtube&utm_medium=affiliate&utm_campaign=striver_dp_videos&leftPanelTab=1)
There are 3 different approaches to it.
**Approach 1: Dynamic Programming (Take/Not Take)**
1. In this approach we represent our recurrence using two parameters `f(i,prev)` which means LIS from ind i to n when previous element in LIS was `arr[prev]`
2. If the prev is smaller than `arr[i]` then we have two options either to take `arr[i]` in our LIS or not take.
3. If the prev is greater than `arr[i]` then we have only one option i.e to not take `arr[i]`.

```
int lis(int i, int num, int arr[], int n, vector<vector<int>> &dp){
    // Gives run time error due to dp space of 10^10 which is not possible
    //base case
    if(i==n) return 0;
    if(dp[i][num+1]!=-1) return dp[i][num+1];
    int len=0;
    
    
    if(num==-1 || arr[i]>arr[num]){
        //pick
        len = 1 + lis(i+1, i, arr, n, dp);
    }
     len = max(len,lis(i+1, num, arr, n, dp));
     return dp[i][num+1] = len;
}
```
`TC:O(n^2)`  
`SC: O(n^2) + O(n)`  

**Approach 2: Iterative using LIS array**
1. We use array dp in which `dp[i]` represents the maxlen of LIS from ind 0 till i including `arr[i]`.
2. We also maintain prev indices to back track the LIS sequence. `back[i]` represents the previous element in LIS whose next element is `arr[i]`.
3. For each i from 0 to n we iterate prev from 0 till i-1 and check if prev element can be the prev element in LIS containting `arr[i]` i.e `arr[i] > arr[prev]` 
4. If yes then we check the current value of `dp[i]` if its smaller than `dp[prev] + 1` then we update it and set `back[i] = prev`
5. The final max element of the dp array is the answer.

```
int print_lis(int arr [], int n){
    // In case we want to print LIS we definitely require O(n^2) algo.
    // assume dp[i] is the length of longest increasing subsequence till i  including i
   // assume back[i] contains the index of previous element of LIS whose next element is arr[i]
    
   vector<int> dp(n, 1);
   vector<int> back(n);
    int maxi=0;
    int ind;
    for(int i=0; i<n; i++){
        back[i] = i;
        for(int j=0; j<i; j++){
            if(arr[j] < arr[i] && dp[i] < dp[j] + 1){
                dp[i] = dp[j] + 1;
                back[i] = j;
            }
            if(dp[i] > maxi){
                maxi = dp[i];
                ind = i;
            }
        }
        
    }
    vector<int> ans;
    while(ind!=back[ind]){
        ans.push_back(arr[ind]);
        ind = back[ind];
    }
    ans.push_back(arr[ind]);
    reverse(ans.begin(), ans.end());
//     for(auto it: ans) cout<<it<<" ";
//     cout<<endl;
    return maxi;   
}
```
`TC: O(n^2)` and `SC : O(n^2)`


**Approach 3: Using Binary Search**
1. This is not intuitive but easy
2. We mantain a new array say temp which for each element consist of possible lis. (Although as we are continously updating it, it doesnt give the final LIS)
3. For each ind 0 till n, we check if the last element in temp is smaller then `arr[ind]`
4. if yes then we just pushback `arr[ind]` to the temp arr
5. if not then we find the lowerbound of `arr[ind]` representing the element just greater than or equal to `arr[ind]` and we replace it with `arr[ind]`
6. The final size of temp array gives us the length of LIS.

```
int lis_bsearch(int arr[], int n){
    // This is the optimal nlogn solution using lowerbound, not intuitive but easy
    // inspired from previous solution
    vector<int> ans;
    for(int i=0; i<n; i++){
        if(i==0) ans.push_back(arr[i]);
        else{
            if(arr[i] > ans.back()) ans.push_back(arr[i]);
            else{
                int it = lower_bound(ans.begin(), ans.end(), arr[i]) - ans.begin();
                ans[it] = arr[i]; 
            }
        }
    }
    return ans.size();
}
```
`TC: O(nlogn)` and `SC: O(n)`
