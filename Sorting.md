### QuickSort
**Main Idea:**
1. Select Pivot, Find its position 
2. then do same for left and right subarray
3. If we get n/2 pivot at each call then we perform each call in logn time and we are doing it for n times so nlogn in avg case
4. O(n2) in worst case i.e desc order

```
void qsort(vector<int> &nums, int first, int last){
        if(first>=last){
            return;
        }
        
        int i=first;
        int j=last;
        int pivot=first;
        while(i<j){
            while(i<last && nums[i] <= nums[pivot]){
                i++;
            }
            while(j>first && nums[j] > nums[pivot]){
                j--;
            }
            if(i<j){
                swap(nums[i],nums[j]);
               
            }
        }
        swap(nums[j],nums[pivot]);
        qsort(nums, first, j-1);
        qsort(nums, j+1, last);
        return;
    }
   
    
    void sortColors(vector<int>& nums) {
        qsort(nums,0, nums.size()-1);
    }
```
