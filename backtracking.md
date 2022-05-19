#### [Combination Sum](https://leetcode.com/problems/combination-sum/)
Given an array of distinct integers candidates and a target integer target, return a list of all unique combinations of candidates where the chosen numbers sum to target. You may return the combinations in any order.
The same number may be chosen from candidates an unlimited number of times. Two combinations are unique if the frequency of at least one of the chosen numbers is different.  

![CombSum]()

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
