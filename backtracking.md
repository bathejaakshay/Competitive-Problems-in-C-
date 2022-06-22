#### [1. Combination Sum](https://leetcode.com/problems/combination-sum/)
Given an array of distinct integers candidates and a target integer target, return a list of all unique combinations of candidates where the chosen numbers sum to target. You may return the combinations in any order.
The same number may be chosen from candidates an unlimited number of times. Two combinations are unique if the frequency of at least one of the chosen numbers is different.  

![CombSum](https://github.com/bathejaakshay/Competitive-Problems-in-C-/blob/master/Images/combsum.png?raw=True)

**Approach 1**: **Not Best** : **TC:O(n^n)** 
1. For any sych combinations and permutations where things can repeat, we use backtracking. We try one solution if it aint good we go back and try another.
2. In a recurrsion we use a for loop from currIndex till end. (we use currIndex as we need only unique comb, we already have all req comb with previous Index hence keep record of the currIndex)
3. we push_back our current value before calling the function. If the function returns we pop_back(). (To maintain consistency)
4. If at any moment sum of currvector is same as target we append it in the ans.

```
 void comb_sum(vector<int>&candidates, int target, vector<int> &currans, vector<vector<int>> &ans, int &sum, int currindex){
        if(sum == target){
            ans.push_back(currans);
            return;
        }
        if(sum>target){
            return;
        }
        for(int i=currindex;i<candidates.size();i++){
            
            currans.push_back(candidates[i]);
            sum+=(candidates[i]);
            comb_sum(candidates, target, currans, ans, sum,i);
            sum-=(candidates[i]);
            currans.pop_back();
        }
        return;
    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<int> curr_sum;
        vector<vector<int>> ans;
        int sum=0;
        comb_sum(candidates, target, curr_sum, ans, sum,0);
        return ans;
    }
};
```
**Approach 2:**
1. This is a very simple approach. Just Following the pattern of subseq sum.
2. This is a question of pick and not pick index i.
3. We start from index 0 and call recursion for picking index and not picking index.
4. The difference in subseq prob and this prob is that in this prob we can pick a index any number of times. So in the recursive call of picking i, we again pass i as i is again a candidate to be picked.

**TC:O(2^t * k)**
```
 void comb_sum(vector<int> &candidates, int index, int target, vector<int> &curr_ans,vector<vector<int>> &ans){
        if(index == candidates.size()) {
            if(target == 0){
                ans.push_back(curr_ans);
            }
            return;
        }
        
        //Pick the element at index i
        if(candidates[index] <=target){
            curr_ans.push_back(candidates[index]);
            comb_sum(candidates, index, target-candidates[index], curr_ans, ans);
            curr_ans.pop_back();
        }
        
        //Donot pick the element at index i
        comb_sum(candidates, index+1, target, curr_ans, ans);
        return;
        
        
    }

```
---
#### [1. ii Combination Sum 2](https://leetcode.com/problems/combination-sum-ii/discuss/2167453/C%2B%2B-Simple-Basic-Backtracking-approach.)
**Approach:**
1. Simple approach as subseq sum. The Difference is that array contains duplicates and we need unique combination whose sum is target.
2. For this sort the array initially.
3. Now picking the element is same.
4. While not picking the element at index i make sure you do not pick any of the next continous elements which have same value as i's.

```
void comb_sum(vector<int> &candidates, int index, int target, vector<int> &curr_ans, vector<vector<int>> &ans){
        if(index >= candidates.size()){
            if(target==0){
                ans.push_back(curr_ans);
            }
            return;
        }
        
        //Pick the element at current index
        
        if(candidates[index]<=target){
            curr_ans.push_back(candidates[index]);
            comb_sum(candidates, index+1, target-candidates[index], curr_ans, ans);
            curr_ans.pop_back();
        }
        
        //Do not pick the element at current index and do dont pick all the next contigous elements which have same value as index's.
        
        index++;
        while(index<candidates.size()&& candidates[index-1] == candidates[index]) index++;
        comb_sum(candidates, index, target, curr_ans, ans);
        return;
    }
```

#### [2. Finding All permutations of a string/array](https://www.codingninjas.com/codestudio/problems/758958?topList=striver-sde-sheet-problems&utm_source=striver&utm_medium=website&leftPanelTab=1)

**Approach 1- Using Backtracking and visited array**
1. This is a common pattern approach, in which we buil up permutations level by level. At first level all permutations start with each possible element.
2. At second level we find all possible permuations at pos 2 with given first position. and so on.

```
void perm(vector<int> &nums, vector<bool> &visited, vector<int> &curr_ans, vector<vector<int>> &ans){
        if(curr_ans.size() == nums.size()){
            ans.push_back(curr_ans);
            return;
        }
        for(int i=0; i<nums.size(); i++){
            if(!visited[i]){
                visited[i] =1;
                curr_ans.push_back(nums[i]);
                perm(nums,visited,curr_ans,ans);
                curr_ans.pop_back();
                visited[i] =0;
            }
        }
        
        return;
        
    }
```
`TC : n! function calls * n time of each function call -> n!*n`

**Approach 2- Backtracking with swapping**:
1. The intution is we fix an index and start swapping it with all other indices values ahead of it. and this is done n times;
2. So for first time  we swap first index it with n numbers (including itself)
3. For second time we swap second index with n-1 numbers  (including itself, leaving number at first index as it is fixed)
4. For third time we swap third index with n-2 numbers
5. Little tricky but interesting approach

`T.c : n!*n`

```
void permute(string &s,vector<string> & ans, int index){
    if(index == s.length()) {
        ans.push_back(s);
    }
    else{
        for(int i=index; i<s.length(); i++){
            swap(s[index],s[i]);
            permute(s, ans, index+1);
            swap(s[index],s[i]);
        }
    }
}
vector<string> findPermutations(string &s) {
    // Write your code here.
    vector<string> ans;
    permute(s,ans, 0);
    return ans;
}
```

---

#### 3. (i) Pattern for Finding all subsequences of an array.
**Approach:**
1. We use recursion with backtracking.
2. For each element of an array we have two choices either to take it or not in our ans.
3. Starting from zero index we make two recurvisive funciton calls to next index , one including element at index 0 and another excluding.
4. This is the pattern to remember.


```
class Solution{
public:
	void subseq(int i, vector<int> &arr, vector<int> &curr_ans, vector<vector<int>> &ans){
		if(i>=arr.size()) {
			ans.push_back(curr_ans);
			return;
		}

		curr_ans.push_back(arr[i]);   
		subseq(i+1, arr, curr_ans, ans); // subseqs containing element arr[i]
		curr_ans.pop_back();
		subseq(i+1, arr, curr_ans, ans); // subseqs not containing element arr[i]
	}
};

int main(int argc, char const *argv[])
{
	/* code */
	int n;
	cin>>n;
	vector<int> q(n);
	for(int i=0;i<n;i++){
		cin>>q[i];
	}

	vector<int> curr_ans;
	vector<vector<int>> ans;

	Solution s;

	s.subseq(0, q, curr_ans, ans);
	for (int i = 0; i < ans.size(); ++i)
	{
		/* code */
		for(int j=0; j<ans[i].size(); j++){
			cout<<ans[i][j]<<" "; 
		}
		cout<<endl;
	}

	return 0;
}

```
#### 3. (ii) Pattern for printing anyone 1 subsequence with sum k
**Approach**
1. For printing 1 we can return boolean values to keep record of the recursive calls i.e if they found the subseq or not.

```
bool subseq(int i, vector<int> &arr, vector<int> &curr_ans, vector<vector<int>> &ans, int sum, int req){
		if(i>=arr.size()) {
			ans.push_back(curr_ans);
			if(sum == req) {
				for(int x:curr_ans) cout<<x<<" ";
					cout<<endl;
				return true;
			}
			return false;
		}

		// Pick i in the subsequence
		curr_ans.push_back(arr[i]);
		sum+=(arr[i]);
		if(subseq(i+1, arr, curr_ans, ans,sum, req)) return true;
		sum-=(arr[i]);
		curr_ans.pop_back();

		// Not pick i
		if(subseq(i+1, arr, curr_ans, ans,sum, req)) return true;

		return false;
	}
};

```
#### 3 (iii) Pattern of printing Count of all subsequences with sum k
**Approach**
1. In this pattern in the base case we return 1 when sum==k 
2. We sum up all the returned values for the recursive calls and return that value as ans.

```
int subseq(int i, vector<int> &arr, int sum, int req){
		if(i>=arr.size()) {
			if(sum == req) {
				return 1;
			}
			return 0;
		}

		// Pick i in the subsequence
		// curr_ans.push_back(arr[i]);
		sum+=(arr[i]);
		int l = subseq(i+1, arr, sum, req);
		sum-=(arr[i]);
		// curr_ans.pop_back();

		// Not pick i
		int r = subseq(i+1, arr, sum, req);

		return l+r;
	}
};
```

---

#### 4. String Transfer Using 2 operations.
**Problem** There are 3 string A, B, C. Initially B and C are empty and only A has characters (only lowercased alphabets). Can perform the following operations,
```
1. Remove first character from A and append to B
2. Remove last character from B and append to C
```  
We need to perform the operation and make string A and B empty and only C should contain the characters. Find the lexicographically smallest string C that can be made by performing the operations.

**Approach :**
1. We will be generating all the strings possible using only these two operations.
2. We will start with index 0.
3. For each index we will try pushing a[i] at each location of B and popping the rest to c. 
4. We do this recursively for i=0 to n-1
5. This is a brute force approach T.C O(n^n)

```
main: string a <- input, b = "", c = "";
void rep(string &a, string b, string c, int i, string &ans){
	if(i>=a.length()) {
		while(!b.empty()){
			c+=(b.back());
			b.pop_back();
		}
		if(c.size() == a.size()){
			if(ans == "" || ans>c ){
				ans = c;
			}
			cout<<c<<endl;
		}

		return;
	}
	b.push_back(a[i]);
	rep(a, b, c, i+1, ans);
	b.pop_back();
	while(!b.empty()){
		c += b.back();
		b.pop_back();
		b.push_back(a[i]);
		rep(a,b,c,i+1, ans);
		b.pop_back();		
	}

	return;
	
}

```

---

#### [4. Subsets || - Pattern](https://leetcode.com/problems/subsets-ii/)
**Problem:** Need to find (unique) powerset of an array in O(2^n) TC and SC. 
**Approach**
1. Sort the array.
2. We will recursively find all the subsets.
3. at level 0 of the recurrsion tree we will get empty subset, at level 1 subsets of length 1, at level 2 subsets of length two and so on..
4. for each recursive call we will run a loop from index to n-1 we skip the elements with same values if previously recurrsed for that value.
5. Very common pattern. Its like we are picking and not picking a particular element in the array in each recurrsive call.

```


class Solution {
public:
    // At First level we obtain all subsets of length 1
    // At Second level of rec tree we obtain all subsets of length 2.
    void subdup(vector<int> &nums, int index, vector<int> &curr_ans, vector<vector<int>> &ans){
        ans.push_back(curr_ans);
        for(int i=index; i<nums.size(); i++){
            if(i!=index && nums[i]==nums[i-1]) continue;
            curr_ans.push_back(nums[i]);
            subdup(nums, i+1, curr_ans, ans);
            curr_ans.pop_back();
        }
        
    }
    
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<int> curr_ans;
        vector<vector<int>> ans;
        sort(nums.begin(), nums.end());
        subdup(nums, 0, curr_ans, ans);
        return ans;
        
    }
};

```

---

#### [5. N Queens](https://leetcode.com/problems/n-queens/)

**Approach**
1. The approach is simple backtracking.
2. We each col c we traverse each ith row and see if we can place the queen there. If yes then do same for col i+1. 
3. The issafe block can have three O(n) loops checking for two diagonals and one row. Instead we can maintain a vector as a map we consists key as the diagnoal number or row number and value as if it is marked (marked means there is a queen in that digonal or row).
4. Left Upper diagonal is represented by i+j, Right Upper diagonals are represented by i+(n-j), rows are represented as i;

```
bool isSafe(vector<string> &board, int i, int j, int n, vector<int> &updiag, vector<int> &downdiag, vector<int> &rowmap)
{ 
   
    if(updiag[i+j]==1 || downdiag[i+n-j]==1 || rowmap[i]==1){
        return false;
    }
    return true;
}
void solveQ(vector<string> &board, int n, int col, vector<int> &updiag, vector<int> &downdiag, vector<int> &rowmap, vector<vector<string>> &ans){
    if(col >= n) {
        ans.push_back(board);
        return;
        }
    for(int i=0; i<n; i++){
        if(isSafe(board, i, col, n, updiag, downdiag, rowmap)){
            board[i][col]='Q';
            updiag[i+col]=1;
            downdiag[i+n-col]=1;
            rowmap[i]=1;
            solveQ(board, n, col+1, updiag, downdiag, rowmap, ans);
            
            updiag[i+col]=0;
            downdiag[i+n-col]=0;
            rowmap[i]=0;
            board[i][col]='.';
        }
    }
    return;
}

class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
    string s="";
    for(int i=0;i<n;i++) s+='.';
    vector<string> board(n,s);
    vector<vector<string>> ans;
    vector<int> updiag(2*n,0);
    vector<int> downdiag(2*n,0);
    vector<int> rowmap(n,0);
    solveQ(board, n, 0, updiag, downdiag, rowmap, ans);
    return ans;
    }
};
```

---

#### [6. Sudoku](https://leetcode.com/problems/sudoku-solver/submissions/)
```
bool isSafe(vector<vector<char>> &board, int i, int j, char s){
    int r = 3*(i/3);
    int c = 3*(j/3);
    for(int a=0; a<9; a++){
        if(board[i][a] == s || board[a][j] == s || board[r+a/3][c+a%3] == s) return false;
    }
    return true;
}

bool sudoku(vector<vector<char>> &board){
    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            if(board[i][j] == '.'){
                for(int x=1;x<=9;x++){
                    char s='0'+x;
                    if(isSafe(board, i,j,s)){   
                        board[i][j] = s;
                        if(sudoku(board)) return true;
                        board[i][j] = '.';
                    }
                    if(x==9) return false;
                    
                }
                
            }
        }
    }
    return true;
}

```
