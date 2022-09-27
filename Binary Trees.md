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

