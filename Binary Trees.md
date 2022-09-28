## Creating Tree from scratch

#### Level order and inorder traversal
**Iterative Inorder, Preorder, Postorder using stack : Interesting**  
```
#include<bits/stdc++.h>
using namespace std;

class TreeNode{
public:
	TreeNode *left, *right;
	int val;
	TreeNode() : val(0), left(nullptr), right(nullptr){}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr){}
	TreeNode(int x, TreeNode *l, TreeNode *r) : val(0), left(l), right(r){}

};

class Tree : public TreeNode{
public:
	TreeNode *root, *head = nullptr; 

	Tree(){
		root = new TreeNode();
		head = root;
	}
	Tree(int x){
		root = new TreeNode(x);
	}
	TreeNode * search(TreeNode *root){
		if(root->val == -1){
			return NULL;
		}
		if(root->left == NULL || root->right == NULL) return root;
		TreeNode *left = search(root->left);
		TreeNode *right = search(root->right);
		if(left) return left;
		if(right) return right;
	}
	void insert(int x){
		TreeNode *node = new TreeNode(x);
		TreeNode *ptr = search(root);
		if(ptr->left == NULL){
			ptr->left = node;
		}
		else if(ptr->right == NULL){
			ptr->right = node;
		}
		

	}


}; 

void inorder(TreeNode *root){
	if(root == NULL){
		return;
	}
	inorder(root->left);
	cout<<root->val<<" ";
	inorder(root->right);
}
void levelorder(TreeNode *root){
	queue<TreeNode *> q;

	q.push(root);
	while(!q.empty()){
		int s = q.size();
		for(int i=0; i<s; i++){
			TreeNode *ptr = q.front();
			q.pop();
			cout<<ptr->val<<" ";
			if(ptr->left)
				q.push(ptr->left);
			if(ptr->right)
				q.push(ptr->right);
		}
	}	
}
void preorder_stack(TreeNode *root){
	stack<TreeNode *> st;

	st.push(root);

	while(!st.empty()){
		TreeNode *ptr = st.top();
		st.pop();
		// in preorder first push right node in the stack
		if(ptr->right){
			st.push(ptr->right);
		}
		cout<<ptr->val<<" ";
		if(ptr->left){
			st.push(ptr->left);
		}

	}
}

void inorder_stack(TreeNode *root){
	stack<TreeNode *> st;

	st.push(root);

	while(!st.empty()){
		TreeNode *ptr = st.top();
		if(ptr->left){
			//push all the left nodes and mark the left node as null as we donot want to travel it again when we comeback to root
			st.push(ptr->left);
			ptr->left = NULL;
			
		}
		else{
			cout<<ptr->val<<" ";
			st.pop();
			if(ptr->right)
				st.push(ptr->right);
		}
		
			

	}
}
vector<int> postorder_stack(TreeNode *root){
    stack<TreeNode*> st;
    stack<int> st2;
    st.push(root);
    while(!st.empty()){
        TreeNode *ptr = st.top();
        st.pop();
        st2.push(ptr->val);
        if(ptr->left) st.push(ptr->left);
        if(ptr->right) st.push(ptr->right);
    
    }
    
    vector<int> ans;
    while(!st2.empty()){
        ans.push_back(st2.top()); 
        st2.pop();
    }
    return ans;
}

int main(int argc, char const *argv[])
{
	/* code */

	int n;
	cin>>n;
	int rt; 
	cin>>rt;
	Tree *t = new Tree(rt);
	for(int i=0; i<n-1; i++){
		int item;
		cin>>item;
		t->insert(item);
	}

	inorder(t->root);
	cout<<endl;
	levelorder(t->root);
	cout<<endl;
	preorder_stack(t->root);
	cout<<endl;
	inorder_stack(t->root); // Inorder stack and postorder stack empties the tree so make sure to comment one to run another.
	cout<<endl;
	vector<int> ans = postorder_stack(t->root);
	for(int &x: ans) cout<<x<<" ";
	
	return 0;
}
```

---

