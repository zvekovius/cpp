This program takes a command file and does stuff to a queue.

//Command List:
//1 - enq
//2 - deq 
//3 - front
//4 - isEmpty
//5 - printq
//End Command List

File must be named cmd.txt 

Sample file included. Takes commands that are whitespace delimited. 

The queue is not implemented with the head being the usual "first". It is actually the last where head->next = NULL. This allows us to print the line like back-->n, n, n <---first.

