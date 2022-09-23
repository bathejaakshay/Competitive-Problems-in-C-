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

#### [5. Minimum Window String - HARD](https://www.interviewbit.com/old/problems/window-string/)  
Given two strings A and B, find the minimum sized substr of A which has all chars of B.  
**Approach**
1. We use two pointer approach, i and j
2. We use i to acquire chars and j to release chars.
3. We first create a frequency map for the target String B.
4. Now we start acquiring chars in string A until the match_count is equal to B.len
5. match_count signifies the length of current matching string that matches string B (in terms of chars and not order).
6. once we have acquired all required chars in B (represented by match_count), we start releasing chars from the starting using j, to obtain the smallest substr that has matchcount still equal to B.len
7. We keep on doing these two steps till end and obtain final ans. 
```
string minwin(string a, string b){
    
    unordered_map<char,int> src;
    unordered_map<char, int> tgt;
    
    for(int i=0; i<b.length(); i++){
        tgt[b[i]]++;
    }
    
    int i=0,j=0;
    int match_count=0; // count all the required chars that match b
    int tgtlen=b.length();
    int ans=INT_MAX;
    int ans_i=-1,ans_j=-1;
    while(i<a.length()){
        //Step 1: acquire till match_count not equal to strlen
        while(i<a.length() && match_count<tgtlen){
            src[a[i]]++;
            if(src[a[i]] <= tgt[a[i]]){
                match_count++;
            }
            i++;
            
        }
        
        //Step 2: update ans and release while match_count is same as tgtlen
        while(j<i && match_count==tgtlen){
            
            if(ans > i-j){
                ans = i-j;
                ans_j = j;
            }
            if(src[a[j]]>0)
                src[a[j]]--;
            if(src[a[j]] < tgt[a[j]]){
                match_count--;
            }
            j++;
        }
          
    }
    return ans==INT_MAX?"":a.substr(ans_j,ans); 
    
    
    
}
string Solution::minWindow(string a, string b) {
    
    return minwin(a,b);
}

```
---
#### [6. Longest Substr without repeat](https://www.interviewbit.com/old/problems/longest-substring-without-repeat/)  
**Approach**  
1. We keep track of the chars and its index
2. We also mantain the keyword `l` representing the start of the ans string.
3. whenever a repeating char occurs we find ans and update l if l is lesser than the previous occurence of curr char.
4. we also update map `mp[A[i]]=i`

```
int longsubstr(string A){
    unordered_map<char,int> mp;
    // int count=0;
    int maxi=0;
    int l=0;
    for(int i=0; i<A.length(); i++){
        if(mp.find(A[i]) != mp.end()){
            if(mp[A[i]] >= l){ // We dont want to change l to any index lesser than l itself as if we do so we will loose info of repeating chars that were before l.
            maxi = max(maxi,i-l);
            l = mp[A[i]]+1;
            }
        }
        maxi = max(maxi, i-l+1);
        mp[A[i]] = i;
    }
    return maxi;
}

```

#### [7. Number of subarrays with arithmetic mean k]
Given a subarray NUMS and value k, find number of subarrays in nums that have AM = k.
**Approach**
1. This problem simply gets converted into the number of subarrays sums=0
2. The AM of 4 number say a,b,c,d = k i.e a+b+c+d = 4k, or (a-k) + (b-k) + (c-k) + (d-k) = 0 Now again if some subarray is there that has AM = k then the sum of their numbers - len of subarray \*(k) will be zero.
3. So consider we have updated our nums with each value at index i = `nums[i] - k`
4. Now we just need to find no. of subarray sum 0

```
int solve(vector<int> &nums, int k){
	// number of subarrays with sum = 0 

	/*
		Basically a + b + c + d = 4k i.e a+b+c+d - 4k =0 now when does sum - (i+1)k becomes zero
		This problem gets converted into a number of subarray sum =0 problem 
	*/


	int sum = 0;
	unordered_map<int,int> mp;
	// for(int i=0; i<nums.size(); i++) nums[i] -= k;
		int count=0;
	for(int i=0; i<nums.size(); i++){
		sum+=(nums[i]-k);
		if(sum == 0){
			count++;
		}
		if(mp.find(sum)!=mp.end()){
			count+=(mp[sum]);
		}
		cout<<"sum = "<<sum<<endl;
		mp[sum]++;
	}
	return count;
}
```
---
