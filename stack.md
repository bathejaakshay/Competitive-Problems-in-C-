#### [1. Daily Temperatures](https://leetcode.com/problems/daily-temperatures/)
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

#### [2. Designing a minstack with all O(i) operations, push, pop, top and min_element](https://www.interviewbit.com/old/problems/min-stack/)
**Approach**  
1. Quite simple, just maintain two stacks one for actual elements and another for the min element till ith idx.
2. Now while push we push element to the actual elements stack and push the min of existing mini and current element to the another stack.
3. Rememeber to pop_back from both stacks in case of pop.

```
vector <int> dat;
vector <int> mint;
int top;
MinStack::MinStack() {

    dat.clear();
    mint.clear();
    
}

void MinStack::push(int x) {

    dat.push_back(x);
    if(!mint.empty()){
        mint.push_back(min(mint.back(),x)); // good approach for each index store the minimum till then
    }
    else{
        mint.push_back(x);
    }
}

void MinStack::pop() {
    if(!dat.empty() && !mint.empty()){
    dat.pop_back();
    mint.pop_back();
    }
}

int MinStack::top() {
    
    int top;
    if(!dat.empty())
        top= dat.back();
    else 
        top = -1;
    return top;
}

int MinStack::getMin() {
    int mini;
    if(!mint.empty())
        mini = mint.back();
    else
        mini = -1;
    return mini;
}


```

---

## Monotonic Stack

---

#### [3. Next Greater Element](https://leetcode.com/problems/next-greater-element-i/)
**Approach**
1. For each element we need to find the next greater element just at its right side.
2. for this we start from the right side and start maintaining stack which just contains of the elements in the increasing order.
3. so for each element we pop the elements which are lesser than itself in the stack as they can not be the next greater elements for all the elements left to the current element.
4. if at any moment stack is empty for an element then that means all the elements right to it are smaller so nge is -1;

```
vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        vector<int> nge(nums2.size(), -1);
        stack<int> st;
        unordered_map<int,int> mp;
        for(int i=nums2.size()-1;  i>=0; i--){
            mp[nums2[i]] = i;
            while(!st.empty() && st.top() <= nums2[i]) st.pop();
            if(st.empty()) nge[i] = -1;
            else{
                nge[i] = st.top();
                
            }
            st.push(nums2[i]);
            
        }
        vector<int> ans;
        for(auto &i : nums1) {
            ans.push_back(nge[mp[i]]);
        }
        return ans;
        
    }
```
`TC: O(n)  + O(n)` it is not O(n^2), surely we are popping elements for each index, but total elements pushed and poped is N so total TC is O(2n)  

**Another ques**  
1. Another ques that is generally made out of nge is finding nge in a circular list.
2. The trick is simple we run our for loop for 2n-1 time instead of n, we find nge using `i%n` operator. We apply the same algo.
3. But we only record our ans for `0<=i<n`.

---


#### [4 Sliding Window Maximum](https://www.interviewbit.com/problems/sliding-window-maximum/)
Given a window of size B find all the max in each window of size B.  
**Approach: Dequeue**  
1. We use dequeue here. Variant of Next Great element, just that we maintain a decreasing order in our dequeue.
2. Hypothetically think of the dequeue of size B (Window size), so that whenever an element at front is out of the window we need to pop it.
3. For each element `i` try inserting it in the dequeue.
4. Check if element at front is still valid in the window.
5. push element `i` in the back while maintaining decreasing order i.e pop elements smaller than itself as for future windows they cant be the greatest.
6. now for each window (when i>=B-1) our maximum will always be at front of the dequeue

```
void insert_dq (deque <int> &dq , const vector<int> &A ,int i,int B){
    while(!dq.empty() && i - dq.front() >= B){
        dq.pop_front();
    }
    if(dq.empty()){
        dq.push_back(i);
    }
    else{
        while(!dq.empty() && A[dq.back()] < A[i]){
            dq.pop_back();
        }
        dq.push_back(i);
    }
}
vector<int> Solution::slidingMaximum(const vector<int> &A, int B) {
    vector<int> C;
    deque<int> dq;
    for(int i=0;i<A.size();i++){
        insert_dq(dq,A,i,B);
        if(i>B-2)
            C.push_back(A[dq.front()]);
    }
    return C;
}

```

`TC: O(n) + O(n)`
---

