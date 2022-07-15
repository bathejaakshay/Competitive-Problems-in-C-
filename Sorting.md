### 1. QuickSort
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
---

#### [2. Merge Sorting a Linked List](https://leetcode.com/problems/sort-list/)
**Main Idea:**
1. Find the middle pointer by fast pointer technique
2. run in recurrsion the mergesort for left and right half
3. merge the two sorted halves

```
ListNode* sortList(ListNode* head) {
        if(head==NULL || head->next == NULL){
            return head;
        }
        ListNode* slow = head;
        ListNode* fast = head;
        ListNode* temp = NULL;
        while(fast!=NULL && fast->next != NULL){
            temp = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        temp->next = NULL; //Ending first half with null
        ListNode * l1 = sortList(head); //sort left half
        ListNode * l2 = sortList(slow); //sort right half
        
        return merge(l1,l2);
        
    }
  ListNode *merge(ListNode *l1, ListNode *l2){
      ListNode * curr = new ListNode(0);
      ListNode *ptr = curr;
      while(l1!=NULL && l2!=NULL){
          if(l1->val<=l2->val){
              curr->next = l1;
              l1 = l1->next;
          }
          else{
              curr->next = l2;
              l2 = l2->next;
          }
          curr = curr->next;
      }
     while(l1!=NULL){
         curr->next= l1;
         l1 = l1->next;
         curr = curr->next;
         
     }
      while(l2!=NULL){
          curr->next=l2;
          l2 = l2->next;
          curr=curr->next;
          
              
      }
      return ptr->next;
         
  }
```
---

#### [3. Sort Colors inplace in O(n)](https://leetcode.com/problems/sort-colors/submissions/)
We need to sort the array of colors which consists of numbers representing 3 colors: 0 -> red, 1->white, 2->Blue.  
Quicksort can do it in O(nlogn) but we need something better.

**Approach : Dutch Partitioning**
1. We know that all red colors will come in starting, then white then blue at the last.
2. so we initialize index r=0, w=0, b=n-1;
3. we iterate using w index
4. Now till `w` <= `b`
5. We check what w is?
6. if `nums[w]` is 0 then swap with `nums[r]` and increment r++ and w++
7. if `nums[w]` is 1 then nothing to do just do w++
8. if `nums[w]` is 2 then swap with `nums[b]` and do b--

```
void sortColors(vector<int>& nums) {
              
        int r=0,w=0,b=nums.size()-1;
        while(w<=b){
            if(nums[w] == 0){
                swap(nums[r], nums[w]);
                r++;
                w++;
            }
            else if(nums[w] == 1){
                w++;
            }
            else{
                swap(nums[w], nums[b]);
                b--;
            }
        }
    }
```

