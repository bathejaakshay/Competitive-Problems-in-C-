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
  
  /* Just one change in case of constructing Tree using inorder and postorder:
     In case of post order we construct ptr->right first and then ptr->left. cuz postorder is
     Left-Right-Root, hence we will always get the root of rightsubtree first at the last position of 
     postorder array.
  
  */
  ptr->left = constructBT(in,pre,i,ind-1);
  ptr->right = constructBT(in,pre,ind+1, j);
  
  return ptr; 
}

main(vector<int> in, vector<int> pre){
  TreeNode *head  = constructBT(in,pre, 0,in.size()-1);
  }
```
---
#### [3. Least Common Ancestor](https://www.interviewbit.com/old/problems/least-common-ancestor/)
![lsa](https://github.com/bathejaakshay/Competitive-Problems-in-C-/blob/master/Images/lsa1.png?raw=true)
<!-- ![BM1](https://github.com/bathejaakshay/Competitive-Problems-in-C-/blob/master/Images/bm1.png?raw=true) -->
**Two Approaches:**
**Linear solution using path calculation :** (Applicable irrespective of whether any one of the node exists in the tree or not)  
1) Find path from root to n1 and store it in a vector or array.
2) Find path from root to n2 and store it in another vector or array.
3) Traverse both paths till the values in arrays are same. Return the common element just before the mismatch

**Linear solution using recursion :**  (Applicable only when both the nodes are present in the tree)  
We traverse from the bottom, and once we reach a node which matches one of the two nodes, we pass it up to its parent. The parent would then test its left and right subtree if each contain one of the two nodes. If yes, then the parent must be the LCA and we pass its parent up to the root. If not, we pass the lower node which contains either one of the two nodes (if the left or right subtree contains either p or q), or NULL (if both the left and right subtree does not contain either p or q) up.

*PS:* Approach 1 takes extra memory and approach 2 doesnot. So if it is asked to not use memory and its given that both nodes may not be present. Then, we first traverse the tree 2 times to find if both nodes exist. Then we apply approach 2. 
