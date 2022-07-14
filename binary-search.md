#### [Find First and Last Position of Element in Sorted Array](https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/)
**Approach**
1. We will implement lowerbound and upperbound functions to find the same.
2. The lower_bound function gives us the index of first occurrence of the item or the index of the element just lesser than the item. If the item is lesser than the first element then we return -1 or in real case arr.end()
3. Similarly the upper_bound function gives us the index of the element just greater than the given item. If item is the last element then we get n as index or in real case arr.end()

```
num = [1,2,2,5,8]
item = 1
lower_bound : 0 
upperbound : 1

item = 2
lower_bound = 1
upper_bound = 3

item = 0
lower_bound = -1 (num.end())
upper_bound = 0

item=6
lower_bound = 3
upper_bound = 4

item = 8
lower_bound = 4
upper_bound = 5  (num.end())
```

```
int lower_bound(vector<int> &nums, int i, int j, int item){
    if(i>j) return i; // we return i after seeing that a[index] just before than i is just lesser than item. 
    int mid = (i+j)>>1;
    if(nums[mid]>=item){
        return lower_bound(nums, i, mid-1, item);
    }
    return lower_bound(nums, mid+1, j, item);
    
}
int upper_bound(vector<int> &nums, int i, int j, int item){
    if(i>j) return i; // we return i after seeing that a[index] just before i is the last value <= item.
    int mid = (i+j)>>1;
    if(nums[mid]<=item) upper_bound(nums, mid+1, j, item);
    return upper_bound(nums, i, mid-1, item);
}

vector<int> searchRange(vector<int>& nums, int target) {
        int i = lower_bound(nums, 0, nums.size()-1, target);
        int j = upper_bound(nums, 0, nums.size()-1, target);
        cout<<i<<" "<<j<<endl;
        if(i==nums.size() || nums[i]!=target) return {-1,-1};
        return {i, j-1};
    }
};
```

---

#### [2. Median of a row wise sorted matrix](https://www.interviewbit.com/problems/matrix-median)
**Approach:Brute Force (O(m*nlog(m*n)))**
1. convert 2d into 1d , sort and find median
2. It is given that the number of total elements is odd (So no confusion for find middle)

**Approach : binary search O(log(10^9)*(mlogn))**
1. This is a little tricky approach.
2. We set search space as `l=0` and `h=1e9`
3. We find mid and number of elements <=mid in each row, say k
4. Now if `K <= (n*m/2)` then that means K is not the median and the median exists right to it. so l=mid+1
5. else h = mid-1

```
int upper_bound(vector<int> &arr, int item){

	int i=0, j=arr.size()-1;
	while(i<=j){
		int mid = (i+j)>>1;
		if(arr[mid] <= item){
			i = mid+1;
		}
		else{
			j = mid-1; 
		}
	}
	return i;
}

int Solution::findMedian(vector<vector<int> > &mat) {
long long l=1, h=1e9;
int m = mat.size();
int n = mat[0].size();
	while(l<=h){
		long long mid = (l+h)>>1;

		long long ele = 0;
		for(int i=0; i<m; i++){
			ele+=(upper_bound(mat[i] ,mid));
		}
		if(ele <= (m*n)/2){
			l = mid+1;
		}
		else{
			h = mid-1;
		}
	}
    return l;

}
```

---

#### [3. Find peak Element](https://leetcode.com/problems/find-peak-element/submissions/)  
**Approach: Binary Search**
1. if mid is on down slope then peak exist to the left to it
2. else to the right of it.

```
int fp(vector<int> &nums, int i, int j){
    if(i>j){
        return i;
    }
    int  mid = (i+j)>>1;
    if(mid == nums.size()-1 || nums[mid+1] < nums[mid]){
        return fp(nums, i, mid-1);
    }
    return fp(nums, mid+1, j);
}

```

---
