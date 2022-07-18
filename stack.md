####[1. Daily Temperatures](https://leetcode.com/problems/daily-temperatures/)
Given an array of integers `temperatures` represents the daily temperatures, return an array `answer` such that `answer[i]` is the number of days you have to wait after the `ith` day to get a warmer temperature. If there is no future day for which this is possible, keep `answer[i] == 0` instead.
**Approach: Using Stack O(n)**
1. We create a stack of pairs
2. push the first element with its index to the stack
3. Now for i = 1 to n-1, we compare the element at current index with the stack top
4. If the current element is smaller than the stack top, we just push the element with its index to the stack.
5. Else we pop the elements of the stack top and find their corresponding distance to the current element.
6. Finally we push the current element to the stack.

TC: At worst case each element is pushed once and pop once from the array : O(2N) in case of array with descreasing elements.
```
vector<int> dailyTemperatures(vector<int>& temp) {
       
       stack<pair<int,int>> s;
        s.push({temp[0],0});
        vector<int> ans(temp.size(),0);
        if(temp.size()==1) return {0};
        for(int i=1; i<temp.size(); i++){
            if(s.top().first >= temp[i]){
                s.push({temp[i],i});
            }
            else{
                while(!s.empty()&& s.top().first < temp[i]){
                    auto it = s.top();
                    s.pop();
                    ans[it.second] = i - it.second;
                }
                s.push({temp[i],i});
            }
        }
        return ans;
    }
```

---
