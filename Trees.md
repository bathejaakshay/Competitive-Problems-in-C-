#### 1. Convert Binary Tree into Doubly linked list (using inorder Traversal). Without any extra space and using the same pointers i.e left as previous and right as next.

Main Idea:
a. Keep a global Prev pointer
b. traverse left subtree
c. for current node its left would be prev and update prev->right to be curr.
d. traverse right
e. Maintain Head
```

TreeNode *prev = NULL;
TreeNode * convert(TreeNode *A){
  if (A == NULL) return A;
  
  # Traverse left
  TreeNode *head = convert(A->left);
  
  #Do work for current node
  if(prev==NULL) head = A;
  
  else{
        A->left = prev;
        prev.right = A;
      }
  
  prev = A;
  
  # Do same work for right
  convert(A->right);
  return head;
  
}
```

---
