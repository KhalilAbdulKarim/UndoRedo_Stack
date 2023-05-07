/*
 * created by Khalil Abdel Karim on 30/04/2023
 * This file contains the main program of the project
 */

#include "URStack.h"
#include <iostream>
#include <string>

using namespace std;

void displayMenu();

template<typename DataType>
void test(int selection, URStack<DataType> &stack);


int main() {
    int capacity;
    int option;

    cout << "\n Enter the capacity of the U/R Stack " << endl;
    // A capacity must be set
    cin >> capacity;

    if (capacity <= 0) {
        cout << "capacity is set to 20 ";
    }

    // create a stack with a capacity set by the user
    URStack<string> stack(capacity);

    displayMenu();
    cout << "\n======= Please Choose an option ======= " << endl;

    cin >> option;

    do {

        // if option is not right re-display menu
        if (option < 0 || option > 6) {

            displayMenu();

            cout << "\nPlease choose a number from the menu" << endl;

            cin >> option;

        } else {

            if (option > 0 && option <= 6) {

                // We cannot replace it with else because if the choice is 0, nothing should happens

                test(option, stack);

                displayMenu(); //redisplay the menu after each choice

                cout << "\nPlease choose a number from the menu" << endl;

                cin >> option;
            }
        }
    } while (option != 0);

    return 0;
}

// URStack Operations
void displayMenu() {

    cout << "\n Undo/Redo Stack Manipulation Menu";
    cout << "\n 1 - Insert a new Action. ";
    cout << "\n 2 - Undo. ";
    cout << "\n 3 - Redo. ";
    cout << "\n 4 - Display All Actions . ";
    cout << "\n 5 - Display Previous Actions. ";
    cout << "\n 6 - Display Next Actions. ";
    cout << "\n 0 - To exit\n";
}

// selection from the display menu is needed
template<typename DataType>
void test(int selection, URStack<DataType> &stack) {

    int capacity;
    string action;

    switch (selection) {
        // exit the program
        case 0:

            exit(0);
            break;

            // Inserts New Action to stack
        case 1:
            cout << "\nEnter an action to add to the stack: ";
            cin.ignore();
            getline(cin, action);
            stack.insertNewAction(action);
            cout << "\nAction added successfully!\n";

            break;


            // Undo function
        case 2:

            stack.undo();
            break;


            // Redo function
        case 3:

            stack.redo();
            break;


            // Display All Actions
        case 4:

            cout << "Display all actions : " << endl;
            stack.displayAll();

            break;


            // Display Previous Actions
        case 5:

            cout << "Display previous actions : " << endl;
            stack.displayPrevious();

            break;


            //  Display Next Actions
        case 6 :
            cout << "Display next actions : " << endl;
            stack.displayNext();

            break;

            // Default
        default:
            cout << "\n Invalid selection";
            break;

    }
}





