#### [1. Maximum Score Of Spliced Array - Kadane's](https://leetcode.com/problems/maximum-score-of-spliced-array/)
Given two arrays num1 and num2. You are allowed to do one operation or do nothing. Take a any subarray of one array and swap it with that of other array with same indices.
You need to find maximum array sum of `max(sum(num1),sum(num2))` given this option.
**Approach**
1. The question is which subarray will increment the sum of my current array by the maximum. 
2. So we can find the difference array between the two arrays and find the max subarray sum using kadane. 
3. we would need to try this two ways nums1 - nums2 then add max subarray sum to sum of nums2 or nums2 - nums1 then add the max subarray sum to sum of nums1. 
4. The maximum of them will be the answer. A short way to do the same this is written below.
```
int maximumsSplicedArray(vector<int>& nums1, vector<int>& nums2) {   
        int sum=0, sum2=0, ans=0;
        for(int &i: nums1) sum+=i;
        for(int &i: nums2) sum2+=i;
        
        ans = max(sum,sum2);
        
        int maxi1=0, maxi2=0;
        int sum11=0;
        int sum22=0;
        for(int i=0; i<nums1.size(); i++){
            sum11+=(nums1[i] - nums2[i]);
            sum22+=(nums2[i] - nums1[i]);
            maxi1 = max(maxi1, sum11);
            maxi2 = max(maxi2, sum22);
            if(sum11<0) sum11=0;
            if(sum22<0) sum22=0;
        }
        
        ans = max(ans, sum + maxi2);
        ans = max(ans, sum2 + maxi1);
        return ans;
    }
```
