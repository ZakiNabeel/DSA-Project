#include <iostream>
#include <fstream>
#include "AVL.h"
#include "AVL_String.h"
using namespace std;

// Utility function to get string length
int getLen(char*& string) {
    int count = 0;
    while (string[count] != '\0') {
        count++;
    }
    return count + 1; // Include space for null terminator
}

class FileSystem {
    char* fileName;
    AVLString** avl_S;
    int numAvl;
    AVL<int>* avlInt;
    AVL<float>* avlFloat;
    int numberColumns;
    char** columns;

public:
    FileSystem(char* f = nullptr) {
        fileName = new char[30]();
        avl_S = nullptr;
        numAvl = 0;
        avlInt = nullptr;
        avlFloat = nullptr;
        numberColumns = 0;
        columns = nullptr;
    }


    void printColumns() {
        cout << "The columns in the file named " << fileName << " are: " << endl;
        for (int i = 0; i < numberColumns; i++) {
            cout << columns[i] << endl;
        }
    }

    void addColumn(char* message) {
        if (!columns) {
            columns = new char* [1];
            columns[0] = nullptr;
            copyString(columns[0], message);
        }
        else {
            char** temp = new char* [numberColumns + 1];
            for (int i = 0; i < numberColumns; i++) {
                temp[i] = columns[i];
            }
            temp[numberColumns] = nullptr;
            copyString(temp[numberColumns], message);

            delete[] columns; 
            columns = temp;
        }
        numberColumns++;
    }

    char**& getColumns() {
        return columns;
    }

    void setFileName(char* message) {
        copyString(fileName, message);
    }

    void getFileName() const {
        cout << "File Name: " << fileName << endl;
    }

    void setColumnsNumber(int c) {
        numberColumns = c;
    }

    int getColumnsNumber() {
        return numberColumns;
    }

    ~FileSystem() {
        delete[] fileName;
        if (columns) {
            for (int i = 0; i < numberColumns; i++) {
                delete[] columns[i];
            }
            delete[] columns;
        }
    }

    bool correctSelection(char*& message) {
        for (int i = 0; i < getColumnsNumber(); i++) {
            if (strcmp(columns[i], message) == 0) {
                cout << "Column " << columns[i]<< " has been selected! " << endl;
                return 1;

            }
        }
        return 0;
    }

    int obtainColumnIndex(char*& message) {
        for (int i = 0; i < getColumnsNumber(); i++) {
            if (strcmp(columns[i], message) == 0) {
                return i;

            }
        }
    }


    //Initializing AVL Trees
    void initializeAVL_Int() {
        avlInt = new AVL<int>();
    }

    void initialize_AVL_S() {
        if (!avl_S) {
            numAvl++;
            avl_S = new AVLString * [numAvl];
			avl_S[numAvl - 1] = new AVLString();

        }
        else {
            AVLString** temp = new AVLString * [numAvl + 1];
            for (int i = 0; i < numAvl; i++) {
                temp[i] = avl_S[i];
            }
            temp[numAvl] = new AVLString();
            delete[] avl_S;
            avl_S = temp;
            numAvl++;
        }

    }

    int getNumAVL() {
        return numAvl;
    }
    
    //Add data in AVL trees
    void addDataInAVL_Int(int d) {
        avlInt->insert(d);
    }

    void addDataInAVL_S(char* message) {
        avl_S[numAvl-1]->insert(message);
    }

    AVLString** getAVL() {
        return avl_S;
    }

};

