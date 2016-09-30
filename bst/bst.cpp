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

private:
	treeNode* partialInsertHelper(int, treeNode*);
	void preorderHelper(treeNode*);
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

//this is a wrapper function for our actual insert function
//it helps create a cleaner interface for the user to use 
//by removing the need for them to know about any of the internal
//parts of the class.
void bst::partialInsert(int val)
{
	//the wrapper simply calls the actual recursive function
	//which is private because it needs to use one of the private
	//variables as a parameter. We do not want the average user to 
	//call this function as they would not have access to the root
	//variable of the class. By passing root we are telling the function
	//to try to insert our number somewhere in the tree
	root = partialInsertHelper(val, root);
}

//here we define teh actual recursive implementation for our insert.
//the goal of the function is to fund the correct location in the tree
//for the new node to be placed according to BST rules. Note this function
//does not implement those rules, it only shows a very simple instance of
//inserting into a tree
treeNode* bst::partialInsertHelper(int val, treeNode* node)
{
	//if the node we are passed is null then create a new node and return it back
	//to the calling function. By returning either a new node here or the 
	//node we were passed via the return at the bottom we ensure that the 
	//links in the tree are hooked properly. Try removing the return line
	//at the bottom of the function and see what happens, what is the end 
	//result and why is that result happening?
	if(node == NULL)
	{
		treeNode* tmp = new treeNode;
		tmp->val = val;
		tmp->left = NULL;
		tmp->right = NULL;
		return tmp;
	}
	//if the node is not NULL, recursivly call insert and pass it the pointer
	//to the left child of our current node, this effectivly passes the left
	//subtree to the function.
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
		//else do this stuff to the right. node->right
	}
	return node;
}

void bst::preorder()
{
	//if node->left != NULL recurse
	preorderHelper( root );
	cout << endl; 

}

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

int main()
{
	bst bst1;

	bst1.partialInsert(5);

	for(int i = 0; i < 10; i++)
	{
		bst1.partialInsert(i);
	}
	bst1.preorder();
	return 0;
}
