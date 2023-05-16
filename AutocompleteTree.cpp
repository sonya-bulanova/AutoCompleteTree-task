#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include <queue>

#define NO_OF_CHARS 256

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

    void AddWord(std::string _word);
    const Node* FindElement(std::string key);
private:
    //алгоритм поиска подстроки в строке
    bool FindSymbolInString(std::string strng, std::string symbol);
    void badCharHeuristic(std::string str, int size, int badchar[NO_OF_CHARS]);
    Node* _root;
};

//алгоритм поиска по дереву:
const Node* AutoCompleteTree::FindElement(std::string key)
{
    //чтобы не было зависимости от  регистра
    std::transform(key.begin(), key.end(), key.begin(), ::tolower);
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

        if (FindSymbolInString(node->key, key)){
          std::cout << "key: " << node->key << std::endl;
          //return node;
        }

        if (node->leftChild != nullptr)
            q.push(node->leftChild);
        if (node->rightChild != nullptr)
            q.push(node->rightChild);
    }
}

void AutoCompleteTree::AddWord(std::string _word) {
    std::transform(_word.begin(), _word.end(), _word.begin(), ::tolower);
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
    //std::cout << "Word: " << _word << std::endl;
}

void AutoCompleteTree::badCharHeuristic(std::string str, int size, int badchar[NO_OF_CHARS]){
    int i;
    for (i = 0; i < NO_OF_CHARS; i++)
        badchar[i] = -1;
    for (i = 0; i < size; i++)
        badchar[(int)str[i]] = i;
}

bool AutoCompleteTree::FindSymbolInString(std::string big_txt, std::string key_symb){
    int m = key_symb.size();
    int n = big_txt.size();

    int badchar[NO_OF_CHARS];

    badCharHeuristic(key_symb, m, badchar);

    int s = 0;
    while (s <= (n - m))
    {
        int j = m - 1;

        while (j >= 0 && key_symb[j] == big_txt[s + j])
            j--;

        if (j < 0)
        {
            //std::cout << "key_symbtern occurs at shift = " << s << std::endl;
            s += (s + m < n) ? m - badchar[big_txt[s + m]] : 1;
            return true;
        }
        else
        {
            int bc = badchar[big_txt[s + j]];
            s += std::max(1, j - bc);
        }
    }
    return false;
}

int main()
{
    //создадим словарь... слов :)
    AutoCompleteTree act;
    act.AddWord("aBstRactIon");
    act.AddWord("incapsulation");
    act.AddWord("inheritage");
    act.AddWord("queue");
    act.AddWord("unicode");
    act.AddWord("lVaLue");
    act.AddWord("rvalue");
    act.AddWord("VOID");
    act.AddWord("unique_ptr");
    act.AddWord("linux");
    act.AddWord("Geant4");
    act.AddWord("ROOT CERN")

    std::string key;
    //вводим по символу, нужно, чтобы метод искал сначала по первой букве, потом по двум...
    while(key != "quit"){ //пусть цикл эмулирует чат...
      //то есть, ввели букву l -- нам предложили "linux" или "lvalue" или "incapsulation" -- все, где есть l
      std::cin >> key;
      act.FindElement(key);
      //ввели символы value -- нам предложили lVaLue или rvalue
    }

    //std::cout << "Hello World!\n";
}
