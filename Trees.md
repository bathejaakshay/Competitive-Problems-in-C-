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

---

#### [4. Check If a given Binary Search Tree is VALID or NOT](https://www.interviewbit.com/old/problems/valid-binary-search-tree/)

**Naive Approach:**  
For each Node in the Tree check if its value is greater than the max value in its left subTree and lesser then the minimum value in its right subtree and if its left subTree and right subTree are valid or not in recurrsion. But This will take a lot of time as for each node we are check all other nodes so O(n2). If we keep min and max of right and left subtree parallely are compare the O(n). But there exist more easy, efficient and intuitive solution than this.

**Another Approach**  
Check the inorder Traversal of the given BST and see if the keys are sorted.

**Best Approach: Range Method**  
In this approach we specify a range for each node and check if its value lie within that range. And similarly we check for left and right subtree. An example with ranges of all nodes is given below. T(n) = O(n)

<figure>
<center><img src="https://github.com/bathejaakshay/Competitive-Problems-in-C-/blob/master/Images/isvalidBST.png?raw=True" alt="drawing" width="400"/></center>
<center><figcaption>Checking Binary Search Tree is Valid</figcaption></center>
</figure>

```
bool isValid(TreeNode* root, int min, int max){
    
    if(root == NULL) return true;
    
    if(root->val > min && root->val<max && isValid(root->left, min, root->val) && isValid(root->right, root->val, max) return true;
    else return false;
}

bool isValidBST(TreeNode *root){

  return isValid(root, INT_MIN, INT_MAX); //Driver code: for root the range is [INT_MIN,INT_MAX]
  
}
```

---

#### [5. Creating Unique BST](https://www.interviewbit.com/old/problems/unique-binary-search-trees/)

**Approach**
1. We do this recursively.
2. We maintain two pointers start and end.
3. We need to make each node a key once.
4. So we traverse from start to end using curr pointer
5. Now we know all the nodes left to curr will come as left child to it and right nodes will come as right child to it. We are traversing in sorted order.
6. As we are returning all possible left and right subtrees in each call. we need to take all `left*right` combination of trees with root node and add to our ans and return. 
7. In base case we return list with NULL which represent that a node doest has left or right child respt.

```
vector<TreeNode *> all_BST(int start, int end){
    if(start>end) return {NULL};    
    vector<TreeNode *> ans;
    
    vector<TreeNode *> l; vector<TreeNode*>r;
    
    for(int curr = start; curr<=end; curr++){
        l = all_BST(start, curr-1);
        r = all_BST(curr+1, end);
        for(int x=0; x<l.size(); x++){
            for(int y =0; y<r.size();y++){
                    TreeNode* root = new TreeNode(curr);
                    
                    root->left = l[x];
                    root->right = r[y];
                    ans.push_back(root);
                }
            }
        
        
    }
    return ans;
   
} 


vector<TreeNode*> Solution::generateTrees(int A) {
   vector<TreeNode *> ans = all_BST(1, A);
   return ans;
    }

```

---



