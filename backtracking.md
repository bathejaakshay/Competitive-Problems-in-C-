#### [Combination Sum](https://leetcode.com/problems/combination-sum/)
Given an array of distinct integers candidates and a target integer target, return a list of all unique combinations of candidates where the chosen numbers sum to target. You may return the combinations in any order.
The same number may be chosen from candidates an unlimited number of times. Two combinations are unique if the frequency of at least one of the chosen numbers is different.  

![CombSum](https://github.com/bathejaakshay/Competitive-Problems-in-C-/blob/master/Images/combsum.png?raw=True)

**MainIdea:** 
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

---

#### [2. Finding All permutations of a string/array](https://www.codingninjas.com/codestudio/problems/758958?topList=striver-sde-sheet-problems&utm_source=striver&utm_medium=website&leftPanelTab=1)

**Approach - Backtracking with swapping**:
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

#### 3. Pattern for Finding all subsequences of an array.
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
