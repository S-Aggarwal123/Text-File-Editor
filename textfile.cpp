#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Node structure for linked list
struct Node
{
  string line;
  Node *next;

  Node(const string &data) : line(data), next(nullptr) {}
};

class TextEditor
{
private:
  Node *head;
  Node *tail;
  string filename;

public:
  TextEditor() : head(nullptr), tail(nullptr) {}
  ~TextEditor() { clear(); }

  void displayMenu()
  {
    cout << "===== Text File Editor =====" << endl;
    cout << "1. Create a new file" << endl;
    cout << "2. Open an existing file" << endl;
    cout << "3. Edit current file" << endl;
    cout << "4. Save current file" << endl;
    cout << "5. Close current file" << endl;
    cout << "6. Exit" << endl;
    cout << "=============================" << endl;
  }

  void createNewFile()
  {
    clear();
    filename = "";
    cout << "Enter filename to create: ";
    cin >> filename;
    ofstream outFile(filename);
    if (!outFile)
    {
      cerr << "Error: Unable to create file!" << endl;
    }
    else
    {
      cout << "File created successfully." << endl;
      outFile.close();
    }
  }

  void openFile()
  {
    clear();
    filename = "";
    cout << "Enter filename to open: ";
    cin >> filename;
    ifstream inFile(filename);
    if (!inFile)
    {
      cerr << "Error: Unable to open file!" << endl;
    }
    else
    {
      string line;
      while (getline(inFile, line))
      {
        append(line);
      }
      inFile.close();
      cout << "File opened successfully." << endl;
    }
  }

  void editFile()
  {
    if (head == nullptr)
    {
      cerr << "Error: No file is currently open!" << endl;
      return;
    }

    cout << "Enter line number to edit (1-" << countLines() << "): ";
    int lineNumber;
    cin >> lineNumber;

    if (lineNumber < 1 || lineNumber > countLines())
    {
      cerr << "Error: Invalid line number!" << endl;
      return;
    }

    cout << "Enter new text for line " << lineNumber << ": ";
    string newText;
    cin.ignore();
    getline(cin, newText);

    Node *current = head;
    int currentLine = 1;
    while (currentLine < lineNumber)
    {
      current = current->next;
      currentLine++;
    }

    current->line = newText;
    cout << "Line " << lineNumber << " edited successfully." << endl;
  }

  void saveFile()
  {
    if (head == nullptr)
    {
      cerr << "Error: No file is currently open!" << endl;
      return;
    }

    ofstream outFile(filename);
    if (!outFile)
    {
      cerr << "Error: Unable to save file!" << endl;
      return;
    }

    Node *current = head;
    while (current != nullptr)
    {
      outFile << current->line << endl;
      current = current->next;
    }

    outFile.close();
    cout << "File saved successfully." << endl;
  }

  void closeFile()
  {
    clear();
    filename = "";
    cout << "File closed." << endl;
  }

  void clear()
  {
    Node *current = head;
    while (current != nullptr)
    {
      Node *next = current->next;
      delete current;
      current = next;
    }
    head = nullptr;
    tail = nullptr;
  }

  void append(const string &line)
  {
    Node *newNode = new Node(line);
    if (head == nullptr)
    {
      head = newNode;
      tail = newNode;
    }
    else
    {
      tail->next = newNode;
      tail = newNode;
    }
  }

  int countLines()
  {
    int count = 0;
    Node *current = head;
    while (current != nullptr)
    {
      count++;
      current = current->next;
    }
    return count;
  }
};

int main()
{
  TextEditor editor;
  int choice;

  do
  {
    editor.displayMenu();
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
      editor.createNewFile();
      break;
    case 2:
      editor.openFile();
      break;
    case 3:
      editor.editFile();
      break;
    case 4:
      editor.saveFile();
      break;
    case 5:
      editor.closeFile();
      break;
    case 6:
      cout << "Exiting program." << endl;
      break;
    default:
      cout << "Invalid choice. Please enter a number between 1 and 6." << endl;
    }

    cout << endl;

  } while (choice != 6);

  return 0;
}
