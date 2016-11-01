#include <iostream>
#include <iomanip>
#include <fstream>
#include <stack>
#include <queue>
#include <vector>

//Using Stack Class
//stack<int> mystack;
//mystack.push()
//mystack.pop()

using namespace std;

class graph_list{
public:
	graph_list();
	graph_list(int, int);
	void setEdge(int, int);
	void printGraph();
	void dfs(int);
	void bfs(int);
	void dfs_st(int);
	void bfs_st(int);
	bool directed;
private:
	struct listNode{
		int val;
		listNode* next;
	};
	int nodeCount;
	listNode* list;
};

graph_list::graph_list()
{
	nodeCount = 0;
	list = NULL;
}

graph_list::graph_list(int nodes, int dir)
{
	int i;
	nodeCount = nodes + 1;

	list = new listNode[ nodeCount ];

	if( dir == 1 )
		directed = true;
	else
		directed = false;

	for(i=0; i < nodeCount; i++)
	{
		list[i].val = -1;
		list[i].next = NULL;
	}
}

void graph_list::setEdge( int source, int destination )
{
		//Directed Implementation.
		listNode* tmp = NULL;
		tmp = new listNode();
		tmp->val = destination;
		tmp->next = list[source].next;
		list[source].next = tmp;
}

void graph_list::printGraph()
{
	int i;
	listNode* tmp;

	for(i=0; i < nodeCount; i++)
	{
		cout << i << " | ";

		tmp = list[i].next;
	
		while(tmp != NULL )
		{
			cout << "-->" << tmp->val;
			tmp = tmp->next;
		}
		cout << "--> NULL" << endl;
	}
}

void graph_list::dfs( int start )
{
	stack<int> s;
	vector<bool> visited;
	listNode* tmp; 
	int i = 0, node;

	for( i = 0; i < nodeCount; i++)
		visited.push_back(false);
	
	s.push(start);

	while( !s.empty() )
	{
		//Node is just an int. Not the whole object. Just the value of the object
		node = s.top();
		s.pop();
		if( !visited[node])
		{
			cout << node;
			visited[node] = true;
			tmp = list[node].next;
			while( tmp != NULL )
			{
				if( !visited[tmp->val])
					s.push(tmp->val);
				tmp = tmp->next;
			}
		}	
	}
	cout << endl;
}

//Needs work.
void graph_list::dfs_st( int start )
{

	stack<int> s;
	vector<bool> visited;
	vector<int> tree;
	listNode* tmp; 
	int i = 0, node;

	for( i = 0; i < nodeCount; i++)
	{	
		visited.push_back(false);
		tree.push_back(-1);
	}

	s.push(start);

	while( !s.empty() )
	{
		//Node is just an int. Not the whole object. Just the value of the object
		node = s.top();
		s.pop();
		if( !visited[node])
		{
			if( tree[node] != -1 )
			{
				cout << "(" << tree[node] << ", " << node << ")";
			}
			visited[node] = true;
			tmp = list[node].next;
			while( tmp != NULL )
			{
				if( !visited[tmp->val])
				{
					s.push(tmp->val);
					tree[tmp->val] = node;
				}				
				tmp = tmp->next;
			}
		}	
	}
	cout << endl;
}

void graph_list::bfs( int start )
{
	queue<int> q;
	vector<bool> visited;
	listNode* tmp; 
	int i = 0, node;

	for( i = 0; i < nodeCount; i++)
		visited.push_back(false);
	
	q.push(start);

	while( !q.empty() )
	{
		//Node is just an int. Not the whole object. Just the value of the object
		node = q.front();
		q.pop();
		if( !visited[node])
		{
			cout << node;
			visited[node] = true;
			tmp = list[node].next;
			while( tmp != NULL )
			{
				if( !visited[tmp->val])
					q.push(tmp->val);
				tmp = tmp->next;
			}
		}	
	}
	cout << endl;
}

//Needs work
void graph_list::bfs_st( int start )
{
	queue<int> q;
	vector<bool> visited;
	vector<int> tree;
	listNode* tmp; 
	int i = 0, node;

	for( i = 0; i < nodeCount; i++)
	{	
		visited.push_back(false);
		tree.push_back(-1);
	}
	
	q.push(start);

	while( !q.empty() )
	{
		//Node is just an int. Not the whole object. Just the value of the object
		node = q.front();
		q.pop();
		if( !visited[node])
		{
			if( tree[node] != -1 )
			{
				cout << "(" << tree[node] << ", " << node << ")";
			}
			visited[node] = true;
			tmp = list[node].next;
			while( tmp != NULL )
			{
				if( !visited[tmp->val])
				{
					q.push(tmp->val);
					if( tree[tmp->val] == -1 )
						tree[tmp->val] = node;
				}				
				tmp = tmp->next;
			}
		}	
	}
	cout << endl;
}

int main ()
{
	ifstream file;
	int nodes, src, dst, dir;
	graph_list* gl = NULL;

	file.open("dat.txt");
	file >> nodes;
	file >> dir;

	gl = new graph_list(nodes, dir);

	while( file >> src )
	{
		file >> dst;
		gl->setEdge( src, dst );
		if(!gl->directed)
			gl->setEdge( dst, src );
	}
	
	file.close();

	ifstream commands;
	commands.open("cmd.txt");


	//Variable to hold command and data.
	int command = 0;
	int data = 0;
	
	while(commands >> command)
	{
		if( command == 1 or command == 2 or command == 3 or command == 4 )
		{
			commands >> data;
		}
		switch(command)
		{
			case 1 : gl->dfs( data );
					break;
			
			case 2 : gl->bfs( data );
					break;

			case 3 : gl->dfs_st( data );
					break;

			case 4 : gl->bfs_st( data );
					break;
					
			default : cout << "Invalid command, skipping." << endl;
		}
	}
	commands.close();

	return 0;
}
