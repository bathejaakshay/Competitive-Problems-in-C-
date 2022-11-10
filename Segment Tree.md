## Segment Trees
Used for range queries e.g

- Find sum of subarray i to j (log n) time
- Find the max of the values represented by the elements in range i to j. O(log n) time
- Find the min of the values represented by the elements in the range i to j. O(log n) time

It follows the same data structure as heap. 
i.e The root is stored at i=0 in the arr, left child is stored at `2*i+1` and right child at `2*i+2`

If the range that we are searching is from 0 to n then we need an array of size atmax `4*n` and atleast `2*pow(2,ceil(logn))`.
The size keyword of the segment tree say size is the such that size >= n and size is the minimum possible power of 2 e.g if n=6 then size is 8 and actual size of the seg tree is `2*8`. 


#### [1. Longest Increasing Subsequence II](https://leetcode.com/contest/weekly-contest-310/problems/longest-increasing-subsequence-ii/)

You are given an integer array nums and an integer k. 

Find the longest subsequence of nums that meets the following requirements:  

- The subsequence is strictly increasing and 
- The difference between adjacent elements in the subsequence is at most k.

Return the length of the longest subsequence that meets the requirements.  

A subsequence is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.  


**Solution : The code is well commented**
```
struct segment_tree
{
	vector<int> maxi; // this is our segment tree which tells us the maximum of segments.
	int size;
	/* when the size of total range is known then we can use intitialize function 
		It will intialize the size to the closest power of 2 for n e.g if n=6 then size = 8;
	*/
	void init(int n){
		size=1;
		while(size<n) size*=2; //It is proved that size of segment tree wont be greater than 4*n so SC = O(4N)

		maxi.assign(2*size+1,0); //intitalized seg_tree.
        
        // The size variable should be floor(log2n) of the total size of the segment tree.
	}

	void build(vector<int> &a, int x, int lx, int rx){
		// if we have all the values of the elements to be present at leaf node precomputed, then we can simply build the whole segment tree in O(n) time.
		// This is good because if we insert one by one using `set` fucntion then it will take O(nlogn) time.

		if(lx==rx){ // leaf node
			if(lx<a.size()){ // if leaf node is in the required max range.
				maxi[lx] = a[x];
			}
			return;
		}
		int mid = (lx+rx)>>1;
		build(a, 2*x+1, lx, mid);
		build(a, 2*x+2, mid+1, rx);
		a[x] = max(a[2*x+1], a[2*x+2]);
		return;
	}

	void build(vector<int> &a){
		build(a, 0, 0, size);
		return;
	}

	// This set method is actually used to set the element in the segment tree and update all its parents.
	void set(int i, int v, int x, int lx, int rx){
		if(rx==lx){
			maxi[x] = v;
			return;
		}

		int mid = (lx + rx)/2;
		if(i<=mid)
			set(i, v, 2*x+1, lx, mid); // its actually lx and mid-1 but we as we are taking tight left and loose right bound so we write lx and mid.
		else
			set(i, v, 2*x+2, mid+1, rx); // this is actually mid and rx-1

		maxi[x] = max(maxi[2*x+1], maxi[2*x+2]); 

	}

	// set a value v for an element i of some range. Note that we cant just simply assign the val to the index
	// We have to go to the leaf node and then update its parent nodes.
	void set(int i, int v){
		//The user will actually use this function
		// we call the set function from the root node where x = 0, lx=0 and rx = size
		set(i, v, 0, 0, size);
	}

	int max_element(int x, int lx, int rx, int l, int r){
		if(lx>r || rx<l) return INT_MIN; // current segment or window is completely out of the queried window
		if(lx >= l && rx<=r){ // current window is completely inside the queried window  
			return maxi[x];  
		}
		


		//Overlapping window/segment

		int mid = (lx + rx)/2;
		int left_max = max_element(2*x+1, lx, mid, l, r);
		int right_max = max_element(2*x+2, mid+1, rx, l, r);

		return max(left_max, right_max);
	}
	int max_element(int l, int r){
		return max_element(0, 0, size, l, r);
	}


	
};


class Solution {
public:
    int lengthOfLIS(vector<int>& nums, int k) {
        vector<int> lis(nums.size(), 1);
        int ans = 1;

        int maxi = *max_element(nums.begin(), nums.end());

        segment_tree st;
        st.init(maxi+k+1);

        for(int i=nums.size()-1; i>=0; i--){
        	int l = nums[i]+1;
            int r = nums[i]+k;
            int max_val = st.max_element(l,r);
            ans = max(ans, max_val+1);
            st.set(nums[i], max_val+1);
        }
        return ans;
    }
};

```

