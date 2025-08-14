#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
using namespace std;

// 动态队列模板
template<class T>
class queue {
private:
    T* elements;
    int capacity;
    int frontIndex;
    int rearIndex;

    void resize() {
        int newCapacity = capacity * 2;
        T* newElements = new T[newCapacity];
        
        int j = 0;
        for (int i = frontIndex; i != rearIndex; i = (i + 1) % capacity) {
            newElements[j++] = elements[i];
        }
        newElements[j] = elements[rearIndex];

        delete[] elements;
        elements = newElements;
        capacity = newCapacity;
        frontIndex = 0;
        rearIndex = j;
    }

public:
    queue(int initialCapacity = 10) 
        : capacity(initialCapacity), frontIndex(0), rearIndex(-1) {
        elements = new T[capacity];
    }

    ~queue() { delete[] elements; }

    bool empty() const { return rearIndex == -1; }

    void push(const T& val) {
        if (size() == capacity - 1) resize();
        rearIndex = (rearIndex + 1) % capacity;
        elements[rearIndex] = val;
        if (frontIndex == -1) frontIndex = 0;
    }

    void pop() {
        if (empty()) return;
        if (frontIndex == rearIndex) {
            frontIndex = 0;
            rearIndex = -1;
        } else {
            frontIndex = (frontIndex + 1) % capacity;
        }
    }

    T& front() {
        if (empty()) throw runtime_error("Queue is empty");
        return elements[frontIndex];
    }

    int size() const {
        if (empty()) return 0;
        return (rearIndex >= frontIndex) ? 
            rearIndex - frontIndex + 1 : 
            capacity - frontIndex + rearIndex + 1;
    }
};

// 动态栈模板
template<class T>
class stack {
private:
    T* elements;
    int capacity;
    int topIndex;

    void resize() {
        capacity *= 2;
        T* newElements = new T[capacity];
        for (int i = 0; i <= topIndex; ++i) {
            newElements[i] = elements[i];
        }
        delete[] elements;
        elements = newElements;
    }

public:
    stack(int initialCapacity = 10) 
        : capacity(initialCapacity), topIndex(-1) {
        elements = new T[capacity];
    }

    ~stack() { delete[] elements; }

    void push(const T& val) {
        if (topIndex + 1 >= capacity) resize();
        elements[++topIndex] = val;
    }

    void pop() {
        if (!empty()) --topIndex;
    }

    T& top() {
        if (empty()) throw runtime_error("Stack is empty");
        return elements[topIndex];
    }

    bool empty() const { return topIndex == -1; }

    int size() const { return topIndex + 1; }
};

struct node {
    node* parent;
    node* leftchild;
    node* brother;
    int filetype; // 1:目录 0:文件
    string filename;

    node(node* p = nullptr, node* left = nullptr, node* bro = nullptr, 
         int type = 1, string name = "")
        : parent(p), leftchild(left), brother(bro), 
          filetype(type), filename(name) {}
};

class catalogtree {
private:
    node* root;
    node* cur;

    string getPath(node* n) {
        stack<string> pathStack;
        while (n != root) {
            pathStack.push(n->filename);
            n = n->parent;
        }

        string path = "/";
        while (!pathStack.empty()) {
            path += pathStack.top() + "/";
            pathStack.pop();
        }
        if (path.length() > 1) path.pop_back(); // 移除末尾斜杠
        return path;
    }

public:
    catalogtree() : root(new node()), cur(root) {
        root->filename = "";
        root->filetype = 1;
    }

    ~catalogtree() { clear(root); }

    void clear(node* n) {
        if (!n) return;
        clear(n->leftchild);
        clear(n->brother);
        delete n;
    }

    queue<string> splitPath(const string& path) {
        queue<string> parts;
        if (path.empty()) return parts;

        size_t start = 0, end = 0;
        if (path[0] == '/') {
            parts.push("");
            start = 1;
        }

        while ((end = path.find('/', start)) != string::npos) {
            if (end != start) {
                parts.push(path.substr(start, end - start));
            }
            start = end + 1;
        }

        if (start < path.size()) {
            parts.push(path.substr(start));
        }

        return parts;
    }

