#### 1. Convert Binary Tree into Doubly linked list (using inorder Traversal). Without any extra space and using the same pointers i.e left as previous and right as next.

Main Idea:
a. Keep a global Prev pointer
b. traverse left subtree
c. for current node its left would be prev and update prev->right to be curr.
d. traverse right
e. Maintain Head
```
TreeNode * convert(TreeNode *A){

}
```
