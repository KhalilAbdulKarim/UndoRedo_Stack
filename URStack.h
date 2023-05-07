/*
* Created by Khalil Abdel Karim on 30/04/2023.
* URStack.h contains the declaration of class Undo/Redo Stack
*
* * * Basic Operations :
* Constructor for creating an empty URStack object with a given capacity or a default capacity of 20 if the capacity is
not specified.
* InsertNewAction : function that inserts a new action at the top of the stack
* undo: function that displays the current item pointed to by the current pointer and moves the pointer back
one position in the stack.
* redo: function that moves the current pointer forward one position in the stack and displays the item at the new
position, if there is one.
* displayAll : Display all the items in the URStack object from top to bottom
* displayPrevious : displays all the actions in the URStack starting from the current item and moving backward
in the URSTack.
* displayNext :displays all the actions in the URStack that are on top of the current item from bottom to top
----------------------------------------------------------------------------------------------------------------------*/

#ifndef URSTACK_H
#define URSTACK_H

#include <iostream>

using namespace std;

template<typename dataType>
class URStack {

private:

    template<typename nodeData>
    class Node {

    public :

        nodeData data;
        Node<nodeData> * next;

        Node(nodeData n) {
            data = n;
            next = nullptr;
        }

    };

    typedef Node<dataType> * NodePtr;
    //pointer o the top node of the stack
    NodePtr top;
    //pointer to the current node of the stack
    NodePtr current;
    // max number of actions allowed
    int capacity;
    // actual number of actions saved in the stack
    int size;

public:

    /**
    * Constructor for creating an empty URStack object with a given capacity specidied by the user.
    * @param capacity: integer representing the maximum number of actions allowed to be saved in the URStack
    * (default value is 20)
    * @pre None.
    * @post A new URStack object is created with the specified capacity .The top and current pointers
    * are initialized to NULL and size is set to 0.
    */

    URStack(int capacity = 20);

    /**
    * Insert a new item to the top of the URStack object according to specific rules.
    * @param item: the new item to be inserted.
    * @pre None.
    * @post If the URStack is empty, add the new item to the top of the URStack.
    * Otherwise, if current == top, add the new item to the top of the URStack, remove the least recent item if the
    * URStack is considered as full.
    * Otherwise, remove all items between current and top, and add the new item to the top of the URStack.
    * Every time a new item is added, the size of the URStack must be updated to the actual number of items in the
    * URStack and both the top and current pointers must be pointing to the most recently added item.
    */

    void insertNewAction(const dataType &);

    /**
    * Undo the current item of the URStack object and move the current pointer forward in the URStack.
    * @param None.
    * @pre None.
    * @post If the current pointer is not NULL, display the current item and move the current pointer forward.
    * Otherwise, do nothing.
    */

    void undo();

    /**
    * Redo the previous item of the URStack object and move the current pointer backward in the URStack.
    * @param None.
    * @pre None.
    * @post If the current pointer is not already pointing to the top of the URStack, move the current pointer backward
    * and display the new current item.
    * Otherwise, do nothing.
    */

    void redo();

    /**
    * Display all the items in the URStack object from top to bottom.
    * @param None.
    * @pre None.
    * @post Display all the items in the URStack object from top to bottom.
    */

    void displayAll();

    /**
    * Display all the items in the URStack object starting from the current item and moving backward in the URStack
    * (from top to bottom).
    * @param None.
    * @pre None.
    * @post Display all the items in the URStack object starting from the current item and moving backward in the
    * URStack (from top to bottom).
    */

    void displayPrevious();

    /**
    * Display all the items in the URStack object that are on top of the current item from bottom to top.
    * @param None.
    * @pre None.
    * @post Display all the items in the URStack object that are on top of the current item from bottom to top.
    */

    void displayNext();

};

// Implementation of the constructor
template<typename dataType>
URStack<dataType>::URStack(int capacity) {

    // if capacity not specified by the user , set 20 by default
    this->capacity = (capacity > 0) ? capacity : 20;
    size = 0;
    top = nullptr;
    current = nullptr;
}

// Implementation of Insert New Action Function

