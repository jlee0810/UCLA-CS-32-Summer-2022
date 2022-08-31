#include "LinkedList.h"

using namespace std;

LinkedList::LinkedList()
{
    head = nullptr; //initialize head to nullptr
}

LinkedList::LinkedList(const LinkedList& rhs) //Copy constructor
{
    if (rhs.head == nullptr) //If rhs is empty, set head to nullptr
        head = nullptr;
    
    else //rhs is not empty
    { 
        head = new Node; //Create a new node
        head->value = rhs.head->value; //Set the value of the new node to the value of the reference linked list
        Node *curr = head; //Create a node pointer to point to the head node
        Node *rhsCurr = rhs.head->next; //We already copied over rhs head node so create a pointer of the node after the head of rhs
        while (rhsCurr != nullptr) //Until the last node of the reference linked list
        {
            curr->next = new Node; //Make a new node and have the current node point to it as the next node
            curr = curr->next; //Move the current node to the next node
            curr->value = rhsCurr->value; //Set the value of the current node to the value of the current node of the reference linked list
            rhsCurr = rhsCurr->next; //Move the node pointer to the next node of the reference linked list
        }
        curr->next = nullptr; //Set the next node of the last node of the new copied linked list to nullptr
    }
}

LinkedList::~LinkedList()
{
    Node *p = head; //Create a node pointer to point to the head node
    while (p != nullptr) //Until the last node
    {
        Node *n = p -> next; //Create a node pointer to point to the next node of the current node
        delete p; //Delete the current node
        p = n; //Set the current node to the next node
    }
}


const LinkedList& LinkedList::operator=(const LinkedList& rhs) //Assignment Operator
{
	if (this == &rhs) //Check for alliasing 
	{
        return *this;
	}

    //Since it is not an alias delete the original linked list
    Node *p = head; 
    while (p != nullptr) //Until the last node
    {
        Node *n = p -> next;
        delete p; 
        p = n; 
    }

    if (rhs.head == nullptr) //If rhs is empty, set head to nullptr
        head = nullptr;
    
    else //rhs is not empty so we essentially use the copy constructor again
    {
        head = new Node; //Create a new node
        head->value = rhs.head->value; //Set the value of the new node to the value of the reference linked list
        Node *curr = head; //Create a node pointer to point to the head node
        Node *rhsCurr = rhs.head->next; //We already copied over rhs head node so create a pointer of the node after the head of rhs
        while (rhsCurr != nullptr) //Until the last node of the reference linked list
        {
            curr->next = new Node; //Make a new node and have the current node point to it as the next node
            curr = curr->next; //Move the current node to the next node
            curr->value = rhsCurr->value; //Set the value of the current node to the value of the current node of the reference linked list
            rhsCurr = rhsCurr->next; //Move the node pointer to the next node of the reference linked list
        }
        curr->next = nullptr; //Set the next node of the last node of the new copied linked list to nullptr
    }

    return *this;
}

void LinkedList::insertToFront(const ItemType &val)
{
    Node *p = new Node; //Make a new node and have a node pointer point to it
    p->value = val; //Set the value of the new node to the value passed in
    p->next = head; //Set the next node of the new node to the head node
    head = p; //Set the head node to the new node
}


void LinkedList::printList() const
{
    Node *p = head; //Create a node pointer to point to the head node
    if (p == nullptr) //If empty simply return and do nothing
        return;
    else {
        while (p != nullptr) //Until the node pointer is not nullptr 
        {
        cout << p->value << " "; //Print the value of the current node and have a space then move the pointer to the next node
        p = p->next;
        }
        cout << endl; //Spec requires that function ends with a new line
    }
}


bool LinkedList::get(int i, ItemType& item) const 
{
    int size = this->size(); //Get the size of the linked list
	if (i < 0 || i >= size) //Check for the validity of the index passed in (i.e. if it is less than 0 or greater than or equal to the size of the linked list it is invalid)
		return false;

	Node* p = head; //Create a node pointer to point to the head node

	for (int indexP = 0; indexP < i; indexP++) 
	{
		p = p->next;
	}
	item = p->value;
	return true;
}

void LinkedList::reverseList()
{
    Node *current = head; //have the "current" node to point to head
    Node *prev = nullptr; //have the prev and next node to point to nullptr
    Node *next = nullptr;

    while (current != nullptr) { //until current becomes a nullptr set current's next node as previous node
        next = current -> next;
        current -> next = prev;
        prev = current;
        current = next; 
    }

    head = prev; //Set head accordingly
}

void LinkedList::printReverse() const
{
    if (head == nullptr) //If empty list simply return and do nothing
        return;
    
    Node *p = head; //Create a node pointer to point to the head node
    int counter = 0; //Create two counters to keep track of the number of nodes in the linked list
    int numberOfNodes = 0; 
    while (p != nullptr) {
        counter++;
        numberOfNodes++;
        p = p->next;
    }

    string *list = new string[counter]; //Create a string array to store the values of the linked list
    p = head;
    while (p != nullptr) {//Starting from the end of the array enter the values of the linked list (right to left)
        list[counter - 1] = p->value;
        p = p->next;
        counter--;
    }

    for (int i = 0; i < numberOfNodes; i++) { //Now read the array from beginning to end (left to right)
        cout << list[i] << " ";
    }

    delete [] list; //delete the list so we dont end up with memory leak
    cout << endl; //newline after the last item
}

void LinkedList::append(const LinkedList &other) 
{   
    //Return the copy of other if linked list is empty
    if (head == nullptr)
        *this = other; //Assignment operator in use
    
    //Since we know list is not empty, append other to the end of this linked list
    else
    {
        Node *p = head; //Have the pointer point to the last node of this linked list
        while (p->next != nullptr) 
        {
            p = p->next; 
        }
        LinkedList temp = other; //Make a copy of the other linked list (copying not inefficient in this case because we need to append the entire linked list anyways)

        Node *q = temp.head; 
        p->next = q; //Set the next node of the last node of this linked list to the head node of temp
        temp.head = nullptr; //Set the head node of temp to nullptr
    }
}

void LinkedList::swap(LinkedList &other) //To swap LL we simply just have to switch heads
{
    Node *temp = head;
    head = other.head;
    other.head = temp;
}

int LinkedList::size() const
{
    int count = 0; //Initialize a counter variable and until p becomes a nullptr increment by one at each node
    Node *p = head;
    while (p != nullptr)
    {
        count++;
        p = p->next;
    }
    return count;
}