#### [1. Largest Permuatation after B swtiches](https://www.interviewbit.com/old/problems/largest-permutation/)

**Problem Statement:**  
Given an integer array A of size N consisting of unique integers from 1 to N. You can swap any two integers atmost B times.  
Return the largest lexicographical value array that can be created by executing atmost B swaps.  
Problem Constraints  
1 <= N <= 10^6  
1 <= B <= 10^9  

E.g: N = [2,4,1,3] B = 2  
step 1: 4 2 1 3  
step 2: 4 3 1 2  

output: 4 3 1 2  

**Naive Approach**  
For each element Find maximum in its right array and swap places. T(n) = O(n^2)

**Smart Approach**  
1. We Check whether element at ith pos is value N-i i.e the value that should have been there. If not the swap it with N-i valued index.  
2. This can be efficiently done using unordered_map

```
vector<int> Solution::solve(vector<int> &A, int B) {
    
    unordered_map<int,int> mp;
    for(int i=0; i<A.size() ;i++){
        mp[A[i]] = i;
    }
    int n=A.size();
    for(int i=0;i<A.size() && B;i++){
        if(A[i]!=A.size()-i){
            swap(A[i],A[mp[A.size()-i]]);
            mp[A[mp[A.size()-i]]] = mp[A.size()-i];
            mp[A[i]] = i;
            B--;
        }
    }
    return A;
}

```

---

#### [2. Largest Number in an array](https://leetcode.com/problems/largest-number/)
**Problem:**  
Given a list of non-negative integers nums, arrange them such that they form the largest number and return it.  
Since the result may be very large, so you need to return a string instead of an integer.  
**Main Idea:**  
1. Sort the array in a way that concatenation two numbers is always greater

```
bool comparator(int a,int b){
    string x=to_string(a);
    string y=to_string(b);
    if(x+y > y+x) return true;
    return false;
}
class Solution {
public:
    string largestNumber(vector<int>& nums) {
        
        if(nums.size()==1){
            string ans =  to_string(nums[0]);
            return ans;
        }
        int i;
        for(i=0;i<nums.size();i++){
            if(nums[i]>0) break;
        }
        if(i==nums.size()) return "0"; \\Edge case when array contains only zeros
        sort(nums.begin(),nums.end(),comparator);
        string ans =to_string(nums[0]);
        for(i=1;i<nums.size();i++){
            string curr = to_string(nums[i]);
                ans = ans+curr;
        }
        return ans;
    }
};
```
---

#### [3. Smallest Distinct Subsequence of a string](https://leetcode.com/problems/remove-duplicate-letters/)

**Problem:**  
Given a string s, remove duplicate letters so that every letter appears once and only once. You must make sure your result is the smallest in lexicographical order among all possible results.  

**Example 1:**  
Input: s = "bcabc"  
Output: "abc"  

**Example 2:**  
Input: s = "cbacdcbc"  
Output: "acdb"  
 **Constraints:**  
1 <= s.length <= 104  
s consists of lowercase English letters.  

**Approach**
1. For each char keep track of its last index in lastidx array
2. Maintain a bool array seen[] to represent if that char has been seen already or not.
3. We also maintain a stack to keep record of smallest distinct subsequence
4. Now iterate from index 0 to str.length()
5. In each iteration check if char at i is already seen. If yes then no need to process it just continue.
6. Else pop out all the chars in stack and mark them unseen which are lexicographically greater than curr char i.e str[i] and they have duplicate at some later position than i.
7. Now push the current char and mark it as seen.

```

class Solution {
public:
    string removeDuplicateLetters(string s) {
        
        //lastidx to track the last index of each char
        vector<int> lastidx(26,-1); 
        for(int i=0;i<s.length();i++) lastidx[s[i] - 'a']=i;
        
        //bitmask to see if we have seen that char or not
        vector<bool> seen(26,false);
        
        //stack to keep distinct smallest subsequence 
        stack<char> st;
        
        for(int i=0; i<s.length(); i++){
            if(seen[s[i]-'a'] == false){
                while(!st.empty() && st.top()>s[i] && i<lastidx[st.top()-'a']){
                    seen[st.top()-'a'] = false;
                    st.pop();
                }
            st.push(s[i]);
            seen[s[i]-'a']=true;    
            }
            
        }
        string ans="";
        while(!st.empty()){
            ans = st.top() + ans;
            st.pop();
        }
         return ans;
    }
    
    
   
};
```
---

