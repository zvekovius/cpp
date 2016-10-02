#include <iostream>
#include <fstream>

using namespace std;
// 1 - Insert
// 2 - Inorder
// 3 - Postorder
// 4 - Preorder
// 5 - Search
// 6 - Delete
// 7 - findHeight
// 8 - findMin
// 9 - findMax

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
	void remove(int);
	void height();

private:
	treeNode* partialInsertHelper(int, treeNode*);
	void preorderHelper(treeNode*);
	void postorderHelper(treeNode*);
	void inorderHelper(treeNode*);
	treeNode* searchHelper(int, treeNode*, treeNode* );
	void removeHelper(int, treeNode*, treeNode*);
	int heightHelper();
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
		cout << "Inserting: " << val << endl;
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
	//with searchHelper using the pointer method, we can call it by other functions and get useful returns (like remove).

	//A value to return to the user facing side.
	bool found;

	//Declare a pointer to determing if the search helper found our value.
	treeNode* foundPtr;	
	
	//Set the base condition to NULL.
	foundPtr = NULL;
	
	//Set pointer = to the searchHelper function.
	foundPtr = searchHelper( val, root, foundPtr );

	

	//Check if searchHelper returned anything.
	if( foundPtr == NULL )
	{
		found = false;
	}
	else 
	{
		found = true;
	}

	//Return bool.
	return found;
}


treeNode* bst::searchHelper( int val, treeNode* node, treeNode* found )
{
	
	if(node != NULL )
	{
		if( val == node->val )
		{
			found = node;
			return found;
		}

		else if( val < node->val )
		{
			return searchHelper( val, node->left, found);
		}
		else if( val >= node->val )
		{	
			return searchHelper( val, node->right, found);
		}

	}
	else if( root == NULL )
		cout << "Tree empty." << endl; 
	found = NULL; 
	return found;
}


void bst::remove( int val )
{
	/* This function calls searchHelper function to get the value we are looking for. This allows the function to avoid any recursive calls if its not needed.
	   However, this does potentially include another search through the tree. The thinking behind this is to reduce another O(n) call if it isn't needed. Since searching is O(log(n)) we should have some wins for calling it before jumping into a O(n) function. */

	//Pointer to hold return from search.
	treeNode* removalPointer;
	//Pointer to aide in switching values around.
	treeNode* tmp = NULL;

	//Search for our value.
	removalPointer = searchHelper( val, root, removalPointer );
	
	if( removalPointer != NULL )
	{
		cout << "Removing: " << val << endl; 
		//Begin case tests
		
		//If we have an orphan leaf, recurse.
		if( removalPointer->left == NULL and removalPointer->right == NULL)
		{
			removeHelper( val, root, tmp );
		}

		//If we have a parent with two children, recurse.
		if( removalPointer->left != NULL and removalPointer->right != NULL)
		{
			removeHelper( val, root, tmp );
		}
		//Case does not require recusrive function.
		else if( removalPointer->left != NULL and removalPointer->right == NULL)
		{
			tmp = removalPointer->left;
			removalPointer->val = tmp->val; 
			removalPointer->left = tmp->left;
			delete(tmp);
		}
		//Case does not require recusrive function.
		else if( removalPointer->left == NULL and removalPointer->right != NULL )
		{
			tmp = removalPointer->right; 
			removalPointer->val = tmp->val; 
			removalPointer->right = tmp->right; 
			delete(tmp); 
			//removeHelper( val, removalPointer );
		}
	}
	else
		cout << "Value: " << val << " cannot be removed. Not found." << endl;
}

void bst::removeHelper( int val, treeNode* node, treeNode* tmp )
{
	//parent nodes (2 children)
	//--> Find the largest item in the left subtree
	//--> Find the smallest item in the right subtree
	//--> Put that node in place of the one you want to remove.
	cout << "I'm going to recurse to delete!" << endl;

	//Since this function is called, we know the value is somewhere in the tree.
	if( node != NULL )
	{
		if ( val == node->val )
		{
			tmp = node; 		
			cout << "Found value for recurse removal." << endl;
		}
		else if( val < node-> val )
			return removeHelper( val, node->left, tmp );
		else if( val >= node->val )
			return removeHelper( val, node->right, tmp );
			
		if( tmp != NULL )
		{
			cout << "I should be ignored until the last call returns." << endl;
		}
	}	
}

void bst::height()
{

}

int bst::heightHelper()
{
//Number of nodes to the root, from the deepest node in the tree.
//Recursively calculate the height of the left subtree
//Recurse calc. the height of the right subtree
//Figure out which one is bigger and add one.
//Return that back.

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
		if( command == 1 or command == 5 or command == 6 )
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
			case 6 : bst1->remove( data );
					break;

//			case 7 : bst1->height();
//					break;

//			case 8 : bst1->findMin();
//					break;

//			case 9 : bst1->findMax();
//					break;
			default : cout << "Invalid command, skipping." << endl;
		}
	}
	commands.close();
	
	return 0;
}
