#### 1. Convert Binary Tree into Doubly linked list (using inorder Traversal). Without any extra space and using the same pointers i.e left as previous and right as next.
[Link to the gfg lecture](https://practice.geeksforgeeks.org/tracks/DSASP-Tree/?batchId=154&tab=1)

Main Idea:
1. Keep a global Prev pointer
2. traverse left subtree
3. for current node its left would be prev and update prev->right to be curr.
4. traverse right
5. Maintain Head
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
        prev->right = A;
      }
  
  prev = A;
  
  # Do same work for right
  convert(A->right);  /* Also remember that in C++ even if you dont catch the returned object it still works fine*/
  return head;
  
}
```

---
