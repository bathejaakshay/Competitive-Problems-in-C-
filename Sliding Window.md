#### [1. Frequency of the Most Frequent Element](https://leetcode.com/problems/frequency-of-the-most-frequent-element/)
The frequency of an element is the number of times it occurs in an array.  

You are given an integer array nums and an integer k. In one operation, you can choose an index of nums and increment the element at that index by 1.  

Return the maximum possible frequency of an element after performing at most k operations.  

 
```
Example 1:

Input: nums = [1,2,4], k = 5
Output: 3
Explanation: Increment the first element three times and the second element two times to make nums = [4,4,4].
4 has a frequency of 3.
```

**Approach: Sliding Window**
1.  Sort the array
2.  We maintain a window w of elements which gives us the frequency of the max element in that window.
3.  We maintain simple `sum` of the current window and check if adding the next element `j+1` in this window is possible by checking `sum + k >= (i-j+1)*nums[j+1]` 
4.  i.e `currsum + k >= curr_windsize*new_max_frequent_element`
5.  To keep things simple we always maintain sum, or (in case of bits manipulation) of the window to keep essence of each element and to remove esssence of elements at head we do `sum-=num[i]` or `sum^num[i]`     
6.  So if the condition mentioned in point 3 doesnot satisfy then we compress the window till it satisfy by doing `sum-=nums[i++]`
7.  After that if the condition satisfy then we update our ans `res = max(res, j-i+1 + 1)` we added 1 to the current window because we are checking if we can accomodate next element in the current window

```
    int maxFrequency(vector<int>& nums, int k) {
      int i=0;
      int curr_k=k;
      int res=1;
      sort(nums.begin(), nums.end());
        long long sum=0;
      for(int j=0; j<nums.size()-1; j++){
          sum+=(long long)nums[j];
          while(i<j && sum + k  < (long long)nums[j+1]* (long long)(j-i+1)){
              sum-=nums[i];
              i++;
          }
          if((long long)nums[j+1]*(j-i+1) <= ((long long)curr_k + sum)){
            res = max(res, j-i+2);  
          }
          else{
              sum=0; 
              i++;
          }
          
         
      }
        
        return res;
    }

```

---