---

#### [Total Cost to Hire K Workers](https://leetcode.com/problems/total-cost-to-hire-k-workers/description/)
You are given a 0-indexed integer array costs where costs[i] is the cost of hiring the ith worker.  

You are also given two integers k and candidates. We want to hire exactly k workers according to the following rules:  

You will run k sessions and hire exactly one worker in each session.  
In each hiring session, choose the worker with the lowest cost from either the first candidates workers or the last candidates workers. Break the tie by the smallest index.  
For example, if costs = [3,2,7,7,1,2] and candidates = 2, then in the first hiring session, we will choose the 4th worker because they have the lowest cost [3,2,7,7,1,2].  
In the second hiring session, we will choose 1st worker because they have the same lowest cost as 4th worker but they have the smallest index [3,2,7,7,2]. Please note that the indexing may be changed in the process.  
If there are fewer than candidates workers remaining, choose the worker with the lowest cost among them. Break the tie by the smallest index.  
A worker can only be chosen once.  
Return the total cost to hire exactly k workers.  

**Approach: Segment Tree MLE**  
- K times we need to find min of (0,i) and (n-j,n) and add it to cost.
- At every iteration we update the smallest value picked up with INT_MAX and change the range to (0,i+1) if it comes from left other wise (j-1,n)
```
class SegmentTree{
    // In segment Tree each node contains sum, max, min of some range [tl,tr]
    // The range of leaf elements is just one element.

    // This is a min segment tree.
    public:
    int cap;
    int *t;
    int *posi; // This is to store the actual positions of leaf nodes in the segment tree. e.g arr [1,10,20,33] , suppose val 10 is stored at node V i.e 5, t[5] = 10, we also store its corresponding location in arr, posi[5] = 1.
    // We use posi to retrieve the location of val in arr and update its val in segment tree. (For simple queries just use *t and ignore *posi)
    SegmentTree(){

    }
    SegmentTree(int n){
        cap = n;
        int size=1;
		posi = new int[4*n];
        t = new int[4*n];
    }
    void build(vector<int> a, int v, int tl, int tr){
        // This takes O(N) time.
        // V is the node in the segment tree e.g V=1 is the root node
        // tl and tr is the range of node V e.g range of root is 0 to n-1

        
        if(tl == tr){
        // once tl==tr it means the range contains only one element e.g (0) or (1) or (n) and its node in segment tree is V, v is the location in segment tree where the ans to this range lies.
            t[v] = a[tl];
            posi[v] = tl;
        }
        else{
            // Build the tree in top down manner.
            int tm = (tl+tr)>>1;

            build(a, 2*v, tl, tm);
            
            build(a, 2*v+1, tm+1, tr);
            

            // While back tracking set the val of curr t[v] = min of its left and right child. and set posi accordingly.
            if(t[2*v] <= t[2*v+1]){
                t[v] = t[2*v];
                posi[v] = posi[2*v];
            }
            else{
                t[v] = t[2*v+1];
                posi[v] = posi[2*v+1];
            }
        }
    }

    pair<int,int> find_min(int v, int tl , int tr, int l, int r){
        // To find min in the range [l,r], we perform divide and conquer.
        // Three cases are possible, either the range matches the current range.
        // If not then we find mid and get two intervals [l,mid] and [mid+1,r]
        // If it left range doesnt overlap with current range and we keep on diving it until l becomes <= r where we stop and return INT_MAX.
        // If it overlaps then we go into the overlapping interval and find the value of that interval.
        
        if(l>r) return {INT_MAX,0};
        if(tl == l && tr == r){
            return {t[v], posi[v]};
        }
        int tm = (tl+tr)>>1;
        auto min1 = find_min(2*v, tl, tm, l, min(r,tm));
        auto min2 = find_min(2*v+1, tm+1, tr, max(l, tm+1), r);
        
        if(min1.first<=min2.first){
            return min1;
        }
        return min2;

    }

    void update(int v, int tl, int tr, int pos, int new_val){
        // V corresponds to the current location in the segment tree whose interval is tl,tr

        // We want to update the val at pos in given arr and update its val.
        // So we first find its location v in the segment tree and update all its parents recursively.
        if(tl == tr) {
            t[v] = new_val;
            posi[v] = tl;         
                     
             }
        else {
            int tm = (tl+tr)>>1;
            if(pos<=tm){
                update(2*v, tl, tm, pos, new_val);
            }
            else update(2*v+1, tm+1, tr, pos, new_val);
            // while tracing back after value is updated, update all the min values along the path
            if(t[2*v] <= t[2*v+1]){
                t[v] = t[2*v];
                posi[v] = posi[2*v];
            }
            else{
                t[v] = t[2*v+1];
                posi[v] = posi[2*v+1];
            }
            
        }
        

    }
};

long long totcost(vector<int>& costs, int k, int candidates){
    SegmentTree t(costs.size());
        t.build(costs, 1, 0, costs.size()-1);
        long long cost=0;
        int n = costs.size();
        int l1=0, h1=candidates-1;
        int l2=costs.size()-candidates , h2 = costs.size()-1;
        while(k>0){
            auto min1 = t.find_min(1, 0, n-1, l1, h1);
            auto min2 = t.find_min(1, 0, n-1, l2, h2);
            if(min1.first <= min2.first){
                t.update(1, 0, n-1, min1.second, INT_MAX);
                cost+=((long long)(min1.first));
                h1 = min(h1+1, n-1);
            }
            else{
                t.update(1, 0, n-1, min2.second, INT_MAX);
                cost+=((long long)(min2.first));
                l2 = max(0, l2-1);
            }
            k--;
            
        }
        return cost;
   
}

```

