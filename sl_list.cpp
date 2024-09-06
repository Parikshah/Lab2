#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "s_node.hh"

using namespace std;

template<typename T>
class SL_List {
public:
    SL_List() { head = nullptr; numNodes = 0; }

    // Required functions
    void insertHead(T value);
    void deleteHead();
    void insertAt(T value, int index);
    void deleteAt(int index);
    void printSize();
    void printValue(int index);
    void printAllValues();
    void printFrequency(T value);
    void printIndex(T value);

private:
    S_Node<T>* head;
    int numNodes;
};

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

template<typename T>
void SL_List<T>::insertHead(T value) {
    S_Node<T>* newNode = new S_Node<T>(value, head);
    head = newNode;
    numNodes++;
}

template<typename T>
void SL_List<T>::deleteHead() {
    if (head != nullptr) {
        S_Node<T>* temp = head;
        head = head->getNext();
        delete temp;
        numNodes--;
    }
}

template<typename T>
void SL_List<T>::insertAt(T value, int index) {
    if (index < 0 || index > numNodes) {
        return; // invalid index
    }
    if (index == 0) {
        insertHead(value);
        return;
    }
    S_Node<T>* current = head;
    for (int i = 0; i < index - 1; i++) {
        current = current->getNext();
    }
    S_Node<T>* newNode = new S_Node<T>(value, current->getNext());
    current->setNext(newNode);
    numNodes++;
}

template<typename T>
void SL_List<T>::deleteAt(int index) {
    if (index < 0 || index >= numNodes) {
        return; // invalid index
    }
    if (index == 0) {
        deleteHead();
        return;
    }
    S_Node<T>* current = head;
    for (int i = 0; i < index - 1; i++) {
        current = current->getNext();
    }
    S_Node<T>* temp = current->getNext();
    current->setNext(temp->getNext());
    delete temp;
    numNodes--;
}

template<typename T>
void SL_List<T>::printSize() {
    cout << numNodes << endl;
}

template<typename T>
void SL_List<T>::printValue(int index) {
    if (index < 0 || index >= numNodes) {
        cout << "ERROR" << endl;
        return;
    }
    S_Node<T>* current = head;
    for (int i = 0; i < index; i++) {
        current = current->getNext();
    }
    cout << current->getValue() << endl;
}

template<typename T>
void SL_List<T>::printAllValues() {
    S_Node<T>* current = head;
    while (current != nullptr) {
        cout << current->getValue() << endl;
        current = current->getNext();
    }
}

template<typename T>
void SL_List<T>::printFrequency(T value) {
    S_Node<T>* current = head;
    int frequency = 0;
    while (current != nullptr) {
        if (current->getValue() == value) {
            frequency++;
        }
        current = current->getNext();
    }
    cout << frequency << endl;
}

template<typename T>
void SL_List<T>::printIndex(T value) {
    S_Node<T>* current = head;
    int index = 0;
    while (current != nullptr) {
        if (current->getValue() == value) {
            cout << index << endl;
            return;
        }
        current = current->getNext();
        index++;
    }
    cout << "-1" << endl;
}

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

int main(int argc, char** argv) {
    SL_List<string> MyList;

    ifstream inStream;
    string line, word;

    if (argc < 2) {
        cout << "Please specify filename on command line\n";
        exit(1);
    }

    inStream.open(argv[1]);

    if (inStream.fail()) {
        cout << "Failed to open file\n";
        exit(1);
    }

    while (getline(inStream, line)) {
        vector<string> wordVec;
        stringstream ls(line);
        while (ls >> word) {
            wordVec.push_back(word);
        }

        // Command parsing logic
        if (wordVec.size() > 0) {
            string command = wordVec[0];

            if (command == "insertHead" && wordVec.size() == 2) {
                MyList.insertHead(wordVec[1]);
            } else if (command == "deleteHead" && wordVec.size() == 1) {
                MyList.deleteHead();
            } else if (command == "insertAt" && wordVec.size() == 3) {
                MyList.insertAt(wordVec[1], stoi(wordVec[2]));
            } else if (command == "deleteAt" && wordVec.size() == 2) {
                MyList.deleteAt(stoi(wordVec[1]));
            } else if (command == "printSize" && wordVec.size() == 1) {
                MyList.printSize();
            } else if (command == "printValue" && wordVec.size() == 2) {
                MyList.printValue(stoi(wordVec[1]));
            } else if (command == "printAllValues" && wordVec.size() == 1) {
                MyList.printAllValues();
            } else if (command == "printFrequency" && wordVec.size() == 2) {
                MyList.printFrequency(wordVec[1]);
            } else if (command == "printIndex" && wordVec.size() == 2) {
                MyList.printIndex(wordVec[1]);
            }
        }
    }

    inStream.close();
    return 1;
}
