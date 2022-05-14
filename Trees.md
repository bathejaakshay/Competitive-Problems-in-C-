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


#### 2. Construct a Binary Tree using Inorder and Preorder Traversal. \ [Inorder Traversal of Cartesian Tree](Inorder Traversal of Cartesian Tree)
**Main Idea:**  
1. We will use Preorder to get the root of the current inorder array.
2. Then we find the root in the inorder array.
3. We create a Tree Node with root and do the same for its left and right.

```
indexpre=0;

TreeNode* constructBT(vector<int> &in, vector<int> &pre, int i, int j){
  
  if(i>j) return NULL /*sReached the end*/  
  
  //root of the current array is pre[indexpre]
  int val = pre[indexpre++]
  int ind;
  
  //find the root in the inorder
  for(int x=i; x<=j; x++){
    if(val == in[x]) ind = x;
    break;  
  } 
  
  TreeNode *ptr = new TreeNode(val);
  ptr->left = constructBT(in,pre,i,ind-1);
  ptr->right = constructBT(in,pre,ind+1, j);
  
  return ptr; 
}

main(vector<int> in, vector<int> pre){
  TreeNode *head  = constructBT(in,pre, 0,in.size()-1);
  }
```
---
