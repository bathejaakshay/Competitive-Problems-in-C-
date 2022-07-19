#### [1. Palindromic LL](https://leetcode.com/problems/palindrome-linked-list/)
**Approach**:
1. Either reverse first half or second half and compare the two halfs.
2. Use fast pointer
```
bool isPalindrome(ListNode* head) {
        if(head->next == NULL) return true;
        ListNode *p1=head,*p2 = head;
        while(p2!=NULL && p2->next!=NULL && p2->next->next!=NULL){ // will stop at n/2-1
            p1=p1->next;
            p2=p2->next->next;
        }
        
        ListNode *prev3 = p1->next;
        ListNode *p3 = prev3->next;
        prev3->next = NULL;
        while(p3 != NULL){
            ListNode *temp = p3->next;
            p3->next = prev3;
            prev3 = p3;
            p3 = temp; 
        }
        p1->next = prev3;
        
        ListNode *p4 = head;
        while(prev3!=NULL){
            if(p4->val!=prev3->val) return false;
            p4 = p4->next;
            prev3 = prev3->next; 
        }
        return true;
        
    }
```

---

