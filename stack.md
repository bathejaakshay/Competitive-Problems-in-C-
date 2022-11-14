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


**Approach-2 : Sliding Window using Priority queue O(nlogn)**
- push all elements into pq till we reach the window size
- once we reach find maxi
- if window size becomes greater than required then shrink window size and pop all out of bounds elements.
- As out of bounds elements can be smaller and be at lower level in pq. So be before setting maxi we always try to pop the out of bounds elements.

```
vector<int> slidingMaximum_pq(const vector<int> &A, int B){
    priority_queue<pair<int,int>> pq;
    vector<int> ans;
    int j=0;
    for(int i=0; i<A.size(); i++){
        pq.push({A[i], i});
        if(i-j+1 > B){
            j++;
        }
        while(pq.top().second < j) pq.pop();
        
        if(i-j+1 == B){
            ans.push_back(pq.top().first);
        }
        
    }
    return ans;
}
```
---

#### [5. Next Greater Element 2](https://leetcode.com/problems/next-greater-element-ii/)
Find next greater element of each element in a circular array i.e `next element of A[n-1] is A[0]`

**Approach**
1. Use the same logic as NGE1 but we need to traverse the array twice.
2. Once the monotonic stack is mantained after one traversal we use the same stack for the next traversal.
3. We do not need to mind about traversing through the same index in the second iteration as we will pop the same value as current index.
```
vector<int> nge2(vector<int> &nums){
stack<int> st;
    // 5 elements 5 * 2 = 10 9%5 = 4
    vector<int> ans(nums.size(), -1);
    int n = nums.size();
    for(int i=nums.size()*2-1; i>=0; i--){
        while(!st.empty() && st.top()<=nums[i%n]) st.pop();
        if(!st.empty()){
            ans[i%n] = st.top();
        }
        st.push(nums[i%n]);
        
    }
return ans;
}

```

#### [6. 907. Sum of Subarray Minimums - HARD](https://leetcode.com/problems/sum-of-subarray-minimums/)

**Approach PLE and NLE**: 
```
class Solution {
public:
    int sumSubarrayMins(vector<int>& arr) {
    // We maintain two arrays 
    // left and right where left[i] represents of i from previous less element and right[i] represents distance of i from next less element.
    // The total no of subarrays with ith element as min is equal to left[i] * right[i] ans their total cost is A[i] * left[i] *right[i], we find this for all elements and sum them up.
    int n = arr.size();
     vector<long long> left(n); // For what distance is the ith element is minimum in the left distance, so if there is no other element smaller than i in lhs then that means all the subarrays possible at lhs that includes i has smallest element as i. So we keep distance i by default;
        
        
    vector<long long> right(n); // similar for right we keep dist of i from end by default
        
    for(int i=0; i<n; i++){
        left[i] = i+1;
        right[i] = n-i;
    }
        
    stack<int> st1,st2;
    for(int i=0; i<arr.size(); i++){
        while(!st1.empty() && arr[st1.top()] > arr[i]){
            st1.pop();
        }
        if(!st1.empty()){

            left[i] = i - st1.top(); 
        }
        st1.push(i);
        
        
    }
        for(int i=arr.size()-1; i>=0; i--){
        // cout<<" i = "<<i<<endl;
        while(!st2.empty() && arr[st2.top()] >=arr[i]){ // Always remember to keep one bound to be tight and other to be loose, here bound for finding right is loose and for left is tight
            st2.pop();
        }
        if(!st2.empty()){
        // cout<<" i = "<<i<<" "<<arr[i]<<" nxt lesser = "<<arr[st2.top()]<<endl;
            right[i] = st2.top()-i; 
        }
        st2.push(i);
    }
    // for(int i=0; i<n; i++){
    //     cout<<" i = "<<i<<" left[ i ]= "<<left[i]<<" right[i] = "<<right[i]<<endl;
    // }
    int ans = 0;
    int mod = 1e9 +7;
    for(int i=0; i<n; i++){
        ans = (ans + (arr[i] * left[i] *right[i])%mod)%mod;
    }  
    return ans;
        
    
    }
};
```
---
#### [7. Asteroid Collision](https://leetcode.com/problems/asteroid-collision/)

We are given an array asteroids of integers representing asteroids in a row.  

For each asteroid, the absolute value represents its size, and the sign represents its direction (positive meaning right, negative meaning left). Each asteroid moves at the same speed.  

Find out the state of the asteroids after all collisions. If two asteroids meet, the smaller one will explode. If both are the same size, both will explode. Two asteroids moving in the same direction will never meet.  

