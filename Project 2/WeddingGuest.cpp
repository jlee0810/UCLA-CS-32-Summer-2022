#include "WeddingGuest.h"
using namespace std;


WeddingGuest::WeddingGuest()
{
    m_size = 0; //Added a private member variable size to ease the process
    m_head = nullptr;
    m_tail = nullptr;
}

WeddingGuest::WeddingGuest(const WeddingGuest& other) 
{
    m_size = other.m_size; //set size equal to reference

    if (other.m_head == nullptr) { //If other list is empty, set head and tail to nullptr
        m_head = nullptr;
        m_tail = nullptr;
    } 
        
    else { //Utilized the singly linked list copy constructor and tweaked it to set the tail accordingly
        m_head = new Node; //Currently there is only one node so head and tail are both equal to the same node
        m_tail = m_head;

        m_head-> value = other.m_head->value; //Copy over the value, name from the first node
        m_head->firstName = other.m_head->firstName;
        m_head->lastName = other.m_head->lastName;
        m_head->next = nullptr; 
        m_head->prev = nullptr; 

        Node *curr = m_head; //Create a pointer to the current node
        Node *otherCurr = other.m_head-> next; //Create a pointer to the other node's second node
        while (otherCurr != nullptr) //Until othercurr runs out of nodes
        {
            curr->next = new Node; //Create new node and assign it as current's next node
            curr->next->prev = curr; //Set current's next node's previous node to current

            curr = curr->next; //move over to the newly made node 
            curr->value = otherCurr->value; //copy over the values/names
            curr->firstName = otherCurr->firstName;
            curr->lastName = otherCurr->lastName;

            otherCurr = otherCurr->next;
        }
        curr->next = nullptr; //At the last node so set it's next  as nullptr and set it as the tail
        m_tail = curr;
    }
}

WeddingGuest::~WeddingGuest() 

{
    Node* p = m_head; //Loop through all the nodes and delete one by one
    while (p != nullptr) {
        Node* temp = p;
        p = p-> next;
        delete temp;
    }
}


WeddingGuest& WeddingGuest::operator=(const WeddingGuest& other)
{
    if (& other == this) //check for aliasing 
        return *this;
    
    WeddingGuest temp(other); //Make a temporary temp double linked list to make a copy and use our swap function to get all the guests
    swapWeddingGuests(temp); 
    return *this;
}

bool WeddingGuest::noGuests() const
{
    if (m_size == 0) //We have our memember variable of size and if it is 0 == no guest if not there are guests
        return true;
    else
        return false;
}

int WeddingGuest::guestCount() const
{
    return m_size; //Just return our member variable size
}

bool WeddingGuest::inviteGuest(const std::string& firstName, const std::string& lastName, const GuestType& value)
{
    //check if guest is already on the list
    Node* p = m_head;
    while (p != nullptr) { //Go through the linked list to see if there are any exact matches if there is return false
        if (p->lastName == lastName && p->firstName == firstName) {
            return false;
        }
        p = p->next;
    }

    if (m_head == nullptr) { //If the list is empty set the new node to head and tail and set the name and value for the new node
        m_head = new Node;
        m_head->value = value;
        m_head->firstName = firstName;
        m_head->lastName = lastName;
        m_head->next = nullptr;
        m_head->prev = nullptr;
        m_tail = m_head;
        m_size++;
    }

    else if (lastName <= m_head -> lastName) { //When the last name is less or equal to the head's last name
        if (lastName == m_head->lastName) { //If last name is equal to head's last name there are two cases to consider one where the first name alphabetically comes before head's firstname and when it is after
            if (firstName <= m_head->firstName) { //first name is less or equal to head's first name set it as the new head
                Node* temp = new Node;
                temp->value = value;
                temp->firstName = firstName;
                temp->lastName = lastName;
                temp->next = m_head;
                m_head->prev = temp;
                m_head = temp;
                m_size++;
            }
            else { //first name input is greater than head's first name
                Node* p = m_head;
                while (p->next != nullptr && p->next->lastName == lastName && p->next->firstName < firstName) { //To find the right name spot, loop while last name is equal, next node's first name is less than firstname input
                    p = p->next;
                }
                //We found the right place
                Node* temp = new Node; //Create a new node and place in the right name and value
                temp->value = value; 
                temp->firstName = firstName;
                temp->lastName = lastName;
                temp->next = p->next; //Set the new node's next node to current node's next node
                temp->prev = p; //set the new node's prev node to current node 
                p->next = temp; //Set current pointer's next node to new node
                if (temp->next != nullptr) { //If the new node's next node is not a null pointer
                    temp->next->prev = temp; //set the new node's next node's previous to new node
                }
                else {
                    m_tail = temp; //because its a nullptr we set tail to the new node
                }
                m_size++; //increment size by one since we added a new node
            
            } 
        }
        else { //means lastname < head's last name so we set this guest to the head
            Node* temp = new Node; 
            temp->value = value;
            temp->firstName = firstName;
            temp->lastName = lastName;
            temp->next = m_head;
            m_head->prev = temp;
            m_head = temp;
            m_size++;
        }
    }

    else { //The guest belongs somewhere in the middle or end of the linked list
        Node* p = m_head;
        while (p->next != nullptr && p->next->lastName <= lastName) { //Loop until current node's next node is not nullptr and the next node's last name is less than lastname input
            if (p->next->lastName == lastName && p->next->firstName >= firstName) {
                break;
            }
            p = p->next;
        }
        if (p->next == nullptr) { //The name belongs at the end of the list and set it as the tail node
            m_tail = new Node;
            m_tail->value = value;
            m_tail->firstName = firstName;
            m_tail->lastName = lastName;
            m_tail->next = nullptr;
            p->next = m_tail;
            m_tail->prev = p;
            m_size++;
        }

        else { //The name belongs somewhere in the middle of the list
            Node* temp = new Node;
            temp->value = value;
            temp->firstName = firstName;
            temp->lastName = lastName;
            temp->next = p->next;
            temp->prev = p;
            p->next = temp;
            temp->next->prev = temp;
            m_size++;
        }
    }
    return true;
}

