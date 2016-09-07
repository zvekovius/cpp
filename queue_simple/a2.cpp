//Zac Vekovius
//CSC300
//Assignment 2 - Queue

#include <iostream>
#include <fstream>

//Command List:
//1 - enq
//2 - deq 
//3 - front
//4 - isEmpty
//5 - printq
//End Command List

using namespace std;

//Define a struct for the queue.
struct queue{
	int val;
	queue* next;
};

//Class to handle all queue operations.

class queueOps{
public: 
	queueOps();
	void enq(int);
	void deq();
	void front();
	bool isEmpty();
	void printq();
private:
	queue* head;
	queue* back;
};

queueOps::queueOps()
{
	head = NULL;
	back = NULL;
}

void queueOps::enq(int data)
{
	//Create the new structure member.
	queue* tmp;
	tmp = new queue;
	tmp->val = data;
	tmp->next = NULL;

	//Create a pointer to hold the previous position.
	queue* previousPos;

	//Create a pointer to traverse the list.
	queue* traverseList;

	if( head != NULL )
	{
		//Use the back pointer to append to the queue.
		back->next = tmp;
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

void queueOps::deq()
{
	if(head != NULL)
	{
		//Creat new pointer to store temp position.
		queue* newHead;
		
		//Set the next item in queue to temp pointer from head -> next.
		newHead = head->next;
	
		//Release the current head.
		delete(head);
		
		//Make the head the next item in line.
		head = newHead;
	}
	else
	{
		//Do nothing. No list to act on.
	}
}

void queueOps::front()
{
	//Check to make sure there is a queue to get front of.
	if( head != NULL )
	{
		//Print the value of head->val
		cout << "Front: " << head->val << endl;
	}
}

bool queueOps::isEmpty()
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

void queueOps::printq()
{
	cout << "Back -->";

	queue* tmp; 
	tmp = head; 

	while( tmp != NULL)
	{
		cout << tmp->val << " ";
		tmp = tmp->next;
	}

	cout << "<-- Front" << endl;
}

int main()
{
	//Create Class.
	queueOps* q = new queueOps();

	//Setup file.
	ifstream commands;
	commands.open("cmd.txt");

	//Variable to hold command and data.
	int command = 0;
	int data = 0;
	
	while(commands >> command)
	{
		if( command == 1 )
		{
			commands >> data;
		}
		switch(command)
		{
			case 1 : q->enq(data);
					break;
			
			case 2 : q->deq();
					break;

			case 3 : q->front();
					break;

			case 4 :
					if( q->isEmpty())
					{
						cout << "Queue is empty." << endl;
					}
					else
					{
						cout << "Queue is not empty." << endl;
					}
					break;
			
			case 5 : q->printq();
					break;

			default : cout << "Invalid commands, skipping." << endl;
		}
	}
	commands.close();

	delete(q);

	return 0;
}
