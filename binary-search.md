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

#### [4. Finding element in the sorted rotated array](https://leetcode.com/problems/search-in-rotated-sorted-array/)
**Approach - 1**
1. Firstly find the element after which the elements are inserted in rotated manner i.e in the array all the elements i> ind -> `a[i]<a[ind]`
2. This is done using modified bsearch in which we find the down slope.
3. If no such element exist then the array is not rotated and we can simply apply bsearch to whole array
4. else we need to check if required item exist in first subarray or second and apply the b_search likewise.

```
int b_search(vector<int>& nums, int i, int j, int item){
        if(i > j) return -1; 
        int mid = (i+j)/2;
        if(nums[mid] == item) return mid;
            if(nums[mid]<item){
                return b_search(nums, mid+1, j, item);
            }
            else{
                return b_search(nums, i, mid-1, item);
            }
        
    }
    int get_pivot(vector<int> &nums, int i, int j, int item){
        if(i>j) return -1;
        int mid = (i+j)/2;
        if(mid == nums.size()-1){
            return -1;
        }
        if(nums[mid] > nums[mid+1]){
            return mid; 
        }
        else{
            if(nums[mid] < nums[nums.size()-1]){
                return get_pivot(nums, i, mid-1, item);
            }
            else{
                return get_pivot(nums, mid+1, j, item);
            }
        }
            
    }
    int search(vector<int>& nums, int target) {
        if(nums.size()==1){
            if(nums[0]==target) return 0;
            else return -1;
        }
        int pivot = get_pivot(nums, 0, nums.size()-1, target);
        if (pivot==-1){
            return b_search(nums, 0, nums.size()-1,target);
        }
        else{
             if(target<=nums[pivot] && target>=nums[0]){
                return b_search(nums,0,pivot, target);
            }
            else{
                return b_search(nums, pivot+1,nums.size()-1,target);
            }
        }
    }
};

```

**Approach 2:**
1. Instead of finding pivot first and then applying bsearch we can do both side by side in a way
2. We first find mid and check if first half is sorted : if yes then we check if item lies in first half by comparing item with `a[low]` and `a[mid]`: if yes the we reject second half else we reject first half.
3. If left half wasn't sorted then it is intuitive that right half will definitely be sorted. Then we check if element lies in the second half if yes then we reject first half else we reject second half.

```
int rot_bsearch(vector<int> &nums, int item){
    int l = 0, h = nums.size()-1;
    while(l<h){
        int mid = (l+h)/2;
        if(nums[mid] == item){
            return mid;
        }
        
        if(nums[l] <= nums[mid]){
            if(item >= nums[l] && item<nums[mid]){
                h = mid-1;
            }
            else{
                l = mid+1;
            }
        }
        else{ // if lest half aint sorted then right half is def sorted
            
            if(item>nums[mid] && item <= nums[h]){
                l=mid+1;
            }
            else{
                h=mid-1;
            }
           
        }
            
        
    }
    if(l==h&& nums[l] == item) return l;
    return -1;
}
```

---

#### [5. Book Allocation](https://www.interviewbit.com/problems/allocate-books/)

Given an array of integers A of size N and an integer B.  

College library has N bags,the ith book has A[i] number of pages.  

You have to allocate books to B number of students so that maximum number of pages alloted to a student is minimum.  

A book will be allocated to exactly one student.  
Each student has to be allocated at least one book.  
Allotment should be in contiguous order, for example: A student cannot be allocated book 1 and book 3, skipping book 2.  
Calculate and return that minimum possible number.  

NOTE: Return -1 if a valid assignment is not possible.  


**Approach: Recurrsion**
`TC: Exponential`
**Approach: DP**
`TC : O(n^2)`

**Approach Binary Search - VIMP**

**Binary Search Function:**

1. To apply Binary Search we need to find the search space. 
2. `Low` : Now the minimum number of books that can be allocated to a student is the min of all books (This is the case when the number of books = number of students.)
3. `high` : The maximum number of books that can be allocated to a student is the sum of all books. (This is the case only there is only one student)
4. Now our final ans will lie between low and high.
5. We compute mid = (low + high)>>1. This mid is our `barrier`. That is we check if the books allocation is possible to `B` students when each student cant be allocated pages more than `barrier`. 
6. If yes then we know that the allocation will be possible for all pages> barrier, but we need minimum page allocation hence we drop the right half and do `high = mid-1`. We keep track of these barrier by doing `ans = mid`
7. Else `low = mid+1`
8. Once `low>high` We have our final answer as `ans` or `low`.