bool WeddingGuest::alterGuest(const std::string& firstName, const std::string& lastName, const GuestType & value)
{
    Node *p = m_head;
    while (p != nullptr) {
        if (p->lastName == lastName && p->firstName == firstName) { //Loop until we find the exact match name
            p->value = value; //change the value since it is a match
            return true;
        }
        p = p->next;
    }
    return false;
}

bool WeddingGuest::inviteOrAlter(const std::string& firstName, const std::string& lastName, const GuestType& value)
{
    if (invitedToTheWedding(firstName, lastName)) {
        return alterGuest(firstName, lastName, value); //Since the guest is already invited we alter
    }
    else {
        return inviteGuest(firstName, lastName, value); //Since the guest is not invited we invite the guest
    }
}

bool WeddingGuest::crossGuestOff(const std::string& firstName, const std::string& lastName)
{
    Node* p = m_head;
    while (p != nullptr) {
        if (p->lastName == lastName && p->firstName == firstName) { //Break when current node has the same full name as the input
            break;
        }
        p = p->next;
    }
    if (p == nullptr) { //At this point we haven't found a match so we return false
        return false;
    }
    else {
        if (p == m_head) { //If the match node is the head node
            m_head = p->next; //Set the head node to the next node
            if (m_head != nullptr) { //If the list is not empty
                m_head->prev = nullptr; //Set the head node's previous to nullptr
            }
            else { //If the list is empty
                m_tail = nullptr; //Set the tail node to nullptr
            }
        }
        else if (p == m_tail) { //If the match node was a tail node
            m_tail = p->prev; //Set the tail node to the previous node
            m_tail->next = nullptr; //Set the previous node's next node to nullptr
        }
        else {
            p->prev->next = p->next; //Set the previous node's next node to the next node
            p->next->prev = p->prev; //Set the next node's previous node to the previous node
        }
        delete p; //Now cross off the guest name/match node
        m_size--; //decrement list size by 1
        return true; //since we did cross off we return true
    }
}

bool WeddingGuest::invitedToTheWedding(const std::string& firstName, const std::string& lastName) const
{
    Node* p = m_head;
    while (p != nullptr) {
        if (p->lastName == lastName && p->firstName == firstName) { //If there is an exact match for a name return true
            return true; 
        }
        p = p->next;
    }
    return false; //since we did not find a match at this point return false
}

bool WeddingGuest::matchInvitedGuest(const std::string& firstName, const std::string& lastName, GuestType& value) const
{
    Node* p = m_head;
    while (p != nullptr) {
        if (p->lastName == lastName && p->firstName == firstName) { //If there is an exact match for a name 
            value = p->value; //change the value accordingly
            return true;
        }
        p = p->next;
    }
    return false; //since we did not find a match at this point return false
}

