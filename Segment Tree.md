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
