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
/* This queue will be implemented with the tail being a usual "head" and the head will actually be the "last"element in the list where head->next is NULL. This will allow us to prin the list back->front. All enqueue operations will be prepending elements onto the queue. */

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

	cout << "ENQ: " << tmp->val << endl;

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

//This is now a priority dequeue.
void queueOps::deq()
{
	if(head != NULL)
	{
		//Creat new pointer to store temp position.
		queue* lowestNode;
		queue* previousNode;
		queue* beforeLowest;

		//Since head->next won't be a value, we need to traverse to find when the pointer is null.
		queue* traverseQueue;
		
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
			if( lowestNode->val >= traverseQueue->val )
			{
				lowestNode = traverseQueue;
				beforeLowest = previousNode;
			}
			previousNode = traverseQueue;
			traverseQueue = traverseQueue->next;

			if(lowestNode->val >= traverseQueue->val and traverseQueue == head )
			{
				lowestNode = traverseQueue;
				beforeLowest = previousNode;
			}

		}

		//If there is only 1 element in the list.

		if(head == back )
		{
			cout << "DEQ: " << head->val << endl;
			delete(head);
			head = NULL;
			back = NULL;
		}
		else if( head == lowestNode )
		{
			cout << "DEQ: " << lowestNode->val << endl;
			delete(lowestNode);
			head = beforeLowest;
			head->next = NULL; 
		}
		else if( back == lowestNode )
		{
			cout << "DEQ: " << lowestNode->val << endl;
			back = back->next;
			delete(lowestNode);
		}
		else
		{
			cout << "DEQ: " << lowestNode->val << endl;
			beforeLowest->next = lowestNode->next;
			delete(lowestNode);
		}
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

	//Only attempt to print if there is something in the queue.
	if( head != NULL )
	{
		queue* tmp; 
		tmp = back; 
		
		while( tmp != NULL)
		{
			cout << tmp->val << " ";
			tmp = tmp->next;
		}
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
