#include <iostream>
#include <stack>
//树的非递归遍历

using namespace std;
typedef struct Node_{
	int val;
	struct Node_ *right;
	struct Node_ *left;
} TreeNode;

 
void preorderTraversal(TreeNode* root) {
	//前序
    stack<TreeNode*> s;
    if (root == NULL)
    	return;
    	
    s.push(root);
    while(!s.empty()) {
        TreeNode* p = s.top();
        s.pop();
        cout<<(p->val)<<' ';
        if (p->right)
            s.push(p->right);
        if (p->left)
        	s.push(p->left);
    }
    return result;
}

void inorderTraversal(TreeNode* root) {
	//中序 
    stack<TreeNode*> s;
    if (root == NULL)
        return ;
    TreeNode* p = root;
    while (!s.empty() || p != NULL) {
        if (p != NULL) {
        	// push 左子树入栈
	        s.push(p);
	        p = p->left;
    	} else {
        	// 左子树为空时，访问该节点，然后访问右子树
            p = s.top();
            cout<<(p->val)<<' ';
            s.pop();
            p = p->right;
        }
    }  
}




int main() 
{
	
	
	
	
	return 0;	
} 
