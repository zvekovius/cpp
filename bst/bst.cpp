#include <iostream>

using namespace std;

struct treeNode
{
	int val;
	treeNode* left;
	treeNode* right;
};

class bst
{
public:
	bst();
	void partialInsert(int);
	void preorder();
	void postorder();
	void inorder();
	void search();

private:
	treeNode* partialInsertHelper(int, treeNode*);
	void preorderHelper(treeNode*);
	void postorderHelper(treeNode*);
	void inorderHelper(treeNode*);
	void searchHelper(treeNode*);
	treeNode* root;
};

bst::bst()
{
	root = NULL;
}

//preorder traversal
//visit the node
//traverse the left subtree
//traverse the right subtree
//Follow track, when you hit the left, print.

//Inorder Traversal
//Traverse the left subtree
//Visit the node
//Traverse the right subtree
//Follow track, when you hit the bottom, print. 

//Postorder traversal
//Traverse the left subtree
//Traverse the right subtree
//Visit the Node
//Follow the track, when you hit the right, print.

void bst::partialInsert(int val)
{
	root = partialInsertHelper(val, root);
}

treeNode* bst::partialInsertHelper(int val, treeNode* node)
{
	if(node == NULL)
	{
		treeNode* tmp = new treeNode;
		tmp->val = val;
		tmp->left = NULL;
		tmp->right = NULL;
		return tmp;
	}
	else
	{
		if( val < node->val )
		{
			//If val < node->val
			node->left = partialInsertHelper(val, node->left);
		}
		else if ( val >= node->val )
		{
			node->right = partialInsertHelper(val, node->right);
		}
	}
	return node;
}

void bst::preorder()
{
	cout << "Preorder: ";
	preorderHelper( root );
	cout << endl; 

}

//preorder traversal
//visit the node
//traverse the left subtree
//traverse the right subtree
//Follow track, when you hit the left, print.


void bst::preorderHelper(treeNode* node)
{
//	if(node->left != NULL or node->right != NULL )
	if(node != NULL)
	{
		cout << node->val << " "; 
		preorderHelper(node->left);
		preorderHelper(node->right);
	}

}

void bst::postorder()
{
	cout << "Postorder: ";
	postorderHelper( root );
	cout << endl;
}

//Postorder traversal
//Traverse the left subtree
//Traverse the right subtree
//Visit the Node
//Follow the track, when you hit the right, print.


void bst::postorderHelper( treeNode* node )
{
	if(node != NULL)
	{
		preorderHelper(node->left);
		preorderHelper(node->right);
		cout << node->val << " "; 
	}
}

void bst::inorder()
{
	cout << "Inorder: ";
	inorderHelper( root );
       	cout << endl;	
}

//Inorder Traversal
//Traverse the left subtree
//Visit the node
//Traverse the right subtree
//Follow track, when you hit the bottom, print. 


void bst::inorderHelper( treeNode* node )
{
	if(node != NULL)
	{
		preorderHelper(node->left);
		cout << node->val << " "; 
		preorderHelper(node->right);
	}
}

void bst::search()
{
	searchHelper( root );
}

void bst::searchHelper( treeNode* node )
{
// come up with this yet.
}

int main()
{
	bst bst1;

	bst1.partialInsert(5);

	for(int i = 0; i < 10; i++)
	{
		bst1.partialInsert(i);
	}
	bst1.preorder();
	bst1.inorder();
	bst1.postorder();
	return 0;
}
