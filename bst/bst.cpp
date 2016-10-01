#include <iostream>
#include <fstream>

using namespace std;
// 1 - Insert
// 2 - Inorder
// 3 - Postorder
// 4 - Preorder
// 5 - Search


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
	bool search(int);

private:
	treeNode* partialInsertHelper(int, treeNode*);
	void preorderHelper(treeNode*);
	void postorderHelper(treeNode*);
	void inorderHelper(treeNode*);
	bool searchHelper(int, treeNode*);
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
		//If value is less than root, to the left.
		if( val < node->val )
		{
			//cout << "going left " << val << endl;
			node->left = partialInsertHelper(val, node->left);
		}
		//If value is greather than root, to the right.
		else if ( val >= node->val )
		{
			//cout << "going right " << val << endl;
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
		postorderHelper(node->left);
		postorderHelper(node->right);
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
		inorderHelper(node->left);
		cout << node->val << " "; 
		inorderHelper(node->right);
	}
}

bool bst::search( int val )
{
	bool found;
	found = searchHelper( val, root );	
	return found;
}


bool bst::searchHelper( int val, treeNode* node )
{
	
	if(node != NULL )
	{
		if( val == node->val )
		{
			return true;
		}

		else if( val < node->val )
		{
			return searchHelper( val, node->left);
		}
		else if( val >= node->val )
		{	
			return searchHelper( val, node->right);
		}

	}
	return false;
}

int main()
{
	bst* bst1 = new bst();
	
	ifstream commands;
	commands.open("cmd.txt");

	//Variable to hold command and data.
	int command = 0;
	int data = 0;
	
	while(commands >> command)
	{
		if( command == 1 or command == 5 )
		{
			commands >> data;
		}
		switch(command)
		{
			case 1 : bst1-> partialInsert( data );
					break;
			
			case 2 : bst1->inorder();
					break;

			case 3 : bst1->postorder();
					break;

			case 4 : bst1->preorder();
					break;
					
			case 5 : 
					if( bst1->search( data ) == true )
					{
						cout << "We found: " << data << endl;
					}
					else
					{
						cout << "We did not find: " << data << endl;
					}
					break;

			default : cout << "Invalid command, skipping." << endl;
		}
	}
	commands.close();
	
	return 0;
}
