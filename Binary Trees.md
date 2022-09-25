## Creating Tree from scratch

#### Level order and inorder traversal

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
	return 0;
}
```
