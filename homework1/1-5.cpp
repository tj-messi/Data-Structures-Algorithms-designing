#include <cstdlib>  
#include <iostream>  
#include <string>  
#include <cstdio>  
#include <limits>  
#define MAX_LIST_LENGTH 1000000 
#define INITIAL_LIST_SIZE 1000  
#define LIST_INCREMENT 100       
#define ElemType int  
#define SAFE_CIN(x) cin >> x    
  
using namespace std;  
  
 
struct Pupil {  
    int serialNum;  
    string identifier;  
    string fullName;  
};  
   
struct SequentialList {  
    ElemType* elements;          
    int currentLength;         
    int allocatedSize;           
    Pupil students[100001];     
};  
  
  
bool InitializeList(SequentialList& list) {  
    list.elements = (int*)malloc(INITIAL_LIST_SIZE * sizeof(int));  
    list.currentLength = 0;  
    list.allocatedSize = INITIAL_LIST_SIZE;  
    return true;  
}  
  
 
void InputToList(SequentialList& list, int numStudents) {  
    for (int i = 1; i <= numStudents; ++i) {  
        list.currentLength++;  
        list.students[i].serialNum = i;  
        SAFE_CIN(list.students[i].identifier);  
        SAFE_CIN(list.students[i].fullName);  
    }  
}  
   
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
            
        for (int i = 1; i <= list.currentLength; ++i) {  
            list.students[i].serialNum = i;  
        }  
    }  
}  
  

void DeleteFromList(SequentialList& list, int position) {  
    if (position < 1 || position > list.currentLength) {  
        cout << "-1" << endl;  
    } else {  
        for (int i = position; i < list.currentLength; ++i) {  
            list.students[i] = list.students[i + 1];  
        }  
          
        list.currentLength--;  
        cout << "0" << endl;  
          
        
        for (int i = 1; i <= list.currentLength; ++i) {  
            list.students[i].serialNum = i;  
        }  
    }  
}  
  

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