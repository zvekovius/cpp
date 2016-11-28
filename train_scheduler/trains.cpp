#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>
#include <vector>
#include <climits>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;


/*
// Remaining Items to Implement:
- Find the shortest OVERALL travel time (layovers included)
----> Input: Departure station number, arrival station number, time you will arrive at your departure station in 24 hour format (HH:MM).
- Change canReach & directRoute functions to care about times when adding to the queue.
- Cleanup duplication of code (3 different functions for is there a route, shortest route, shortest route overall).

Program Assumes:
-> There will be no station name duplication
-> Station names are not case sensitive (e.g. Rapid_city is the same as rapid_city)
-> Locale & Unicode are not issues with matching station names.


*/


class train_manage{
public:
	train_manage(int); //Initialize the class.
	void setEdge( int, int, int, int); //Add a train movement to the schedule.
	void addStation( int, string ); //Add a station to the list.	
	string findStationByNumber(int); //Function to print station name given its number
	int findStationByName(string); //Function to print station number given its name. 
	vector<string> stations;//Array to hold the stations. - Public so it can be called from main during testing. MOVE ME TO PRIVATE
	bool debug; //Turns on debug statements
	void printGraph();
	void printSchedule();
	bool determineDirect(int,int);
	void shortestTrainRide(int,int);
	bool canReachDest(int,int);
	bool overallShortestRoute( int,int,int);
	int stringToInt( string );
	
private:
	int nodeCount; //Keeps track of how many stations we have.
	//Structure to hold the train schedule.
	struct listNode{
		int dst_station;
		int dep_time;
		int arv_time;
		int ride_time;
		listNode* next;
	};
	struct queuep{
		int val;
		int weight;
		queuep* next;
	};
	struct totalTime {
		int dep_station;
		int dst_station;
		int train_time;
		int layover_time;
		totalTime* next;
	};
	void enq(int,int);
	int next();
	void deq();
	bool isEmpty();
	//Array to hold the parents of all listNodes.
	listNode* list;	
	queuep* head;
	queuep* back;
};

train_manage::train_manage(int nodes)
{
	debug = false;
	nodeCount = 0;
	nodeCount = nodes + 1;
	int i;
	
	list = new listNode[ nodeCount ];
	
	
	//Initialize the array for all initial values. Use -1 as no times, or stations will use negative ints.
	for( i = 0; i < nodeCount; i++ )
	{
		list[i].dst_station = -1;
		list[i].dep_time = -1;
		list[i].arv_time = -1;
		list[i].ride_time = -1;
		list[i].next = NULL;

		stations.push_back("Undefined");
	}
}

void train_manage::setEdge( int source, int destination, int dtime, int atime )
{
	//Train schedule will be a directed graph in nature.
	listNode* tmp = NULL; 
	tmp = new listNode();
	tmp->dst_station = destination;
	tmp->dep_time = dtime;
	tmp->arv_time = atime;
	tmp->ride_time = atime - dtime;
	tmp->next = list[source].next;
	list[source].next = tmp;
}

void train_manage::addStation( int station_number, string station_name )
{
	stations[station_number] = station_name;
}

string train_manage::findStationByNumber(int station)
{
	//Indexing a value larger than the array or less than the array will seg fault.
	//Domain is 0->INT_MAX
	if( station < nodeCount and station >= 0 and station < INT_MAX )
	{
		string station_name = stations[station];
		
		if( station_name == "Undefined" )
			return "Station Number Not defined";
		else
			return station_name;
	}
	else
	{
		return "Error, Station Number does not exist";
	}
}

int train_manage::findStationByName(string station)
{
	bool found = false;
	string compare_string = ""; //String to lower & compare against input.
	
	for( int i = 0; i < nodeCount; i++)
	{
		//Set string & set all case to lower.
		compare_string = stations[i];
		std::transform(compare_string.begin(), compare_string.end(), compare_string.begin(), ::tolower);
		if(compare_string == station)
		{
			found = true;
			return i;
		}
	}
	if(!found)
		return -1;
}

