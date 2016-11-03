#include <iostream>
#include <iomanip>
#include <fstream>
#include <stack>
#include <queue>
#include <vector>
#include <climits>

//Using Stack Class
//stack<int> mystack;
//mystack.push()
//mystack.pop()

using namespace std;

class graph_list{
public:
	graph_list();
	graph_list(int, int);
	void setEdge(int, int, int);
	void printGraph();
	void dfs(int);
	void bfs(int);
	void dfs_st(int);
	void bfs_st(int);
	void dkstra(int, int);
	bool directed;
private:
	struct listNode{
		int val;
		int weight;
		listNode* next;
	};
	int nodeCount;
	listNode* list;
	bool debug;
};

graph_list::graph_list()
{
	nodeCount = 0;
	list = NULL;
}

graph_list::graph_list(int nodes, int dir)
{
	debug = true;
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

void graph_list::setEdge( int source, int destination, int weight )
{
		//Directed Implementation.
		listNode* tmp = NULL;
		tmp = new listNode();
		tmp->val = destination;
		tmp->weight = weight;
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
			cout << "-->" << tmp->val << "(" << tmp->weight << ")";
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

void graph_list::dkstra( int start, int dst )
{
	queue<int> q;
	vector<bool> visited;
	vector<int> cost;
	listNode* tmp; 
	int i = 0, node;

	for( i = 0; i < nodeCount; i++)
		visited.push_back(false), cost.push_back(INT_MAX);
	
	cost[start] = 0;

	q.push(start);

	while( !q.empty() )
	{
		//Node is just an int. Not the whole object. Just the value of the object
		node = q.front();
		q.pop();
		if( !visited[node])
		{
			visited[node] = true;
			tmp = list[node].next;
			while( tmp != NULL )
			{
				//cost[node] + current_cost (tmp->weight) <-- That's from node. cost[node] is from start -> node.
				if(debug)
				{
					cout << "Cost[Node]: " << cost[node] << endl;
					cout << "tmp->val: " << tmp->val << endl;
					cout << "tmp->weight: " << tmp->weight << endl;
					cout << "cost[node] + tmp->weight < cost [tmp->val]" << endl;
					cout << cost[node] << " + " << tmp->weight << " < " << cost[tmp->val] << endl;				
				}
				if ( tmp->weight + cost[node] < cost[tmp->val] )
					cost[tmp->val] = tmp->weight + cost[node];				
				else if( (cost[node] + tmp->weight) < cost[tmp->val] )
					cost[tmp->val] = tmp->weight + cost[tmp->val];
				if( !visited[tmp->val])
					q.push(tmp->val);
				tmp = tmp->next;
			}
		}	
	}
	cout << "Dijkstra's" << endl;
	cout << "Source: " << start << endl; 
	cout << "Destination: " << dst << endl;
	cout << "Cost: " << cost[dst] << endl;
}

int main ()
{
	ifstream file;
	int nodes, src, dst, dir, weight, dest;
	graph_list* gl = NULL;

	file.open("dat.txt");
	file >> nodes;
	file >> dir;

	gl = new graph_list(nodes, dir);

	while( file >> src )
	{
		file >> dst;
		file >> weight;
		gl->setEdge( src, dst, weight );
		if(!gl->directed)
			gl->setEdge( dst, src, weight );
	}
	
	file.close();

	ifstream commands;
	commands.open("cmd.txt");


	//Variable to hold command and data.
	int command = 0;
	int data = 0;
	
	while(commands >> command)
	{
		if( command == 1 or command == 2 or command == 3 or command == 4 or command == 5 )
		{
			commands >> data;
		}
		if( command == 5 )
			commands >> dest;

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

			case 5 : gl->dkstra( data, dest );
					break;

			case 9 : gl->printGraph();
					break;
					
			default : cout << "Invalid command, skipping." << endl;
		}
	}
	commands.close();

	return 0;
}
