//Project 1 Phase 1 
//Name: Maria Arriola
//Description: Creates a hash table of double linked lists that contains athletes with it's information.
//Athletes can be added, searched, deleted, and displayed. 
/*At first the hash function I chose was the division method but there were too many collisions
therefore to minimize the collisions I instead implemented the multiplication method for creating
my hash function. An advatage of this method is that the hash table size 
is not critical. The constant alpha has to be bigger than zero but less 
than 1 therefore I chose the number 0.234262434. The number of 
collisions decreased when comparing to the hash function implementing 
the division method. 
*/
#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <cstring>
#include <fstream>

#define alpha 0.234262434

using namespace std;

//struct Athlete represents some athlete with it's information
struct Athlete
{
    string discipline, gender, team_or_ind, event, venue, medal, person, country;
};

//class LinkedList will contains a linked list of athletes

struct Node{

    struct Athlete * athlete;
    struct Node * next;
};
class LinkedList
{
private:
    struct Node* head;


public:
    LinkedList();

    void  addAthlete(struct Athlete *);
    struct Athlete *athletesearch(string);
    struct Athlete *athletedelete(string);
    void printList();
    int count;
};

//Constructor to initialize the linked list
LinkedList::LinkedList()
{
    head = NULL;
    count = 0;
}

/**
 * loops through the linkedlist until it finds the athlete
 * and returns struct Athlete *foundAtlhete or NULL if the athlete does not exist.
 */

struct Athlete* LinkedList::athletesearch(string athleteinfo)
{
    struct Node *temp= head;
    while(temp!=NULL)
    {

        if((temp->athlete->discipline+temp->athlete->gender+temp->athlete->event+temp->athlete->person).compare(athleteinfo)==0)
        {
                return temp->athlete;
        }
        else
            temp=temp->next;
    }
    return NULL;
}

//searches for a specific athlete by going through the linkedlist of athletes until found and deleted or returns NULL.
struct Athlete* LinkedList::athletedelete(string athleteinfo)
{   struct Node *temp= head->next;
    struct Node *prev=head;

    if(head == NULL)//list is empty
        return NULL;

 	//delete head
    if((head->athlete->discipline+head->athlete->gender+head->athlete->event+head->athlete->person).compare(athleteinfo)==0)
    {
        head=head->next;
        count--;
        return prev->athlete;
    }

    //delete the athlete when its located inbetween or is the last node in the linkedlist
    while(temp!=NULL)
    {
        if((temp->athlete->discipline+temp->athlete->gender+temp->athlete->event+temp->athlete->person).compare(athleteinfo)==0)
        {
                prev->next= temp->next;
           		count--;
                return temp->athlete;


        }
        else
        {
            temp=temp->next;
            prev= prev->next;
        }

    }
    return NULL;  //athlete doesn't exist
}


//Adds athletes to the linked list along with the athletes data and returns true
void  LinkedList::addAthlete(struct Athlete * athlete)
{
    struct Node * newNode = (struct Node *) malloc(sizeof(struct Node));
    newNode->athlete = athlete;

	if (head ==NULL)
	{
		head = newNode;
		head->next=NULL;
	}
	else
	{
	newNode->next = head;
	head=newNode;
	}
   // newNode->next = head;
   // head = newNode;
    count++;

   // return true;
}

//Prints the entire list of athletes in the linkedlist including their information
void LinkedList::printList()
{
    Node* current=head;
    if(head==NULL)
    {
        cout<<"The list is empty\n"<<endl;
    }
    else
    {
        while(current!=NULL)
        {
            cout << endl;
            cout<<"discipline:\t " << current->athlete->discipline<<endl;
            cout<< "gender: \t"<<current->athlete->gender<< endl;
            cout<<"team_or_ind:\t" <<current->athlete->team_or_ind<<endl;
            cout<<"event:\t" <<current->athlete->event<<endl;
            cout<<"venue:\t" <<current->athlete->venue<<endl;
            cout<<"medal:\t" <<current->athlete->medal<<endl;
            cout<<"athlete:\t"<<current->athlete->person<<endl;
            cout<<"country:\t" <<current->athlete->country<<endl;

            current=current->next;
        }
        return;
    }
}

//Converts the user input string into a number
int stringtonumber(string word)
{
    const char* arr= word.c_str();
    int size=0;
    size_t i;
    for( i  = 0; i< word.length(); i++ )
    {
        size = arr[i]+size;
    }
    return size;
}

