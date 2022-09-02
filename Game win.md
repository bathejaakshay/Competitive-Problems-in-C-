#### [1. Predict the Winner](https://leetcode.com/problems/predict-the-winner/)  
You are given an integer array nums. Two players are playing a game with this array: player 1 and player 2.  

Player 1 and player 2 take turns, with player 1 starting first. Both players start the game with a score of 0.  
At each turn, the player takes one of the numbers from either end of the array (i.e., nums[0] or nums[nums.length - 1]) which reduces the size of the array by 1.  
The player adds the chosen number to their score. The game ends when there are no more elements in the array.  

Return true if Player 1 can win the game. If the scores of both players are equal, then player 1 is still the winner, and you should also return true.  
You may assume that both players are playing optimally.  
```
Example:
Input: nums = [1,5,233,7]
Output: true
Explanation: Player 1 first chooses 1. Then player 2 has to choose between 5 and 7. No matter which number player 2 choose, player 1 can choose 233.
Finally, player 1 has more score (234) than player 2 (12), so you need to return True representing player1 can win.
```
There are two dp approaches, both O(n^2) time complexity
In this ques we just want ans in true or false i.e if the player 1 wins or not. so the following approach will work.  
But if we need to compute the amount of winning coins collected by player 1 then we follow approach2.   
**Approach 1**  
  - At each step we find how much more score will the current player will get than another player given it takes either first coin or last coin.
  - As we start with player 1, the ans will sum to the score that player 1 gets more  than player 2.
  - If this score is <0 then player 1 loses else it wins.

```
int max_candies(int i, int j,  vector<int> &candies, vector<vector<int>> &dp){
	if(i == j){
		
		return dp[i][j]= candies[i];
	}
	if(i==j-1) {
		return dp[i][j] = max(candies[i]-candies[j],candies[j] - candies[i]);

	}
	if(dp[i][j]!=-1)
       return dp[i][j];
	int left = max_candies(i+1, j, candies, dp);
	int right = max_candies(i, j-1, candies, dp);

	return dp[i][j] = max(candies[i]-left, candies[j]-right);
}
```

**Approach2**  
1. In case we need to find the actual value that players collected optimally we have to return a pair which consist of current sum of amount collected by each player.
2. Remember to use this step i.e to return both amount using pairs whenever we want to collect coins at alternate levels.
3. We use separate functions for both the players. But we use the same dp for both the functions as the calls for i and j will always be unique.

```
vector<int> max_candies_jerry(int i, int j, vector<int> &candies, vector<vector<vector<int>>> &dp);
vector<int> max_candies_tom(int i, int j,  vector<int> &candies, vector<vector<vector<int>>> &dp){
	if(i == j){
		return {candies[i],0};
	}
	if(i==j-1) {
		return {max(candies[i],candies[j]),min(candies[i], candies[j])};

	}
	if(dp[i][j][0]!=-1 && dp[i][j][1]!=-1) return dp[i][j];
	auto left = max_candies_jerry(i+1, j, candies, dp);
	auto right = max_candies_jerry(i, j-1, candies, dp);

	if(left[0]+candies[i] > right[0] + candies[j]){
		left[0]+=(candies[i]);
		return dp[i][j] = left;
	}
	right[0]+=(candies[j]);
	return dp[i][j] = right;

}
vector<int> max_candies_jerry(int i, int j,vector<int> &candies, vector<vector<vector<int>>> &dp){
	if(i == j){
		return {0, candies[i]};
	}
	if(i==j-1) {
		return {min(candies[i], candies[j]), max(candies[i], candies[j])};

	}
	if(dp[i][j][0]!=-1 && dp[i][j][1]!=-1) return dp[i][j];
	auto left = max_candies_tom(i+1, j, candies, dp);
	auto right = max_candies_tom(i, j-1, candies, dp);

	if(left[1]+candies[i] > right[1] + candies[j]){
		left[1]+=(candies[i]);
		return dp[i][j] = left;
	}
	right[1]+=(candies[j]);
	return dp[i][j] = right;	
}
```

---
