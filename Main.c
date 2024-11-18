#include <stdio.h>
#include <stdlib.h> //Added for malloc


//declares a data type named Queue
struct Queue
{
   int head; // head will hold the index of head
   int tail; //tail will hold the index of tail
   unsigned int length; //variable length holds the length of the queue
   char *data; // the array that will hold the data of the queue in order
};

// Build of a queue
//first allocates memory for the structure, queue. Then allocates memory for the array of the queue.
//stores the size of the array in the the structure.
//it will provide an error messege if the memory was not allocated successfully.
//initializes the head and tail elements to 0, and initailizes all values of the queue to -128.
void build(struct Queue **q, unsigned int length)
{
   // Allocate memory for the queue structure
   *q = (struct Queue*) malloc(sizeof(struct Queue));
  
   if (!(*q)) //checks if the space in memory for the queue structure was allocated
   {
       //prints error message if the memory was not allocated
       printf("build()>> Error: Failed to allocate memory for the queue structure.\n");
       exit (1);
       
   }
  
   (*q)->length = length;   // Sets the size of the queue to be equal the length submitted in the build parentheses
   (*q)->data = (char*) malloc(length * sizeof(char)); // Allocates memory for the array
  
   if (!(*q)->data)//Checks if the space in memory for the data array was allocated
   {
       //Prints error message if the memory was not allocated
       printf("build()>> Error: Failed to allocate memory for the queue data.\n");
       free(*q); // Frees the previously allocated Queue structure if the memory was not allocated
       exit(1);
   }


   (*q)->head = 0;  // Initializes head to 0
   (*q)->tail = 0;  // Initializes tail to 0
  
   // Initialize all elements to a default value (e.g., -128)
   for (unsigned int i = 0; i < length; i++)
   {
       (*q)->data[i] = -128;
   }

    //Only prints the following messages if the function worked properly and did not encounter any errors.
   printf("build()>> Building a queue of length %u\n", length); 
   printf("build()>> Allocated memory for the structure at address %p.\n", &(*q)->data);
   printf("build()>> Initialized all elements of data to -128\n");
}

//Enqueue function
//First, it checks if the queue is already full (overflow)
//If the queue is not full, it adds a value to the tail and increments the tail by one unit.
void enqueue(struct Queue *q, char x)
{
   //Checks for overflow
   if (((*q).tail + 1) % (*q).length == (*q).head)
   {
       //prints if the queue was attempted to overflow
       printf("\nenqueue()>> Attempt to overflow the queue at %p was prevented.\n", &(*q).data[(*q).tail]);
       return;// returns and does not add to the queue or increment the tail
   }
  
   q->data[q->tail] = x;  // Adds the element x at the tail
  
   if ((*q).tail == (*q).length) //If the tail is already at the end of the array, it sets the tail as 1 in order to allow for a circular Queue.
       (*q).tail = 1;
      
   else (*q).tail = ((*q).tail + 1); //If the tail is not at the end of the array, it simply increments it to the next index.
  
}

//Dequeue function
//First, it checks if the queue is empty (underflow)
//If the queue is not empty, it stores the value in the head and moves the head to the next index.
//The old value of head which is stored in x is then returned.
char dequeue(struct Queue *q)
{
   //Checks for underflow
   if (q->head == q->tail)
   {
       printf("\ndequeue()>> Attempt to underflow the queue at %p was prevented.\n", &(*q).data[(*q).head]);
       return -127;  // Return an error value (-127 indicates underflow), does not dequeue or increment the head
   }
  
   char x = (*q).data[(*q).head]; //Stores the value in head inside of x
  
   if ((*q).head == (*q).length)//Moves the head forward cicularly.
       (*q).head = 1;
   else (*q).head = (*q).head + 1;
  
   return x; //Returns the value that is dequeued
}

//Start of main function
int main(int argc, const char * argv[]) {
  
   struct Queue *qptr = NULL;// Creates a queue pointer and points it to null


   build(&qptr, 5);//Builds the queue of size 5
   // ====== Beginn Test Case 1
   enqueue(qptr, 1); //Calls for the enqueue function to insert "1" into tail and increment the tail to the next slot
   enqueue(qptr, 2); //Calls for the enqueue function to insert "2" into tail and increment the tail to the next slot
   enqueue(qptr, 3); //Calls for the enqueue function to insert "3" into tail and increment the tail to the next slot
   enqueue(qptr, 4); //Calls for the enqueue function to insert "4" into tail and increment the tail to the next slot
   enqueue(qptr, 5); // This should trigger an overflow prevention because the queue is already full
   enqueue(qptr, 6); // Another overflow attempt
   printf("Dequeue() %d \n", dequeue(qptr)); //Dequeues head and returns the first value of 1
   printf("Dequeue() %d \n", dequeue(qptr)); //Dequeues head and returns the second value of 2
   printf("Dequeue() %d \n", dequeue(qptr)); //Dequeues head and returns the third value of 3
   printf("Dequeue() %d \n", dequeue(qptr)); //Dequeues head and returns the fourth value of 4
   printf("Dequeue() %d \n", dequeue(qptr)); //Triggers an underflow error!! Because the Queue is already empty
   printf("Dequeue() %d \n", dequeue(qptr)); //Triggers an underflow error!! Because the Queue is already empty
   // ====== End Test Case 1
  
   // frees anything that was created with malloc
   if (qptr->data) free(qptr->data);
   if(qptr) free(qptr);
   printf("\n");
   return 0;
}
//End of main function
