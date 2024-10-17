// ECCS 2681: Project #2 - Implanting Specific "Flavors" of a Tree / Map (Hash Map)
// Description: Implementing a hash map that inserts, deletes, and searches
// Authors: Sarah Tucker and Hailey Wendt
// Last Updated: 30 April 2023
// Sources for Code: ChatGPT

#include <iostream>
#include <cstring>

using namespace std;

// Maximum size of hash table
const int MAX_SIZE = 100;

// Define node structure for linked list
struct Node {
    // int value that serves as a key/identifier for this node
    int key;
    
    // int value that represents the data stored in this node
    int value;
    
    // a pointer to another Node struct, representing the next node in the linked list
    Node* next;
};

// Define hash table class
class HashMap {
private:
    // used to store the nodes in the hash table
    // [MAX_SIZE] determines the maximum size of the hash table
    Node* table[MAX_SIZE];

    // Hash function: takes an int key as input and returns index in table array where corresponding node should be stored
    int hash(int key) {
         // Calculates the mod of the key with MAX_SIZE
        return key % MAX_SIZE;
    } // end hash function

public:
    // Constructor: initializes table array with all elements set to NULL
    HashMap() {
        // sets a block of memory to a specified value
        memset(table, 0, sizeof(table));
    } // end constructor

    // Insert function: inserts a new node with passed values into hash table
    void insert(int key, int value) {
        // computing hash index
        int index = hash(key);
        
        // new node created
        Node* node = new Node();
        
        // key and value fields are set to the input values
        node->key = key;
        node->value = value;
        
        // next is set to NULL
        node->next = NULL;
        
        // checks to see if a node exists at the computed hash index
        if (table[index] == NULL) {
            // if NULL, the new node is assigned to table[index]
            table[index] = node;
        } // end if
        
        // collision has occurred, new node to be added to end of linked list node already present
        else {
            // temporary node for while loop
            Node* temp = table[index];
            
            // linked list is traversed by following next pointers until end of list is reached
            while (temp->next != NULL) {
                temp = temp->next;
            } // end while
            
            // new node is added to end of list by setting next of last node in list to point to new node
            temp->next = node;
        } // end else
    } // end insert function

    // Delete function: takes passed value and removes the node with this key from the hash table, if it exists
    void remove(int key) {
        // compute hash index for given key
        int index = hash(key);
        
        // temporary node for while loop
        Node* temp = table[index];
        
        // set prev node to NULL
        Node* prev = NULL;
        
        // linked list of nodes at this index are traversed
        // checks if current node's key matches input key
        // if not matched, sets prev to current node and moves to next node
        // if matched, loop exits
        while (temp != NULL && temp->key != key) {
            prev = temp;
            temp = temp->next;
        } // end while

        // indicates input key was not found in hash table, since while loop was exited and temp == NULL
        if (temp == NULL) {
            return;
        } // end if

        // node with input key is first node in linked list
        if (prev == NULL) {
            // table[index] is updated to point to next node in list
            table[index] = temp->next;
        } // end if
       
        // node with input key is not first node in list
        else {
            // next pointer of prev is updated to point to node after current node
            prev->next = temp->next;
        } // end else

        // current node is deleted
        delete temp;
    } // end delete function

    // Search function: takes passed value and returns int value associated with input key in hash table, if it exists
    int search(int key) {
        // compute the hash index for given key
        int index = hash(key);
        
        // temporary node for while loop
        Node* temp = table[index];

        // linked list of nodes at this index are traversed
        while (temp != NULL) {
            // checks if current node's key matches input key
            if (temp->key == key) {
                // returns value associated with key
                return temp->value;
            } //end if
           
            // if node with input is not found, loop continues by moving to next node
            temp = temp->next;
        } // end while
       
        // key not found in hash table
        return -1;
    } // end search function

    // Print function: traverses the hash table and prints out each key-value pairs stored in hash table in format (key, value)
    void print() {
        // prints each index number 
        for (int i = 0; i < MAX_SIZE; i++) {
            cout << i << ": ";
            
            // set to first node at current index
            Node* temp = table[i];
            
            // traverses the linked list of node at current index, continues until temp == NULL, indicating end of linked list
            while (temp != NULL) {
                // key-value pairs of each node are printed 
                cout << "(" << temp->key << ", " << temp->value << ") ";
                temp = temp->next;
            } // end while
            
            // newline character is printed
            cout << endl;
        } // end for
    } // end print function
}; // end of class

// Example usage
int main() {
    HashMap map;
    map.print(); // outputs a empty hash table
    map.insert(1, 10); // adding key-value pair to hash table
    map.insert(2, 20); // adding key-value pair to hash table
    map.insert(3, 30); // adding key-value pair to hash table
    map.print(); // outputs the hash table with the new key-value pairs
    /*
        Output:
        0:
        1: (1, 10)
        2: (2, 20)
        3: (3, 30)
        4:
        ...
    */
    map.remove(2); // removing the key-value pair with key of 2
    map.print(); // outputs updated hash table
    /*
        Output:
        0:
        1: (1, 10)
        2:
        3: (3, 30)
        4:
        ...
    */
    return 0;
}
