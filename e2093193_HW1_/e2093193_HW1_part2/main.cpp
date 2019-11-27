#include <iostream>
#include <stdlib.h>
#include<fstream>
#include<string>
#include <limits>
#include <map>
//STORING TEXT VALUES INTO 2D ARRAY FUNCTION IS TAKEN FROM
 //https://stackoverflow.com/questions/30441732/store-txt-file-values-into-2d-array

 //ONLY DFT ALGORITHM WORKS IN PART 2. BFT ALGORITHM DOES NOT WORK.

using namespace std;

const int MaxStackSize=50;
const int WIDTH = 6;
const int HEIGHT = 6;
int visited[6];
int visited_queue[6]={0,0,0,0,0,0};
int c=0;
int d=0;
char set_vertex;
const char visitchar[6] = {'A', 'B', 'C', 'D', 'E', 'F'}; //initializing visitchar
const char queuechar[6] = {'A', 'B', 'C', 'D', 'E', 'F'}; //initializing queuechar
template <class T>
class Stack
{
private:
T stacklist[MaxStackSize];
int top;

public:
Stack(void) // constructor to initialize top modification operations
{
    top=-1;
}
void Push(const T& item)
{
  //can not push if stack has exceeded its limits
if (top==MaxStackSize-1)
{
cerr<<"Stack overflow"<<endl;
exit(1);
}
// increment top ptr and copy item into list
top++;
stacklist[top] =item;
}
T Pop(void) //Pop
{
T temp;
if (top==-1) // if stack empty nothing to pop
{
cerr<<"Stack empty"<<endl; exit(1);
}
temp=stacklist[ top] ; // record the top element
top--; // decrement top and return the earlier top element
return temp;
}
void ClearStack(void) //just copy top item without modifying stack contents
{
top=-1;
}
T Peek(void) const
{
T temp;
if (top==-1) // if stack empty nothing to pop
{
 exit(1);
}
temp=stacklist[ top] ; // record the top element //  return the earlier top element
return temp;
} //check stack state returns top element value without removal
int StackEmpty(void) const //returns true if the stack is empty
{
    return top==-1; // value is 1 if equal, 0 otherwise
}
int StackFull(void) const //returns true if the stack is full
{
    return top==MaxStackSize-1;
}
};


const int MaxQSize=50;
template <class T>
class Queue

{
private: // queue array and its parameters

int front, rear, count;
T qlist[ MaxQSize] ;

public: //constructor

Queue(void)
{
 front=0;
 rear=0;
 count=0;
} // initialize data members
//queue modification operations
void QInsert(const T& item)
{
if (count==MaxQSize) // terminate if queue is full
{
cerr<<"Queue overflow! "<<endl;
exit(1);
}
count++; //increment count, assign item to qlist and update rear
qlist[rear] =item;
rear=(rear+1)% MaxQSize;
}
T QDelete(void)
{
T temp;
if (count==0) // if qlist is empty, terminate the program
{
cerr<<"Deleting from an empty queue!"<<endl;
}
temp=qlist[front] ; count--; //record value at the front of the queue decrease count
front=(front+1) % MaxQSize; return temp; // advance front and return former front
}
void ClearQueue(void);  // queue access

T QFront(void) const // queue test methods
 {
    return qlist[front];
}

int QLength(void) const // a function which finds the size of the queue
{
    return count;
}
int QEmpty(void) const // if the queue is empty
{
    return (count == 0);
}
int QFull(void) const // if the queue is full
{
    return (count == MaxQSize);
}
};
int condition(char f) // condition function which assigns characters to numbers
{
int g;
   switch (f)
   {
       case 'A': g=0; return g; break;
       case 'B': g=1; return g; break;
       case 'C': g=2; return g; break;
       case 'D': g=3; return g; break;
       case 'E': g=4; return g; break;
       case 'F': g=5; return g; break;
   }
}


 int main()
    {
        int input[HEIGHT][WIDTH]; // STORING TEXT VALUES INTO 2D ARRAY FUNCTION IS TAKEN FROM https://stackoverflow.com/questions/30441732/store-txt-file-values-into-2d-array
        Stack<int> s;
        Queue<int> q;

        cout<< "Please enter the destination : ";
        cin>>set_vertex;

        for(int i = 0; i < HEIGHT; i++)
        {
            for(int j = 0; j < WIDTH; j++)
            {
                input[i][j] = 0;
            }
        }

        std::ifstream file("EE441HW1.txt");
        for(int i = 0; i < HEIGHT; i++)
        {
            std::string row;
            if (file >> row) {
                for (int j = 0; j != std::min<int>(WIDTH, row.length()) ; ++j)
                {
                    input[i][j] = row[j]-0x30;
                }

            } else break;
        }

        for(int i=0;i<6;i++) //Initializing visited matrix elements to zero.
        {
         visited[i]=0;
        }

        q.QInsert(queuechar[0]); //visiting starting_Vertex
        visited_queue[0]=1; //  remember that starting_Vertex is visited

  while (!q.QEmpty())  //
        {
            d=condition(q.QFront()); // starting vertex's condition
            q.QDelete(); // delete the front when the queue is not empty vertex
            for(int i=0; i<6; i++)
            {
                if (input[d][i]== 1)
                {
                    if(visited_queue[i]==0)
                    {
                     visited_queue[i]=1; //Visit all unvisited vertices that are reachable from the deleted vertex
                     q.QInsert(queuechar[i]); //Insert these new vertices to the queue


                    }
                }

            }
        }

        s.Push(visitchar[0]); //visiting starting_Vertex
        visited[0]=1;     //  remember that starting_Vertex is visited
        cout<<"DFT Algorithm : "<<visitchar[0]<<" ";

       while (!s.StackEmpty()) //when the stack is not empty
        {
            c=condition(s.Peek());  // starting vertex's condition
		for (int i=0; i<6;i++)
		{
			{
			if(input[c][i]==1)
				if (visited[i]==0) // If the vertex is not visited
				{
					visited[i]=1; //Visit an unvisited vertex reachable from the vertex at the top of the stack
					s.Push(visitchar[i]); //Push that vertex on to the stack
					cout<<visitchar[i]<<" ";
					c=i;
					if(visitchar[i] == set_vertex) // when destination is equal to the visited char, clear the stack and go out of the while loop
                    {
                        s.ClearStack(); //
                        break;
                    }
					break;
				}
			}
			if (i==5){ //If all vertices reachable from the vertex at the top of the stack are visited, pop the stack
				s.Pop();
			}
		}
	}
    }