//Includes the hash function which returns the index which identifies where the string should be placed in hash table
int gethash(string word, int tablesize)
{
    int size= stringtonumber(word);
    int hash = tablesize*(size*alpha-((int)(size*alpha))); //hash function
    return hash;
}

//inserts the  new athlete into the hash table
void hash_insert(struct Athlete *newAthlete, int size, LinkedList**hashTable)
{
    int index = gethash(
            newAthlete->discipline + newAthlete->gender + newAthlete->event + newAthlete->person,
            size);
    hashTable[index]->addAthlete(newAthlete);

}

//deletes the athlete from the hash table by calling the delete  funciton of the linked list
 Athlete * hash_delete(string search, int size, LinkedList **hashTable)
 {
     int indextosearch = gethash(search, size);
     //cout << "index: " << indextosearch << endl;
     LinkedList *temp = hashTable[indextosearch];
     struct Athlete * result = temp->athletedelete(search);
     return result;
 }

//searches at a specific index of the hash table and goes through the linked list until  the athlete is found
Athlete * hash_search(string search, int size, LinkedList **hashTable) {
    int indextosearch = gethash(search, size);
    //cout << "index: " << indextosearch << endl;
    LinkedList *temp = hashTable[indextosearch];
    struct Athlete * result = temp->athletesearch(search);
    return result;
}

int main() {
    int size=0;
    string line;
    getline(cin,line);
    istringstream ss(line);
    ss>>size;

//creates the hash table
    LinkedList **hashTable = (LinkedList**) malloc(sizeof(LinkedList)*size);
    for(int k = 0; k < size; k++){
        hashTable[k] = new LinkedList();
    }

    //retrieves inputes of athletes
    getline(cin, line);
    while(line.compare("InsertionEnd")!=0) {
        struct Athlete *newAthlete = (struct Athlete *) malloc(sizeof(struct Athlete));

        char *str = (char *) line.c_str();

        char *token = strtok(str, ",");
        newAthlete->discipline = token;
        token = strtok(NULL, ",");
        newAthlete->gender = token;
        token = strtok(NULL, ",");
        newAthlete->team_or_ind = token;
        token = strtok(NULL, ",");
        newAthlete->event = token;
        token = strtok(NULL, ",");
        newAthlete->venue = token;
        token = strtok(NULL, ",");
        newAthlete->medal = token;
        token = strtok(NULL, ",");
        newAthlete->person = token;
        token = strtok(NULL, ",");
        newAthlete->country = token;

        hash_insert(newAthlete, size, hashTable);
        getline(cin,line);
    }
    int number;
    getline(cin, line);
    istringstream st(line);
    st >> number;
     for(int i=0; i<number;i++)
     {
         getline(cin,line);
         char *str = (char *) line.c_str();

         char *token = strtok(str, ",");
         if(line.compare("hash_display")==0)
         {

             for(int j=0; j<size;j++ )
             {
                 cout << endl;
                 cout<<"index: "<<j<<", linked list size:  " <<hashTable[j]->count<<endl;
                 hashTable[j]->printList();
             }

         }

         if(strcmp(str, "hash_search")==0)
         {
             string search = "";
             token = strtok(NULL, ",");
             search= search+token;
             string discipline = token;
             token = strtok(NULL, ",");
             string gender= token;
             search= search+token;
             token = strtok(NULL, ",");
             string event = token;
             search= search+token;
             token = strtok(NULL, ",");
             string athlete = token;
             search= search+token;


             struct Athlete * result = hash_search(search, size, hashTable);

             if(result!=NULL)
             {
                 cout<<"The medal recipient "+result->person+ " has the medal of "+result->medal<<endl;
             }
             else
             {
                 cout<<athlete+" for "+discipline+" with event "+ event+" not found"<<endl;
             }


         }
         else if(strcmp(str, "hash_delete")==0)
         {
             string search = "";
             token = strtok(NULL, ",");
             search= search+token;
             string discipline = token;
             token = strtok(NULL, ",");
             string gender= token;
             search= search+token;
             token = strtok(NULL, ",");
             string event = token;
             search= search+token;
             token = strtok(NULL, ",");
             string athlete = token;
             search= search+token;

             struct Athlete * result = hash_delete(search, size, hashTable);
             if(result!=NULL)
             {

                 cout<<"The medal recipient "+result->person+ " for "+result->discipline+" with event "+result->event+ " deleted"<<endl;
                 delete result;
             }
             else
             {
                 cout<<athlete+" for "+discipline+" with event "+ event+" not found"<<endl;
             }
         }


     }

}