```
Example
Input: asteroids = [10,2,-5]
Output: [10]
Explanation: The 2 and -5 collide resulting in -5. The 10 and -5 collide resulting in 10.
```

**Approach : Stack**
1. Push all the positive elements to the stack one by one
2. if the current element has a negative value then pop all the elements from the stack that are lesser than current one's magnitude
3. if the stack becomes empty then push current negative value to the answer vector. because for this particular element there will be no more collisions
4. Similairly do for the rest.

```
vector<int> astcoll(vector<int> &ast){
    stack<int> st;
    vector<int> ans;
    for(int i=0; i<ast.size(); i++){
        if(ast[i]<0){
        while(!st.empty() && ast[st.top()] < -ast[i]) {
            st.pop();
        }
        if(st.empty())
            ans.push_back(ast[i]);
        else if(ast[st.top()] == -ast[i]) st.pop();
        }
        else{
            st.push(i);
        }
    }
    int x = ans.size();
    while(!st.empty()){
        ans.push_back(ast[st.top()]);
        st.pop();
    }
    reverse(ans.begin()+x, ans.end());
    return ans;
}

class Solution {
public:
    vector<int> asteroidCollision(vector<int>& ast) 
```


---

#### [8. Sum of Subarray Ranges](https://leetcode.com/problems/sum-of-subarray-ranges/)  
**Approach : monotonic stack O(n)**  
Using the idea of following ques:
[Sum of subarray minimums](https://leetcode.com/problems/sum-of-subarray-minimums/)

We apply the same code twice, first to find `x =  sum of subarray minimums`  and then to find `y = sum of subarray maximums` then we get the final `result = y-x`.  
Instead of finding difference of max and min in each subarray and then accumulating that for each subarray, we sum up all the maximums and minimums and substract minimums from the maximums.  

Σ(max-min) = Σ(max) - Σ(min)

**Note: **  
While applying this code always remember to keep one bound to be loose (e.g <=) and other to be tight (e.g <) for computing left and right from stack.
```
long long usingstack(vector<int> &nums){
    stack<int> st1, st2;
    vector<long long> left(nums.size()), right(nums.size());
    long long res=0;
    for(int i=0; i<nums.size(); i++){
        left[i] = i+1;
        right[i] = nums.size()-i;
    }
    for(int i=0; i<nums.size(); i++){
        while(!st1.empty() && nums[st1.top()]>=nums[i] ){ 
            st1.pop();
        }
        if(!st1.empty()){
            left[i] = (long long) i-st1.top();
        }
        st1.push(i);
        
    }
    for(int i=nums.size()-1; i>=0; i--){
        while(!st2.empty() && nums[st2.top()]> nums[i]) st2.pop();
        if(!st2.empty()){
            right[i] = st2.top()-i;
        }
        st2.push(i);
    }
    
    for(int i=0; i<nums.size(); i++){
        res-=((long long)(nums[i] * left[i] * right[i]));
    }
    st1 = stack<int>();
    st2 = stack<int>();
    for(int i=0; i<nums.size(); i+=1){
        left[i] = i+1;
        right[i] = nums.size()-i;
    }
    
    for(int i=0; i<nums.size(); i++){
        while(!st1.empty()&& nums[st1.top()] <= nums[i]) st1.pop();
        if(!st1.empty()) left[i] = i-st1.top();
        st1.push(i);
    }   
    
    for(int i=nums.size()-1 ; i>=0; i--){
        while(!st2.empty() && nums[st2.top()] < nums[i]) st2.pop();
        if(!st2.empty()) right[i] = st2.top() - i;
        st2.push(i);
    }
    
    for(int i=0; i<nums.size(); i+=1){
        res+=((long long)(nums[i]*left[i]*right[i]));
    }
    return res;
    
}
```

---

#### [ Shortest Unsorted Continuous Subarray IMP](https://leetcode.com/problems/shortest-unsorted-continuous-subarray/description/)  
Given an integer array nums, you need to find one continuous subarray that if you only sort this subarray in ascending order, then the whole array will be sorted in ascending order.  

Return the shortest such subarray and output its length.  
**Approach**
1. Using monotonic stack
2. we use two traversal to find min start of the unsorted subarray and max end of unsorted subarray
3. for start we find previous smaller or equal and while popping previous greater elements compared to current we update start.
4. for end we traverse backwards and find next eq or greater and while popping smaller elements than current in the stack we update end.
5. finally if end-start>1 then return end-start+1 else 0

```
int findUnsortedSubarray(vector<int>& nums) {
        stack<int> st;
        int start = nums.size();
        int end = 0;
        int i;
        for( i=1;i<nums.size(); i++){
            if(nums[i]<nums[i-1]) break;
        }
        if(i==nums.size()) return 0;
        st.push(0);
        for(i=1; i<nums.size(); i++){
            while(!st.empty() && nums[st.top()] > nums[i]) {
                start  = min(start, st.top());
                st.pop();
                }
            st.push(i);
            
        }
        while(!st.empty()) st.pop();
        st.push(nums.size()-1);
        for(i=nums.size()-2; i>=0; i--){
            while(!st.empty() && nums[st.top()] < nums[i]) {
                end = max(end, st.top());
                st.pop();
                }
            
            st.push(i);
        }
        return (end-start <= 0) ? 0 : end-start+1;
    }
```


---

#### [Sum of min elements of all subarrays](https://www.geeksforgeeks.org/count-of-contiguous-subarrays-possible-for-every-index-by-including-the-element-at-that-index/)
**Approach : O(N)**

- For each element `i` we need to know no. of contigous elements strictly greater than `val[i]` before index `i`  and after index `i` say `left[i] and right[i]`.
- Now for element i the contribution to the sum would be `val[i] * (left[i]+1) * (right[i] + 1)`. `(left[i]+1) * (right[i] + 1)` are all subarrays that has `val[i]` as the min element.  
- Do this for all elements.
- We can perform this using monotonic stack. Find next smaller elements and for each index i the number of elements `"count"` greater than equal to `val[i]` after i would be index of next smaller element - current. so `right[i] = count`
- Similarily for `left[i]` we can compute

### Try to always store indices in the stack instead of actual values

```
int solve(int n, vector<int> &choco){
// Finding sum of min elements of all possible subarrays
// For each index find left[i] strictly contigous greater number after i + 1
// ans right[i] strick contigous greater number before i  + 1

stack<int> st;

vector<int> left(n), right(n);
// find prev smaller
for(int i=0; i<n; i++){
    while(!st.empty() && st.top() > choco[i]){
        st.pop();
    }
    if(st.empty()){
        left[i] = i+1;
    }
    else{
        left[i] = i-st.top();
    }
    st.push(choco[i]);
}
//find next smaller to get strictly greater elements 
while(!st.empty()) st.pop();
for(int i=n-1; i>=0; i--){
    while(!st.empty() && choco[st.top()] > choco[i]){
        st.pop();
    }
    // we know that st.top is prev smaller element to i so all elements between st.top + 1 to i are greater than i
    // That is what we wanted
    if(st.empty()){
        right[i] = n-i;
    }
    else{
        right[i] = st.top()-i;
    }
    st.push(i);
}

int sum=0;

for(int i=0; i<n; i++){
    sum+=(choco[i]*left[i]*right[i]);
}
return sum;

}

```
---

#### [Second Greatest Element in Array / Next Greatest IV - Hard](https://leetcode.com/contest/biweekly-contest-90/problems/next-greater-element-iv/)

For each element in the array find their second next greater element in the array.  
**Approach O(nlogn)**
- Firstly we find next greater element
- Now we find for each element `A[i]` , all the elements for who `A[i]` is next greater.
- Now we maintain min heap
- for each element `A[i]` we check all top elements in min heap that are lesser than `A[i]` and make `A[i]` their second greater.
- Now push all elements for whom `A[i]` is next greater into the pq. We are pushing cuz we know `A[i]` is their first greater now whatever comes next element that is greater than pq.top is their second greater.

```
vector<int> secondGreaterElement3(vector<int> &nums){
    stack<int> st;
    int n = nums.size();
    vector<int> ng(n,n);
    for(int i=n-1; i>=0; i--){
        while(!st.empty() && nums[st.top()] <= nums[i]){
            st.pop();
        }
        if(!st.empty()){
            ng[i] = st.top();
        }
        st.push(i);
    }
    unordered_map<int,vector<int>> mp;
    for(int i=0; i<ng.size(); i++){
        if(ng[i]<n)
            mp[ng[i]].push_back(i);
    }
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>> > q;
    vector<int> sng(n,-1);
    for(int i=0; i<nums.size(); i++){
        while(!q.empty() && q.top().first < nums[i]){
            sng[q.top().second] = nums[i];
            q.pop();
        }
        if(!mp[i].empty()){
            for(int &it: mp[i]){
                q.push({nums[it],it});
            }
        }
    }
    return  sng;
}

```
---