void train_manage::printGraph()
{
	int i;
	listNode* tmp;

	cout << "Dep. Station | --> Arrival Station (dep. time)(arr. time) -->" << endl;
	
	for(i=0; i < nodeCount; i++)
	{
		cout << i << " | ";

		tmp = list[i].next;
	
		while(tmp != NULL )
		{
			cout << "-->" << tmp->dst_station << "(" << tmp->dep_time << ")" << "(" << tmp->arv_time << ")" << "(" << tmp->ride_time << ")";
			tmp = tmp->next;
		}
		cout << "--> NULL" << endl;
	}
}

void train_manage::printSchedule()
{
	int i = 0;
	
	//Variables to get formatted times from minutes since midnight to HH:MM (24 hour format).
	int time = 0;
	int hours = 0;
	int minutes = 0;
	int format_time_dep_hours = 0;
	int format_time_dep_minutes = 0;
	int format_time_arr_hours = 0;
	int format_time_arr_minutes = 0;
	
	listNode* tmp; 
	
	for(i=0; i < nodeCount; i++)
	{
		tmp = list[i].next;
		
		while(tmp != NULL)
		{
			time = tmp->arv_time - tmp->dep_time;
			hours = time/60;
			minutes = time % 60;
			format_time_dep_hours = tmp->dep_time / 60;
			format_time_dep_minutes = tmp->dep_time % 60;
			format_time_arr_hours = tmp->arv_time / 60;
			format_time_arr_minutes = tmp->arv_time % 60;
			
			//Clean me up.
			cout << i << "-" << stations[i] << " leaves at " << setfill('0') << setw(2) << format_time_dep_hours << ":" << setfill('0') << setw(2) << format_time_dep_minutes << " and arrives at " << tmp->dst_station << "-" << stations[tmp->dst_station] << " at " << setfill('0') << setw(2) << format_time_arr_hours << ":" << setfill('0') << setw(2) << format_time_arr_minutes << ", " << hours << " hr and " << minutes << " min total." << endl;
			tmp = tmp->next;
		}
	}
}

bool train_manage::determineDirect( int dep, int arr )
{
	int i = 0;
	bool found;
	
	listNode* tmp;
	tmp = list[dep].next;
		
	while(tmp != NULL)
	{
		if( tmp->dst_station == arr )
		{
			found = true;
			break;
		}
		else
			tmp = tmp->next;
	}
}

void train_manage::shortestTrainRide( int start, int dst )
{
	//Using Dijkstra's to find shortest path.
	vector<bool> visited;
	vector<int> cost;
	listNode* tmp; 
	int i = 0, node;
	bool reachable = false;
	int hours = 0;
	int minutes = 0;

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
				//cost[node] + current_cost (tmp->ride_time) <-- That's from node. cost[node] is from start -> node.
				if(debug)
				{
					cout << "Cost[Node]: " << cost[node] << endl;
					cout << "tmp->dst_station: " << tmp->dst_station << endl;
					cout << "tmp->ride_time: " << tmp->ride_time << endl;
					cout << "cost[node] + tmp->ride_time < cost [tmp->dst_station]" << endl;
					cout << cost[node] << " + " << tmp->ride_time << " < " << cost[tmp->dst_station] << endl;				
				}
				if ( tmp->ride_time + cost[node] < cost[tmp->dst_station] )
					cost[tmp->dst_station] = tmp->ride_time + cost[node];				
				else if( (cost[node] + tmp->ride_time) < cost[tmp->dst_station] )
					cost[tmp->dst_station] = tmp->ride_time + cost[tmp->dst_station];
				if( tmp->dst_station == dst )
					reachable = true;
				if( !visited[tmp->dst_station])
					enq(tmp->dst_station, tmp->ride_time);
				tmp = tmp->next;
			}
		}	
	}
	
	//If it can be reached using different trains:
	if(reachable)
	{
		hours = cost[dst]/60;
		minutes = cost[dst]%60;
		
		cout << "To go from " << stations[start] << " to " << stations[dst] << " you will need to the train for " << hours << " hours and " << minutes << " minutes." << endl;
	}
	else
		cout << "Your destintation is not reachable from that depature station" << endl;
}