**boolean : Book allocation function given barrier and B students**
1. We start with `studentsalloted = 1` and `pages = 0`
2. Now we check for each book
3. If `pages + book[i] <= barrier` then allocate those pages to the student, `pages+=(book[i])`
4. Else we increase the students alloted count `studentsalloted++` and allot the `pages = book[i]`.
5. Finally if the `studentsalloted <= Given B Students` then allocation is possible hence `return true` else `false`   


```
bool allocation(int barrier, vector<int> &A, int students){
    
    int stu=1, pages=0;
    for(int i=0; i<A.size(); i++){
        if(A[i] > barrier) return false; // If any book size if greater than the barrier then that means it cant be allocate to any student
        if(pages+A[i] > barrier){
            stu++;
            pages = A[i];
        }
        else{
            pages+=(A[i]);
        }
    }
    return stu<=students;
}
int bsearch(int i, int j, vector<int> &A, int students, int ans){
    int mid;
    while(i<=j){
        mid = (i+j)>>1;
        if(allocation(mid, A, students)){
            ans = mid;
            j = mid-1;
        }
        else{
            i = mid+1;
        }
    }
    return ans;
}

int Solution::books(vector<int> &A, int B) {

    int j = accumulate(A.begin(), A.end(),0);
	int i = *max_element(A.begin(), A.end());
	// If total no of students is greater than total no of books then atleast one student will remain empty which is not allowed
    if(B > A.size()){
		return -1;
	}
	int ans = -1;
	int x = bsearch(i,j,A,B,ans);
	return x;
}

```

`TC: O(nlogn)`


---
#### [6. Aggressive Cows](https://www.codingninjas.com/codestudio/problems/aggressive-cows_1082559?leftPanelTab=1)
Given an array of location of Barns `V`, and total number of cows `C`. We need to place the cows on the given barns such the maximum distance between any two cows is minimum.  
**Approach:**  
1. Similar to Book allocation we use the same Binary Search approach.
2. The minimum distance possible in any case is 1 and the maximum is the value of max element. This will be our low and high for the binary search
3. Now we find the mid and check if cows allocation is possible into the barns with maxi distance (barrier) of `mid`. If yes then it is intuitive that allocation is possible for any value > mid so we do `high = mid-1` and keep track of the possible `ans = mid`.
4. Else we do `low = mid+1`.

```
#include<bits/stdc++.h>
bool ispos(vector<int> &v, int mini, int c){
    int i=0;
    int fin = *max_element(v.begin(), v.end());
    int prev=0;
    while(c>0 && i<v.size()){
        if(i==0 || v[i] - prev >= mini){
            c--;
            prev = v[i];
        }
        i++;
    }
    if(c==0) return true;
    return false;
}
int aggrcow(vector<int> &v, int c){
    int low = 1;
    int high = *max_element(v.begin(), v.end());
    int ans = 0;
    while(low<=high){
        int mid = (low+high)>>1;
        if(ispos(v, mid, c)){
            ans = mid;
            low = mid+1;
        }
        else{
            high = mid-1;
        }
    }
    return ans;
}

int aggressiveCows(vector<int> &v, int k)
{
    sort(v.begin(), v.end());
        // int ans=0;
    int ans = aggrcow(v,k);
    return ans;
    //    Write your code here.
}
```

`TC: O(nlogn)`
---

#### [7. Median of two sorted arrays](https://leetcode.com/problems/median-of-two-sorted-arrays/)
**Approach Binary Search: O(log(m+n))**  
Notes to be added

