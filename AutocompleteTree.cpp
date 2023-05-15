#include <iostream>
#include <string>
#include <queue>

struct Node {
    Node(std::string k, Node* p = nullptr) : key(k), parent(p) {
        leftChild = nullptr;
        rightChild = nullptr;
    };

    ~Node() {
        if (leftChild != nullptr) delete leftChild;
        if (rightChild != nullptr) delete rightChild;
    }

    Node* parent;
    Node* leftChild;
    Node* rightChild;

    std::string key;
};

class AutoCompleteTree {
public:
    AutoCompleteTree() {
        _root = nullptr;
    }

    ~AutoCompleteTree() {
        if (_root != nullptr) delete _root;
    }

    const Node* FindElement(const std::string key);
    void AddWord(std::string _word);
private:
    Node* _root;
};

//алгоритм поиска по дереву:
const Node* AutoCompleteTree::FindElement(const std::string key)
{
    if (_root == nullptr)
        return nullptr;
    // Создаем пустую очередь для добавления узлов с одинакового уровня -
    // имеющие одинаковую высоту
    std::queue<Node*> q;
    // кладем корень в очередь
    q.push(_root);
    while (q.empty() == false)
    {
        Node* node = q.front();
        q.pop();

        if (node->key == key)
            return node;

        if (node->leftChild != nullptr)
            q.push(node->leftChild);
        if (node->rightChild != nullptr)
            q.push(node->rightChild);
    }
}

void AutoCompleteTree::AddWord(std::string _word) {
    if (_root == nullptr) {
        _root = new Node(_word);
    }
    else {
        Node* current = _root;
        Node* newNode = nullptr;
        while (newNode == nullptr) {
            if (current->key >= _word) {
                // если элемент меньше текущего, идем влево
                if (current->leftChild != nullptr) {
                    current = current->leftChild;
                    continue;
                }
                // если левого узла нет, то нашли место для нового элемента
                newNode = new Node(_word, current);
                current->leftChild = newNode;
            }
            else {
                // если элемент меньше текущего, идем вправо
                if (current->rightChild != nullptr) {
                    current = current->rightChild;
                    continue;
                }
                // если правого узла нет, то нашли место для нового элемента
                newNode = new Node(_word, current);
                current->rightChild = newNode;
            }
        }
    }
}

int main()
{
    //создадим словарь... слов :)
    AutoCompleteTree act;
    act.AddWord("abstraction");
    act.AddWord("incapsulation");
    act.AddWord("inheritage");
    act.AddWord("queue");
    act.AddWord("unicode");
    act.AddWord("lvalue");
    act.AddWord("rvalue");
    act.AddWord("void");
    act.AddWord("unique_ptr");
    act.AddWord("linux");

    std::cout << "Hello World!\n";
}