bool train_manage::canReachDest( int start, int dst )
{
	//Using Dijkstra's to find shortest path.
	vector<bool> visited;
	vector<int> cost;
	listNode* tmp; 
	int i = 0, node;
	bool reachable = false;
	int hours = 0;
	int minutes = 0;

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
				//cost[node] + current_cost (tmp->ride_time) <-- That's from node. cost[node] is from start -> node.
				if(debug)
				{
					cout << "Cost[Node]: " << cost[node] << endl;
					cout << "tmp->dst_station: " << tmp->dst_station << endl;
					cout << "tmp->ride_time: " << tmp->ride_time << endl;
					cout << "cost[node] + tmp->ride_time < cost [tmp->dst_station]" << endl;
					cout << cost[node] << " + " << tmp->ride_time << " < " << cost[tmp->dst_station] << endl;				
				}
				if ( tmp->ride_time + cost[node] < cost[tmp->dst_station] )
					cost[tmp->dst_station] = tmp->ride_time + cost[node];				
				else if( (cost[node] + tmp->ride_time) < cost[tmp->dst_station] )
					cost[tmp->dst_station] = tmp->ride_time + cost[tmp->dst_station];
				if( tmp->dst_station == dst ) 
				{	
					reachable = true;
				}
				if( !visited[tmp->dst_station])
					enq(tmp->dst_station, tmp->ride_time);
				tmp = tmp->next;
			}
		}	
	}
	return reachable;
}

bool train_manage::overallShortestRoute( int start, int dst, int start_time )
{
	//Using Dijkstra's to find shortest path.
	vector<bool> visited;
	vector<int> cost;
	vector<int> parent;
	listNode* tmp; 
	listNode* previous;
	int i = 0, node = -1;
	bool reachable = false;
	bool found = false;
	int hours = 0; //Conversion variables from minutes since midnight -> 24 Hour format
	int minutes = 0;
	int layover_hold = -1; //Holds the layover time from the last parent node.
	int compare = 0; //We can't over-write layover-hold, so have a compare value for adding to all weights.

	//Initialize all vectors.
	for( i = 0; i < nodeCount; i++)
		visited.push_back(false), cost.push_back(INT_MAX), parent.push_back(-1);
	
	//Set the weight to the starting value and sent our starting value to the queue with a weight of 0.
	cost[start] = 0;
	enq(start, 0);
	
	//While the priority queue is not empty.
	while( !isEmpty())
	{
		//Node is just an int. Not the whole object. Just the value of the object
		//Get the next node in the queue.
		node = next();
		//Pop it from priority queue.
		deq();
		
		//If we haven't locked this node in yet, start processing it.
		if( !visited[node])
		{
			//For this implementaiton, if we have reached our destination, we are done.
			if(node == dst)
				break;
			
			//Mark the node as done & visisted.
			visited[node] = true;
			
			//Set our traversal pointer to the first node in the graph.
			tmp = list[node].next;
			
			
			//Setting the layover time for the base case.
			//base case condition
			if( node == start )
				layover_hold = start_time;
			//iteration cases (holdovers).
			else
				layover_hold = previous->arv_time;
			while( tmp != NULL )
			{
				compare = tmp->dep_time - layover_hold;
				//Subtract the depature time of the next value from the arv_time of the last train.
				if( node == start)
				{
					if(compare >= 0)
						found = true;
				}
				//cost[node] + current_cost (tmp->ride_time) <-- That's from node. cost[node] is from start -> node.
				if(debug)
				{
					//Debug statements for following the calculations.
					cout << "Going from: " << node << " to " << tmp->dst_station << endl;
					cout << "Cost[Node]: " << cost[node] << endl;
					cout << "tmp->dst_station: " << tmp->dst_station << endl;
					cout << "tmp->ride_time: " << tmp->ride_time << endl;
					cout << "layovertime " << compare << endl;
					cout << "cost[node] + tmp->ride_time < cost [tmp->dst_station]" << endl;
					cout << cost[node] << " + " << tmp->ride_time << " < " << cost[tmp->dst_station] << endl;				
				}
				
				//Set distance if our layover time + ride time is less thant he current cost, we haven't visited the node and the current cost is not Infinity.
				if ( ((tmp->ride_time + compare) + cost[node] < cost[tmp->dst_station]) && !visited[tmp->dst_station] && cost[node] != INT_MAX )
				{	
					cost[tmp->dst_station] = tmp->ride_time + compare + cost[node];
					if(parent[node] == -1)
						parent[node] = tmp->dst_station;
				}

				//Keep track if we actually get to our destination or not.
				if( tmp->dst_station == dst ) 
				{
					reachable = true;
				}
				//layover_hold makes sure the schedule is actually possible.
				//This assumes if arr_time & dep_time at one station are the same, the traveler would
				//still make it. 0 would be threshold of layover time.
				//If its negative, it won't work.
				
				//If we haven't verified this node yet, place it on the queue to be processed. The Queue is priority so we don't worry abou the weight yet. 
				//Process the layover time to this node, if its less than 0 we assume that train will not work for us.
				if( !visited[tmp->dst_station] and compare >= 0)
				{
					previous = tmp;
					enq(tmp->dst_station, tmp->ride_time + compare);
					
					/*
					if( parent[node] == -1 )
						parent[node] = tmp->dst_station;*/
				}
				tmp = tmp->next;
			}
			//If we have gone through all of the trains for the start station with the given time & have not returned a true found boolean. 
			//Exit with false as there is no way to leave the first station.
			if( node == start && !found)
				return false;
		}	
	}
	cout << endl;
	
	for( i=start; i < nodeCount; i++ )
	{
		if(parent[i] != -1)
		{
			cout << "(" << i << "," << parent[i] << ")";
		}
	}
	return reachable;
}

