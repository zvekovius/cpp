#include <iostream>
#include <iomanip>
#include <fstream>
#include <stack>
#include <queue>
#include <vector>
#include <climits>

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
	int next();
	void enq(int, int);
	void deq();
	bool isEmpty();
	void dkstra(int, int);
	void prim( int );
	bool directed;
private:
	struct listNode{
		int val;
		int weight;
		listNode* next;
	};
	//implement my own priority queue as I couldn't get the STL class priority queue to happen correctly.
	struct queuep{
		int val;
		int weight;
		queuep* next;
	};
	int nodeCount;
	listNode* list;
	bool debug;
	queuep* head;
	queuep* back;
};

graph_list::graph_list()
{
	nodeCount = 0;
	list = NULL;
}

graph_list::graph_list(int nodes, int dir)
{
	debug = false;
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

	head = NULL;
	back = NULL;
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

void graph_list::enq(int data, int weight)
{
	//Create the new structure member.
	queuep* tmp;
	tmp = new queuep;
	tmp->val = data;
	tmp->weight = weight;
	tmp->next = NULL;


	if( head != NULL )
	{
		//Use the back pointer to append to the queue.
		tmp->next = back;
		back = tmp;
	}
	else
	{
		//Set the head and back pointers as this value is everything.
		head = tmp;
		head->next = NULL;
		back = tmp; 
		back->next = NULL;
	}
}

int graph_list::next()
{
	if(head != NULL)
	{
		//Creat new pointer to store temp position.
		queuep* lowestNode;
		queuep* previousNode;
		queuep* beforeLowest;

		//Since head->next won't be a value, we need to traverse to find when the pointer is null.
		queuep* traverseQueue;
		
		//Set the pointer to the back of the queue.
		traverseQueue = back;
		
		//Set all tracking nodes to the end of the queue.
		previousNode = traverseQueue;
		beforeLowest = traverseQueue;
		lowestNode = traverseQueue;
		

		//Find the highest value in the queue closest to head (equal to).
		//Also track the node before the highest value for fixup.
		while( traverseQueue->next != NULL )
		{
			if( lowestNode->weight >= traverseQueue->weight )
			{
				lowestNode = traverseQueue;
				beforeLowest = previousNode;
			}
			previousNode = traverseQueue;
			traverseQueue = traverseQueue->next;

			if(lowestNode->weight >= traverseQueue->weight and traverseQueue == head )
			{
				lowestNode = traverseQueue;
				beforeLowest = previousNode;
			}

		}

		//If there is only 1 element in the list.

		if(head == back )
		{
			return head->val;
		}
		else
		{
			return lowestNode->val;
		}
	}
	else
	{
		return 0;
	}
}

void graph_list::deq()
{
	if(head != NULL)
	{
		//Creat new pointer to store temp position.
		queuep* lowestNode;
		queuep* previousNode;
		queuep* beforeLowest;

		//Since head->next won't be a value, we need to traverse to find when the pointer is null.
		queuep* traverseQueue;
		
		//Set the pointer to the back of the queue.
		traverseQueue = back;
		
		//Set all tracking nodes to the end of the queue.
		previousNode = traverseQueue;
		beforeLowest = traverseQueue;
		lowestNode = traverseQueue;
		

		//Find the highest value in the queue closest to head (equal to).
		//Also track the node before the highest value for fixup.
		while( traverseQueue->next != NULL )
		{
			if( lowestNode->weight > traverseQueue->weight )
			{
				lowestNode = traverseQueue;
				beforeLowest = previousNode;
			}
			previousNode = traverseQueue;
			traverseQueue = traverseQueue->next;

			if(lowestNode->weight >= traverseQueue->weight and traverseQueue == head )
			{
				lowestNode = traverseQueue;
				beforeLowest = previousNode;
			}

		}

		//If there is only 1 element in the list.

		if(head == back )
		{
			delete(head);
			head = NULL;
			back = NULL;
		}
		else if( head == lowestNode )
		{
			delete(lowestNode);
			head = beforeLowest;
			head->next = NULL; 
		}
		else if( back == lowestNode )
		{
			back = back->next;
			delete(lowestNode);
		}
		else
		{
			beforeLowest->next = lowestNode->next;
			delete(lowestNode);
		}
	}
	else
	{
		//Do nothing. No list to act on.
	}
	


}
bool graph_list::isEmpty()
{
	//Check if head is null or not. If it is, return 1. Else return 0.
	if( head == NULL )
	{
		return true;
	}
	else
	{
		return false;
	}
}

void graph_list::dkstra( int start, int dst )
{
	vector<bool> visited;
	vector<int> cost;
	listNode* tmp; 
	int i = 0, node;

	for( i = 0; i < nodeCount; i++)
		visited.push_back(false), cost.push_back(INT_MAX);
	
	cost[start] = 0;

	enq(start, 0);

	while( !isEmpty())
	{
		//Node is just an int. Not the whole object. Just the value of the object
		node = next();
		deq();
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
					enq(tmp->val, tmp->weight);
				tmp = tmp->next;
			}
		}	
	}
	cout << "Dijkstra's" << endl;
	cout << "Source: " << start << endl; 
	cout << "Destination: " << dst << endl;
	cout << "Cost: " << cost[dst] << endl;
}


void graph_list::prim( int start )
{
	cout << "Prim: " << endl;
	vector<bool> visited;
	vector<int> tree;
	vector<int> cost;
	listNode* tmp; 
	int i = 0, node;

	for( i = 0; i < nodeCount; i++)
		visited.push_back(false), cost.push_back(INT_MAX), tree.push_back(-1);
	
	cost[start] = 0;

	enq(start, 0);


	while( !isEmpty() )
	{
		//Node is just an int. Not the whole object. Just the value of the object
		node = next();
		deq();
		if( !visited[node])
		{
			if(debug)
					cout << "Before tree print 1" << endl;
			if( tree[node] != -1 )
			{
				cout << "(" << tree[node] << ", " << node << ")";
			}
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
				{
					enq(tmp->val, tmp->weight);
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
	int nodes, src, dst, dir, weight, dest;
	bool direct;
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
	direct = gl->directed;
	file.close();

	ifstream commands;
	commands.open("cmd.txt");


	//Variable to hold command and data.
	int command = 0;
	int data = 0;
	
	while(commands >> command)
	{
		if( command == 1 or command == 2 or command == 3 or command == 4 or command == 5 or command == 6 )
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

			case 5 : if(direct)
					{						
						cout << "Undirected graph, Dijkstra may fail, running Prim's as well." << endl;
						gl->prim( data );
					}					
					gl->dkstra( data, dest );
					break;

			case 6 : if(!direct)
					 { 
						cout << "Directed graph, prim may fail. No Destination to run Dijkstra." << endl;
					 }				
					gl->prim( data );
					
					break;

			case 9 : gl->printGraph();
					break;
					
			default : cout << "Invalid command, skipping." << endl;
		}
	}
	commands.close();

	return 0;
}
