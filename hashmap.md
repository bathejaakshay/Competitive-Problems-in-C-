#### [1. K difference pairs](https://leetcode.com/problems/k-diff-pairs-in-an-array/submissions/)
```
class Solution {
public:
    int findPairs(vector<int>& nums, int k) {
        set<pair<int,int>> st;
        sort(nums.begin(),nums.end()); // To maintain the order of elements in array while inserting pairs
        unordered_map<int,int> mp;
        for(int i=0;i<nums.size(); i++){
            
            if(mp.find(nums[i]-k)!=mp.end()){   // Dont check abs-difference cuz the array is sorted and hence the paired element of current element must be seen before itself. i.e i<j  and a[j] - a[i] = k then a[i] will always be there in mp while computing for a[j].
                st.insert(pair(nums[i],nums[i]-k)); // To keep unique pairs
            }
            
            mp[nums[i]]=1;
            
        }
        
    return st.size();
    }
};
```

---

#### [2. Subarrays with given XOR](https://www.interviewbit.com/old/problems/subarray-with-given-xor/)

**Approach**
1. Same logic as prefix sum.
2. intialize xor = 0;
3. for each element compute the xor : `xor^=A[i]`
4. Now if this is equal to required Xor B then count++
5. else we find if `xor^B` exist in map i.e suppose two subarrays 0 to i whose exor is x and i+1 to j whose exor is B, Now currently we have `xor` from say o to j
6. Now if we do xor^B then exor for i+1 to j zeros out and what remains is x i.e exor 0 to i. So we increment the count by the same.

```
int Solution::solve(vector<int> &A, int B) {

    unordered_map<int,int> mp;
    int x = 0, ans=0;
    for(int i=0;i<A.size();i++){
            x^=A[i];
            
            if(x == B){
                ans++;
            }
            
            if(mp.find(x^B) != mp.end()){
                ans+=(mp[x^B]);
            }
            mp[x]++;
        }
    return ans;
    
}
    
```

---

#### [3. Points on the straight line](https://www.interviewbit.com/old/problems/points-on-the-straight-line/)
**Approach**  
1. For each point (x1,y1) we look at each other point (x2,y2), we compute is they are the exact same points (will just add to the ans), or if they lie of the vertical line i.e (x1 = x2 and y1!=y2) (We do this as we can find slope of vertical line)
2. Else we find the slope and increment its counter in the map and find max points in the same line for the current point (x1,y1)
3. We also check if vertical points are larger than current max.
4. After all iterations for current point 
5. we find final max corresponding to all the points. maxp = max(maxp, curr_max + overlap + 1)

```
int Solution::maxPoints(vector<int> &A, vector<int> &B) {
    unordered_map<double,int> m;
    int maxp=0;
    int cur,overlap,vertical;
    int n=A.size();
    for(int i=0;i<n;i++)
    {   cur=overlap=vertical=0;
        for(int j=i+1;j<n;j++)
        {   if(A[i]==A[j] && B[i]==B[j])
            {   overlap++;
            }
            else if(A[i]==A[j])
            {   vertical++;
            }
            else
            {   double ydif=(double)B[j]-(double)B[i];
                double xdif=(double)A[j]-(double)A[i];
                double slope=ydif/xdif;
                m[slope]++;
                cur=max(cur,m[slope]);
            }
            cur=max(cur,vertical);
        }
        maxp=max(maxp,cur+overlap+1);
        m.clear();
    }
    return maxp;
}

```
`TC : O(n^2)`
---

#### [4. Subarray with B odd Numbers](https://www.interviewbit.com/old/problems/subarray-with-b-odd-numbers/)
**Approach**  
1. Either convert array into binary with 0 representing even and 1 representing odd. Now just find number of subarrays with sum B
2. Or we can perform prefix directly by counting number of odds within each array. Logic is same as in point 1.

```
int odd(vector<int> &A, int B){
    int count =0 ;
    unordered_map<int,int> mp;
    int ans=0;
    for(int i=0; i<A.size(); i++){
        if(A[i]%2!=0){
            count++;
        }
        if(count == B){
            ans++;
        }
        if(count>=B){
            if(mp.find(count-B)!=mp.end()){
                ans+=mp[count-B];
            }
        }
        mp[count]++;
        
    }
    return ans;
}

```  
By converting array to binary.
```
int odd(vector<int> &A, B){
unordered_map<int, int> map;
    int curr_sum = 0; //prefix sum
    int count = 0; //count of all subarrays

    for(int i = 0; i<A.size(); i++){
        if(A[i] % 2 == 0) A[i] = 0;
        else A[i] = 1; // odd nos become 1. Now subarrays with sum = B should be found
    }
    
    for(int i = 0; i<A.size(); i++){
        curr_sum += A[i];
        if(curr_sum == B) count += 1;
        if(map.find(curr_sum - B) != map.end()){
            count += map[curr_sum - B];
        }
        map[curr_sum]++;
    }
    return count;
    

}
```

---