    node* navigate(queue<string>& parts) {
        node* current = parts.empty() ? cur : root;
        if (parts.front() == "") {
            current = root;
            parts.pop();
        }

        while (!parts.empty()) {
            string part = parts.front();
            parts.pop();

            if (current->filetype != 1) return nullptr;
            node* child = current->leftchild;
            while (child && child->filename != part) {
                child = child->brother;
            }
            if (!child) return nullptr;
            current = child;
        }
        return current;
    }

    void dir() {
        if (cur->filetype != 1) {
            cout << "Not a directory" << endl;
            return;
        }

        node* child = cur->leftchild;
        while (child) {
            cout << child->filename << (child->filetype ? "/" : "") << endl;
            child = child->brother;
        }
    }

    void cd(const string& path) {
        if (path == "..") {
            if (cur != root) cur = cur->parent;
            return;
        }

        queue<string> parts = splitPath(path);
        node* target = navigate(parts);
        if (target && target->filetype == 1) {
            cur = target;
        } else {
            cout << "Invalid path" << endl;
        }
    }

    bool mkdir(const string& name) {
        if (cur->filetype != 1) return false;

        // 检查重名
        node* child = cur->leftchild;
        while (child) {
            if (child->filename == name) return false;
            child = child->brother;
        }

        // 插入到链表末尾
        node** pp = &(cur->leftchild);
        while (*pp) pp = &((*pp)->brother);
        *pp = new node(cur, nullptr, nullptr, 1, name);
        return true;
    }

    void save(const string& filename) {
        ofstream file(filename);
        stack<node*> s;
        s.push(root);

        while (!s.empty()) {
            node* n = s.top();
            s.pop();

            if (n != root) {
                file << getPath(n) << " " << (n->filetype ? "dir" : "file") << "\n";
            }

            // 反向压栈保持顺序
            stack<node*> temp;
            node* child = n->leftchild;
            while (child) {
                temp.push(child);
                child = child->brother;
            }
            while (!temp.empty()) {
                s.push(temp.top());
                temp.pop();
            }
        }
    }

    void load(const string& filename) {
        ifstream file(filename);
        clear(root);
        root = new node();
        cur = root;

        string line;
        while (getline(file, line)) {
            size_t splitPos = line.find(' ');
            string path = line.substr(0, splitPos);
            string typeStr = line.substr(splitPos + 1);

            queue<string> parts = splitPath(path);
            if (parts.empty()) continue;

            node* parent = root;
            while (!parts.empty()) {
                string part = parts.front();
                parts.pop();

                node** childPtr = &(parent->leftchild);
                while (*childPtr && (*childPtr)->filename != part) {
                    childPtr = &((*childPtr)->brother);
                }

                if (!*childPtr) {
                    *childPtr = new node(parent, nullptr, nullptr, 
                                      (parts.empty() && typeStr == "dir") ? 1 : 0, 
                                      part);
                }
                parent = *childPtr;
            }
        }
    }
};

int main() {
    catalogtree fs;
    string cmd;

    while (true) {
        cout << "> ";
        getline(cin, cmd);

        queue<string> tokens;
        istringstream iss(cmd);
        string token;
        while (iss >> token) tokens.push(token);
        if (tokens.empty()) continue;

        string action = tokens.front();
        tokens.pop();

        if (action == "exit") break;
        else if (action == "dir") fs.dir();
        else if (action == "cd") fs.cd(tokens.empty() ? "" : tokens.front());
        else if (action == "mkdir") fs.mkdir(tokens.front());
        else if (action == "save") fs.save(tokens.front());
        else if (action == "load") fs.load(tokens.front());
        else cout << "Unknown command" << endl;
    }
}