/* ----------------------------------- Utility Functions  --------------------------------
------------------------ Functions not satisfying user input directly --------------------
*/

int stringToInt( string convert )
{
	int result = -1;
	stringstream ss(convert);
	return ss >> result ? result: -1;
}

void train_manage::enq(int data, int weight)
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

int train_manage::next()
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

void train_manage::deq()
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
bool train_manage::isEmpty()
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


int main ()
{
	ifstream stationsFile;
	int source = 0, destination = 0, dep_time = 0, arr_time = 0, nodes = 0, station_number = 0;
	int userIn = 0;
	bool route = false;
	int colon_found = 0;
	string station_name = "";
	train_manage* tm = NULL;
	string dep_time_s = ""; //string to keep user input for departure time in 24 hour format. 
	string hours_s = ""; //String to keep the split dep_time_s hours.
	string minutes_s = ""; //String to keep the minutes of dep_time_s.
	int hours = 0; //Integer to keep the hours from string conversion to be converted to minutes since midnight. 
	int minutes = 0; //Integer to keep the hours from string conversion to be converted to minutes since midnight.
	
	stationsFile.open("stations.dat");
	if(stationsFile)
	{
		//This loop is duplicated... But we need a way to get total # of nodes to init our class.
		while( stationsFile >> station_number )
		{
			stationsFile >> station_name;
			nodes++;
		}
		
		stationsFile.clear();
		stationsFile.seekg(0, ios::beg);
		

		
		tm = new train_manage(nodes);
		
		while( stationsFile >> station_number )
		{
			stationsFile >> station_name;
			tm->addStation( station_number, station_name );
		}
		
		stationsFile.close();
	}
	else
	{
		cout << "Could not open stations.dat" << endl;
		return 1;
	}
	
	ifstream schedule; 
	
	schedule.open("trains.dat");
	if(schedule)
	{
		while( schedule >> source )
		{
			schedule >> destination;
			schedule >> dep_time;
			schedule >> arr_time;
			tm->setEdge( source, destination, dep_time, arr_time );
		}
	}
	else
	{
		cout << "Could not open trains.dat" << endl;
		return 1;
	}
	
	schedule.close();
	
	cout << "Stations & Train Schedule Loaded" << endl;
	cout << "Welcome to the Train Scheduler 2000!" << endl;
	
	do {
		cout << "----------------------------------------" << endl;
		cout << "Enter one of the following options" << endl;
		cout << "Enter 7 or Ctrl+C to exit Train Scheduler 2000" << endl;
		cout << "Option 0 - Print Complete Train Schedule" << endl;
		cout << "Option 1 - Find station by name" << endl;
		cout << "Option 2 - Find station by number" << endl;
		cout << "Option 3 - Determine if there is a direct route from one station to another" << endl;
		cout << "Option 4 - Determine if you can get from one station to another" << endl;
		cout << "Option 5 - Find shortest riding time between two stations" << endl;
		cout << "Option 6 - Find overall travel time from one station to another" << endl;
		cout << "Option 7 - Exit Train Scheduler 2000" << endl;
		if(tm->debug)
			cout << "Option 8 - Print Graph" << endl;
		cout << "----------------------------------------" << endl;
		cout << "Option: ";
		cin >> userIn;
		switch(userIn)
		{
			case 0:
				tm->printSchedule();
				break;
			case 1:
				cout << "Enter Station Name to search for: ";
				cin >> station_name;
				std::transform(station_name.begin(), station_name.end(), station_name.begin(), ::tolower);
				station_number = tm->findStationByName( station_name );
				if(station_number != -1)
					cout << station_name << " is station number: " << station_number << endl;
				else
					cout << "Station name not found" << endl;
				break;
			case 2:
				cout << "Enter the station number you want the name for: ";
				cin >> station_number;
				station_name = tm->findStationByNumber( station_number );
				cout << station_name << endl;
				break;
			case 3: 
				cout << "Enter your departing station: ";
				cin >> source;
				cout << "Enter your destination station: ";
				cin >> destination;
				
				route = tm->determineDirect( source, destination );
				
				//Clean output up.
				if(route)
					cout << "There is a direct route from: " << source << "-" << tm->stations[source] << " to " << destination << "-" << tm->stations[destination] << endl;
				else
					cout << "There is not a direct route from: " << source << "-" << tm->stations[source] << " to " << destination << "-" << tm->stations[destination] << endl;
				break;
			case 4:
				cout << "Enter your departing station: ";
				cin >> source;
				cout << "Enter your destination station: ";
				cin >> destination;
				
				route = tm->canReachDest( source, destination );
				if(route)
					cout << "There is a route from " << tm->stations[source] << " to " << tm->stations[destination] << endl;
				else
					cout << "There is not a route from " << tm->stations[source] << " to " << tm->stations[destination] << endl;
				break;
			case 5:
				cout << "Enter your departing station: ";
				cin >> source;
				cout << "Enter your destination station: ";
				cin >> destination;
				tm->shortestTrainRide(source, destination);
				break;
			case 6:
				cout << "Enter your departing station: ";
				cin >> source;
				cout << "Enter your destination station: ";
				cin >> destination;
				cout << "Enter your departing time (24 Hour format HH:MM): ";
				cin >> dep_time_s;
				
				//Split the string give by user into hours & minutes
				if((colon_found = dep_time_s.find(":")) != string::npos)
				{
					hours_s = dep_time_s.substr(0, colon_found);
					minutes_s = dep_time_s.substr(colon_found+1, string::npos);
				}
				
				//converstion from string hours_s to in hours & string minutes_s to int minutes.
				hours = stringToInt(hours_s);
				minutes = stringToInt(minutes_s);
				if( hours == -1 or minutes == -1)
				{
						cout << "Error converting user time to integer. Exiting" << endl;
						return 1;
				}
				if( hours >= 24 or hours < 0 or minutes >= 60 or minutes < 0)
				{
					cout << "Time entered is not valid" << endl;
					return 1;
				}
				
				//Now that we have them converted to ints, make them the same time metric the graph uses (minutes since midnight).
				hours = hours * 60; 
				dep_time = hours + minutes;
				if(tm->debug)
					cout << "Dep Time after conversion is: " << dep_time << endl;
				
				//After everything is gathered from user, send to the Dijkstra function to print out a shortest overall tree.
				if(!tm->overallShortestRoute(source, destination, dep_time))
					cout << "You cannot get to your destintation with that given time, ensure there is at least a route from your depature to your arrival station (Option 4)" << endl;
				
				break;
			case 7: 
				return 0;
			case 8: 
				tm->printGraph();
				break;
			default:
				cout << "Invalid Option" << endl;
				break;
		}
	} while( userIn != 7 );
	return 0;
}