template<typename dataType>
void URStack<dataType>::insertNewAction(const dataType &item) {
    // top == NULL if the stack is empty
    if (top == NULL) {
        // create  a new node on the top
        top = new Node<dataType>(item);
        current = top;
        size++;
        return;
    }
    // size == capacity checks if the stack is full to remove the least element
    if (size == capacity) {
        //set a temp equal to top
        NodePtr temp = top;
        NodePtr tempPrev;

        // iterate until reaching temp
        while (temp->next != NULL) {

            tempPrev = temp;
            temp = temp->next;
        }

        delete temp;
        tempPrev->next = NULL;
        size--;
    }

    // checks if the current action is the top action to insert

    if (top == current) {

        NodePtr element = new Node<dataType>(item);

        element->next = top;
        top = element;
        current = top;
        size++;

        return;
    }


    // top action to delete the actions in between

    if (top != current) {

        NodePtr beforeDel;
        NodePtr del = top;
        NodePtr insert = new Node<dataType>(item);

        // iterate through the stack before reaching current
        while (del->next != current) {

            beforeDel = del;
            del = del->next;
            delete beforeDel;
        }

        top = insert;
        top->next = current;
        current = top;

        return;
    }
}

// Implementation of undo function
template<typename dataType>
void URStack<dataType>::undo() {

    if (current != NULL) {

        cout << "Undoing: " << current->data << "\n";
        current = current->next;
        size--;
        return;
    }
    // else
    cout << "Stack is Empty \n";
}

// Implementation of Redo function
template<typename DataType>
void URStack<DataType>::redo() {
    // Checking if stack is empty

    if (current != NULL) {

        // checks if the current action is the most recent

        if (current == top) {

            cout << "This is the current action: " << top->data << "\n";
            return;
        }

        // checks if the current is

        if (current != top) {

            NodePtr temp = top;

            while (temp->next != current) {

                temp = temp->next;
            }

            current = temp;

            cout << "Redoing: " << current->data << "\n";

            size++;

            return;
        }
    }

    // redoing from the last element

    if (current == NULL && top != NULL) {

        NodePtr temp = top;

        while (temp->next != NULL) {

            temp = temp->next;
        }

        current = temp;
        size++;
        cout << "Redoing: " << current->data << "\n";
        return;
    }

    // else

    cout << "Stack is Empty \n";
}

// Implementation of display previous actions

template<typename DataType>
void URStack<DataType>::displayPrevious() {
    // if empty
    if (current == NULL) {

        cout << "Stack is Empty \n";
        return;
    }

    if (current != NULL) {
        // set temp equal to current
        NodePtr temp = current;
        // iterating till reaching a null element
        while (temp != NULL) {
            // print data
            cout << temp->data;

            if (temp->next != NULL) {

                cout << ",";
            }
            temp = temp->next;
        }
        cout << "\n";
    }
}

// Implementation of display all actions function
template<typename DataType>
void URStack<DataType>::displayAll() {
    //if null
    if (top == nullptr) {

        cout << " Stack is empty " << endl;
    } else {
        // set temp equal to top
        NodePtr temp = top;

        // iterate till reaching a null element
        while (temp != nullptr) {
            // print data
            cout << temp->data;

            if (temp->next != nullptr) {

                cout << ",";
            }
            temp = temp->next;
        }
        // print an empty line
        cout << endl;
    }
}

// Implementation of Display Next function

template <typename dataType> void URStack <dataType> ::displayNext(){

    // Stack is empty

    if(current == NULL){

        cout << "List is empty \n";
        return;
    }

    // Only 1 element in the Stack

    if(current == top){

        cout << "This is the current action: " << top -> data << "\n";
        return;
    }

    // Array size print reverse

    int nextSize = 0;

    NodePtr temp = top;

    // calculating number of next elements

    while(temp != current){

        temp = temp -> next;
        nextSize++;
    }

    // dynamic array to print elements


    dataType *printArray = new dataType[nextSize];

    // re using the old temp pointer

    temp = top;

    // filling an array with the next elements

    for(int i = 0; i < nextSize; i++){

        printArray[i] = temp->data;
        temp = temp -> next;
    }

    // printing array in reverse

    for (int i = nextSize - 1; i >= 0; i--) {

        cout << printArray[i] << "\n";

        if (i >= 1) {
            cout << " , ";
        }
    }

    cout<< "\n";
}


#endif //URSTACK_H