---

**Approach : Priority queue**  
-  As we saw in segment tree after each update of minimum value we either increase our range from left or right.
-  as the query range is monotonically increasing or decreasing and it is not like (0,4), (1,2) (0,3), we can simply apply Priority queue.
-  first add first candidates and last candidate int the pq with ditinction between first candidates and last candidates elements.
-  We also maintain visited arr to not visit a node more than once.
-  Now for each K we sum up the min element and push more elements accoring to the min element being from  left part or right part.

```
ong long totalCost(vector<int>& costs, int k, int candidates) {
            int n = costs.size(), i=0, j= n-1;

            priority_queue<pair<int,pair<int,int>>, vector<pair<int, pair<int,int>>>, greater<pair<int,pair<int,int>>> > pq;

            vector<int> visited(n,0);
            while(i<candidates){

                if(!visited[i]){
                    visited[i]=1;
                    pq.push({costs[i], {i,1}});

                }
                i++;
            }

            while(j>=n-candidates){
                if(!visited[j]){
                    visited[j]=1;
                    pq.push({costs[j], {j,2}});
                }
                j--;
            }
    long long cost=0;

    while(k>0){
        k--;

        cost+=pq.top().first;
        auto it = pq.top();
        pq.pop();
        if(i<=j){
            if(it.second.second==1){
                if(!visited[i]){
                    visited[i] =1;
                    pq.push({costs[i],{i,1}});
                    i++;
                }
            }
            else {
                if(!visited[j]){
                    visited[j] =1;
                    pq.push({costs[j],{j,2}});
                    j--;
                 }
            }
        }
        
        }
    return cost;
    }
```