// Reading CSV File
void readFile(char*& message, FileSystem*& fs, ifstream & csvFile) {
    csvFile.open(message);
    if (!csvFile.is_open()) {
        cout << "File not found" << endl;
        return;
    }
    cout << "File is found" << endl;

    // Tree selection
    bool selectionOfTree = false;
    char* type = new char[4];
    type[0] = '\0';
    while (!selectionOfTree) {
        cout << "Choose the tree type: (AVL, B, R&B)" << endl;
        cin.getline(type, 4);
        if (strcmp(type, "AVL") == 0 || strcmp(type, "B") == 0 || strcmp(type, "R&B") == 0) {
            selectionOfTree = true;
        }
        else {
            cout << "Invalid Tree Type" << endl;
        }
    }

    char* container = new char[1];
    container[0] = '\0';
    int tempCount = 1;
    char temp;

    // Reading columns
    //oNLY PROCESSING FRO THE COLUMN NAMES RIGHT NOW
    while (csvFile.get(temp)) {
        if (temp == '\n') {
            break; 
        }
        else if (temp == ',') {
            container[tempCount - 1] = '\0'; 
            fs->addColumn(container);

            tempCount = 1;
            delete[] container;
            container = new char[tempCount];
            container[0] = '\0';
        }
        else {
            char* tempContainer = new char[tempCount + 1];
            for (int i = 0; i < tempCount; i++) {
                tempContainer[i] = container[i];
            }
            delete[] container;

            tempContainer[tempCount - 1] = temp;
            tempContainer[tempCount] = '\0'; 
            container = tempContainer;
            tempCount++;
        }
    }

    // Final column
    if (tempCount > 1) {
        container[tempCount - 1] = '\0';
        fs->addColumn(container);
    }

    delete[] container;
    delete[] type;
}

////isInteger
//bool integerDetection(char * & message) {
//    int i = 0;
//    while (message[i] != '\0') {
//        if ((message[i] >= 65 && message[i] <= 90) || (message[i] >= 97 && message[i] <= 122) || message[i]=='.') {
//            return 0;
//        }
//        i++;
//    }
//    return 1;
//}
//
////isCharacterArray
//bool charArrayDetection(char*& message) {
//    int i = 0;
//    while (message[i] != '\0') {
//        if ((message[i] >= 65 && message[i] <= 90) || (message[i] >= 97 && message[i] <= 122)) {
//            return 1;
//        }
//        i++;
//    }
//    return 0;
//}
//
////Float Detctetion
//bool floatDetection(char*& message) {
//    int i = 0;
//    bool pointDetected = 0;
//    while (message[i] != '\0') {
//        if ((message[i] >= 65 && message[i] <= 90) || (message[i] >= 97 && message[i] <= 122)) {
//            return 0;
//        }
//        else if (message[i] == '.') {
//            pointDetected = 1;
//        }
//        i++;
//    }
//    return (1*pointDetected);
//}
//
////Date Detection
//bool dateDetection(char*& message) {
//	int i = 0;
//	int count = 0;
//	while (message[i] != '\0') {
//		if (message[i] == '/' || message[i]=='-') {
//			count++;
//		}
//		i++;
//	}
//	return (count == 2);
//}


void AvlTreeMaking(FileSystem*& fs, ifstream& csvFile, int index) {
    fs->initialize_AVL_S();

    int currLine = 0;
    int currIndex = 0;

    // Temporary variables
    char* container = new char[1];
    container[0] = '\0';
    int tempCount = 1;
    char temp;

    while (csvFile.get(temp)) {
        if (temp == '\n') {
            if (currLine > 0 && currIndex == index) {
                fs->addDataInAVL_S(container);
               // cout << "Added to tree: " << container << endl;
            }
            currLine++;
            currIndex = 0;
            tempCount = 1;
            delete[] container;
            container = new char[1];
            container[0] = '\0';
        }
        else if (temp == ',') {
            if (currLine > 0 && currIndex == index) {
                fs->addDataInAVL_S(container);
                //cout << "Added to tree: " << container << endl;
            }
            currIndex++;
            tempCount = 1;
            delete[] container;
            container = new char[1];
            container[0] = '\0';
        }
        else if (currLine > 0 && currIndex == index) {
            char* tempContainer = new char[tempCount + 1];
            for (int i = 0; i < tempCount - 1; i++) {
                tempContainer[i] = container[i];
            }
            tempContainer[tempCount - 1] = temp;
            tempContainer[tempCount] = '\0';
            delete[] container;
            container = tempContainer;
            tempCount++;
        }
    }

    // Handle the final case (last line or EOF without newline)
    if (currIndex == index) {
        fs->addDataInAVL_S(container);
        cout << "Added to tree: " << container << endl;
    }
    
}