bool WeddingGuest::verifyGuestOnTheList(int i, std::string& firstName, std::string& lastName, GuestType & value) const
{
    if (i < 0 || i >= m_size) { //Check if the index is valid if it is less than 0 or greater or equal then the index is valid
        return false;
    }
    else {
        Node* p = m_head; //since it is a valid index we loop through the linked list and set the name and values accordingly
        for (int j = 0; j < i; j++) {
            p = p->next;
        }
        firstName = p->firstName; 
        lastName = p->lastName;
        value = p->value;
        return true;
    }
}

void WeddingGuest::swapWeddingGuests(WeddingGuest& other) { //Simply swap the head, tail pointer and change the size for each

    Node* temp = m_head; //Make a temp pointer to save current head
    m_head = other.m_head; //Swap the head pointers
    other.m_head = temp; 
    temp = m_tail; //Make the temp pointer to save current tail
    m_tail = other.m_tail; //Swap the tail pointer
    other.m_tail = temp;
    int tempSize = m_size; //Make a temp int variable to save current size
    m_size = other.m_size; //Swap the size variables
    other.m_size = tempSize;
}

bool joinGuests(const WeddingGuest & odOne, const WeddingGuest & odTwo, WeddingGuest & odJoined)
{
    string lastName;
    string firstName;
    GuestType value;
    GuestType value2; //This variable is here to save the value for comparison (for cases such as full name is equal but value is different)

    bool answer = true;

    //check for aliasing
    if (&odOne == &odTwo) {
        odJoined = odOne; //Make odJoined equal to odOne since odOne and odTwo joined would be a copy of odOne or odTwo
        return answer; //return true since there was no guest that appeared on both list but had different values
    }

    //Make an empty temp list that we will save our joined result to
    WeddingGuest temp;
 
    for (int i = 0; i < odOne.guestCount(); i++) {
        //Iterate through the odOne guest list
        odOne.verifyGuestOnTheList(i, firstName, lastName, value); //Get the first name, last name, and value of the guest at index i

        if (odTwo.matchInvitedGuest(firstName, lastName, value2)) { //If the guest is also on the odTwo list have the value that the person maps to saved to value2
            if (value != value2) {
                //If the guest is invited to the wedding with a different value
                answer = false;
            }
            else {
                //If the guest is invited to the wedding with the same value
                temp.inviteGuest(firstName, lastName, value); //Invite the guest to the wedding
            }
        }
        else {
            temp.inviteGuest(firstName, lastName, value); //If the guest is not on the odTwo list invite
        }
    }

    for (int i = 0; i < odTwo.guestCount(); i++) {
        //Iterate through the odTwo guest list
        odTwo.verifyGuestOnTheList(i, firstName, lastName, value); //Get the first name, last name, and value of the guest at index i

        if (odOne.matchInvitedGuest(firstName, lastName, value2)) { //If the guest is also on the odOne list have the value that the person maps to saved to value2
            if (value != value2) { 
                //If the guest is invited to the wedding with a different value
                answer = false;
            }
            else {
                //If the guest is invited to the wedding with the same value
                temp.inviteGuest(firstName, lastName, value); //Invite the guest to the wedding
            }
        }
        else {
            temp.inviteGuest(firstName, lastName, value); //If the guest is not on the odOne list invite
        }
    }

    odJoined = temp; //Set the odJoined list to the temp list
    return answer;
}

void attestGuests (const std::string& fsearch,
                   const std::string& lsearch,
                   const WeddingGuest& odOne,
                   WeddingGuest& odResult)
{
    string firstName;
    string lastName;
    GuestType value;

    //Make an empty temp list that we will save our search result to
    WeddingGuest temp;

    if ((fsearch == "*") && (lsearch == "*")) { //If both search strings are wildcards then temp is simply a copy of odOne
        temp = odOne;
    }

    for (int i = 0; i < odOne.guestCount(); i++) { //Iterate through the odOne guest list


        odOne.verifyGuestOnTheList(i, firstName, lastName, value); //Get the first name, last name, and value of the guest at each index

        if (firstName == fsearch && lastName == lsearch) { //If the first name and last name are equal to the search strings
            temp.inviteGuest(firstName, lastName, value); //Invite the guest
        }
        else if ((fsearch == "*") && (lastName == lsearch)) { //If the first name was a wildcard and the last name is equal to the search string
            temp.inviteGuest(firstName, lastName, value); //Invite that guest because the first name is a wildcard and last name matches
        } 
        else if ((lsearch == "*") && (firstName == fsearch)) { //If the last name was a wildcard and the first name is equal to the search string
            temp.inviteGuest(firstName, lastName, value); //Invite that guest because the last name is a wildcard and first name matches
        }
    }
    odResult = temp; //Set the odResult list to the temp list
}