#### [4 Meeting Rooms required](https://www.interviewbit.com/old/problems/meeting-rooms/)
**Problem**  
Given an 2D integer array A of size N x 2 denoting time intervals of different meetings.  
Where:  
A[i][0] = start time of the ith meeting.  
A[i][1] = end time of the ith meeting.  
Find the minimum number of conference rooms required so that all meetings can be done.


**Approach:**
1. Sort the intervals by their start time
2. Use a minheap to keep record of the least end time for any allocated room
3. Now for each interval loop at the top element of the min heap if current room's start time is later than already allocated room then that means we do not require extra room as we can allocate that particular room to that. So we remove that end time from min heap so that other rooms do not use that room.
4. If it clashes with the current room then it is intuitive that all other allocated room also clash hence we increase the number of rooms required.


```
int Solution::solve(vector<vector<int> > &A) {

    sort(A.begin(),A.end());
    int count=0;
    int mini=INT_MIN;
    priority_queue<int, vector<int>, greater<int>> pq;
    for(int i=0;i<A.size();i++){
        int start = A[i][0], end = A[i][1];
        if(start>=mini && !pq.empty()){
            pq.pop();
        }
        else{
            count++;
        }
        pq.push(end);
        mini = pq.top();
    }
    return count;
}
```

---

#### [5 Minimum number of arrows to burst balloons](https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/)
There are some spherical balloons taped onto a flat wall that represents the XY-plane. The balloons are represented as a 2D integer array points where `points[i] = [xstart, xend]` denotes a balloon whose horizontal diameter stretches between xstart and xend. You do not know the exact y-coordinates of the balloons.  
Arrows can be shot up directly vertically (in the positive y-direction) from different points along the x-axis. A balloon with xstart and xend is burst by an arrow shot at x if `xstart <= x <= xend.` There is no limit to the number of arrows that can be shot. A shot arrow keeps traveling up infinitely, bursting any balloons in its path.  
Given the array points, return the **minimum** number of arrows that must be shot to burst all balloons.  
```
Example 1:  
Input: points = [[10,16],[2,8],[1,6],[7,12]]  
Output: 2  
Explanation: The balloons can be burst by 2 arrows:
- Shoot an arrow at x = 6, bursting the balloons [2,8] and [1,6].
- Shoot an arrow at x = 11, bursting the balloons [10,16] and [7,12].
```

**Main Idea**
1. The main case to think of while designing the solution is the following example: [[1,10],[2,5],[7,9]]
2. We want to start from the greatest starting time i.e the last interval.
3. Put its Start time in min heap and keep moving backwards till their ending time is greater than pq.top() time.
4. Then do pq.pop() count++ and pq.push() current interval.
5. After do this till starting we count the remaining intervals in the priority queue by popping them.

```
bool compare(vector<int> &a, vector<int> &b){
    if(a[0]>b[0]){
        return true;
    }
    else if(a[0] == b[0]){
        if(a[1]>b[1]){
            return true;
        }
        else return false;
    }
    return false;
}
class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        sort(points.begin(),points.end(), compare );
        priority_queue<int, vector<int> , greater<int>> pq;
        int count=0;
        for(int i=0;i<points.size();i++){
            if(pq.empty()){
                pq.push(points[i][0]);
                
            }
            else{
                while(!pq.empty()&&pq.top()>points[i][1]){
                    count++;
                    pq.pop();
                }
                if(pq.empty()){
                    pq.push(points[i][0]);
                }
                
            }
        }
        while(!pq.empty()){
            count++;
            pq.pop();
        }
        return count;
    }
};
```
