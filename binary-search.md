####[Find First and Last Position of Element in Sorted Array](https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/)
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
    // base case
    if(i>j) return j;
    
    int mid = i+ (j-i)/2;
    if(nums[mid] == item && (mid==0 || nums[mid-1]!=nums[mid])){
        return mid;
    }
    if(item <= nums[mid]){
        return lower_bound(nums, i, mid-1, item);
    }
    else{
        return lower_bound(nums, mid+1, j, item);
    }
        
}
int upper_bound(vector<int> &nums, int i, int j, int item){
    if(i>j) return i;
    
    int mid = i + (j-i)/2;
    
    if(item == nums[mid] && (mid == nums.size()-1 || nums[mid]!=nums[mid+1])){
        return mid+1;
    }
    if(item >= nums[mid]){
        return upper_bound(nums, mid+1, j, item);
    }
    else{
        return upper_bound(nums, i, mid-1, item);
    }
}

vector<int> searchRange(vector<int>& nums, int target) {
        int i = lower_bound(nums, 0, nums.size()-1, target);
        int j = upper_bound(nums, 0, nums.size()-1, target);
        cout<<i<<" "<<j<<endl;
        if(i<0 || nums[i]!=target) return {-1,-1};
        return {i, j-1};
    }
};
```

---
