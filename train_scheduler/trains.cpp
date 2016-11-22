#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>
#include <vector>
#include <climits>
#include <string>
#include <algorithm>

using namespace std;

// Remaining Items to Implement:
/*
- Is station B reachable from Station A. 
----> Input: Depature and Arrival station number.
- Shortest riding time between 2 stations (hours:minutes) from A to B
----> Only time spent on train (no layover time).
----> If no route is there, alert user. 
----> Input: Departure and arrival station number
- Find the shortest OVERALL travel time (layovers included)
----> Input: Departure station number, arrival station number, time you will arrive at your departure station in 24 hour format (HH:MM).


Program Changes / Questions for Instructor:
-> Move the stations vector to private after done debugging.
-> Check output screen shots and make sure functions return similar output
-> Which file will always come first? Stations or train schedule? -- Assume station definitions?
-> Can we assume the stations file will not try to overwrite a station that is already defined?


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
private:
	int nodeCount; //Keeps track of how many stations we have.
	//Structure to hold the train schedule.
	struct listNode{
		int dst_station;
		int dep_time;
		int arv_time;
		listNode* next;
	};
	
	//Array to hold the parents of all listNodes.
	listNode* list;	
};

train_manage::train_manage(int nodes)
{
	debug = true;
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
			cout << "-->" << tmp->dst_station << "(" << tmp->dep_time << ")" << "(" << tmp->arv_time << ")";
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

int main ()
{
	ifstream stationsFile;
	int source = 0, destination = 0, dep_time = 0, arr_time = 0, nodes = 0, station_number = 0;
	int userIn;
	bool route = false;
	string station_name = "";
	train_manage* tm = NULL;
	
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
				cout << "Enter your beginning station: ";
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