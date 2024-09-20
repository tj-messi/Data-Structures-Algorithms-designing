#include <cstdlib>  
#include <iostream>  
#include <string>  
#include <cstdio>  
#include <limits>  
#define MAX_LIST_LENGTH 1000000 // Maximum size of the list  
#define INITIAL_LIST_SIZE 1000  // Initial size of the list  
#define LIST_INCREMENT 100      // Increment size for the list  
#define ElemType int  
#define SAFE_CIN(x) cin >> x    // Macro for safer cin usage (not actually needed here but can be useful)  
  
using namespace std;  
  
// Student information structure  
struct Pupil {  
    int serialNum;  
    string identifier;  
    string fullName;  
};  
  
// Define the structure of the sequential list  
struct SequentialList {  
    ElemType* elements;         // Pointer to the base address of the current list  
    int currentLength;          // Current length of the list  
    int allocatedSize;          // Allocated size of the list  
    Pupil students[100001];     // Array to store student information (note: this might be unnecessary if elements is used)  
};  
  
// Initialize the sequential list  
bool InitializeList(SequentialList& list) {  
    list.elements = (int*)malloc(INITIAL_LIST_SIZE * sizeof(int));  
    list.currentLength = 0;  
    list.allocatedSize = INITIAL_LIST_SIZE;  
    return true;  
}  
  
// Input content into the sequential list  
void InputToList(SequentialList& list, int numStudents) {  
    for (int i = 1; i <= numStudents; ++i) {  
        list.currentLength++;  
        list.students[i].serialNum = i;  
        SAFE_CIN(list.students[i].identifier);  
        SAFE_CIN(list.students[i].fullName);  
    }  
}  
  
// Insert an element into the sequential list at position i  
void InsertToList(SequentialList& list, int position) {  
    if (position < 1 || position > list.currentLength + 1) {  
        cout << "-1" << endl;  
    } else {  
        if (list.currentLength <= MAX_LIST_LENGTH) {  
            int* newSpace = (ElemType*)realloc(list.elements, (list.allocatedSize + LIST_INCREMENT) * sizeof(ElemType));  
            list.elements = newSpace;  
            list.allocatedSize += 1;  
        }  
          
        for (int i = list.currentLength; i >= position; --i) {  
            list.students[i + 1] = list.students[i];  
        }  
          
        list.currentLength++;  
        list.students[position].serialNum = position;  
        SAFE_CIN(list.students[position].identifier);  
        SAFE_CIN(list.students[position].fullName);  
          
        cout << "0" << endl;  
          
        // Update serial numbers  
        for (int i = 1; i <= list.currentLength; ++i) {  
            list.students[i].serialNum = i;  
        }  
    }  
}  
  
// Delete an element from the sequential list at position i  
void DeleteFromList(SequentialList& list, int position) {  
    if (position < 1 || position > list.currentLength) {  
        cout << "-1" << endl;  
    } else {  
        for (int i = position; i < list.currentLength; ++i) {  
            list.students[i] = list.students[i + 1];  
        }  
          
        list.currentLength--;  
        cout << "0" << endl;  
          
        // Update serial numbers  
        for (int i = 1; i <= list.currentLength; ++i) {  
            list.students[i].serialNum = i;  
        }  
    }  
}  
  
// Query student by ID  
void QueryByID(SequentialList& list, string query) {  
    bool found = false;  
    for (int i = 1; i <= list.currentLength; i++) {  
        if (list.students[i].identifier == query) {  
            cout << list.students[i].serialNum << " " << list.students[i].identifier << " " << list.students[i].fullName << endl;  
            found = true;  
            break;  
        }  
    }  
    if (!found) {  
        cout << "-1" << endl;  
    }  
}  
  
// Query student by name  
void QueryByName(SequentialList& list, string query) {  
    bool found = false;  
    for (int i = 1; i <= list.currentLength; i++) {  
        if (list.students[i].fullName == query) {  
            cout << list.students[i].serialNum << " " << list.students[i].identifier << " " << list.students[i].fullName << endl;  
            found = true;  
            break;  
        }  
    }  
    if (!found) {  
        cout << "-1" << endl;  
    }  
}  
  
int main() {  
    string command, subCommand, queryStr;  
    int position, numStudents;  
    SequentialList list;  
      
    InitializeList(list);  
      
    SAFE_CIN(numStudents);  
    InputToList(list, numStudents);  
      
    while (true) {  
        SAFE_CIN(command);  
        if (command == "insert") {  
            SAFE_CIN(position);  
            InsertToList(list, position);  
        } else if (command == "remove") {  
            SAFE_CIN(position);  
            DeleteFromList(list, position);  
        } else if (command == "check") {  
            SAFE_CIN(subCommand);  
            if (subCommand == "no") {  
                SAFE_CIN(queryStr);  
                QueryByID(list, queryStr);  
            } else if (subCommand == "name") {  
                SAFE_CIN(queryStr);  
                QueryByName(list, queryStr);  
            }  
        } else if (command == "end") {  
            cout << list.currentLength << endl;  
            break;  
        }  
    }  
      
    return 0;  
}