```
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if(nums2.size()<nums1.size()){
            return findMedianSortedArrays(nums2, nums1);
        }
        int s1 = nums1.size();
        int s2 = nums2.size();
        
        int l = 0, h = nums1.size(), mid, cut1, cut2, l1,l2,r1,r2;
        while(l<=h){
            
            mid = (l+h)>>1;
            cut1 = mid;
            cut2 = (s1+s2+1)/2 - cut1;
            l1 = cut1 == 0 ? INT_MIN : nums1[cut1-1];
            r1 = cut1 == s1 ? INT_MAX : nums1[cut1];
            l2 = cut2 == 0 ? INT_MIN : nums2[cut2-1];
            r2 = cut2 == s2 ? INT_MAX : nums2[cut2];
            if(l1<=r2 && l2<=r1){
                if((s1+s2)%2!=0){
                    return max(l1,l2);
                }
                else{
                    double ans = (max(l1,l2) + min(r1,r2))/2.0;
                    return ans;
                }
            }
            else if(l1>r2){
                h = cut1-1;
            }
            else{
                l = cut1+1;
            }
        }
        
        return 0.0;
    }
};
```
#### [8. Minimum Time to Complete Trips](https://leetcode.com/problems/minimum-time-to-complete-trips/)
You are given an array time where `time[i]` denotes the time taken by the ith bus to complete one trip.  

Each bus can make multiple trips successively; that is, the next trip can start immediately after completing the current trip. Also, each bus operates independently; that is, the trips of one bus do not influence the trips of any other bus.  

You are also given an integer totalTrips, which denotes the number of trips all buses should make in total. Return the minimum time required for all buses to complete at least totalTrips trips.  

**Approach : Brute Force**  
Check whether the min time can be 1, 2, 3, 4, 5...  
Why do we need to check for each time linearly instead we check in jumps through binary search.

**Approach : Things happening in parallel (Buses making trips independently) and we have a range then use binary search**
1. We know that the minimum time possible to complete `totTrips` is 1 and max time is `min time to cover 1 trip * totTrips`. 
2. So we can apply binary search in this range and at each mid we can ask number of trips that can be completed before time = mid if it is <= `totTrips` then high=mid-1
3. else low = mid+1;

```
class Solution {
public:
    long long minimumTime(vector<int>& time, int k) {
        // int t=0;
    if(time.size()==1) return (long long) k * (long long)time[0];   
    int maxi = *min_element(time.begin(), time.end());
    
    long long high = (long long)k * (long long)maxi;
    long long low = 1;
    while(low<=high){
        long long mid = (low+high)/2;
        long long trips = 0;
        
        for(int i=0; i<time.size(); i++){
            trips+=(mid/(long long)time[i]);
            
        }
        if(trips >= k){
            high = mid-1;
        }
        else{
            low = mid+1;
        }
        
    }
    
    return low;
    }
};
```

#### [9. Capacity To Ship Packages Within D Days](https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/)
A conveyor belt has packages that must be shipped from one port to another within days `days`.  

The ith package on the conveyor belt has a weight of `weights[i]`. Each day, we load the ship with packages on the conveyor belt (in the order given by weights). We may not load more weight than the maximum weight capacity of the ship.  

Return the least weight capacity of the ship that will result in all the packages on the conveyor belt being shipped within days days.  
**Approach**
1. The range of capacity of the conveyer belt can be between max(weights) and sum(weights)
2. Now for each mid we would check the number of days required. If it is more than given `days` then that meand current capacity is not enough so we need more capacity hence l =  mid+1; else h = mid - 1;

```
 int shipWithinDays(vector<int>& weights, int days) {
        //minimum capacity should be equal to the maximum weight of any luggage and maximum capacity is sum of all weights;
        
        int h = accumulate(weights.begin(), weights.end(), 0);
        // sort(weights.begin(), weights.end());
        
        int maxi = *max_element(weights.begin(), weights.end());
        int l = maxi;
        while(l<=h){
            int mid = (l+h)>>1;
            //compute number of days to ship packages with mid capacity
            int day=1;
            int w = 0;
            
            for(int i=0; i<weights.size(); i++){
                w += (weights[i]);
                if(w>mid){
                    day++;
                    w = weights[i];

                }
            }
            if(day <= days){
                h = mid-1;
            }
            else{
                l = mid+1;
            }
            
        }
        return l;
    }
```
TC: O(log(range) * (for loop)) : O(log(sum(weights)) * len(weight vector))  
