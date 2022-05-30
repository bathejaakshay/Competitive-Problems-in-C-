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
---

#### [Merge Sorting a Linked List](https://leetcode.com/problems/sort-list/)
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
