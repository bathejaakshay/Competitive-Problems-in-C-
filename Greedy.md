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

---

#### [6 Distribute Candy (Tricky)](https://www.interviewbit.com/old/problems/distribute-candy/)
There are N children standing in a line. Each child is assigned a rating value.

You are giving candies to these children subjected to the following requirements:  
`1. Each child must have at least one candy.`      
`2. Children with a higher rating get more candies than their neighbors.`  
What is the minimum candies you must give?  

Input Format:  
`The first and the only argument contains N integers in an array A.`

Example:  
Input 2:  
    A = [1, 5, 2, 1]  

Output 2:  
    7  
    
Explanation 2:  
    Candies given = [1, 3, 2, 1]  
    
**Main Idea:**
1. The sorting approach doesnt pass all the test cases hence we use a trick for O(n) sol.
2. We parse through the vector twice once from Left to right and right to left respt & maintain two arrays left and right.
3. We check if the previous neighbour is smaller if yes then increment neighbours value by 1 and assign to curr.
4. Finally we traverse the left and right arrays and the max of them.

```

int Solution::candy(vector<int> &A) {

    vector<int> left(A.size(),1); //Initializing with 1 candies as that's the least amount
    for(int i=1;i<left.size();i++){
        if(A[i] > A[i-1]) left[i] = left[i-1]+1;  // Comparing for all the left neighbours
    }
    
    vector<int> right(A.size(),1); //Intializaing with 1 candy
    for(int i=A.size()-2;i>=0;i--){
        if(A[i] > A[i+1]) right[i] = right[i+1]+1; //Comparing for all the right neighbours
    
    }
    
    int count=0;
    for(int i=0;i<A.size();i++){
        count+=(max(left[i],right[i])); //Keeping the max value computed by Left and right neighbour
        // count+=(ans[i]);
    }
    return count;
    
}

```

---

#### [7, Reconstruction of queue by height - **GOOD Problem**](https://leetcode.com/problems/queue-reconstruction-by-height/)  
**Problem:**  
You are given an array of people, people, which are the attributes of some people in a queue (not necessarily in order). Each `people[i] = [h_i, k_i]` represents the ith person of height `h_i` with exactly `k_i` other people in front who have a height greater than or equal to h_i.  
Reconstruct and return the queue that is represented by the input array people. The returned queue should be formatted as an array queue, where `queue[j] = [hj, kj]` is the attributes of the jth person in the queue (`queue[0]` is the person at the front of the queue).  

Basically we need to rearrange the people array such that each person can come in its correct position to satisfy the height order mentioned in their second attribute.  
**Example:** 
```
Input: people = [[7,0],[4,4],[7,1],[5,0],[6,1],[5,2]]
Output: [[5,0],[7,0],[5,2],[6,1],[4,4],[7,1]]
Explanation:
Person 0 has height 5 with no other people taller or the same height in front.
Person 1 has height 7 with no other people taller or the same height in front.
Person 2 has height 5 with two persons taller or the same height in front, which is person 0 and 1.
Person 3 has height 6 with one person taller or the same height in front, which is person 1.
Person 4 has height 4 with four people taller or the same height in front, which are people 0, 1, 2, and 3.
Person 5 has height 7 with one person taller or the same height in front, which is person 1.
Hence [[5,0],[7,0],[5,2],[6,1],[4,4],[7,1]] is the reconstructed queue.
```

**Approach:**
1. We will start from the smallest height guy and keep fixing its smallest possible position.
2. For e.g in the above example we start with height h=4 and we know that 4 person of more or equal height will come in front of it some leave 4 vacant places and fixed the 5th vacant space for it.
3. We will keep doing it till last element. We maintain a bool array to represent if the pos is vacant or not.
4. Also while sorting initially maintain the order in a way that for equal height people we can assign the guy with higher second argument as we would need to fix its position first.

```
bool comparator(const vector<int> &a, const vector<int> &b){
    if(a[0]<b[0]){
        return true;
    }
    else if(a[0]==b[0]){
        return a[1]>b[1];
    }
    else return false;
}
class Solution {
public:
    /*
    7 4 7 5 6 5
    0 4 1 0 1 2 //Req
    1 5 1 4 2 4 //Possible 5 elements have height >= 4 but we need only 4
    5-0 7-0 5-2 6-1 4-4 7-1
    
    */
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        sort(people.begin(),people.end(),comparator);
        
        vector<vector<int>> ans (people.size(), vector<int>(2));
        vector<bool> occ(people.size(),false);
        for(int i=0;i<people.size();i++){
            int count=0;
            int req = people[i][1];
            int j=0;
            for(j=0;j<occ.size();j++){
                if(occ[j]==false){
                    count++;
                    if (req+1==count){
                        break;
                    }
                }
            }
            ans[j][0] = people[i][0];
            ans[j][1] = people[i][1];
            occ[j] = true;
        }
        return ans;
    }
};
```

#### [8. Majority Element](https://www.interviewbit.com/old/problems/majority-element/)
**Problem** For an unordered array output the element which occurs more than floor(n/2) time where n is the size of the array.
**Approach:**
1. There are many approaches including hashmap. But the most efficient is to use a count variable and majority index variable to keep indx of current majority element.
2. Now iterate through the array and see if the elements are same as majority element if yes then inc the count else dec
3. if the count==0 then change the majority index to current variable.