#### [2. Maximum path sum in a Binary Tree](https://leetcode.com/problems/binary-tree-maximum-path-sum/)
The  nodes can be positive or negative
**Approach** 
1. Similar to the diameter of the graph question.
2. We make maxi as the global variable to keep record of the maximum path sum
3. For current node we want max sum of the left straight path and right and then we update maxi if current + left_path +  right_path > maxi
4. and return current + max(left_path, right_path)
5. Note : We never want our left and right to be negative so we do left_path = max(0, left_path) and right_path = max(0, right_path)

```
int maxp(TreeNode *root, int &maxi){
    if(root== NULL) return 0;
    int left = max(0,maxp(root->left, maxi));
    int right = max(0,maxp(root->right, maxi));
    if(left + right + root->val > maxi)
        maxi = left + right + root->val;
    return max(left, right) + root->val;
    
    
}

class Solution {
public:
    int maxPathSum(TreeNode* root) {
        int maxi = INT_MIN; 
        maxp(root, maxi);
        return maxi;
    }
};
```

#### 3. Check if two trees are identical
**Approach**
- Try any traversal pre,post or inorder if it comes out to be same for both trees then they are identical
- Another way is to do bfs using queue


#### [4. Binary ZigZag Traversal](https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/) 
**Approach**
- Using queue level order it is simple

```
vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
      int i=0;
        if(root==NULL) return {};
        queue<TreeNode*> q;
        q.push(root);
        vector<vector<int>> ans;
        while(!q.empty()){
            int s = q.size();
            vector<int> v;
            for(int i=0; i<s; i++){
                TreeNode *ptr = q.front();
                q.pop();
                if(ptr->left)
                    q.push(ptr->left);
                if(ptr->right)
                    q.push(ptr->right);
                    
                v.push_back(ptr->val);
                
            }
            if(i%2==0){
                ans.push_back(v);
            }
            else{
                reverse(v.begin(), v.end());
                ans.push_back(v);
            }
            i++;
            
        }
        return ans;
    }
    
```

####[4. Vertical Traversal in Binary Tree - IMPORTANT](https://leetcode.com/problems/vertical-order-traversal-of-a-binary-tree/)

Given the root of a binary tree, calculate the vertical order traversal of the binary tree.  

For each node at position `(row, col)`, its left and right children will be at positions `(row + 1, col - 1) and (row + 1, col + 1)` respectively. The root of the tree is at `(0, 0)`.

**Approach**
- Maintain a queue with Node and its coordinate in x axis and y axis.
- maintain a map of multisets. The key of the map is the y axis of a node. The values are x_axis comp and value of that node which goes into the corresponding multiset.

```
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        queue<pair<TreeNode*, pair<int,int>>> q;
        q.push({root,{0,0}});

        map<int,multiset<pair<int,int>>> mp;
        
        while(!q.empty()){
            int s = q.size();
            for(int i=0; i<s; i++){
                    auto it = q.front();
                    q.pop();
                    mp[it.second.second].insert({it.second.first, it.first->val});
                    if(it.first->left)
                        q.push({it.first->left, {it.second.first+1, it.second.second-1}});
                if(it.first->right)
                        q.push({it.first->right, {it.second.first+1, it.second.second+1}});
                }
        }
        
        vector<vector<int>> finall;
        for(auto x: mp){
            vector<int> m;
            for(auto j : x.second){
                m.push_back(j.second);
            }            
            finall.push_back(m);
        }
        return finall;
    }
```

---
#### [5. Right View of the binary Tree](https://leetcode.com/problems/binary-tree-right-side-view/)

**Approach**
1. Level order approach is easy but more space consuming.
2. Recursive approach is using Reverse preorder traversal i.e root right left.
3. maintain level count and only append to vector, the node which reach that level first.

