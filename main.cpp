#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct Node {
  int data;
  Node* left;
  Node* right;
};

class BinarySearchTree {
private:
  Node* root;

  Node* createNode(int value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
  }

  Node* insert(Node* root, int value) {
    if (root == nullptr) {
      return createNode(value);
    }
    if (value < root->data) {
      root->left = insert(root->left, value);
    } else if (value > root->data) {
      root->right = insert(root->right, value);
    }
    return root;
  }

  Node* findMin(Node* node) {
    while (node->left != nullptr) {
      node = node->left;
    }
    return node;
  }

  Node* remove(Node* root, int value) {
    if (root == nullptr) {
      return root;
    }
    if (value < root->data) {
      root->left = remove(root->left, value);
    } else if (value > root->data) {
      root->right = remove(root->right, value);
    } else {
      if (root->left == nullptr) {
        Node* temp = root->right;
        delete root;
        return temp;
      } else if (root->right == nullptr) {
        Node* temp = root->left;
        delete root;
        return temp;
      }
      Node* temp = findMin(root->right);
      root->data = temp->data;
      root->right = remove(root->right, temp->data);
    }
    return root;
  }

  bool search(Node* root, int value) {
    if (root == nullptr) {
      return false;
    }
    if (root->data == value) {
      return true;
    }
    if (value < root->data) {
      return search(root->left, value);
    } else {
      return search(root->right, value);
    }
  }

  void printTree(Node* root, int depth = 0) {
    if (root == nullptr) {
      return;
    }
    printTree(root->right, depth + 1);
    for (int i = 0; i < depth; ++i) {
      cout << "\t";
    }
    cout << root->data << endl;
    printTree(root->left, depth + 1);
  }

public:
  BinarySearchTree() : root(nullptr) {}

  void insert(int value) {
    root = insert(root, value);
  }

  bool contains(int value) {
    return search(root, value);
  }

  void remove(int value) {
    root = remove(root, value);
  }

  void printTree() {
    cout << "Binary Search Tree:" << endl;
    printTree(root);
  }

  void addFromFile() {
    int numCount;
    cout << "Enter the number of numbers you want to add from file: ";
    cin >> numCount;
    ifstream file("nums.txt");
    int num;
    for (int i = 0; i < numCount && file >> num; ++i) {
      insert(num);
    }
    file.close();
  }

  void addNumbersManually() {
    int numCount;
    cout << "Enter the number of numbers you want to add manually: ";
    cin >> numCount;
    cout << "Enter " << numCount << " numbers separated by spaces: ";
    for (int i = 0; i < numCount; ++i) {
      int num;
      cin >> num;
      insert(num);
    }
  }

  void deleteNumber() {
    int value;
    cout << "Enter number to delete: ";
    cin >> value;
    remove(value);
  }

  void searchNumber() {
    int value;
    cout << "Enter number to search: ";
    cin >> value;
    if (search(root, value)) {
      cout << "Number " << value << " is found in the tree." << endl;
    } else {
      cout << "Number " << value << " is not found in the tree." << endl;
    }
  }
};

int main() {
  BinarySearchTree tree;
  int running = 1;
  char choice[3];

  while (running) {
    cout << "Select an option:" << endl;
    cout << "A: Add numbers manually" << endl;
    cout << "AF: Add numbers from file" << endl;
    cout << "P: Print tree" << endl;
    cout << "D: Delete number" << endl;
    cout << "S: Search for number" << endl;
    cout << "Q: Quit" << endl;
    cout << "Enter choice: " << endl;
    cin >> choice;

    if (strcmp(choice, "A") == 0) {
      tree.addNumbersManually();
    } else if (strcmp(choice, "AF") == 0) {
      tree.addFromFile();
    } else if (strcmp(choice, "P") == 0) {
      tree.printTree();
    } else if (strcmp(choice, "D") == 0) {
      tree.deleteNumber();
    } else if (strcmp(choice, "S") == 0) {
      tree.searchNumber();
    } else if (strcmp(choice, "Q") == 0) {
      running = 0;
    } else {
      cout << "Invalid choice. Please try again." << endl;
    }
  }

  return 0;
}