```
int majority_element(const vector<int> &A){
    
    int majority_idx = 0,count,i;
    for(count=1,i=1;i<A.size();i++){
        if(A[i] == A[majority_idx]){
            count++;
            }
         else{
            count--;
         }
         if(count==0){
         count=1;
         majority_idx = i;
         }
    }
return A[majority_idx];
}
```
---

#### [9. Minimum Intervals to remove to make all other non overlapping](https://leetcode.com/problems/non-overlapping-intervals/)
**Approach:**
1. Always remember to use priority queue (max heap) on end time for such ques.
2. Firstly sort by start time.
3. Now traverse from left to right. 
4. If the interval overlaps with q.top() (q.top() contains max end time for currently seen non overlapping intervals), then see if q.top() is also greater than current interval's end time. if yes then remove it and count++. Do it till no such interval is there in priority queue.The idea is to always keep an interval with lesser end time in case of overlapping.
5. If no overlapping then push current interval else if current interval is still overlapping and has bigger end time also then dont push it and do count++

```
int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end());
        int count=0;
        priority_queue<int> q;
        for(int i=0;i<intervals.size();i++){
            if(q.empty()){
                q.push(intervals[i][1]);
                
            }
            else{
                while(!q.empty()&&q.top()>intervals[i][0]&&q.top() > intervals[i][1]){
                    q.pop();
                    count++;
                }
                if(q.empty()||q.top()<=intervals[i][0]){
                    q.push(intervals[i][1]);
                }
                else if(!q.empty()&&q.top()>intervals[i][0] && q.top() <= intervals[i][1]){
                    count++;
                }
            }
        }
        return count;
    }
```
---
#### [10. Goodland electricity](https://www.hackerrank.com/challenges/pylons/problem)
Given n cities, we need to distribute electricity to every city. Given an array arr representing the possiblilty of setting up a powerplant in ith city as {0 or 1}. Find the minimum no. of powerplant required if distribution range of each power plant is i-k+1 to i+k-1.

**Approach Greedy : Tricky**
1. Always try to fit the powerplant in the last possible location.
2. Starting from i=0 and loc = i+k-1 i.e the last idx of current window.
3. `if(arr[loc] == 1)` i.e a powerplant needs to be setup here. 
4. So count++ and now we know this plant will further cover k-1 cities ahead of it.
5. So we directly jump the i to loc + k. and loc = i+k-1 and we repeat step 3.
6. In step 3 if `arr[loc] == 0` then we need to traverse back in the current window i.e `[ loc to i -k +1]` by doing loc-- and repeat step 3.
7. If in step 6 we do not find any 1 in the window  `[ loc to loc -k +1]` then that means powerplant allocation is not possible. i.e if loc < i -k + 1 (previous wind reached) or loc<0 then we return -1;
 
```
int pylon (int k, vector<int> &arr){
    
    int i=0, count=0;
    int loc = i+k-1;
    while(i<arr.size()){
        if(arr[loc] == 1){
            count+=1;
            i = loc+k;
            loc = i+k-1;
            if(loc>arr.size()){
                loc = arr.size()-1;
            }
        }
        else{
            loc--;
            if(loc < i - k  + 1 || loc<0) // gone into previous area as no 1 was found 
                return -1;
        }
    }

```
`TC: O(N)`

---

## Looks DP But is Greedy Pattern

#### Find the lexicographically smallest order of N numbers such that the total of N numbers <= Threshold value

#### [11. Tushar's Birthday Bombs](https://www.interviewbit.com/old/problems/tushars-birthday-bombs/)  
Given an arr of strength of n friends of tushar and tushar capacity to  bear kicks. Find the lexicographically smallest indices of friends such that no. of kicks is maximum within tushar's capacity.  
**Approach : Greedy**
1. Firstly compute the size of ans then we will look for the lexicographically smallest ans
2. We can compute the size of the ans by dividing the Capacity by the min element in the strength arr and values will be the index of this strength
3. Now lets say the min element was at ith index.
4. `Curr capacity = A[i] * cap/A[i]`
5. Now we know that if there exist lexicographically smaller ans then its indices must be from 0 to i-1
6. Now start from index 0 we will check how many index 0 can replace ith index in the ans.
7. It can replace index i at loc 0 of ans if `curr_cap - A[i] + A[replacer or 0] <= cap`. Remember A friend can kick infinite number of times.
8. Simiarly we do this for rest of the elements till i-1

```

vector<int> Solution::solve(int A, vector<int> &B) {

    
    int x = min_element(B.begin(), B.end()) - B.begin();
    int si = A/B[x];
    vector<int> ans(si, x);
    int k=0;
    int capi = B[x]*si;
    // cout<<capi<<endl;
    for(int i=0; i<=x-1; i++){
        while(capi - B[x] + B[i] <= A && k<ans.size()){
            ans[k] = i;
            capi = capi - B[x] + B[i];
            k++;
        }
        
    }
    return ans;
}

```