```
void traverse(TreeNode *root, int level, vector<int> &ans){
    // reverse pre order: root right left
    if(root==NULL) return;
    if(level == ans.size()) ans.push_back(root->val);
    traverse(root->right, level+1, ans);
    traverse(root->left, level+1, ans);
}
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> ans;
        traverse(root, 0, ans);
        return ans;
    }
};
```
---
#### [6. Symmetric Tree]()
Is the tree symmetric along the center?
Two ways
**Approach: Two pointers One Traversal**\
1. We can use two pointers and traverse the tree once and simultaneously move these pointers to the left and right to check mirror property.
```
//Approach 2
void traverse1(TreeNode *root, vector<pair<int,int>> &a1, int level){   
    if(root==NULL) return;
    
    traverse1(root->left, a1, level+1);
    a1.push_back({root->val, level});
    traverse1(root->right, a1, level+1);
    
}

void traverse2(TreeNode *root, vector<pair<int,int>> &a2, int level){
    if(root==NULL) return;
    traverse2(root->right, a2, level+1);
    a2.push_back({root->val, level});
    traverse2(root->left, a2, level+1);
    
}

//Approach 1
bool sym(TreeNode *rootl, TreeNode *rootr){
    if(rootl == NULL || rootr == NULL) return rootl == rootr;
    if(rootl->val != rootr->val) return false;
    return sym(rootl->left, rootr->right) && sym(rootl->right, rootr->left);
}
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        return root==NULL || sym(root->left, root->right);
        // vector<pair<int,int>> a1,a2;
        // traverse1(root, a1, 0);
        // traverse2(root, a2, 0);
        // if(a1.size()!=a2.size()) return false;
        // for(int i=0; i<a1.size(); i++){
        //     if((a1[i].first != a2[i].first) || (a1[i].second!=a2[i].second)) return false;
        // }
        // return true;
    }
};
```

**Approach: 2 traversals**
1. First traversal we get left root right and each element in ans is the val with the level info.
2. Second traversal we get right root left and each element in ans is tha val with the level info.
3. Now the generated two ans should be exactly same for the tree to be symmetric

#### [7. Lowest Common Ancestor](https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/)

**Approach: Easy recurrsion**
```
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(root==NULL) return NULL;
        if(root == p || root == q) return root;
        TreeNode *left = lowestCommonAncestor(root->left, p,q);
        TreeNode *right = lowestCommonAncestor(root->right, p, q);
        if(left== NULL && right == NULL) return NULL;
        if(left == NULL) return right;
        if(right == NULL) return left;
        return root;
        
    }
```

#### [8. Width of a binary tree : Tricky](https://leetcode.com/problems/maximum-width-of-binary-tree/)
Width is defined by the number of nodes possible in the first node and last node at any level
**Approach**  
- Level order traversal
- We will keep the intuition of `2*i as left and 2*i+1 as right of root i=1`. But this will lead to over flow of the value int if the tree is skewed
- So we act smart we need each of our level index should start with zero. This is possible if during computation of left index we substract the first index val in that level from i so `left = 2*(i-start_index of level)` and `right = 2*(i-start_index of level + 1)`

```
int widthOfBinaryTree(TreeNode* root) {
        if(root==NULL) return 0;
        queue<pair<TreeNode*, long long>> q;
        q.push({root, 1});
        long long maxi = 1;
        while(!q.empty()){
            int s = q.size();
            if(s>1){
                auto it = q.front();
                s--;
                q.pop();
                long long start = it.second;
                if(it.first->left){
                    q.push({it.first->left, (long long)2*(it.second-start)});
                    
                }
                if(it.first->right){
                    q.push({it.first->right, (long long)2*(it.second-start)+1});
                }
                
                for(int i=0; i<s; i++){
                    auto it = q.front();
                q.pop();
                int end = (long long)it.second;
            
                if(it.first->left){
                    q.push({it.first->left,(long long) 2*(it.second-start)});
                    
                }
                if(it.first->right){
                    q.push({it.first->right,(long long) 2*(it.second-start)+1});
                }
                    // cout<<"end = "<<end<<" start = "<<start<<" it = "<<it.first->val<<endl;
                    maxi = max(maxi, end-start+1);
                }
                
            }
            else{
                auto it = q.front();
                q.pop();
                if(it.first->left){
                    q.push({it.first->left, (long long)2*(0)});
                    
                }
                if(it.first->right){
                    q.push({it.first->right, (long long)2*(0)+1});
                }
                
            }
        }
        return maxi;
    }
```