//Tree Maker
void makeTree(FileSystem * & fs, char * & selectionColumn, ifstream & csvFile) {

    int index = fs->obtainColumnIndex(selectionColumn);
    cout << "Selected column index: " << index << endl;

    csvFile.seekg(0, ios::beg); 

    AvlTreeMaking(fs, csvFile, index);
    
    cout << "-----" << endl;
    fs->getAVL()[fs->getNumAVL()-1]->preorderTraversal();

    //int tempRow = 0;
    //char tempChar;
    //char* container = new char[1];
    //container[0] = '\0';
    //int tempCount = 1;

    //int currIndex = 0;

    ////This loop identifies the type of data present in the column
    //while (tempRow < 2) {
    //    while (csvFile.get(tempChar)) {
    //        if (tempChar == '\n')tempRow++;
    //        if (tempRow >= 2) break;
    //        else if (tempRow == 1) {
    //            if (tempChar == ',') {
    //                currIndex++;
    //            }
    //            if (currIndex == index) {
    //                char* tempContainer = new char[tempCount + 1];
    //                for (int i = 0; i < tempCount; i++) {
    //                    tempContainer[i] = container[i];
    //                }
    //                delete[] container;

    //                tempContainer[tempCount - 1] = tempChar;
    //                tempContainer[tempCount] = '\0';
    //                container = tempContainer;
    //                tempCount++;
    //            }
    //        }
    //    }
    //}

    //currIndex = 0;

    //bool isInteger = integerDetection(container);
    //bool isCharArray = charArrayDetection(container);
    //bool isDate = dateDetection(container);
    //bool isFloat = floatDetection(container);

    //if (isInteger) {
    //    cout << "Is integer" << endl;
    //    fs->initializeAVL_Int();
    //    AvlIntTreeMaking(fs, csvFile, index);
    //}
    //else if (isCharArray) {
    //    cout << "Is char arra" << endl;

    //}
    //else if (isDate) {
    //    cout << "Is date" << endl;

    //}
    //else {
    //    cout << "Is float" << endl;
    //}

}

// Init operation
void init(char*& message, FileSystem*& fs, ifstream & csvFile) {
    fs->setFileName(message);
    fs->getFileName();
    readFile(message, fs, csvFile);
    fs->printColumns();
    cout << "Choose any Column : " << endl;
    char* selectionColumn = new char[30];
    
    bool selection = 0;
    while (!selection) {
        cin.getline(selectionColumn, 30);
        selection = fs->correctSelection(selectionColumn);
    }

    makeTree(fs, selectionColumn, csvFile);
}

int main() {
    FileSystem* fs = new FileSystem();
    ifstream csvFile;
    while (true) {
        char* command = new char[30]();
        cout << "Enter command: ";
        cin.getline(command, 30);

        char* commandExtract = new char[15]();
        int i = 0;
        while ((command[i] != ' ') && (command[i] != '\0')) {
            commandExtract[i] = command[i];
            i++;
        }
        commandExtract[i] = '\0';
        i++;

        char* message = new char[25]();
        int j = 0;
        while (command[i] != '\0') {
            message[j] = command[i];
            i++;
            j++;
        }
        message[j] = '\0';

        if (strcmp(commandExtract, "init") == 0) {
            init(message, fs, csvFile);
        }
        else {
            cout << "Invalid Command" << endl;
        }

        delete[] command;
        delete[] commandExtract;
        delete[] message;
    }

    delete fs;
    return 0;
}
