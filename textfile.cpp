#include <iostream>
#include <fstream>
#include <string>

struct Node
{
  std::string line;
  Node *next;

  Node(const std::string &str) : line(str), next(nullptr) {}
};

class TextEditor
{
private:
  Node *head;
  Node *tail;

public:
  TextEditor() : head(nullptr), tail(nullptr) {}

  ~TextEditor()
  {
    Node *current = head;
    while (current != nullptr)
    {
      Node *next = current->next;
      delete current;
      current = next;
    }
  }

  void createNewFile(const std::string &filename)
  {
    clear();
    std::ofstream outFile(filename);
    if (!outFile)
    {
      std::cerr << "Error: Unable to create file!" << std::endl;
    }
    else
    {
      std::cout << "File created successfully." << std::endl;
      outFile.close();
    }
  }

  void loadFile(const std::string &filename)
  {
    std::ifstream file(filename);
    if (!file)
    {
      std::cerr << "Error opening file." << std::endl;
      return;
    }

    clear();
    std::string line;
    while (std::getline(file, line))
    {
      append(line);
    }
    file.close();
  }

  void saveFile(const std::string &filename)
  {
    std::ofstream file(filename);
    if (!file)
    {
      std::cerr << "Error opening file." << std::endl;
      return;
    }

    Node *current = head;
    while (current != nullptr)
    {
      file << current->line << std::endl;
      current = current->next;
    }
    file.close();
  }

  void append(const std::string &line)
  {
    Node *newNode = new Node(line);
    if (tail)
    {
      tail->next = newNode;
    }
    else
    {
      head = newNode;
    }
    tail = newNode;
  }

  void insert(int position, const std::string &line)
  {
    if (position < 0)
      return;

    Node *newNode = new Node(line);
    if (position == 0)
    {
      newNode->next = head;
      head = newNode;
      if (!tail)
      {
        tail = newNode;
      }
      return;
    }

    Node *current = head;
    for (int i = 0; current != nullptr && i < position - 1; ++i)
    {
      current = current->next;
    }
    if (current == nullptr)
      return;

    newNode->next = current->next;
    current->next = newNode;
    if (newNode->next == nullptr)
    {
      tail = newNode;
    }
  }

  void remove(int position)
  {
    if (position < 0 || head == nullptr)
      return;

    Node *toDelete = nullptr;
    if (position == 0)
    {
      toDelete = head;
      head = head->next;
      if (head == nullptr)
      {
        tail = nullptr;
      }
    }
    else
    {
      Node *current = head;
      for (int i = 0; current != nullptr && i < position - 1; ++i)
      {
        current = current->next;
      }
      if (current == nullptr || current->next == nullptr)
        return;

      toDelete = current->next;
      current->next = toDelete->next;
      if (toDelete->next == nullptr)
      {
        tail = current;
      }
    }
    delete toDelete;
  }

  void display() const
  {
    Node *current = head;
    int lineNumber = 1;
    while (current != nullptr)
    {
      std::cout << lineNumber++ << ": " << current->line << std::endl;
      current = current->next;
    }
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
};

int main()
{
  TextEditor editor;
  std::string filename = "";

  bool running = true;
  while (running)
  {
    std::cout << "------TEXT EDITOR------" << std::endl;
    std::cout << "1. Create New File" << std::endl;
    std::cout << "2. Open Newly Created File" << std::endl;
    std::cout << "3. Display text" << std::endl;
    std::cout << "4. Append line" << std::endl;
    std::cout << "5. Insert line" << std::endl;
    std::cout << "6. Remove line" << std::endl;
    std::cout << "7. Save and exit" << std::endl;
    std::cout << "8. Exit without saving" << std::endl;

    std::cout << "Enter your Choice" << std::endl
              << std::endl;
    int choice;
    std::cin >> choice;
    std::cin.ignore();

    switch (choice)
    {
    case 1:

    {
      std::cout << "Enter the filename you want to create" << std::endl;
      std::cin >> filename;
      filename += ".txt";
      editor.createNewFile(filename);
      editor.loadFile(filename);
    }

    case 2:
      std::cout << filename << std::endl;
      editor.loadFile(filename);
      break;

    case 3:
      editor.display();
      break;
    case 4:
    {
      std::cout << "Enter line to append: ";
      std::string line;
      std::getline(std::cin, line);
      editor.append(line);
      break;
    }
    case 5:
    {
      std::cout << "Enter position and line to insert: ";
      int position;
      std::string line;
      std::cin >> position;
      std::cin.ignore();
      std::getline(std::cin, line);
      editor.insert(position, line);
      break;
    }
    case 6:
    {
      std::cout << "Enter position to remove: ";
      int position;
      std::cin >> position;
      editor.remove(position);
      break;
    }
    case 7:
      editor.saveFile(filename);
      running = false;
      break;
    case 8:
      running = false;
      break;
    default:
      std::cout << "Invalid choice" << std::endl;
      break;
    }
  }

  return 0;
}
