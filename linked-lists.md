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

#### [2. Intersection of Two Linked Lists](https://leetcode.com/problems/intersection-of-two-linked-lists/)  
Two optimal approaches with TC:O(m+n) SC: O(1)  
**Approach 1 : Length difference**
1. Compute the difference in the length between two. 
2. This tells us no of extra nodes in the bigger linked list before the intersection part.
3. Now we traverse those many nodes in the bigger LL
4. Now we start traversing both LL together and we know they will meet at a common point else they have to meet at NULL

```
ListNode* lendiff(ListNode *headA, ListNode *headB){
    int a=0,b=0;
    ListNode* ptr1 = headA;
    ListNode* ptr2 = headB;
    while(ptr1!=NULL){
        a++;ptr1=ptr1->next;
        
    }
    while(ptr2!=NULL){
        b++; ptr2 = ptr2->next;
        
    }
    int diff=abs(a-b);
    ptr1 = headA;
    ptr2 = headB;
    if(a>b){
        while(diff>0)
        {
            ptr1 = ptr1->next;
            diff--;
        }
        
        
    }
    else{
        while(diff>0){
            ptr2= ptr2->next;
            diff--;
        }
    }
    
    while(ptr1!=NULL){
        if(ptr1 == ptr2){
            return ptr1;
        }
        ptr1=ptr1->next;
        ptr2 = ptr2->next;
    }
    return ptr1;   
}
```

**Approach 2: Common Sense not so common though :D**
1. We start traversing both the lists together. The moment one ends we start it again we the head of another list.
2. This ensures that in `O(2*m + 2*n)` steps they both will definitely meet at the same point if the intersection point exit
3. Else they have to meet at NULL
4. The intuition is that right half of the intersection takes same no of steps to cover by both LL. The difference lies in the former part.
5. So if we make sure that both traverse the same no of steps in the former part then they will definitely meet at the intersection point.


```
ListNode *commonsense(ListNode *headA, ListNode *headB){
    ListNode *p1 = headA;
    ListNode *p2 = headB;
    while(p1!=p2)
    {
        
        
        if(p1 == NULL){
            p1 = headB;
            
        }
        else{
            p1 = p1->next;
        }
        if(p2 == NULL){
            p2 = headA;
        }
        else{
            p2 = p2->next;
        }
        
    }
    return p1;
}
```

---
#### [3. Find if a cycle exist in the LL given only a head pointer](https://leetcode.com/problems/linked-list-cycle/)
**Approach**
1. Quite simple. Using slow and fast pointer approach
2. Use slow pointer to move by one position and fast to move by two position.
3. If a cycle exists that they will meet at some point.

`TC: O(N), SC:O(1)`

---

#### [4. Flatten a linked list]()

**Approach: Merge**
1. Approach is easy to use merge but not in a merge sort fashion.
2. We keep on merging two linked lists into one starting from ending.

```
Node* merge(Node *p1, Node *p2){
    Node *t1,*t2;
    // cout<<"started"<<endl;
    Node *prev = new Node(0);
    Node *fin = prev;
    
    while(p1!=NULL && p2!=NULL){
        t1 = p1->bottom; t2 = p2->bottom;
        if(p1->data <= p2->data){
            
            prev->bottom = p1;
            prev = p1;
            p1 = t1;
        }
        else{
            if(p1->data > p2->data ){
                prev->bottom = p2;
                prev = p2;
                p2 = t2;
            }
            
        }
       
    }
    while(p1!=NULL){
        prev->bottom = p1;
        prev = p1;
        p1 = p1->bottom;
    }
    while(p2 != NULL){
        prev->bottom = p2;
        prev = p2;
        p2 = p2->bottom;
    }
    prev->bottom = NULL;
    
    return fin->bottom;
}    
    
Node *flatten(Node *root)
{
   // Your code here
   if(root == NULL || root->next == NULL) return root;
   root->next = flatten(root->next);
   return merge(root, root->next);
}

```

---

#### [5. Longest Consecutive Sequence](https://leetcode.com/problems/longest-consecutive-sequence/)
**Approach : O(n)**
1. Create an unordered_set of given array, `unordered_set(nums.begin(), nums.end())`
2. After that for each element count and remove all elements that are lesser than the element consecutively in a loop.
3. After that for each element count and remove all elements that are greater than the element consecutively in a loop.
4. Remove the current element and update the ans

```
int longestConsecutive(vector<int>& nums) {
    unordered_set<int> mp(nums.begin(), nums.end());       
    int ans=0;
      for(int i=0; i<nums.size(); i++){
              if(mp.find(nums[i])==mp.end()) continue;
              int l=nums[i]-1;
              while(mp.find(l)!=mp.end()){
                  mp.erase(l);
                  l--;
              }
              int r = nums[i]+1;
              while(mp.find(r)!=mp.end()){
                  mp.erase(r);
                  r++;
              }
              mp.erase(nums[i]);
              ans = max(ans, r-l-1);
          }
      
        return ans;
    }
```

---
#### [6. Flatten a multilevel doubly linked list with next, prev, and child pointers](https://leetcode.com/problems/flatten-a-multilevel-doubly-linked-list/)
**Approach**
1. We just need to remember how to apply recurrsions in a Linked List.
2. We recursively move on till last node and flatten it.
3. Then we flatten the second last node set its next as last node
4. We keep on doing it till the start.

```
pair<Node*,Node*> flat(Node *root){
    if(root == NULL) return {NULL,NULL};
    pair<Node*, Node*> pp;
    if(root->next == NULL){
        if(root->child!=NULL){
            pp = flat(root->child);
            
            root->next = pp.first;
            root->next->prev = root;
            pp.second->next = NULL;
            root->child = NULL;
            return {root, pp.second};
        }
        else
            return {root,root};
    }
    auto pt = flat(root->next);
    root->next = pt.first;
    if(root->child!=NULL){
        Node *temp = root->next;
        auto pt2 = flat(root->child);
        root->next = pt2.first;
        root->next->prev = root;
        pt2.second->next = temp;
        if(temp!=NULL)
            pt2.second->next->prev = pt2.second;
        root->child = NULL;
        
    }
    else{
        root->next->prev = root;
    }
    return {root, pt.second};
    
}
class Solution {
public:
    Node* flatten(Node* head) {
        pair<Node*, Node*> nn = flat(head);
        return nn.first;
    }
};
```
